<?php
require_once('curios_entities.inc');
require_once('curios_configuration.inc');

function curios_views_default_views() {
  $config = _curios_configuration();
  $views = array();
  $exports_path = drupal_get_path('module', 'curios') . '/views';
  $use_exports = FALSE;

  foreach ($config['rdf_views'] as $view_name=>$view_spec) {
    $view_file = $view_spec->getMachineName().'.view.inc';
    $view_path = $exports_path.'/'.$view_file;
    
    // If an exported view exists in /views/view_name.view.inc
    // then import that view.
    // Otherwise the default view is generated is generated from the view spec.
    if ($use_exports && file_exists($view_path)) {
      drupal_set_message($view_spec->getMachineName().': importing view from '.$view_file.'.');
      include_once $view_path;
      $views[$view_name] = $view;
    } else {
      drupal_set_message($view_spec->getMachineName().': generating default view.');
      $views[$view_name] = __curios_generate_default_view($view_spec);
    }
    
    // TODO generate update views from view spec.
  }
  
  return $views;
}

function __format_name($name) { return _curios_split_camel_case($name); }

function __curios_generate_default_view(&$view_spec) {
  $config = _curios_configuration();

  $view = new view;
  $view->name = $view_spec->getMachineName();
  $view->human_name = $view_spec->getLabel();
  $view->description = $view_spec->getLabel() .' ('. $view_spec->getMachineName() .')';
  $view->base_table = 'sparql_views_3605289727'; //_sparql_views_hash($endpoint); // TODO get real endpoint base table
  //$view->base_table = 'sparql_views_-689677569'
  $view->tag = 'CURIOS';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE;
  
  // Base fields: URI, dc:title, dc:description.
  $resource_name = $view_spec->getResource()->getMachineName();
  $base_fields = array(
    'title'       => $resource_name.'_dc_title', 
    'description' => $resource_name.'_dc_description');

  // CURIOS options
  $view->curios_options['resource_name'] = $resource_name; // Not used currently, config has mapping view_name => resource_name

  // Attachments for object fields.
  $object_fields = array();
  foreach ($view_spec->getObjectFields() as $field_id) {
    if ($field_id == 'hc_file')
      continue;
    
    $has_range = __curios_generate_object_block($view, $view_spec, $base_fields, $field_id);

    if (!$has_range)
      $object_fields[] = $field_id;
  }

  // Primary views.
  __curios_generate_view_master($view, $view_spec, $base_fields, $object_fields);
  __curios_generate_view_listing($view, $view_spec, $base_fields);
  __curios_generate_view_details($view, $view_spec, $base_fields, $object_fields);
  __curios_generate_view_images($view, $view_spec, $base_fields);

  return $view;
}

