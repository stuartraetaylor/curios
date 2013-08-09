<?php

/**
 * Implements hook_views_data.
 *
 * Declare custom field handlers.
 */
function curios_views_data() {
  $data = array();
  $data['views']['curios_link_target_rewriter'] = array(
    'title' => t('Link Target Rewriter'),
    'help' => t('Rewrites link target based on the ontology.'),
    'field' => array(
      'help' => t('CURIOS link target rewriter.'),
      'handler' => 'curios_link_target_rewriter',
    ),
  );
  $data['views']['curios_image_thumbnail_field'] = array(
    'title' => t('Image thumbnail field'),
    'help' => t('Displays images with thumbnails using Timthumb.'),
    'field' => array(
      'help' => t('CURIOS image thumbnail field.'),
      'handler' => 'curios_image_thumbnail_field',
    ),
  );
  return $data;
}

/**
 * Implements hook_view_pre_render.
 *
 * This hook fires after the query has run and before the view is rendered.
 */
function curios_views_pre_render(&$view) {
  _curios_views_link_target_rewriter($view);
  _curios_view_rewrite_title($view);
}

/**
 * Rewrite the page title based on the current panel varient and view being displayed.
 */
function _curios_view_rewrite_title(&$view) {
  if (startsWith('ldcms_', $view->name)) {
    // Remove h1 title.
    drupal_add_css('#page-title { display: none; }', array('type' => 'inline'));

    // Set page title.
    switch ($view->current_display) {
      case 'listing':
        drupal_set_title($view->human_name);
        break;
      case 'summary':
        if (!empty($view->result)) {
          $config = curios_configuration();
          $view_spec = $config->getViewSpec($view->name);
          $resource_id = $view_spec->getResource()->getId();
          $title_field = $config->getTitleFieldId();

          drupal_set_title($view->result[0]->{$resource_id.'_'.$title_field});
        }
        
        break;
    }
  }
}

/**
 * Rewrite the link target for relationships with multiple targets.
 *
 * Certain relationships (such as associatedWith) have multiple targets (e.g., hc_person, hc_business etc.).
 * This function uses the class assertions from the ontology and the relationship targets specified in the configuration
 * to determine the most appropriate relationship target page at runtime.
 */
function _curios_views_link_target_rewriter(&$view) {
  $display_name = $view->current_display;
  $display = $view->display[$display_name];

  if (!empty($view->result) && startsWith('object_', $display_name) && $display->display_options['curios']['rewrite_object_target'] == TRUE) {
    // Get resource for this view.
    $config = curios_configuration();
    $view_spec = $config->getViewSpec($view->name);
    $resource = $view_spec->getResource();
    $resource_name = $resource->getMachineName();

    // Uses the relationship declaration from the view to find the relationship field object.
    $view_relationship = reset($display->display_options['relationships']);
    $field_id = substr($view_relationship['field'], strlen($resource_name)+1); // non-typed field name.
    $ranges = $resource->getObjectFieldRanges();

    // Possible targets for this view.
    $available_target_resources = $ranges[$field_id];

    // Find types for each subject and rewrite link target.
    $types = __group_object_result_types($view->result);

    foreach ($types as $target_individual=>$individual_types) {
      // Find resource names for each class from query.
      $candidate_targets = array();
      foreach ($individual_types as $rdf_class) {
        $candidate_resource = __curios_resource_id_from_class_uri($rdf_class, $config);

        if ($candidate_resource) {
          $candidate_targets[] = $candidate_resource;
        }
      }

      // Find target resource from candidate resources.
      $intersect = array_intersect($candidate_targets, $available_target_resources);
      $target_resource = !empty($intersect) ? reset($intersect) : 'hc_subject'; // pick one or fall back to subject.

      // Rewrite link using target resource path.
      $target_view = $config->getViewIdForResource($target_resource);

      // Remove extra results.
      $duplicates = count($types[$target_individual])-1;
      $removed = 0;
      foreach ($view->result as $key=>$result) {
        if ($duplicates == $removed) {
          break;
        }

        if ($result->{'hc_subject_hc_subject_id'} == $target_individual) {
          unset($view->result[$key]);
          $removed += 1;
        }
      }

      // Finally update the pager and set our result.
      // FIXME this misses results since the paged queries have LIMIT
      $view->total_rows -= $removed;
      //$view->query->pager->total_items -= $removed;
      //$view->query->pager->update_page_info();

      // Let the display know about the new relationship targets to be passed to the custom field handler.
      $display->display_options['curios']['relationship_targets'][$target_individual] = $target_view;
    }
  }
}

function __group_object_result_types($results) {
  $types = array();
  foreach ($results as $result) {
    $types[$result->{'hc_subject_hc_subject_id'}][] = $result->{'hc_subject_type'};
  }
  return $types;
}



