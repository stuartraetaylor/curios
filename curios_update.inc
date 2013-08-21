<?php
/*
 * curios_update.inc
 * 
 * Copyright (c) 2011-2013, Stuart Taylor (staylor@abdn.ac.uk),
 * University of Aberdeen. All rights reserved.
 *
 * CURIOS: Linked Data CMS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software. If not, see <http://www.gnu.org/licenses/>.
 */
 
require_once('scripts/php_fast_cache.php');

/**
 * Page callback.
 *
 * Displays the main 'Manage Repository' page.
 */
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
<ul>
<li><a href="$base_path/tools">Repository administration tools</a></li>
</ul>
EOT;
  $page[] = array('#markup' => $content);

  return $page;
}

/**
 * Page callback.
 *
 * Displays the 'Admin Tools' page.
 */
function curios_admin_tools_page() {
  $latest_records = _curios_latest_record_identifiers(15);
  $content = '';

  $content .= '<p>This page contains a selection of admin tools for the Hebridean Connections repository.</p>';
  $content .= '<h2>Recently created records:</h2>';
  $content .= '<ul>';
  foreach ($latest_records as $id=>$title) {
    $content .= "<li>$id &mdash; $title</li>";
  }
  $content .= '</ul>';

  return array('#markup' => $content);
}

/**
 * Loads a SPARQL Views resource type.
 */
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

/**
 * Form callback.
 *
 * Lists the resources that can be created,
 */
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

/**
 * Submit handler.
 *
 * Redirect the insert form to the appropriate insert form page.
 */
function curios_manage_insert_form_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $path = "curios/manage/create/$type";

  $form_state['redirect'] = array($path, array(), 302);
}

/**
 * Form callback.
 *
 * Gets the browsing class and subject id of the reocrd to be updated.
 */
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

/**
 * Submit handler.
 *
 * Redirects to the appropriate update page.
 */
function curios_manage_update_form_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $id = $form_state['values']['subject_id'];
  $path = "curios/manage/edit/$type/$id";

  $form_state['redirect'] = array($path, array(), 302);
}

/**
 * Submit handler.
 *
 * Removes a record from the triple store.
 */
function curios_delete_form_submit($form, &$form_state) {
  // TODO add confirm form
  $subject_id = $form_state['values']['identifier'];
  $success = _curios_subject_delete($subject_id);

  if ($success) {
    drupal_set_message("The record has been deleted successfully  (ID: $subject_id)", 'status', FALSE);
    $form_state['redirect'] = array("curios/manage", array(), 302);
  } else {
    drupal_set_message("Failed to delete record", 'status', FALSE);
  }
}

/**
 * Generates a form select element from the browsing classes in the configuration.
 */
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

/**
 * Page callback.
 *
 * Insert Record form page.
 */
function curios_insert_form_page($resource_type) {
  $page = array();
  $page[] = array('#markup' => "<p>Complete the form below to create a new record.</p>");
  $page[] = drupal_get_form('curios_insert_form', $resource_type);
  return $page;
}

/**
 * Page callback.
 *
 * Page to select to resource type to be created.
 */
function curios_insert_page() {
  $page = array();
  $page[] = array('#markup' => "<p>Select the record type below then click 'Next' to continue.</p>");
  $page[] = drupal_get_form('curios_manage_insert_form');

  return $page;
}

/**
 * Form callback.
 *
 * Insert record form. This form accepts title, description and literal fields.
 */
