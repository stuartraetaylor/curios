<?php
class curios_handler_field extends views_handler_field {

  /**
   * Implements views_handler_field#query().
   */
  function query() {
    $this->field_alias = 'curios_rewrite_link' . $this->position;
    //$this->view->views_php = TRUE;
  }

  /**
   * Implements views_handler_field#render().
   */
  function render($values) {
    // Replace the link target path.
    $config = curios_configuration();
    $display = $this->view->display[$this->view->current_display];
    $targets = $display->display_options['curios']['relationship_targets'];
    $subject_id = $values->{'hc_subject_hc_subject_id'};
    $target_view = $config->getView($targets[$subject_id]);
    $target_path = $target_view->getPath();
    $this->options['alter']['path'] =  $target_path. strstr($this->options['alter']['path'], '/');
    return parent::render($values);
  }
}
