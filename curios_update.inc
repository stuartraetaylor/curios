<?php

// PAGES

/* Update */
function curios_update_form_page($resource_name, $subject_id) {
  $page = array();
  $page[] = array('#markup' => '<h2>CURIOS Update Form Page</h2>');
  $page[] = drupal_get_form('curios_update_form', $resource_name, $subject_id);
  return $page;
}

/* Insert */
function curios_insert_page() {
  $page = array();
  $page[] = array('#markup' => '<h2>CURIOS Insert Form Page</h2>');

  $resources = entity_load('sparql_views_resource_type');
  $resource_list = '';
  foreach ($resources as $entity) {
    $resource_list .= '<li><a href="/curios/insert/'. $entity->name . '">' . $entity->name . '</a></li>';
  }

  $page[] = array('#markup' => "<ul>$resource_list</ul>");
  return $page;
}

function curios_insert_form_page($resource_name) {
  $page = array();
  $page[] = array('#markup' => '<h2>CURIOS Insert Form Page</h2>');
  $page[] = drupal_get_form('curios_insert_form', $resource_name);
  return $page;
}

/* Delete */
function curios_delete_form_page() {
  $page = array();

  $page[] = array('#markup' => '<h2>CURIOS Delete Form Page</h2>');
  $page[] = drupal_get_form('curios_delete_form');
  return $page;
}


// FORMS

/* Update */
function curios_update_form($form, $form_state, $resource_name, $subject_id) {
  $resource_type = sparql_views_resource_type_load($resource_name);
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  // Look up configuration and execute view.
  $config = _curios_configuration();
  $resource_config = $config['rdf_resources'][$resource_name];
  $view_config = _curios_get_view($resource_name);
  //$view = views_get_view('hc_boats');
  $view_result = views_get_view_result($view_config->getMachineName(), 'details', $subject_id, $resource_config->getRDFType());

  $form = array();
  $form['status'] = array('#markup' => "<h3>Update: <em>".$resource_type->label." ".$subject_id." (".$subject_id." : ".$resource_type->name.")</em></h3>");
  $form['resource'] = array('#type' => 'hidden', '#value' => $resource_name);
  $form['identifier'] = array('#type' => 'hidden', '#value' => $subject_id);

  foreach ($field_instances as $instance) {
    //$block['content'] .= '<p><label style="display: inline-block; font-weight: bold; width: 280px;">'.$instance['label'].':</label>';
    //$block['content'] .= '<input type="text" name="'.$instance['field_name'].'"/>&nbsp;&nbsp;';
    //$block['content'] .= '';
    $results_field = $resource_name.'_'.$instance['field_name'];
    $value = empty($view_result[0]->$results_field) ? '' : $view_result[0]->$results_field;

    $form[$instance['field_name']] = array(
      '#type' => 'textfield',
      '#default_value' => $value,
      '#title' => t($instance['label']),
      '#field_suffix' => '<em style="font-size: 0.7em;">('.$rdf_mapping[$instance['field_name']]['predicates'][0].')</em>',
    );

    $form['old_'.$instance['field_name']] = array(
      '#type' => 'hidden',
      '#value' => $value,
    );
  }

  $form['submit'] = array('#type' => 'submit', '#value' => 'Submit');
  $form['reset'] = array('#markup' => '<input type="reset" class="form-submit" />');

  return $form;
}

/* Insert */
function curios_insert_form($form, $form_state, $resource_name) {//dpm($form_state);
  $resource_type = sparql_views_resource_type_load($resource_name);
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  $form = array();
  $form['status'] = array('#markup' => "<h3>Add new: <em>".$resource_type->label." (".$resource_type->name.")</em></h3>");
  $form['resource'] = array('#type' => 'hidden', '#value' => $resource_name);

  $form['identifier'] = array(
    '#type' => 'textfield',
    '#title' => t('Identifier'),
  );

  foreach ($field_instances as $instance) {
    //$block['content'] .= '<p><label style="display: inline-block; font-weight: bold; width: 280px;">'.$instance['label'].':</label>';
    //$block['content'] .= '<input type="text" name="'.$instance['field_name'].'"/>&nbsp;&nbsp;';
    //$block['content'] .= '';

    $form[$instance['field_name']] = array(
      '#type' => 'textfield',
      '#title' => t($instance['label']),
      '#field_suffix' => '<em style="font-size: 0.7em;">('.$rdf_mapping[$instance['field_name']]['predicates'][0].')</em>',
    );
  }

  $form['submit'] = array('#type' => 'submit', '#value' => 'Submit');
  $form['reset'] = array('#markup' => '<input type="reset" class="form-submit" />');

  return $form;
}

/* Delete */
function curios_delete_form($form, $form_state) {//dpm($form_state);
  $form = array();
  $form['subject_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject Id'),
  );

  $form['submit'] = array('#type' => 'submit', '#value' => 'Delete');

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

  // Calculate difference.
  $triples_delete = '';
  $triples_insert = '';
  foreach ($field_instances as $instance) {
    $form_value_new = $form_state['values'][$instance['field_name']];
    $form_value_old = $form_state['values']['old_'.$instance['field_name']];

    if ($form_value_new != $form_value_old) {
      $triples_delete .= '      ' . $rdf_mapping[$instance['field_name']]['predicates'][0]  ." \"$form_value_old\";\n";
      $triples_insert .= '      ' . $rdf_mapping[$instance['field_name']]['predicates'][0]  ." \"$form_value_new\";\n";
    }
  }

  if (!empty($triples_delete)) {
    __curios_subject_update($subject_id, $triples_insert, $triples_delete);
  } else {
    drupal_set_message(t('No fields to update.'));
  }
}

/* Submit */
function curios_insert_form_submit($form, &$form_state) {
  $resource_name = $form_state['values']['resource'];
  //$resource_type = sparql_views_resource_type_load($resource_name);
  $entity_info = entity_get_info('sparql_views_resource');
  $rdf_mapping = $entity_info['bundles'][$resource_name]['rdf_mapping'];
  $field_instances = field_read_instances(array(
    'entity_type' => 'sparql_views_resource',
    'bundle' => $resource_name,));

  $subject_id = $form_state['values']['identifier'];
  $rdf_type = $rdf_mapping['rdftype'][0];
  $triples_insert = '';
  foreach ($field_instances as $instance) {
    $form_value = $form_state['values'][$instance['field_name']];
    if (!empty($form_value)) {
      $triples_insert .= '      ' . $rdf_mapping[$instance['field_name']]['predicates'][0]  ." \"$form_value\";\n";
    }
  }

  __curios_subject_insert($subject_id, $rdf_type, $triples_insert);
}

/* Delete */
function curios_delete_form_submit($form, &$form_state) {
  $subject_id = $form_state['values']['subject_id'];
  __curios_subject_delete($subject_id);
}