function curios_insert_form($form, $form_state, $resource_type) {
  $config = curios_configuration();
  $browsing_class = $config->getResource($resource_type->name);
  $view_spec_id = $config->getViewIdForResource($browsing_class->getId());
  $view_spec = $config->getViewSpec($view_spec_id);

  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_type->name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_type->name));

  $break = array('#markup' => '<br/>');

  $form = array();
  $form['status'] = array('#markup' => "<h3>Create new: <strong>".$resource_type->label."</strong></h3>");//<span style=\"font-size: 0.8em; text-style: italic;\">(".$resource_type->name.")</span>
  $form['resource'] = array('#type' => 'hidden', '#value' => $resource_type->name);

  // Get title and description fields from view spec.
  $title_field = $config->getField($view_spec->getTitleFieldId());
  $description_field = $config->getField($view_spec->getDescriptionFieldId());

  $form[$title_field->getId()] = array(
    '#type' => 'textfield',
    '#title' => t($title_field->getLabel()),
    '#required' => TRUE,
    '#size' => '80',
    '#field_suffix' => '<em style="font-size: 0.7em;">('. $rdf_mapping[$title_field->getId()]['predicates'][0] .')</em>',
  );
  $form[$description_field->getId()] = array(
    '#type'=>'text_format',
    '#title' => t($description_field->getLabel()),
    '#required' => TRUE,
    '#cols' => '80',
    '#rows' => '4',
    '#format' => 'filtered_html',
    '#field_suffix' => '<em style="font-size: 0.7em;">('. $rdf_mapping[$description_field->getId()]['predicates'][0] .')</em>',
  );
  $form[] = $break;

  $form['optional_fields'] = array(
  '#type' => 'fieldset',
    '#title' => t('Additional Fields'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  foreach ($field_instances as $instance) {
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
      '#autocomplete_path' => 'curios/manage/autocomplete_fields/'. $resource_type->name .'/'. $instance['field_name'] ,
      '#field_suffix' => '<em style="font-size: 0.7em;">('.$rdf_mapping[$instance['field_name']]['predicates'][0].')</em>',
    );
  }

  $form[] = $break;
  $form['submit'] = array('#type' => 'submit', '#value' => 'Create New Record');

  return $form;
}

/**
 * Submit handler.
 *
 * Processes the insert form and builds the set of triples to be inserted.
 */
