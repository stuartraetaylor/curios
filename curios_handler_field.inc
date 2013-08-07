<?php

class curios_link_target_rewriter extends views_handler_field {

  /**
   * Implements views_handler_field#query().
   */
  function query() {
    $this->field_alias = 'curios_rewrite_link_' . $this->position;
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

class curios_image_thumbnail_field extends views_handler_field {

  function query() {
    $this->field_alias = 'curios_image_thumb_' . $this->position;
  }

  function render($values) {
    $timthumb_path = '/' . drupal_get_path('module', 'curios') . '/scripts/timthumb.php';
    $w = '260';

    $image_url = $values->{'hc_imagefile_hc_url'};
    $image_url = str_replace('http://www.hebrideanconnections.com/', 'http://www.dotrural.ac.uk/curiosdemo/images/', $image_url);
    $title = $values->{$this->options['title_field']};

    $timthumb_url = $timthumb_path . "?w=$w&src=" . urlencode($image_url);
    $image_output = "<a href=\"$image_url\" title=\"$title\" rel=\"lightbox[gallery]\"><img src=\"$timthumb_url\" width=\"$w\" alt=\"$title\" /></a>";
    
    return $image_output;
  }
}
