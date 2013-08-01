<?php
//function curios_views_pre_build(&$view) { }
//function curios_views_pre_execute(&$view) { }
//function curios_views_pre_render(&$view) { }
//function curios_views_post_render(&$view, &$output, &$cache) { }
//function curios_views_pre_view(&$view, &$display_id, &$args) { }
//function mymodule_views_handlers() { }

function curios_views_data() {
  $data = array();
  $data['views']['curios_link_target_rewriter'] = array(
    'title' => t('Link Target Rewriter'),
    'help' => t('Rewrites link target based on the ontology.'),
    'field' => array(
      'help' => t('CURIOS custom field handler.'),
      'handler' => 'curios_handler_field',
    ),
  );
  return $data;
}


function curios_views_pre_render(&$view) {
  _curios_views_link_target_rewriter($view);
  _curios_view_rewrite_title($view);
}

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
        $config = _curios_configuration();
        $view_spec = $config->getView($view->name);
        $resource_id = $view_spec->getResource()->getId();
        $title_field = $config->getTitleField();
        $field = $resource_id.'_'.$title_field;
        drupal_set_title($view->result[0]->{$field});
        break;
    }
  }
}

function curios_views_pre_view(&$view, &$display_id, &$args) {
  if ($view->name == "foo" && $view->current_display == "bar") {
    //$view->display[$view->current_display]->display_options["title"] = "THE TITLE";
    //$view->display[$view->current_display]->handler->options["title"] = "The New Title";
  }
}

function _curios_views_link_target_rewriter(&$view) {
  $display_name = $view->current_display;
  $display = $view->display[$display_name];

  if (!empty($view->result) && startsWith('object_', $display_name) && $display->display_options['curios']['rewrite_object_target'] == TRUE) {
    // Get resource for this view.
    $config = _curios_configuration();
    $view_spec = $config->getView($view->name);
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
      $target_view = $config->getViewForResource($target_resource);

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