function curios_insert_form_submit($form, &$form_state) {
  $config = curios_configuration();

  $resource_name = $form_state['values']['resource'];
  //$resource_type = sparql_views_resource_type_load($resource_name);
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  $browsing_class = $config->getResource($resource_name);
  $view_spec_id = $config->getViewIdForResource($browsing_class->getId());
  $view_spec = $config->getViewSpec($view_spec_id);
  $title_field = $config->getField($view_spec->getTitleFieldId());
  $description_field = $config->getField($view_spec->getDescriptionFieldId());

  $subject_id = __generate_new_subject_id();
  $rdf_type = $rdf_mapping['rdftype'][0];
  $triples_insert = array();

  $triples_insert[] = '      ' . $rdf_mapping['hc_subject_id']['predicates'][0]  ." \"$subject_id\"^^<http://www.w3.org/2001/XMLSchema#string>;";  // TODO 'id' field from config
  $required_fields = array($title_field->getId(), $description_field->getId());

  // Add required fields.
  foreach ($required_fields as $field_name) {
    $form_value = $form_state['values'][$field_name];

    if (is_array($form_value)) { // if using a formatter
      $form_value = $form_state['values'][$field_name]['value'];
    }

    $triples_insert[] = '      ' . $rdf_mapping[$field_name]['predicates'][0]  ." \"". __curios_escape_sparql($form_value) ."\"^^<http://www.w3.org/2001/XMLSchema#string>;";
  }

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

  $success = _curios_subject_insert($subject_id, $rdf_type, $triples_insert);

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

/**
 * Page callback.
 *
 * Displays the update form.
 */
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

/**
 * Executes the details view for a specified record, used to display the current values on the update form.
 */
function _curios_execute_details_view($resource_name, $subject_id) {
  $config = curios_configuration();
  $resource_config = $config->getResource($resource_name);
  $view_config_id = $config->getViewIdForResource($resource_name);
  $view_config = $config->getViewSpec($view_config_id);
  
  return views_get_view_result($view_config->getMachineName(), 'details', $subject_id, $resource_config->getRDFType());
}

/**
 * Executes a relationship view, used to display the current relationships in the delete relationships fieldset.
 */
function _curios_execute_relationship_view($resource_name, $relationship_name, $subject_id) {
  $config = curios_configuration();
  $resource_config = $config->getResource($resource_name);
  $view_config_id = $config->getViewIdForResource($resource_name);
  $view_config = $config->getViewSpec($view_config_id);

  return views_get_view_result($view_config->getMachineName(), 'object_'.$resource_name.'_'.$relationship_name,
      $subject_id, $resource_config->getRDFType());

  //  rendering view:
  //
  //  $filters = array('nid' => 5,'title' => 'foo');
  //$view = views_get_view('product_result_exposed');
  //$view->set_exposed_input($filters); // Set exposed filters
  //
  //$view->set_display('block_view');
  //$view->execute();
  //echo $view->render('block_view');
}

/**
 * Page callback.
 *
 * Get the resource type and id to be updated.
 */
function curios_update_page() {
  $page = array();
  $page[] = array('#markup' => "<p>Select the record type and enter the SubjectId below then click 'Next' to continue.</p>");
  $page[] = drupal_get_form('curios_manage_update_form');

  return $page;
}

/**
 * Form callback.
 *
 * The update form. This displays the existing values for a record by executing the appropriate views and using them
 * to render a form. Title, description and literal fields are single value. Relationships can be added or removed, these
 * are multivalued.
 */
function curios_update_form($form, $form_state, $resource_type, $subject_id, $view_result) {
  $config = curios_configuration();
  $browsing_class = $config->getResource($resource_type->name);
  $view_spec_id = $config->getViewIdForResource($browsing_class->getId());
  $view_spec = $config->getViewSpec($view_spec_id);
  
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_type->name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_type->name));

    // Get title and description fields from view spec.
  $title_field = $config->getField($view_spec->getTitleFieldId());
  $description_field = $config->getField($view_spec->getDescriptionFieldId());

  $views_title_field = $resource_type->name.'_'.$title_field->getId();
  $title_value = $view_result[0]->{$views_title_field};
  $views_description_field = $resource_type->name.'_'.$description_field->getId();
  $description_value = $view_result[0]->{$views_description_field};

  $form = array();
  $form['status'] = array('#markup' => "<h3>Edit: <strong>".$resource_type->label."</strong>; ID: <strong>". $subject_id ."</strong>; Name: <strong>". $title_value ."</strong></h3>");
  $form['resource'] = array('#type' => 'hidden', '#value' => $resource_type->name);
  $form['identifier'] = array('#type' => 'hidden', '#value' => $subject_id);

  $break = array('#markup' => '<br/>');

  $form[$title_field->getId()] = array(
    '#type' => 'textfield',
    '#title' => t($title_field->getLabel()),
    '#required' => TRUE,
    '#size' => '80',
    '#field_suffix' => '<em style="font-size: 0.7em;">('. $rdf_mapping[$title_field->getId()]['predicates'][0] .')</em>',
    '#default_value' => $title_value,
  );
  $form['old_'.$title_field->getId()] = array(
    '#type' => 'hidden',
    '#value' => $title_value,
  );
  $form[$description_field->getId()] = array(
    '#type'=>'text_format',
    '#title' => t($description_field->getLabel()),
    '#required' => TRUE,
    '#cols' => '80',
    '#rows' => '4',
    '#format' => 'filtered_html',
    '#field_suffix' => '<em style="font-size: 0.7em;">('. $rdf_mapping[$description_field->getId()]['predicates'][0] .')</em>',
    '#default_value' => $description_value,
  );
  $form['old_'.$description_field->getId()] = array(
    '#type' => 'hidden',
    '#value' => $description_value,
  );
  $form[] = $break;

  $form['optional_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fields / Attributes'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $relationship_options = array();

  foreach ($field_instances as $instance) {
    if (__is_identifier_field($instance) ||
        __is_title_field($instance) ||
        __is_description_field($instance) ||
        __is_special_field($instance, $config)) {
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
        '#autocomplete_path' => 'curios/manage/autocomplete_fields/'. $resource_type->name .'/'. $instance['field_name'] ,
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


  // === RELATIONSHIPS ===

  // Existing relationships.
  $form['relationship_listing_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Existing Relationships'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE, // values stored in a tree for grouping relationship fields.
    '#prefix' => '<div id="relationships-remove-fieldset-wrapper">', // for AJAX callback
    '#suffix' => '</div>',
  );

  if (empty($form_state['storage']['relationship_listing_group_remove'])) {
    $form_state['storage']['relationship_listing_group_remove'] = array();
  }

  $group_count = 0;
  foreach ($relationship_options as $relationship_id=>$relationship_label) {
    $view_results = _curios_execute_relationship_view($resource_type->name, $relationship_id, $subject_id);

    if (!empty($view_results)) {
      $form['relationship_listing_fieldset'][] = array('#markup' => "<h3>$relationship_label:</h3>");
    }

    $previous = array();
    foreach ($view_results as $relationship_value) {
      $current_group_name = 'relationship-'.$group_count;

      // TODO process results properly.
      $relationship_value = array_values((array)$relationship_value);
      $object_value = "$relationship_value[1] ($relationship_value[0])";
      if (in_array($object_value, $previous)) {
        continue;
      }

      // Textbox with current value.
      $form['relationship_listing_fieldset'][$current_group_name]['description'] = array(
        '#type' => 'textfield',
        '#title' => '',
        '#required' => FALSE,
        '#disabled' => TRUE,
        '#size' => '40',
        '#default_value' => $object_value,
      );

      if (in_array($current_group_name, $form_state['storage']['relationship_listing_group_remove'])) {
        $form['relationship_listing_fieldset'][$current_group_name]['description']['#default_value'] = "Delete: [$object_value]";
        
        $form['relationship_listing_fieldset'][$current_group_name]['remove-relationship'] = array('#type' => 'hidden', '#value' => TRUE);
        $form['relationship_listing_fieldset'][$current_group_name]['field'] = array('#type' => 'hidden', '#value' => $relationship_id);
        $form['relationship_listing_fieldset'][$current_group_name]['value'] = array('#type' => 'hidden', '#value' => $relationship_value[0]);

        $form['relationship_listing_fieldset'][$current_group_name]['undo'] = array(
            '#type' => 'submit',
            '#name' => $current_group_name,
            '#value' => t('Undo'),
            '#submit' => array('curios_update_relationship_listing_undo'),
            '#ajax' => array(
              'callback' => 'curios_update_relationship_listing_callback',
              'wrapper' => 'relationships-remove-fieldset-wrapper',
            ),
            '#limit_validation_errors' => array(),
          );
      } else {
        $form['relationship_listing_fieldset'][$current_group_name]['delete'] = array(
            '#type' => 'submit',
            '#name' => $current_group_name,
            '#value' => t("Delete"),
            '#submit' => array('curios_update_relationship_listing_remove'),
            '#ajax' => array(
              'callback' => 'curios_update_relationship_listing_callback',
              'wrapper' => 'relationships-remove-fieldset-wrapper',
            ),
            '#limit_validation_errors' => array(),
          );
      }

      $form['relationship_listing_fieldset'][] = array('#markup' => '<div class="form-row"></div>');
      $previous[] = $object_value;
      $group_count += 1;
    }
  }

  if (!isset($form['relationship_listing_fieldset'][0])) {
    $form['relationship_listing_fieldset'][] = array('#markup' => "<p>No relationships found.</p>");
  } else {
    $form['relationship_listing_fieldset']['#collapsed'] = FALSE;
  }

  // New relationships.
  $form['relationship_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Relationship'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE, //empty($form_state['storage']['relationship_group_count']), // collapsed if not used yet
    '#tree' => TRUE, // values stored in a tree for grouping relationship fields.
    '#prefix' => '<div id="relationships-create-fieldset-wrapper">', // for AJAX callback
    '#suffix' => '</div>',
  );
  $form['relationship_fieldset'][] = array('#markup' => '<p>To add a relationship, select the relationship type
      from the drop down menu and enter the SubjectId of the record in the textbox.</p>');

  if (!empty($relationship_options)) { // If this resource has relationship fields.
    if (empty($form_state['storage']['relationship_group_count'])) {
      $form_state['storage']['relationship_group_count'] = 1;
    }
    if (empty($form_state['storage']['relationship_group_remove'])) {
      $form_state['storage']['relationship_group_remove'] = array();
    }

    $relationship_group_count = $form_state['storage']['relationship_group_count'];
    for ($i = 0; $i < $relationship_group_count; $i++) {
      $current_group_name = 'relationship-'.$i;

      if (in_array($current_group_name, $form_state['storage']['relationship_group_remove'])) {
        continue; // Skip removed groups to retain numbering.
      }

      // Field select drop down.
      $form['relationship_fieldset'][$current_group_name]['field'] = array(
        '#type' => 'select',
        '#empty_option' => '- Select relationship -',
        '#required' => FALSE,
        '#options' => $relationship_options,
      );

      // Field value input.
      $form['relationship_fieldset'][$current_group_name]['value'] = array(
        '#type' => 'textfield',
        '#size' => '32',
        '#required' => FALSE,
      );

      // Add or remove button.
      if ($i < $relationship_group_count - 1) {
        $form['relationship_fieldset'][$current_group_name]['remove'] = array(
          '#type' => 'submit',
          '#name' => $current_group_name, // Allows drupal to distinguish multiple remove submit elements.
          '#value' => t('Remove'),
          '#submit' => array('curios_update_relationship_input_remove'),
          '#ajax' => array(
            'callback' => 'curios_update_relationship_input_callback',
            'wrapper' => 'relationships-create-fieldset-wrapper',
          ),
          '#limit_validation_errors' => array(),
        );
        $form['relationship_fieldset'][$current_group_name]['field']['#required'] = TRUE;
        $form['relationship_fieldset'][$current_group_name]['value']['#required'] = TRUE;
      } else {
        $form['relationship_fieldset'][$current_group_name]['add'] = array(
          '#type' => 'submit',
          '#value' => t('Add'),
          '#submit' => array('curios_update_relationship_input_add'),
          '#ajax' => array(
            'callback' => 'curios_update_relationship_input_callback',
            'wrapper' => 'relationships-create-fieldset-wrapper',
          ),
        );
      }

      $form['relationship_fieldset'][] = array('#markup' => '<div class="form-row"></div>');
    }
  } else {
    $form['relationship_fieldset'][] = array('#markup' => "<p>No relationship fields have been defined for this record type.</p>");
  }

  // Form controls.

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

/** Ajax callback. */
function curios_update_relationship_listing_callback($form, $form_state) {
  return $form['relationship_listing_fieldset'];
}
/** Ajax callback. */
function curios_update_relationship_listing_remove($form, &$form_state) {
  $form_state['storage']['relationship_listing_group_remove'][] = $form_state['triggering_element']['#name'];
  $form_state['rebuild'] = TRUE;
}
/** Ajax callback. */
function curios_update_relationship_listing_undo($form, &$form_state) {
  $remove = function($value) use (&$form_state) { return $value != $form_state['triggering_element']['#name']; };
  $form_state['storage']['relationship_listing_group_remove'] = array_filter($form_state['storage']['relationship_listing_group_remove'], $remove);
  $form_state['rebuild'] = TRUE;
}
/** Ajax callback. */
function curios_update_relationship_input_add($form, &$form_state) {
  $form_state['storage']['relationship_group_count'] += 1;
  $form_state['rebuild'] = TRUE;
}
/** Ajax callback. */
function curios_update_relationship_input_callback($form, $form_state) {
  return $form['relationship_fieldset'];
}
/** Ajax callback. */
function curios_update_relationship_input_remove($form, &$form_state) {
  $form_state['storage']['relationship_group_remove'][] = $form_state['triggering_element']['#name'];
  $form_state['rebuild'] = TRUE;
}


// VALIDATION HANDLERS

/**
 * Form validation handler.
 *
 * Validates the relationships in the update form. The relationships value is checked syntactically, and the relationship
 * is validated against the configuration.
 */
function curios_update_form_validate($form, &$form_state) {
  $resource_name = $form_state['values']['resource'];

  // Validate relationships.
  $relationships = $form_state['values']['relationship_fieldset'];
  array_pop($relationships);

  foreach ($relationships as $field_name=>$relationship) {
    $error_field_name = "relationship_fieldset][$field_name][value";

    if (!__curios_valid_id($relationship['value'])) {
      form_set_error($error_field_name, t('Relationship value is not a valid subject id.'));
    } else if (!_curios_is_valid_relationship_assertion($resource_name, $relationship['field'], $relationship['value'])) {
      form_set_error($error_field_name, 'Relationship type is not valid for subject '. $relationship['value']. '.');
    }
  }
}

/**
 * Uses the relationship targets defined in the configuration to check whether a relationship is valid.
 */
function _curios_is_valid_relationship_assertion($resource_name, $relationship_name, $subject_id) {
  $config = curios_configuration();
  $resource = $config->getResource($resource_name);
  $targets = $resource->getRelationshipTargets($relationship_name);

  $rdf_types = _curios_fetch_subject_types($subject_id);
  foreach ($rdf_types as $type) {
    $candidate_resource = __curios_resource_id_from_class_uri($type, $config);

    if ($candidate_resource && in_array($candidate_resource, $targets)) {
      return TRUE;
    }
  }

  return FALSE;
}



// SUBMIT HANDLERS

/* Update */

/**
 * Submit handler.
 *
 * Processes the update form and generates the tripled to be added/removed.
 */
function curios_update_form_submit($form, &$form_state) {
  $config = curios_configuration();

  $resource_name = $form_state['values']['resource'];
  $subject_id = $form_state['values']['identifier'];

  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  $browsing_class = $config->getResource($resource_name);
  $view_spec_id = $config->getViewIdForResource($browsing_class->getId());
  $view_spec = $config->getViewSpec($view_spec_id);
  $title_field = $config->getField($view_spec->getTitleFieldId());
  $description_field = $config->getField($view_spec->getDescriptionFieldId());

  $triples_delete = array();
  $triples_insert = array();

  $required_fields = array($title_field->getId(), $description_field->getId());

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

  // Add new relationships - last 'add' item is ignored.
  $relationships = $form_state['values']['relationship_fieldset'];
  array_pop($relationships);
  
  foreach ($relationships as $relationship) {
    $predicate = $rdf_mapping[$relationship['field']]['predicates'][0];
    $triples_insert[] = '      '. $predicate .' hc:'. $relationship['value'] ." ;\n";
  }
  
  // Remove existing relationships.
  $relationships = isset($form_state['values']['relationship_listing_fieldset']) ? $form_state['values']['relationship_listing_fieldset'] : array();
  
  foreach ($relationships as $relationship) {
    if (isset($relationship['remove-relationship'])) {
      $predicate = $rdf_mapping[$relationship['field']]['predicates'][0];
      $triples_delete[] = '      '. $predicate .' hc:'. $relationship['value'] ." ;\n";
    }
  }

  $triples_insert = array_unique($triples_insert);
  $triples_insert = join("\n", $triples_insert);
  $triples_delete = array_unique($triples_delete);
  $triples_delete = join("\n", $triples_delete);

  // Submit form.
  if (!empty($triples_delete) || !empty($triples_insert)) {
    $success = _curios_subject_update($subject_id, $triples_insert, $triples_delete);

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

/**
 * Ajax callback.
 *
 * Returns a list of matching values for a literal field input autocomplete.
 */
function curios_autocomplete_fields($resource_name, $field_name, $q = '') {
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];

  $class_name = $rdf_mapping['rdftype'][0];
  $property_name = $rdf_mapping[$field_name]['predicates'][0];

  // Fetch property values.
  $key = __curios_hash($class_name, $property_name);
  $values = phpFastCache::get($key);

  if ($values == NULL) {
    $rs = _curios_fetch_property_values($class_name, $property_name);
    $values = array();

   	if ($rs != NULL) {
			foreach ($rs['result']['rows'] as $row) {
			  $values[$row['value']] = check_plain($row['value']);
			}
		}
  }
  phpFastCache::set($key, $values, 600);

  // Find matches.
  $match_function = function($value) use (&$q) { return startsWith_ncasecmp($q, $value); };
  $matches = array_filter($values, $match_function);

  drupal_json_output($matches);
}

/** Generates a new subject id for the insert page. */
function __generate_new_subject_id() { return intval(_curios_fetch_max_identifier()) + 1; }

// FIXME the conditions in the below functions should eventually be part of the config.
//       update 20130808: the latest version generated in curios_ldcms has most of these definitions
//                        now built in.

// FIXME really hacky way of detecting sparql_view_related_resource's
//     This entity type is defined as a sub type of sparql_views_resource in SPARQL Views,
//     but all that I can get back from the API is its widget type to identify it...
function __is_resource_field($field_instance) { return $field_instance['widget']['type'] == 'options_select'; }

function __is_identifier_field($field_instance) { return $field_instance['field_name'] == 'hc_subject_id'; }
function __is_title_field($field_instance) { return ($field_instance['field_name'] == 'dc_title' || $field_instance['field_name'] == 'hc_english_name' || $field_instance['field_name'] == 'hc_title'); }
function __is_description_field($field_instance) { return ($field_instance['field_name'] == 'dc_description' || $field_instance['field_name'] == 'hc_description'); }
function __is_special_field($field_instance, $config) { return $field_instance['field_name'] == $config->getImageRelationshipFieldId(); }