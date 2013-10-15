<?php
/*
 * curios_ldcms.inc
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

require_once('curios_functions.inc');
require_once('curios_sparql.inc');

/**
 * Loads the configuration spec and creates the LDCMSConfiguration.
 */
function curios_configuration($config_file = NULL) {
  $config = &drupal_static(__FUNCTION__);

  if (!isset($config)) {
    $config_spec = curios_load_configuration_spec($config_file);
    $config = curios_create_configuration($config_spec);
  }

  return $config;
}

/**
 * Creates an LDCMSConfiguration from a config spec.
 */
function curios_create_configuration($config_spec) {
  $config = new LDCMSConfiguration();
  $config->setPrefixToNamespaceMap($config_spec['namespaces']);
  $config->setEndpoints(curios_endpoints());

  __curios_configuration_options($config, $config_spec);
  __curios_configuration_fields($config, $config_spec);
  __curios_configuration_resources_views($config, $config_spec);

  return $config;
}

/**
 * Sets values in LDCMSConfiguration from $options.
 */
function __curios_configuration_options($config, $config_spec) {
  // Title field.
  $title_field_id = $config->getCMSID($config_spec['options']['title_property']);
  $config->setTitleFieldId($title_field_id);

  // Description field.
  $description_field_id = $config->getCMSID($config_spec['options']['description_property']);
  $config->setDescriptionFieldId($description_field_id);

  // Owner field.
  $owner_field_id = $config->getCMSID($config_spec['options']['owner_property']);
  $config->setOwnerFieldId($owner_field_id);

  // Maintainer field.
  $maintainer_field_id = $config->getCMSID($config_spec['options']['maintainer_property']);
  $config->setMaintainerFieldId($maintainer_field_id);

  // Published field.
  $published_field_id = $config->getCMSID($config_spec['options']['published_property']);
  $config->setPublishedFieldId($published_field_id);

  // Image relationship field.
  $image_relationship_id = $config->getCMSID($config_spec['options']['image_relationship_property']);
  $config->setImageRelationshipFieldId($image_relationship_id);

  // URL field.
  $url_field_id = $config->getCMSID($config_spec['options']['url_property']);
  $config->setURLFieldId($url_field_id);
}

/**
 * Creates field and relationship objects for each field in the config spec.
 */
function __curios_configuration_fields($config, $config_spec) {
  // __curios_sparql_fetch_unique_fields_relationships($config);
  foreach ($config_spec['fields'] as $row) {
    $property = $row['property'];

    $id = $config->getCMSID($property);
    $label = isset($row['label']) ? $row['label'] : __curios_label_from_curie($property, $config);
    $type = __curios_translate_field_type($row['type']);

    $config->addField(new RDFField($id, $label, $property, $type));
  }
}

/**
 * Mapping between field types used in the config spec and field types in Drupal.
 */
function __curios_translate_field_type($field_type) {
  switch ($field_type) {
    case 'relationship':
      return 'sparql_views_related_resource';
      break;
    case 'text':
    default:
      return 'text';
  }
}

function __curios_browsing_class_id_from_name($name) {
  return 'ldcms_'.$name; }

/**
 * Creates RDFResource and RDFView instances from the browsing classes defined in the config spec.
 */
