<?php

function curios_resource_type_load($resource_name) {
  if (!empty($resource_name)) {
    $resource_type = sparql_views_resource_type_load($resource_name);
    
    if ($resource_type != NULL) {
      return $resource_type;
    } else {
      return FALSE;
    }
  }

  return $resource_name;
}

function curios_manage_page() {
  $page = array();

  $base_path = base_path() . 'curios/manage';
  $content = <<<EOT
<p>From this page you can create, edit and delete records in the repository.</p>
<ul>
<li><a href="$base_path/create">Create a new record</a></li>
<li><a href="$base_path/edit">Edit or delete an existing record</a></li>
</ul>
<p>Choose an action from the menu to continue.</p>
EOT;
  $page[] = array('#markup' => $content);

  return $page;
}

function curios_manage_insert_form($form, &$form_state) {
  $form = array();

 // $form['fieldset'] = array(
 //   '#type' => 'fieldset',
 //   '#title' => t('Insert New Record'),
 //   '#weight' => 5,
 //   '#collapsible' => TRUE,
 //   '#collapsed' => $collapsed,
 // );
  $form['type'] = __curios_resources_form_select();
  $form['submit'] = array('#type' => 'submit', '#value' => 'Next');
  
  return $form;
}

function curios_manage_insert_form_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $path = "curios/manage/create/$type";

  $form_state['redirect'] = array($path, array(), 302);
}

function curios_manage_update_form($form, &$form_state) {
  $form = array();

  $form['type'] = __curios_resources_form_select();
  $form['subject_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject Id'),
    '#required' => TRUE,
    '#size' => '12',
  );
  $form['submit'] = array('#type' => 'submit', '#value' => 'Next');

  return $form;
}

function curios_manage_update_form_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $id = $form_state['values']['subject_id'];
  $path = "curios/manage/edit/$type/$id";

  $form_state['redirect'] = array($path, array(), 302);
}

function curios_delete_page() {
  $page = array();
  $page[] = array('#markup' => "<p>Enter the SubjectId below then click 'Delete Record' to delete the record.</p>");
  $page[] = drupal_get_form('curios_manage_delete_form');
  return $page;
}

//function curios_manage_delete_form($form, &$form_state, $collapsed = FALSE) {
//  $form = array();
//
// // $form['fieldset']['type'] = __curios_resources_form_select();
//  $form['delete_subject_id'] = array(
//    '#type' => 'textfield',
//    '#title' => t('Subject Id'),
//    '#required' => TRUE,
//    '#size' => '12',
//  );
//  $form['submit'] = array('#type' => 'submit', '#value' => 'Delete Record');
//
//  return $form;
//}

function curios_delete_form_submit($form, &$form_state) {
  // TODO add confirm form
  $subject_id = $form_state['values']['identifier'];
  $success = __curios_subject_delete($subject_id);

  if ($success) {
    drupal_set_message("The record has been deleted successfully  (ID: $subject_id)", 'status', FALSE);
    $form_state['redirect'] = array("curios/manage", array(), 302);
  } else {
    drupal_set_message("Failed to delete record", 'status', FALSE);
  }
}



function __curios_resources_form_select() {
  $options = array();
  $resources = entity_load('sparql_views_resource_type');

  foreach ($resources as $entity) {
    if ($entity->name == 'hc_subject') { // FIXME top level resource should come from confg.
      continue;
    }
    $options[$entity->name] = $entity->label;
  }

  return array(
    '#type' => 'select',
    '#empty_option' => '- Select record type -',
    '#required' => TRUE,
    '#options' => $options,
  );
}




// ------ INSERT -------

function curios_insert_form_page($resource_type) {
  $page = array();
  $page[] = array('#markup' => "<p>Complete the form below to create a new record.</p>");
  $page[] = drupal_get_form('curios_insert_form', $resource_type);
  return $page;
}

function curios_insert_page() {
  $page = array();
  $page[] = array('#markup' => "<p>Select the record type below then click 'Next' to continue.</p>");
  $page[] = drupal_get_form('curios_manage_insert_form');

  return $page;
}

