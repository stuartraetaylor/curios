<?php

function curios_admin() {
  $form = array();

  $form['example_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Current LDCMS configuration'),
    '#default_value' => 'hebridean.inc',
    '#size' => 20,
    '#description' => t("The browsing class mappings used for the LDCMS."),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

function curios_admin_validate($form, &$form_state) {
  form_set_error('example_field', t('Functionality not implemented yet.'));
}
