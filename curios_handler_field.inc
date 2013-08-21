<?php
/*
 * curios_handler_field.inc
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
 
/**
 * Field handler to rewrite link targets generated in curios.views.inc.
 */
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
    $target_view = $config->getViewSpec($targets[$subject_id]);
    $target_path = $target_view->getPath();
    $this->options['alter']['path'] =  $target_path. strstr($this->options['alter']['path'], '/');
    return parent::render($values);
  }
}

/**
 * Field handler to output HTML that displays thumbnail images using Timthumb and Lightbox.
 */
class curios_image_thumbnail_field extends views_handler_field {

  function query() {
    $this->field_alias = 'curios_image_thumb_' . $this->position;
  }

  function render($values) {
    $timthumb_path = '/' . drupal_get_path('module', 'curios') . '/scripts/timthumb.php';
    $w = '260';

    $image_url = $values->{'hc_imagefile_hc_url'};
    $image_url = str_replace('http://www.hebrideanconnections.com/', 'http://www.dotrural.ac.uk/curiosdemo/', $image_url);
    $title = $values->{$this->options['title_field']};

    if (isset($this->options['disable_thumbnail']) && $this->options['disable_thumbnail'] = TRUE) { // Display full size image.
      $image_output = "<a href=\"$image_url\" title=\"$title\" rel=\"lightbox[gallery]\"><img src=\"$image_url\" alt=\"$title\" /></a>";
    } else { // Generate thumbnail.
      $timthumb_url = $timthumb_path . "?w=$w&src=" . urlencode($image_url);
      $image_output = "<a href=\"$image_url\" title=\"$title\" rel=\"lightbox[gallery]\"><img src=\"$timthumb_url\" width=\"$w\" alt=\"$title\" /></a>";
    }

    return $image_output;
  }
}