function curios_insert_form($form, $form_state, $resource_type) {//dpm($form_state);
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_type->name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_type->name));

  $break = array('#markup' => '<br/>');

  $form = array();
  $form['status'] = array('#markup' => "<h3>Create new: <strong>".$resource_type->label."</strong></h3>");//<span style=\"font-size: 0.8em; text-style: italic;\">(".$resource_type->name.")</span>
  $form['resource'] = array('#type' => 'hidden', '#value' => $resource_type->name);

  //$form['identifier'] = array(
  //  '#type' => 'textfield',
  //  '#title' => t('Identifier'),
  //);

   // FIXME dc_title and dc_description should come from config
  $form['dc_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#size' => '80',
    '#field_suffix' => '<em style="font-size: 0.7em;">(dc:title / hc:englishName)</em>',
  );
  $form['dc_description'] = array(
    '#type'=>'text_format',
    '#title' => t('Description'),
    '#required' => TRUE,
    '#cols' => '80',
    '#rows' => '4',
    '#format' => 'filtered_html',
    '#field_suffix' => '<em style="font-size: 0.7em;">(dc:description)</em>',
  );
  $form[] = $break;

  $form['optional_fields'] = array(
  '#type' => 'fieldset',
    '#title' => t('Additional Fields'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  foreach ($field_instances as $instance) {
    //$block['content'] .= '<p><label style="display: inline-block; font-weight: bold; width: 280px;">'.$instance['label'].':</label>';
    //$block['content'] .= '<input type="text" name="'.$instance['field_name'].'"/>&nbsp;&nbsp;';
    //$block['content'] .= '';

    if (__is_identifier_field($instance) || 
        __is_title_field($instance) ||
        __is_description_field($instance) ||
        __is_resource_field($instance)) {
      continue;
    }

    $form['optional_fields'][$instance['field_name']] = array(
      '#type' => 'textfield',
      '#title' => t($instance['label']),
      '#size' => '80',
      '#field_suffix' => '<em style="font-size: 0.7em;">('.$rdf_mapping[$instance['field_name']]['predicates'][0].')</em>',
    );
  }

  $form[] = $break;
  $form['submit'] = array('#type' => 'submit', '#value' => 'Create New Record');
  //$form['reset'] = array('#markup' => '<input type="reset" class="form-submit" value="Clear Form" />');

  return $form;
}

function curios_insert_form_submit($form, &$form_state) {
  $resource_name = $form_state['values']['resource'];
  //$resource_type = sparql_views_resource_type_load($resource_name);
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  $subject_id = __generate_new_subject_id();
  $rdf_type = $rdf_mapping['rdftype'][0];
  $triples_insert = array();
  // FIXME requied triples - should come from config
  $triples_insert[] = '      ' . $rdf_mapping['hc_subject_id']['predicates'][0]  ." \"$subject_id\"^^<http://www.w3.org/2001/XMLSchema#string>;";  // TODO 'id' field from config

  $required_fields = array('dc_title', 'dc_description'); // TODO add into config

  // Add required fields.
  foreach ($required_fields as $field_name) {
    $form_value = $form_state['values'][$field_name];

    if (is_array($form_value)) { // if using a formatter
      $form_value = $form_state['values'][$field_name]['value'];
    }

    $triples_insert[] = '      ' . $rdf_mapping[$field_name]['predicates'][0]  ." \"". __curios_escape_sparql($form_value) ."\"^^<http://www.w3.org/2001/XMLSchema#string>;";
  }

  //$triples_insert .= '      ' . $rdf_mapping['hc_english_name']['predicates'][0]  ." \"". $form_state['values']['dc_title']."\";\n";

  foreach ($field_instances as $instance) {
    if (__is_identifier_field($instance) ||
        __is_title_field($instance) ||
        __is_description_field($instance) ||
        __is_resource_field($instance)) {
      continue;
    }

    $form_value = $form_state['values'][$instance['field_name']];
    if (!empty($form_value)) {
      $triples_insert[] = '      ' . $rdf_mapping[$instance['field_name']]['predicates'][0]  ." \"". __curios_escape_sparql($form_value) ."\"^^<http://www.w3.org/2001/XMLSchema#string>;";
    }
  }

  $triples_insert = array_unique($triples_insert);
  $triples_insert = join("\n", $triples_insert);

  $success = __curios_subject_insert($subject_id, $rdf_type, $triples_insert);

  if ($success) {
    drupal_set_message("The new record has been created successfully (ID: $subject_id)", 'status', FALSE);
    $path = "curios/manage/edit/$resource_name/$subject_id";
    $form_state['redirect'] = array($path, array(), 302);
  } else {
    drupal_set_message("Failed to create record", 'status', FALSE);
  }
}



// ------------

/* Update */
function curios_update_form_page($resource_type, $subject_id = NULL) {
  $view_result = _curios_execute_details_view($resource_type->name, $subject_id);

  if (!empty($view_result)) {
    $page = array();
    $page[] = array('#markup' => "<p>Edit the form below to update this record.</p>");
    $page[] = drupal_get_form('curios_update_form', $resource_type, $subject_id, $view_result);

    return $page;
  } else {
    drupal_set_message("Unknown record: $resource_type->label; ID: $subject_id", 'error', FALSE);
    return curios_update_page();
  }
}

function _curios_execute_details_view($resource_name, $subject_id) {
  $config = _curios_configuration();
  $resource_config = $config['rdf_resources'][$resource_name];
  $view_config = _curios_get_view($resource_name);
  
  return views_get_view_result($view_config->getMachineName(), 'details', $subject_id, $resource_config->getRDFType());
}

function curios_update_page() {
  $page = array();
  $page[] = array('#markup' => "<p>Select the record type and enter the SubjectId below then click 'Next' to continue.</p>");
  $page[] = drupal_get_form('curios_manage_update_form');

  return $page;
}

function curios_update_form($form, $form_state, $resource_type, $subject_id, $view_result) {
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_type->name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_type->name));

  $title_field = $resource_type->name.'_dc_title';
  $title_value = $view_result[0]->$title_field;
  $description_field = $resource_type->name.'_dc_description';
  $description_value = $view_result[0]->$description_field;

  $form = array();
  $form['status'] = array('#markup' => "<h3>Edit: <strong>".$resource_type->label."</strong>; ID: <strong>". $subject_id ."</strong>; Name: <strong>". $title_value ."</strong></h3>");
  $form['resource'] = array('#type' => 'hidden', '#value' => $resource_type->name);
  $form['identifier'] = array('#type' => 'hidden', '#value' => $subject_id);

  $break = array('#markup' => '<br/>');

  // FIXME dc_title and dc_description should come from config
  $form['dc_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#size' => '80',
    '#field_suffix' => '<em style="font-size: 0.7em;">(dc:title / hc:englishName)</em>',
    '#default_value' => $title_value,
  );
  $form['old_dc_title'] = array(
    '#type' => 'hidden',
    '#value' => $title_value,
  );
  $form['dc_description'] = array(
    '#type'=>'text_format',
    '#title' => t('Description'),
    '#required' => TRUE,
    '#cols' => '80',
    '#rows' => '4',
    '#format' => 'filtered_html',
    '#field_suffix' => '<em style="font-size: 0.7em;">(dc:description)</em>',
    '#default_value' => $description_value,
  );
  $form['old_dc_description'] = array(
    '#type' => 'hidden',
    '#value' => $description_value,
  );
  $form[] = $break;

  $form['optional_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Fields'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $relationship_options = array();

  foreach ($field_instances as $instance) {
    if (__is_identifier_field($instance) ||
        __is_title_field($instance) ||
        __is_description_field($instance)) {
        //__is_resource_field($instance)) {
      continue;
    }

    $results_field = $resource_type->name.'_'.$instance['field_name'];
    $value = empty($view_result[0]->$results_field) ? '' : $view_result[0]->$results_field;

    if (__is_resource_field($instance)) { // Relationship.
      $relationship_options[$instance['field_name']] = $instance['label'];
    } else { // Field.
      $form['optional_fields'][$instance['field_name']] = array(
        '#type' => 'textfield',
        '#default_value' => $value,
        '#title' => t($instance['label']),
        '#field_suffix' => '<em style="font-size: 0.7em;">('.$rdf_mapping[$instance['field_name']]['predicates'][0].')</em>',
      );

      $form['old_'.$instance['field_name']] = array(
        '#type' => 'hidden',
        '#value' => $value,
      );

      if (!empty($value)) {
        $form['optional_fields']['#collapsed'] = FALSE;
      }
    }
  }

  if (!empty($relationship_options)) {
    $form['relationship_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Add Relationship'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['relationship_fields']['relationship_select'] = array(
      '#type' => 'select',
      '#empty_option' => '- Select relationship -',
      '#required' => FALSE,
      '#options' => $relationship_options,
    );
  }


  $form['submit'] = array('#type' => 'submit', '#value' => 'Update Record');

  // TODO reset description
  //$form['reset'] = array('#markup' => '<input type="reset" class="form-submit" value="Undo Changes" />');

  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete Record'),
    '#attributes' => array('onclick' => 'return confirm("Are you sure you wish to permanently delete this record?");'),
    '#submit' => array('curios_delete_form_submit'),
  );

  return $form;
}