function __curios_configuration_resources_views($config, $config_spec) {
  $resourceToViewMap = array();
  $baseClassToResourceMap = array();

  $global_title_field = $config->getField($config->getTitleFieldId());
  $global_description_field = $config->getField($config->getDescriptionFieldId());

  $owner_field = $config->getField($config->getOwnerFieldId());
  $maintainer_field = $config->getField($config->getMaintainerFieldId());
  $published_field = $config->getField($config->getPublishedFieldId());

  // Create resources and views for all browsing classes.
  // __curios_sparql_fetch_browsing_classes($config);
  foreach ($config_spec['browsing_classes'] as $row) {
    // View corresponding to browsing class.
    $browsing_class_name = $row['name'];
    $browsing_class_id = __curios_browsing_class_id_from_name($browsing_class_name);
    $browsing_class_label = $row['label'];
    $view_path = __curios_path_from_cmsid($browsing_class_id);

    // Resource corresponding to base class.
    $base_class_curie = $row['class'];
    $resource_id = $config->getCMSID($base_class_curie);
    $resource_label =  __curios_label_from_curie($base_class_curie, $config);
    $resourceToViewMap[$resource_id] = $browsing_class_id;
    $baseClassToResourceMap[$base_class_curie] = $resource_id;

    // Add local title and description fields.
    $title_property = $row['title'];
    $title_field = $config->getCMSID($title_property);
    $description_property = $row['description'];
    $description_field = $config->getCMSID($description_property);

    $config->addResource(new RDFResource($resource_id, $resource_label, $base_class_curie));
    $config->addViewSpec(new RDFViewSpec($browsing_class_id, $browsing_class_label, $view_path, NULL, $config->getResource($resource_id), $title_field, $description_field));
  }
  $config->setResourceToViewMap($resourceToViewMap);
  $config->setBaseClassToResourceMap($baseClassToResourceMap);

  // Set fields and relationships for resources and views.
  foreach ($config->getResources() as $resource) {
    $view_id = $config->getViewIdForResource($resource->getId());
    $view = $config->getViewSpec($view_id);
    $browsing_class_name = $view->getBrowsingClassName();

    // Add fields.
    // __curios_sparql_fetch_fields($browsing_class, $config);
    foreach ($config_spec['field_assignments'][$browsing_class_name] as $row) {
      $property = $row; //$row['p'];

      $field_id = $config->getCMSID($property);
      $field = $config->getField($field_id);

      $resource->addField($field);
    }

    // Add global title and description fields.
    $resource->addField($global_title_field);
    $resource->addField($global_description_field);

    // Add record metadata fields.
    $resource->addField($owner_field);
    $resource->addField($maintainer_field);
    $resource->addField($published_field);

    // Add relationships.
    // __curios_sparql_fetch_relationships($browsing_class, $config);
    foreach ($config_spec['relationship_assignments'][$browsing_class_name] as $row) {
      $property = $row['property'];
      $target = (array)$row['target'];

      $relationship_id = $config->getCMSID($property);
      $relationship = $config->getField($relationship_id); // TODO should be $config->getRelationship
      $resource->addRelationship($relationship);
      
      $target_id_function = function($t) use (&$config) { return $config->getCMSID($t); };
      $targets = array_map($target_id_function, $target);

      $resource->setRelationshipTargets($relationship_id, $targets);
    }

    // Attach fields and relationships to the view spec.
    $field_ids = array();
    foreach ($resource->getDataFields() as $field) {
      if ($field->getId() == $maintainer_field->getId() || $field->getId() == $published_field->getId()) {
        continue;
      }

      $field_ids[] = $field->getId();
    }

    $relationship_ids = array();
    foreach ($resource->getObjectFields() as $relationship) {
      $relationship_ids[] = $relationship->getId();
    }

    $view->setFieldIds($field_ids);
    $view->setRelationshipIds($relationship_ids);
  }
  
}

/**
 * Loads the config spec.
 *
 * If the config spec has not be previously loaded, it is read from a file in the config/ directory.
 */
function curios_load_configuration_spec($config_file = NULL) {
  $force_renew = ($config_file != NULL);
  $config_file = _curios_check_config_file($config_file);

  $config_spec = NULL;
  if (!$force_renew) { // Attempt to read existing config spec.
    $config_spec = curios_load_configuration_spec_from_database($config_file);
  }

  if ($config_spec == NULL || $force_renew) { // Renew configuration.
    $config_spec = curios_load_configuration_from_file($config_file);

    // Update database.
    db_merge('curios_config')
      ->key(array('file' => $config_file))
      ->fields(array('data' => serialize($config_spec)))
      ->execute();
  }

  return $config_spec;
}

/**
 * Loads the config spec from a the specified file.
 */
function curios_load_configuration_from_file($config_file) {
  require "config/$config_file";

  $config_spec = array(
    'namespaces' => $namespaces,
    'options' => $options,
    'fields' => $fields,
    'browsing_classes' => $browsing_classes,
    'field_assignments' => $field_assignments,
    'relationship_assignments' => $relationship_assignments,
  );

  return $config_spec;
}

/**
 * Loads a previously loaded config spec from the database.
 */
function curios_load_configuration_spec_from_database($config_file) {
  $results = db_select('curios_config', 'c')
    ->fields('c')
    ->condition('file', $config_file, '=')
    ->execute()
    ->fetchAssoc();

  return empty($results) ? NULL : unserialize($results['data']);
}

/**
 * Determines the config file name, falls back to sample.ldcms.inc.
 */
function _curios_check_config_file($config_file) {
  if ($config_file == NULL) {
    $current_config_file = variable_get('ldcms_config');
    $config_file = ($current_config_file == NULL) ? 'sample.ldcms.inc' : $current_config_file;
  }

  return $config_file;
}