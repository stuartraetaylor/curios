<?php
require('curios_field_install.inc');

/**
 * Implements hook_admin.
 *
 * Admin settings form found at admin/structure/ldcms.
 */
function curios_admin() {
  $form = array();

  $config_files = _curios_config_file_list();

  $form['config_files'] = array(
    '#type' => 'select',
    '#title' => t('LDCMS configuration file'),
    '#empty_option' => '- Select File -',
    '#default_value' => variable_get('ldcms_config'),
    '#required' => TRUE,
    '#options' => $config_files,
  );

//  $form['quick'] = array(
//    '#type' => 'checkbox',
//    '#title' => t('Quick mode (perform a shallow diff on field and relationship assignments).'),
//  );

  $form['full'] = array(
    '#type' => 'checkbox',
    '#title' => t('Full reload of all Drupal entities (use this if you have modified any field or browsing class definitions).'),
    '#attributes' => array('checked' => 'checked'),
  );
  
  $form['remove_only'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove only, do not create new entities (uninstall mode).'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Load Configuration',
  );

  return $form;
}

/**
 * Implements hook_admin_submit.
 *
 * Submit handler, triggers (re)loading of the configuration, creation of fields, resources etc.
 */
function curios_admin_submit($form, &$form_state) {
  $config_file_previous = variable_get('ldcms_config');
  $config_file_new = $form_state['values']['config_files'];
  variable_set('ldcms_config', $config_file_new);

  // Load old configuration.
  $config_previous = NULL;
  if ($config_file_previous != NULL) {
    $config_data_previous = curios_load_configuration_spec_from_database($config_file_previous);
    
    if ($config_data_previous != NULL) {
      $config_previous = curios_create_configuration($config_data_previous);
    }
  }

  // Load new configuration.
  $config_data_new = curios_load_configuration_spec($config_file_new);
  $config_new = curios_create_configuration($config_data_new);

  if ($form_state['values']['full']) { // Add/remove fields.
    _curios_update_entity_batch_start($config_previous, $config_new, $form_state['values']['remove_only']);
  } else {
    drupal_set_message('Configuration values reloaded.');
  }
}

/**
 * List configuration files.
 *
 * Returns file names matching: config/CONFIG-NAME.ldcms.inc
 */
function _curios_config_file_list() {
  $config_path = drupal_get_path('module', 'curios') . '/config';

  $valid_files = function($f) {
    return preg_match('/^[a-z0-9].*.ldcms.inc$/i', $f);
  };

  $config_files = array_filter(scandir($config_path), $valid_files);
  $config_files = array_combine($config_files, $config_files);

  return $config_files;
}