function __curios_generate_view_master(&$view, &$view_spec, $base_fields, array $object_fields = array()) {
  $config = _curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  //$handler->display->display_options['title'] = ''; // No title.
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  
  // No results behavior: Global: Text area.
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No results found.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;

  // Relationships.
  foreach ($view_spec->getObjectFields() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $handler->display->display_options['relationships'][$field_name]['id'] = $field_name;
    $handler->display->display_options['relationships'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['relationships'][$field_name]['field'] = $field_name;
  }

  /* Declare all fields */
  
  // URI field.
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
        
  // Base fields.
  foreach ($base_fields as $field_name) {
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
  }
  
  // Required data fields.
  foreach ($view_spec->getRequiredDataFields() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
  }
  
  // Optional data fields.
  foreach ($view_spec->getOptionalDataFields() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['required'] = 0;
  }
  
  // Object fields.
  foreach ($object_fields as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['required'] = 0;
  }

  // Global contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);
  
}

function __curios_generate_view_details(&$view, &$view_spec, $base_fields, array $object_fields = array()) {
  $config = _curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();

  /* Display: Details */
  $handler = $view->new_display('block', 'Details', 'details');
  $handler->display->display_options['query']['type'] = 'views_query';
  // Path, menu etc..
  //$handler->display->display_options['path'] = $view_spec->getPath().'/%';

  // Overrides.
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;

  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  //$handler->display->display_options['defaults']['empty'] = FALSE;
  //$handler->display->display_options['defaults']['title'] = FALSE;

  // Pager options.
  $handler->display->display_options['pager']['type'] = 'none';
//  $handler->display->display_options['pager']['type'] = 'full';
//  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
//  $handler->display->display_options['pager']['options']['offset'] = '0';
//  $handler->display->display_options['pager']['options']['id'] = '0';
//  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;

  // Field options.
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 1;

//  // Relationships.
//  foreach ($view_spec->getObjectFields() as $field_id) {
//    $field_name = $resource_name.'_'.$field_id;
//    $handler->display->display_options['relationships'][$field_name]['id'] = $field_name;
//    $handler->display->display_options['relationships'][$field_name]['table'] = $view->base_table;
//    $handler->display->display_options['relationships'][$field_name]['field'] = $field_name;
//    $handler->display->display_options['relationships'][$field_name]['required'] = 0;
//  }

  /* Field: URI */
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$resource_name]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$resource_name]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$resource_name]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['url_encode'] = 0;
  $handler->display->display_options['fields'][$resource_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$resource_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$resource_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$resource_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$resource_name]['hide_alter_empty'] = 0;

  // Field: title.
  $handler->display->display_options['fields'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['label'] = '';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['url_encode'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['element_type'] = 'h1';
  $handler->display->display_options['fields'][$base_fields['title']]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$base_fields['title']]['element_label_colon'] = FALSE;
  $handler->display->display_options['fields'][$base_fields['title']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['required'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['exists'] = 0;

  // Field: description.
  $handler->display->display_options['fields'][$base_fields['description']]['id'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['description']]['field'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['label'] = '';
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['url_encode'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['element_type'] = 'em';
  $handler->display->display_options['fields'][$base_fields['description']]['element_label_type'] = 'strong';
  $handler->display->display_options['fields'][$base_fields['description']]['element_label_colon'] = FALSE;
  $handler->display->display_options['fields'][$base_fields['description']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['hide_empty'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['type'] = 'text_default';
  $handler->display->display_options['fields'][$base_fields['description']]['required'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['exists'] = 0;

  // Newline.
  __curios_field_newline($handler);

  // Required data fields.
  foreach ($view_spec->getRequiredDataFields() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $field = $config['rdf_fields'][$field_id];
    //__new_field_set_defaults($handler, $resource_name.'_'.$field_name);
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['label'] = __format_name($field->getLabel());
    $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['url_encode'] = 0;
    $handler->display->display_options['fields'][$field_name]['element_label_type'] = 'strong';
    $handler->display->display_options['fields'][$field_name]['element_label_colon'] = 1;
    $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
    $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
    $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
    $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;
    $handler->display->display_options['fields'][$field_name]['required'] = 1;
  }

  // Optional data fields.
  foreach ($view_spec->getOptionalDataFields() as $field_id) {
    $field_name = $resource_name.'_'.$field_id;
    $field = $config['rdf_fields'][$field_id];

    // Remove base fields.
    if (in_array($field_name, $base_fields)) {
        continue;
    }

    //__new_field_set_defaults($handler, $resource_name.'_'.$field_name);
    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
    $handler->display->display_options['fields'][$field_name]['label'] = __format_name($field->getLabel());
    $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
    $handler->display->display_options['fields'][$field_name]['alter']['url_encode'] = 0;
    $handler->display->display_options['fields'][$field_name]['element_label_type'] = 'strong';
    $handler->display->display_options['fields'][$field_name]['element_label_colon'] = 1;
    $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
    $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
    $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
    $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;
    $handler->display->display_options['fields'][$field_name]['hide_empty'] = 1;
    $handler->display->display_options['fields'][$field_name]['required'] = 0;
  }

  // Newline.
 // __curios_field_newline($handler);

  // Object fields (with no range specified).
//  foreach ($object_fields as $field_id) {
//    $field_name = $resource_name.'_'.$field_id;
//    $field = $config['rdf_fields'][$field_id];
//    $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
//    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
//    $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
//    $handler->display->display_options['fields'][$field_name]['label'] = __format_name($field->getLabel());
//    $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
//    $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
//    $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['url_encode'] = 0;
//    $handler->display->display_options['fields'][$field_name]['element_label_type'] = 'strong';
//    $handler->display->display_options['fields'][$field_name]['element_label_colon'] = 1;
//    $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
//    $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
//    $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
//    $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;
//    $handler->display->display_options['fields'][$field_name]['hide_empty'] = 1;
//    $handler->display->display_options['fields'][$field_name]['required'] = 0;
//  }

  // Newline.
  __curios_field_newline($handler);

  // Field: search link.
  $field_name = 'searchlink';
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = 'views';
  $handler->display->display_options['fields'][$field_name]['field'] = 'nothing';
  $handler->display->display_options['fields'][$field_name]['ui_name'] = 'Search Link';
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['alter']['text'] = 'Back to listing';
  $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['path'] = $view_spec->getPath().'/';
  $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$field_name]['element_label_colon'] = FALSE;
  $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;

//    // Newline.
//  __curios_field_newline($handler);

  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

}

function __curios_generate_object_block(&$view, &$view_spec, $base_fields, $field_id) {
  $config = _curios_configuration();
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();

  $ranges = $resource->getObjectFieldRanges();
  $field = $config['rdf_fields'][$field_id];
  $field_name = $resource_name.'_'.$field_id;

  // Default.
  $use_rewrite = FALSE;

  // Find target type.
  if (empty($ranges[$field_id])) {
    // No target, default to hc_subject.
    $ranges[$field_id] = 'hc_subject';
  } else if (is_array($ranges[$field_id])) {
    // Non-empty array -> multiple targets.
    $ranges[$field_id] = 'hc_subject';
    $use_rewrite = TRUE;
  } // else -> single target.

  $handler = $view->new_display('block', 'Object: '.$field->getLabel(), 'object_'.$field_name);


  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['options']['offset'] = '0';
  // FIXME using rdf:type increases the results, ARC2 dies, limit to 100 for now
  //$handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  
  //$handler->display->display_options['pager']['type'] = 'mini';
//  $handler->display->display_options['attachment_position'] = 'after';
//  $handler->display->display_options['displays'] = array(
//      'details' => 'details',
//      'default' => 0,
//      'page' => 0,
//  );

  // Indicates whether the pre_render hook should attempt to rewrite the link target.
  $handler->display->display_options['curios']['rewrite_object_target'] = $use_rewrite;

  $handler->display->display_options['title'] = __format_name($field->getLabel());

  // CURIOS specific options...
  $handler->display->display_options['curios']['display_type'] = 'object_block';

  // Overrides.
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = TRUE;
    
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';

  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;

  $handler->display->display_options['query']['options']['consolidate'] = FALSE;

//  /* No results behavior: Global: Text area */
//  $handler->display->display_options['empty']['area']['id'] = 'area';
//  $handler->display->display_options['empty']['area']['table'] = 'views';
//  $handler->display->display_options['empty']['area']['field'] = 'area';
//  $handler->display->display_options['empty']['area']['empty'] = FALSE;
//  $handler->display->display_options['empty']['area']['content'] = '&nbsp;';
//  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
//  $handler->display->display_options['empty']['area']['tokenize'] = 0;

  // Relationship.
  $handler->display->display_options['relationships'][$field_name]['id'] = $field_name;
  $handler->display->display_options['relationships'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['relationships'][$field_name]['field'] = $field_name;
  $handler->display->display_options['relationships'][$field_name]['required'] = 0;

  //if (!empty($ranges[$field_id])) {
  $title_field_name = /*$field_name.'_'.*/$ranges[$field_id].'_dc_title'; // TODO use $base_fields
  $identifier_field_name = /*$field_name.'_'.*/$ranges[$field_id].'_hc_subject_id'; // TODO use $base_fields
  $type_field_name = /*$field_name.'_'.*/$ranges[$field_id].'_type'; // TODO use $base_fields
  $target_view = _curios_get_view($ranges[$field_id]);

  // Identifier.
  $handler->display->display_options['fields'][$identifier_field_name]['id'] = $identifier_field_name;
  $handler->display->display_options['fields'][$identifier_field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$identifier_field_name]['field'] = $identifier_field_name;
  $handler->display->display_options['fields'][$identifier_field_name]['relationship'] = $field_name;
  $handler->display->display_options['fields'][$identifier_field_name]['label'] = '';
  $handler->display->display_options['fields'][$identifier_field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['alter']['url_encode'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['element_label_colon'] = FALSE;
  $handler->display->display_options['fields'][$identifier_field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$identifier_field_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$identifier_field_name]['required'] = 1;

  if (!$use_rewrite) {
    // Display the title field directly (no rewriting).
    $handler->display->display_options['fields'][$title_field_name]['id'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$title_field_name]['field'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['relationship'] = $field_name;
    $handler->display->display_options['fields'][$title_field_name]['label'] = '';//__format_name($field->getLabel());
    $handler->display->display_options['fields'][$title_field_name]['alter']['alter_text'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['make_link'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['alter']['path'] = $target_view->getPath().'/['.$identifier_field_name.']';
    $handler->display->display_options['fields'][$title_field_name]['alter']['absolute'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['external'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['nl2br'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['trim'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['html'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['url_encode'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['max_length'] = '15';
    $handler->display->display_options['fields'][$title_field_name]['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields'][$title_field_name]['alter']['trim'] = TRUE;
    $handler->display->display_options['fields'][$title_field_name]['element_label_type'] = 'strong';
    $handler->display->display_options['fields'][$title_field_name]['element_label_colon'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['element_default_classes'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['hide_empty'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['empty_zero'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['hide_alter_empty'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['hide_empty'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['required'] = 1;
  } else {// Set type and rewrite field and hidden title field for rewriter.
    $handler->display->display_options['fields'][$title_field_name]['id'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$title_field_name]['field'] =  $title_field_name;
    $handler->display->display_options['fields'][$title_field_name]['relationship'] = $field_name;
    $handler->display->display_options['fields'][$title_field_name]['label'] = '';
    $handler->display->display_options['fields'][$title_field_name]['exclude'] = TRUE;
    $handler->display->display_options['fields'][$title_field_name]['alter']['alter_text'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['make_link'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['absolute'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['external'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['nl2br'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['trim'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['html'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['alter']['url_encode'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['element_label_colon'] = FALSE;
    $handler->display->display_options['fields'][$title_field_name]['element_default_classes'] = 1;
    $handler->display->display_options['fields'][$title_field_name]['hide_empty'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['empty_zero'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['hide_alter_empty'] = 0;
    $handler->display->display_options['fields'][$title_field_name]['required'] = 1;

    $handler->display->display_options['fields'][$type_field_name]['id'] =  $type_field_name;
    $handler->display->display_options['fields'][$type_field_name]['table'] = $view->base_table;
    $handler->display->display_options['fields'][$type_field_name]['field'] =  $type_field_name;
    $handler->display->display_options['fields'][$type_field_name]['relationship'] = $field_name;
    $handler->display->display_options['fields'][$type_field_name]['label'] = '';
    $handler->display->display_options['fields'][$type_field_name]['exclude'] = TRUE;
    $handler->display->display_options['fields'][$type_field_name]['alter']['alter_text'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['make_link'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['absolute'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['external'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['nl2br'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields'][$type_field_name]['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields'][$type_field_name]['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['trim'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['html'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['alter']['url_encode'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['element_label_colon'] = FALSE;
    $handler->display->display_options['fields'][$type_field_name]['element_default_classes'] = 1;
    $handler->display->display_options['fields'][$type_field_name]['hide_empty'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['empty_zero'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['hide_alter_empty'] = 0;
    $handler->display->display_options['fields'][$type_field_name]['required'] = 1;

    /* Field: Global: Link Target Rewriter */
    $handler->display->display_options['fields']['curios_link_target_rewriter']['id'] = 'curios_link_target_rewriter';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['table'] = 'views';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['field'] = 'curios_link_target_rewriter';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['label'] = '';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['alter_text'] = TRUE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['text'] = '[hc_subject_dc_title]';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['make_link'] = TRUE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['path'] = 'subjects/[hc_subject_hc_subject_id]';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['hide_alter_empty'] = FALSE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['max_length'] = '15';
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields']['curios_link_target_rewriter']['alter']['trim'] = TRUE;
      }
//  } else {
//    // Plain field name.
//    $handler->display->display_options['fields'][$field_name]['id'] =  $field_name;
//    $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
//    $handler->display->display_options['fields'][$field_name]['field'] =  $field_name;
//    $handler->display->display_options['fields'][$field_name]['relationship'] = $field_name;
//    $handler->display->display_options['fields'][$field_name]['label'] = __format_name($field->getLabel());
//    $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
//    $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
//    $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
//    $handler->display->display_options['fields'][$field_name]['alter']['url_encode'] = 0;
//    $handler->display->display_options['fields'][$field_name]['element_label_type'] = 'strong';
//    $handler->display->display_options['fields'][$field_name]['element_label_colon'] = 1;
//    $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
//    $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
//    $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
//    $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;
//    $handler->display->display_options['fields'][$field_name]['hide_empty'] = 1;
//    $handler->display->display_options['fields'][$field_name]['required'] = 0;
//  }

  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return TRUE;
}

function __curios_generate_view_listing(&$view, &$view_spec, $base_fields) {
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $image_file = $resource_name.'_hc_has_file';
  
  $handler = $view->new_display('block', 'Listing', 'listing');
  
  // Path, menu etc.
  //$handler->display->display_options['path'] = $view_spec->getPath();
  $handler->display->display_options['title'] = $view_spec->getLabel();
  //$handler->display->display_options['menu']['title'] = $view_spec->getLabel();
  //$handler->display->display_options['menu']['type'] = 'normal';
  //$handler->display->display_options['menu']['weight'] = '0';
  //$handler->display->display_options['menu']['name'] = 'menu-curios';
  
  // Overrides.
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;

  // Pager options.
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 20, 50';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  
  // Table options.
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    $resource_name => $resource_name,
    $base_fields['title'] => $base_fields['title'],
    $base_fields['description'] => $base_fields['description'],
    $image_file => $image_file,
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    $resource_name => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['title'] => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $base_fields['description'] => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    $image_file => array(
     'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  
  // Header: page description area.
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = $view_spec->getPageDescription();
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  
  // Field: URI.
  $handler->display->display_options['fields'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['fields'][$resource_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$resource_name]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$resource_name]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$resource_name]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$resource_name]['alter']['url_encode'] = 1;
  $handler->display->display_options['fields'][$resource_name]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$resource_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$resource_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$resource_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$resource_name]['hide_alter_empty'] = 0;

  // Field: subject id.
  $subject_id_field = $resource_name.'_hc_subject_id';  // TODO use $base_fields
  $handler->display->display_options['fields'][$subject_id_field]['id'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$subject_id_field]['field'] = $subject_id_field;
  $handler->display->display_options['fields'][$subject_id_field]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['alter']['url_encode'] = 1;
  $handler->display->display_options['fields'][$subject_id_field]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$subject_id_field]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$subject_id_field]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$subject_id_field]['hide_alter_empty'] = 0;
  
  // Field: title.
  $handler->display->display_options['fields'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['fields'][$base_fields['title']]['label'] = 'Title';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['make_link'] = 1;
  //$handler->display->display_options['fields'][$base_fields['title']]['alter']['path'] = $view_spec->getPath().'/['.$resource_name.']';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['path'] = $view_spec->getPath().'/['.$subject_id_field.']';
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['alter']['url_encode'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['title']]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$base_fields['title']]['required'] = 1;
  
  // Field: description.
  $handler->display->display_options['fields'][$base_fields['description']]['id'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$base_fields['description']]['field'] = $base_fields['description'];
  $handler->display->display_options['fields'][$base_fields['description']]['label'] = 'Description';
  $handler->display->display_options['fields'][$base_fields['description']]['type'] = 'text_plain';
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['trim'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['max_length'] = '180';
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['alter']['url_encode'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$base_fields['description']]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$base_fields['description']]['required'] = 0;

  
  /* Field: HasFile */
  $handler->display->display_options['fields'][$image_file]['id'] = $image_file;
  $handler->display->display_options['fields'][$image_file]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$image_file]['field'] = $image_file;
  $handler->display->display_options['fields'][$image_file]['label'] = 'Files';
  $handler->display->display_options['fields'][$image_file]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['text'] = 'Yes';
  $handler->display->display_options['fields'][$image_file]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$image_file]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$image_file]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$image_file]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$image_file]['element_label_colon'] = 1;
  $handler->display->display_options['fields'][$image_file]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$image_file]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$image_file]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$image_file]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$image_file]['required'] = 0;
  $handler->display->display_options['fields'][$image_file]['exists'] = 1;

  // Contextual filters.
  __curios_rdf_type_filter($handler, $view, $view_spec);
  
  // Exposed filter: title.
  $handler->display->display_options['filters'][$base_fields['title']]['id'] = $base_fields['title'];
  $handler->display->display_options['filters'][$base_fields['title']]['table'] = $view->base_table;
  $handler->display->display_options['filters'][$base_fields['title']]['field'] = $base_fields['title'];
  $handler->display->display_options['filters'][$base_fields['title']]['operator'] = '~=';
  $handler->display->display_options['filters'][$base_fields['title']]['exposed'] = TRUE;
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['operator_id'] = $base_fields['title'].'_op';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['label'] = 'Search '.$view_spec->getLabel();
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['operator'] = $base_fields['title'].'_op';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['identifier'] = 'name';
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['required'] = 0;
  $handler->display->display_options['filters'][$base_fields['title']]['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters'][$base_fields['title']]['sparql_options'] = array(
    'value_type' => 'string',
    'language' => '0',
  );

}

function __curios_generate_view_images(&$view, &$view_spec, $base_fields) {
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  
  /* Display: Images */
  $handler = $view->new_display('block', 'Images', 'images');
  
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['attachment_position'] = 'after';
    $handler->display->display_options['displays'] = array(
      'details' => 'details',
      'default' => 0,
      'page' => 0,
  );
  
  // Overrides.
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = TRUE;
  
  
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  
  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  
  // TODO use some standard RDF image reference
  // Relationship
  $relationship_field = $resource_name.'_hc_has_file';
  $handler->display->display_options['relationships'][$relationship_field]['id'] = $relationship_field;
  $handler->display->display_options['relationships'][$relationship_field]['table'] = $view->base_table;
  $handler->display->display_options['relationships'][$relationship_field]['field'] = $relationship_field;
  $handler->display->display_options['relationships'][$relationship_field]['required'] = 0;

  // Field: file.
  $field_name = 'hc_image_file_hc_file';
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['relationship'] = $relationship_field;
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['exclude'] = TRUE;
  $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$field_name]['element_label_colon'] = FALSE;
  $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$field_name]['required'] = 1;
  
  /* Field: PHP Image Output */
  $field_name = 'hc_image_php_output';
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = 'views';
  $handler->display->display_options['fields'][$field_name]['field'] = 'php';
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['ui_name'] = 'PHP Image Output';
  $handler->display->display_options['fields'][$field_name]['alter']['alter_text'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$field_name]['element_label_colon'] = FALSE;
  $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;
  $handler->display->display_options['fields'][$field_name]['use_php_setup'] = 0;
  $handler->display->display_options['fields'][$field_name]['php_value'] = '$a = "VALUE"; return $a;';
  $handler->display->display_options['fields'][$field_name]['php_output'] = '<?php 
  print($value);
  $image_path = $GLOBALS[\'base_path\'].\'images/\'.str_replace("\\\\", \'/\', $row->hc_image_file_hc_file);

  $output = \'\';
  //$output .= \'Image: \'.$image_path.\'<br />\';
  $output .= \'<img src="\'.$image_path.\'" /><br /><br />\';

  echo $output;
  ?>';
  $handler->display->display_options['fields'][$field_name]['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields'][$field_name]['php_click_sortable'] = '';
  $handler->display->display_options['displays'] = array(
    'details' => 'details',
    'default' => 0,
    'page' => 0,
  );
  
  
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = '&nbsp;';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;

  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);
}


function __curios_rdf_type_filter(&$handler, $view, $view_spec) {
  $resource_name = $view_spec->getResource()->getMachineName();
  $field_name = $resource_name.'_type';
  $handler->display->display_options['arguments'][$field_name]['id'] = $field_name;
  $handler->display->display_options['arguments'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['arguments'][$field_name]['field'] = $field_name;
  $handler->display->display_options['arguments'][$field_name]['default_action'] = 'default';
  $handler->display->display_options['arguments'][$field_name]['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments'][$field_name]['default_argument_options']['argument'] = 'no value';
  $handler->display->display_options['arguments'][$field_name]['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments'][$field_name]['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments'][$field_name]['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments'][$field_name]['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments'][$field_name]['sparql_options'] = array(
    'value_type' => 'uri',
    'language' => '0',
    'code' => 'return \''.$view_spec->getResource()->getRDFType().'\';',
  );
}

function __curios_uri_filter(&$handler, $view, $view_spec) {
  $resource_name = $view_spec->getResource()->getMachineName();
  $handler->display->display_options['arguments'][$resource_name]['id'] = $resource_name;
  $handler->display->display_options['arguments'][$resource_name]['table'] = $view->base_table;
  $handler->display->display_options['arguments'][$resource_name]['field'] = $resource_name;
  $handler->display->display_options['arguments'][$resource_name]['default_action'] = 'not found';
  $handler->display->display_options['arguments'][$resource_name]['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments'][$resource_name]['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments'][$resource_name]['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments'][$resource_name]['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments'][$resource_name]['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments'][$resource_name]['sparql_options'] = array(
    'value_type' => 'uri',
    'language' => '0',
    'code' => 'return \'http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#\'.$this->argument;',
  ); // TODO replace namespace URI with value from config.
}

function __curios_field_newline(&$handler) {
  static $c = 0;
  $field_name = 'newline_'.$c++;
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = 'views';
  $handler->display->display_options['fields'][$field_name]['field'] = 'nothing';
  $handler->display->display_options['fields'][$field_name]['ui_name'] = 'New Line';
  $handler->display->display_options['fields'][$field_name]['label'] = '';
  $handler->display->display_options['fields'][$field_name]['alter']['text'] = '<br/>';
  $handler->display->display_options['fields'][$field_name]['alter']['make_link'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['absolute'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['external'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['nl2br'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields'][$field_name]['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['trim'] = 0;
  $handler->display->display_options['fields'][$field_name]['alter']['html'] = 0;
  $handler->display->display_options['fields'][$field_name]['element_label_colon'] = FALSE;
  $handler->display->display_options['fields'][$field_name]['element_default_classes'] = 1;
  $handler->display->display_options['fields'][$field_name]['hide_empty'] = 0;
  $handler->display->display_options['fields'][$field_name]['empty_zero'] = 0;
  $handler->display->display_options['fields'][$field_name]['hide_alter_empty'] = 0;
}


