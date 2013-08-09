<?php

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
  private $type;

  public function __construct($machine_name, $label, $rdf_predicate, $type) {
    parent::__construct($machine_name, $label);
    $this->rdf_predicate = $rdf_predicate;
    $this->type = $type;
  }

  public function getRDFPredicate() { return $this->rdf_predicate; }
  public function getType() { return $this->type; }

}

/**
 * RDFViewSpec provides some additional information to the Views API to determine
 * how a browsing class (RDFResource) should be displayed.
 */
class RDFViewSpec extends DrupalThing {

  private $path;
  private $browsing_class_curie;
  private $resource;
  private $title_field_id;
  private $description_field_id;
  private $required_data_fields;
  private $optional_data_fields;
  private $optional_object_fields;

  public function __construct($machine_name, $label, $path, $browsing_class_curie, $resource, $title_field, $description_field,
      array $required_data_fields = array(), array $optional_data_fields = array(), array $optional_object_fields = array()) {
    parent::__construct($machine_name, $label);
    $this->path = $path;
    $this->browsing_class_curie = $browsing_class_curie;
    $this->resource = $resource;
    $this->title_field_id = $title_field;
    $this->description_field_id = $description_field;
    $this->required_data_fields = $required_data_fields;
    $this->optional_data_fields = $optional_data_fields;
    $this->optional_object_fields = $optional_object_fields;
  }

  public function getBrowsingClassCURIE() { return $this->browsing_class_curie; }
  public function getBrowsingClassName() { return preg_replace('/^ldcms_/', '', $this->getId()); }
  public function getPath() { return $this->path; }
  public function getTitleFieldId() { return $this->title_field_id; }
  public function getDescriptionFieldId() { return $this->description_field_id; }
  public function getResource() { return $this->resource; }

  public function getRequiredDataFields() { return $this->required_data_fields; }
  public function getOptionalDataFields() { return $this->optional_data_fields; }
  public function getObjectFields() { return $this->optional_object_fields; }

  public function setOptionalAll() {
    // Data fields.
    foreach ($this->resource->getDataFields() as $rdf_field) {
      if ($rdf_field == NULL) { // DEBUG.
        dd("Error: Invalid field declaration in {$this->getId()}.");
        var_dump($this->resource->getDataFields());
      }

      if (!in_array($rdf_field->getMachineName(), $this->required_data_fields)) {
        $this->optional_data_fields[] = $rdf_field->getMachineName();
      }
    }

    // Object fields.
    foreach ($this->resource->getObjectFields() as $rdf_field) {
      if ($rdf_field == NULL) { // DEBUG.
        dd("Error: Invalid field declaration in {$this->getId()}.");;
        var_dump($this->resource->getObjectFields());
      }

      $this->optional_object_fields[] = $rdf_field->getMachineName();
    }
  }

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

  private $title_field_id = NULL;
  private $description_field_id = NULL;
  private $image_relationship_field_id = NULL;

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
  function getResources() { return $this->resources; }
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
  
  function setTitleFieldId($title_field_id) { $this->title_field_id = $title_field_id; }
  function getTitleFieldId() { return $this->title_field_id; }

  function setDescriptionFieldId($description_field_id) { $this->description_field_id = $description_field_id; }
  function getDescriptionFieldId() { return $this->description_field_id; }

  function setImageRelationshipFieldId($image_relationship_field) { $this->image_relationship_field_id = $image_relationship_field; }
  function getImageRelationshipFieldId() { return $this->image_relationship_field_id; }

  function toString_dump() {
    var_dump($this->resourceToViewMap);
    print '<hr/>';
    var_dump($this->resources);
    print '<hr/>';
    var_dump($this->views);
   }

//function addFields(array $fields) { array_merge($this->fields, $fields); }
}
