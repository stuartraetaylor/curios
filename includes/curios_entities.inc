<?php
/*
 * curios_entities.inc
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
 * Top entity in the LDCMS.
 *
 * Each entity has an identifier (machine name) and a label.
 */
abstract class DrupalThing {

  private $id;
  private $label;

  public function __construct($id, $label) {
    $this->id = $id;
    $this->label = $label;
  }

  public function getId() { return $this->id; }
  public function getLabel() { return $this->label; }
  public function getMachineName() { return $this->getId(); }

}

/**
 * An RDFResource corresponds to a browsing class in the configuration.
 *
 * Each RDFResource has a base class, a set of fields, and a set of relationships.
 */
class RDFResource extends DrupalThing {

  private $rdf_type; // base class.
  private $fields;
  private $relationships;
  private $relationship_targets; // relationship_id => target_resource_id.
  private $sub_types; // label => rdf type.

  public function __construct($machine_name, $label, $rdf_type, array $fields = array(), array $relationships = array(), array $relationship_targets = array(), $sub_types = array()) {
    parent::__construct($machine_name, $label);
    $this->rdf_type = $rdf_type;
    $this->fields = $fields;
    $this->relationships = $relationships;
    $this->relationship_targets = $relationship_targets;
    $this->sub_types = $sub_types;
  }

  public function getRDFType() { return $this->rdf_type; }
  public function getDataFields() { return $this->fields; }
  public function getObjectFields() { return $this->relationships; }
  public function getObjectFieldRanges() { return $this->relationship_targets; }
  public function getSubTypes() { return $this->sub_types; }
  public function getFields() { return array_merge($this->fields, $this->relationships); }


  // Methods following LDCMS naming convention.

  public function getBaseClass() { return $this->rdf_type; }
  public function addField($field) { $this->fields[] = $field; }
  public function addRelationship($relationship) { $this->relationships[] = $relationship; }
  public function setRelationshipTargets($relationship_id, array $targets) {
    $this->relationship_targets[$relationship_id] = $targets;
  }
  
  public function getRelationshipTargets($relationship_field = NULL) {
    if ($relationship_field != NULL) {
      return $this->relationship_targets[$relationship_field];
    } else {
      return $this->relationship_targets;
    }
  }

}

/**
 * RDFField corresponds to a field or relationships.
 *
 * Fields and relationships are distinguished by their type attribute.
 */
class RDFField extends DrupalThing {

  private $rdf_predicate;
  private $drupal_field_type;
  private $ldcms_type;

  public function __construct($machine_name, $label, $rdf_predicate, $drupal_field_type, $ldcms_type) {
    parent::__construct($machine_name, $label);
    $this->rdf_predicate = $rdf_predicate;
    $this->drupal_field_type = $drupal_field_type;
    $this->ldcms_type = $ldcms_type;
  }

  public function getRDFPredicate() { return $this->rdf_predicate; }
  public function getEntityType() { return $this->entity_type; }
  public function getDrupalFieldType() { return $this->drupal_field_type; }
  public function getLDCMSType() { return $this->ldcms_type; }
  public function getType() { return $this->getLDCMSType(); }

}

/**
 * RDFViewSpec provides some additional information to the Views API to determine how a browsing class (RDFResource)
 * should be displayed.
 *
 * Originally there was only one display per view spec in the module. Currently the data_fields and object_fields
 * collections are used to specify which fields are displayed in the proprerties display only.
 */
class RDFViewSpec extends DrupalThing {

  private $path;
  private $browsing_class_curie;
  private $resource;
  private $title_field_id;
  private $description_field_id;
  private $data_fields = array();
  private $object_fields = array();

  public function __construct($machine_name, $label, $path, $browsing_class_curie, $resource, $title_field, $description_field) {
    parent::__construct($machine_name, $label);
    $this->path = $path;
    $this->browsing_class_curie = $browsing_class_curie;
    $this->resource = $resource;
    $this->title_field_id = $title_field;
    $this->description_field_id = $description_field;
  }

  public function getBrowsingClassCURIE() { return $this->browsing_class_curie; }
  public function getBrowsingClassName() { return preg_replace('/^ldcms_/', '', $this->getId()); }
  public function getPath() { return $this->path; }
  public function getTitleFieldId() { return $this->title_field_id; }
  public function getDescriptionFieldId() { return $this->description_field_id; }
  public function getResource() { return $this->resource; }


  public function setFieldIds($field_ids) { return $this->data_fields = $field_ids; }
  public function getFieldIds() { return $this->data_fields; }
  public function setRelationshipIds($relationship_ids) { $this->object_fields = $relationship_ids; }
  public function getRelationshipIds() { return $this->object_fields; }

  public function getDataFields() { return $this->getFieldIds(); }
  public function getObjectFields() { return $this->getRelationshipIds(); }

  public function getPageDescription() {
    return 'From this page you can browse and search the Hebridean Connections repository.';
  }

}

/**
 * Linked Data CMS Configuration.
 *
 * The configuration consists of a set of browsing classes (RDFResource), view specifications (RDFViewSpec), fields (RDFField),
 * relationships (RDFField). There are also has tables to map between browsing classes and views specifications, prefixes,
 * namespaces etc.
 *
 * The configuration is generated from a configuration file by the mapping algorithm in curios_ldcms.inc.
 */
class LDCMSConfiguration {

  private $endpoints = array();
  private $prefixToNamespaceMap = array();
  private $namespaceToPrefixMap = array();

  private $fields = array();
  private $resources = array();
  private $views = array();
  private $resourceToViewMap = array();
  private $baseClassToResourceMap = array();

