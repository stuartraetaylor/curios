<?php

/**
 * Implementation of hook_default_panels_layout()
 */
function curios_default_panels_layout() {
  $layouts = array();

  $layout = new stdClass;
  $layout->disabled = FALSE; /* Edit this to true to make a default layout disabled initially */
  $layout->api_version = 1;
  $layout->name = 'hc_subject_page_layout';
  $layout->admin_title = 'Subject Page Layout';
  $layout->admin_description = '';
  $layout->category = 'CURIOS';
  $layout->plugin = 'flexible';
  $layout->settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 2,
          1 => 3,
        ),
        'parent' => 'main',
        'class' => '',
      ),
      2 => array(
        'type' => 'column',
        'width' => '80',
        'width_type' => '%',
        'parent' => 'main-row',
        'children' => array(
          0 => 4,
          1 => 6,
        ),
        'class' => 'Col #1',
      ),
      3 => array(
        'type' => 'column',
        'width' => '20',
        'width_type' => '%',
        'parent' => 'main-row',
        'children' => array(
          0 => 5,
        ),
        'class' => 'Col #2',
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'properties_region',
        ),
        'parent' => '2',
        'class' => '',
      ),
      5 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'relationships_region',
        ),
        'parent' => '3',
        'class' => '',
      ),
      'properties_region' => array(
        'type' => 'region',
        'title' => 'Properties Region',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => 'curios-properties',
      ),
      'relationships_region' => array(
        'type' => 'region',
        'title' => 'Relationships Region',
        'width' => 100,
        'width_type' => '%',
        'parent' => '5',
        'class' => 'curios-relationships',
      ),
      6 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'image_gallery_region',
        ),
        'parent' => '2',
        'class' => '',
      ),
      'image_gallery_region' => array(
        'type' => 'region',
        'title' => 'Image Gallery Region',
        'width' => 100,
        'width_type' => '%',
        'parent' => '6',
        'class' => 'curios-image-gallery',
      ),
    ),
  );
  $layouts['subject_page_layout'] = $layout;

  return $layouts;
}