// SUBMIT HANDLERS

/* Update */
function curios_update_form_submit($form, &$form_state) {
  $resource_name = $form_state['values']['resource'];
  $subject_id = $form_state['values']['identifier'];

  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  $triples_delete = array();
  $triples_insert = array();

  $required_fields = array('dc_title', 'dc_description'); // TODO get from config

  // Add required fields.
  foreach ($required_fields as $field_name) {
    $form_value_new = $form_state['values'][$field_name];
    $form_value_old = $form_state['values']['old_'.$field_name];

    if (is_array($form_value_new)) { // if using a formatter
      $form_value_new = $form_state['values'][$field_name]['value'];
    }

    if ($form_value_new != $form_value_old) {
      $triples_delete[] = '      ' . $rdf_mapping[$field_name]['predicates'][0]  ." \"". __curios_escape_sparql($form_value_old) ."\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
      $triples_insert[] = '      ' . $rdf_mapping[$field_name]['predicates'][0]  ." \"". __curios_escape_sparql($form_value_new) . "\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
    }
  }

  // Calculate difference for remaining fields.
  foreach ($field_instances as $instance) {
    if (__is_identifier_field($instance) ||
        __is_title_field($instance) ||
        __is_description_field($instance) ||
        __is_resource_field($instance)) {
      continue;
    }

    $form_value_new = $form_state['values'][$instance['field_name']];
    $form_value_old = $form_state['values']['old_'.$instance['field_name']];

    if ($form_value_new != $form_value_old) {
      if (!empty($form_value_old)) {
        $triples_delete[] = '      ' . $rdf_mapping[$instance['field_name']]['predicates'][0]  ." \"". __curios_escape_sparql($form_value_old) ."\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
      }

      if (!empty($form_value_new)) {
        $triples_insert[] = '      ' . $rdf_mapping[$instance['field_name']]['predicates'][0]  ." \"". __curios_escape_sparql($form_value_new) ."\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
      }
    }
  }

  $triples_insert = array_unique($triples_insert);
  $triples_insert = join("\n", $triples_insert);
  $triples_delete = array_unique($triples_delete);
  $triples_delete = join("\n", $triples_delete);

  // Submit form.
  if (!empty($triples_delete) || !empty($triples_insert)) {
    $success = __curios_subject_update($subject_id, $triples_insert, $triples_delete);

    if ($success) {
      drupal_set_message("The record has been updated successfully (ID: $subject_id)", 'status', FALSE);
      //$path = "curios/manage/edit/$resource_name/$subject_id";
      //$form_state['redirect'] = array($path, array(), 302);
      //$form_state['rebuild'] = TRUE;
    } else {
      drupal_set_message("Failed to update record", 'status', FALSE);
    }
  } else {
    drupal_set_message('There were no fields to update', 'warning', FALSE);
  }
}




function __generate_new_subject_id() { return intval(__curios_fetch_max_identifier()) + 1; }

// FIXME the conditions in the below functions should eventually be part of the config.

// FIXME really hacky way of detecting sparql_view_related_resource's
//     This entity type is defined as a sub type of sparql_views_resource in SPARQL Views,
//     but all that I can get back from the API is its widget type to identify it...
function __is_resource_field($field_instance) { return $field_instance['widget']['type'] == 'options_select'; }
function __is_identifier_field($field_instance) { return $field_instance['field_name'] == 'hc_subject_id'; }
function __is_title_field($field_instance) { return ($field_instance['field_name'] == 'dc_title' || $field_instance['field_name'] == 'hc_english_name'); }
function __is_description_field($field_instance) { return $field_instance['field_name'] == 'dc_description'; }