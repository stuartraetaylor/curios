<?php

/**
 * Override listings view for hc_image_file.
 *
 * @param type $view
 * @param type $view_spec
 * @param type $base_fields
 * @return type
 */
function __curios_generate_display_listing_hc_imagefile(&$view, &$view_spec, $base_fields) {
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();
  $image_file = $resource_name.'_hc_has_file';

  // Remove image file column.
  $handler = __curios_generate_display('listing', $view, $view_spec, $base_fields, TRUE);
  unset($handler->display->display_options['style_options']['columns'][$image_file]);
  unset($handler->display->display_options['style_options']['info'][$image_file]);
  unset($handler->display->display_options['fields'][$image_file]);

  return $handler;
}

/**
 * Override summary view for hc_image_file.
 *
 * @param type $view
 * @param type $view_spec
 * @param type $base_fields
 * @return type
 */
function __curios_generate_display_summary_hc_imagefile(&$view, &$view_spec, $base_fields) {
  // Remove searchlink.
  $handler = __curios_generate_display('summary', $view, $view_spec, $base_fields, TRUE);
  unset($handler->display->display_options['fields']['searchlink']);
  return $handler;
}

/**
 * Override image gallery view for hc_image_file.
 *
 * @param type $view
 * @param type $view_spec
 * @param type $base_fields
 * @return type
 */
function __curios_generate_display_images_hc_imagefile(&$view, &$view_spec, $base_fields) {
  return FALSE;
}

function __curios_generate_display_properties_hc_imagefile(&$view, &$view_spec, $base_fields) {
  $resource = $view_spec->getResource();
  $resource_name = $resource->getMachineName();

  /* Display: Properties */
  $handler = $view->new_display('block', 'Properties', 'properties');
  $handler->display->display_options['query']['type'] = 'views_query';

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

  // Field options.
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 1;

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

    // Field: file.
  $field_name = 'hc_imagefile_hc_url';
  $handler->display->display_options['fields'][$field_name]['id'] = $field_name;
  $handler->display->display_options['fields'][$field_name]['table'] = $view->base_table;
  $handler->display->display_options['fields'][$field_name]['field'] = $field_name;
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
  $handler->display->display_options['fields'][$field_name]['php_value'] = '';
  $handler->display->display_options['fields'][$field_name]['php_output'] = '<?php
  $image_path = str_replace(\'http://www.hebrideanconnections.com/\', \'http://www.dotrural.ac.uk/curiosdemo/images/\', $row->hc_imagefile_hc_url);
  $output = \'<a href="\'.$image_path.\'" rel="lightbox"><img src="\'.$image_path.\'" /></a><br /><br />\';
  echo $output;
  ?>';
  //var_dump($handler->display->display_options['fields'][$field_name]['php_output']); exit;
  $handler->display->display_options['fields'][$field_name]['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields'][$field_name]['php_click_sortable'] = '';
  $handler->display->display_options['displays'] = array(
    'details' => 'details',
    'default' => 0,
    'page' => 0,
  );

  // Contextual filters.
  __curios_uri_filter($handler, $view, $view_spec);
  __curios_rdf_type_filter($handler, $view, $view_spec);

  return $handler;
}