  private $date_range_resource = NULL;
  private $date_range_from_id = NULL;
  private $date_range_to_id = NULL;

  private $title_field_id = NULL;
  private $description_field_id = NULL;
  private $image_resource_id = NULL;
  private $image_relationship_field_id = NULL;
  private $url_field_id = NULL;
  private $owner_field_id = NULL;
  private $maintainer_field_id = NULL;
  private $published_field_id = NULL;

  private $identifier_field_id = NULL;
  private $default_resource_id = NULL;
  private $default_namespace = NULL;

  function getCMSID($ontology_entity, $is_curie = TRUE) {  // id function
    return $is_curie ? 
      __curios_cmsid_from_curie($ontology_entity, $this) :
      __curios_cmsid_from_uri($ontology_entity, $this);
  }

  function setEndpoints(array $endpoints) { $this->endpoints = $endpoints; }
  function setPrefixToNamespaceMap(array $namespaces) {
    $this->prefixToNamespaceMap = $namespaces;
    $this->namespaceToPrefixMap = array();

    foreach ($this->prefixToNamespaceMap as $prefix=>$ns) {
      $this->namespaceToPrefixMap[$ns] = $prefix;
    }
  }

  function getEndpoints() { return $this->endpoints; }
  function getPrefixToNamespaceMap() { return $this->prefixToNamespaceMap; }
  function getNamespaceToPrefixMap() { return $this->namespaceToPrefixMap; }

  function getNamespace($prefix) { return $this->prefixToNamespaceMap[$prefix]; }
  function getPrefix($namespace) { return $this->namespaceToPrefixMap[$namespace]; }

  function addField($field) { $this->fields[$field->getId()] = $field; }
  function addResource($resource) { $this->resources[$resource->getId()] = $resource; }
  function addViewSpec($view) { $this->views[$view->getId()] = $view; }

  function getFields() { return $this->fields; }
  function getResources($include_daterange = FALSE) {
    if ($include_daterange) {
      return array_merge($this->resources, array($this->getDateRangeResource()));
    }

    return $this->resources;
  }
  function getViews() { return $this->views; }

  function getField($id) { return $this->fields[$id]; }
  function getResource($id) { return $this->resources[$id]; }
  function getViewSpec($id) { return $this->views[$id]; }

  function setResourceToViewMap(array $resourceToViewMap) { $this->resourceToViewMap = $resourceToViewMap; }
  function getResourceToViewMap() { return $this->resourceToViewMap; }
  function getViewIdForResource($resource_id) { return $this->resourceToViewMap[$resource_id]; }

  function setBaseClassToResourceMap(array $baseClassToResourceMap) { $this->baseClassToResourceMap = $baseClassToResourceMap; }
  function getBaseClassToResourceMap() { return $this->baseClassToResourceMap; }
  function getResourceForBaseClass($base_class_curie) {
    return isset($this->baseClassToResourceMap[$base_class_curie]) ? $this->baseClassToResourceMap[$base_class_curie] : NULL;
  }

  function setDefaultNamespace($default_namespace) { $this->default_namespace = $default_namespace; }
  function getDefaultNamespace() { return $this->default_namespace; }

  function setDateRangeResource($date_range_resource) { $this->date_range_resource = $date_range_resource; }
  function getDateRangeResource() { return $this->date_range_resource; }

  function setDateRangeFromId($date_range_from_id) { $this->date_range_from_id = $date_range_from_id; }
  function getDateRangeFromId() { return $this->date_range_from_id; }

  function setDateRangeToId($date_range_to_id) { $this->date_range_to_id = $date_range_to_id; }
  function getDateRangeToId() { return $this->date_range_to_id; }

  function setImageResourceId($image_resource_id) { $this->image_resource_id = $image_resource_id; }
  function getImageResourceId() { return $this->image_resource_id; }
  
  function setDefaultResourceId($default_resource_id) { $this->default_resource_id = $default_resource_id; }
  function getDefaultResourceId() { return $this->default_resource_id; }
  
  function setTitleFieldId($title_field_id) { $this->title_field_id = $title_field_id; }
  function getTitleFieldId() { return $this->title_field_id; }

  function setDescriptionFieldId($description_field_id) { $this->description_field_id = $description_field_id; }
  function getDescriptionFieldId() { return $this->description_field_id; }

  function setImageRelationshipFieldId($image_relationship_field) { $this->image_relationship_field_id = $image_relationship_field; }
  function getImageRelationshipFieldId() { return $this->image_relationship_field_id; }

  function setURLFieldId($url_field) { $this->url_field_id = $url_field; }
  function getURLFieldId() { return $this->url_field_id; }

  function setOwnerFieldId($owner_field_id) { $this->owner_field_id = $owner_field_id; }
  function getOwnerFieldId() { return $this->owner_field_id; }

  function setMaintainerFieldId($maintainer_field_id) { $this->maintainer_field_id = $maintainer_field_id; }
  function getMaintainerFieldId() { return $this->maintainer_field_id; }

  function setPublishedFieldId($published_field_id) { $this->published_field_id = $published_field_id; }
  function getPublishedFieldId() { return $this->published_field_id; }

  function setIdentifierFieldId($identifier_field_id) { $this->identifier_field_id = $identifier_field_id; }
  function getIdentifierFieldId() { return $this->identifier_field_id; }

  function toString_dump() {
    var_dump($this->resourceToViewMap);
    print '<hr/>';
    var_dump($this->resources);
    print '<hr/>';
    var_dump($this->views);
   }

//function addFields(array $fields) { array_merge($this->fields, $fields); }
}
