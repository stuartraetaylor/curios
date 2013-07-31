<?php

function _curios_configuration_TEST($use_cache = FALSE) {
  $config = &drupal_static(__FUNCTION__);

  // Get the configuration from the cache.
  if (!isset($config)) {
    $cache = cache_get('curios-config');
    $config = ($cache && $use_cache) ? $cache->data : __curios_renew_cache_configuration();
    //dpr($config);
  }

  return $config;
}

function __curios_renew_cache_configuration() {
  $config = __curios_create_configuration();
  cache_set('curios-config', $config, 'cache', CACHE_PERMANENT);

  return $config;
}

function __curios_create_configuration() {
  $config = new LDCMSConfiguration();
  $config_spec = __curios_load_configuration_spec();
  $config->setPrefixToNamespaceMap($config_spec['namespaces']);

  $config->setEndpoints(array(
    'dataset' => array(
      'query' => 'http://localhost:3030/dataset/query',
      'update' => 'http://localhost:3030/dataset/update',
    ),
    'config' => array(
      'query' => 'http://localhost:3030/ldcms-config/query',
      'update' => 'http://localhost:3030/ldcms-config/update',
    ),
  ));

  __curios_configuration_fields($config, $config_spec);
  __curios_configuration_resources_views($config, $config_spec);

  return $config;
}

function __curios_load_configuration_spec() {
  require_once 'config/hebridean.inc';

  $config_spec = array(
    'namespaces' => $namespaces,
    'fields' => $fields,
    'browsing_classes' => $browsing_classes,
    'field_assignments' => $field_assignments,
    'relationship_assignment' => $relationship_assignments,
  );

  return $config_spec;
}

function __curios_configuration_fields($config, $config_spec) {
  //$rs = __curios_sparql_fetch_unique_fields_relationships($config);
  foreach ($config_spec['fields'] as $row) {
    $property = $row['property'];

    $id = $config->getCMSID($property);
    $predicate = __curios_curie_from_uri($property, $config);
    $label = isset($row['label']) ? $row['label'] : __curios_label_from_uri($property, $config);

    $config->addField(new RDFField($id, $label, $predicate, $row['type']));
  }
}

function __curios_configuration_resources_views($config, $config_spec) {
  $resourceToViewMap = array();

  $dc_title_uri = $config->getPrefixToNamespaceMap('dc').'title';
  $dc_description_uri = $config->getPrefixToNamespaceMap('dc').'description';

  // Create resources and views for all browsing classes.
  //$rs = __curios_sparql_fetch_browsing_classes($config);
  foreach ($config_spec['browsing_classes'] as $row) {
    // View corresponding to browsing class.
    $browsing_class_uri = $row['uri'];
    $browsing_class_curie = __curios_curie_from_uri($browsing_class_uri, $config);
    $view_label = $row['label'];
    $view_id = $config->getCMSID($browsing_class_uri);
    $view_path = __curios_path_from_uri($browsing_class_uri, $config);

    // Resource corresponding to base class.
    $base_resource = $row['base'];
    $resource_id = $config->getCMSID($base_resource);
    $resource_label =  __curios_label_from_uri($base_resource, $config);
    $resource_type = __curios_curie_from_uri($base_resource , $config);
    $resourceToViewMap[$resource_id] = $view_id;

    // Title field.
    $title_property = $dc_title_uri;//$row['titleField'];
    $title_field_id = $config->getCMSID($title_property);
    $title_field = $config->getField($title_field_id);

    // Description field.
    $description_property = $dc_description_uri;//$row['descriptionField'];
    $description_field_id = $config->getCMSID($description_property);
    $description_field = $config->getField($description_field_id);

    $config->addResource(new RDFResource($resource_id, $resource_label, $resource_type));
    $config->addView(new RDFView($view_id, $view_label, $view_path, $browsing_class_curie, $config->getResource($resource_id), $title_field, $description_field));
  }
  $config->setResourceToViewMap($resourceToViewMap);

  // Set fields and relationships for resources and views.
  foreach ($config->getResources() as $resource) {
    $view_id = $config->getViewForResource($resource->getId());
    $view = $config->getView($view_id);
    $browsing_class = $view->getBrowsingClassCURIE();

    // Add fields.
    //$rs = __curios_sparql_fetch_fields($browsing_class, $config);
    foreach ($config_spec['field_assignments'][$browsing_class] as $row) {
      $property = $row; //$row['p'];

      $field_id = $config->getCMSID($property);
      $field = $config->getField($field_id);

      $resource->addField($field);
    }

    // Add relationships.
    //$rs = __curios_sparql_fetch_relationships($browsing_class, $config);
    foreach ($config_spec['relationship_assignments'][$browsing_class] as $row) {
      $property = $row['property'];
      $target = (array)$row['target'];

      $relationship_id = $config->getCMSID($property);
      $relationship = $config->getField($relationship_id); // TODO should be $config->getRelationship
      $resource->addRelationship($relationship);

      $targets = array();
      foreach ($target as $t) {
        $targets[] = $config->getCMSID($t);
      }

      $resource->setRelationshipTarget($relationship_id, $targets);
    }
dpr($config); return;
    // Set field/relationship preferences.
    $view->setOptionalAll();
  }

}
