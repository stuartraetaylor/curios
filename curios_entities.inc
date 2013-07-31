<?php

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


class RDFResource extends DrupalThing {

  private $rdf_type;
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

  public function addField($field) { $this->fields[] = $field; }
  public function addRelationship($relationship) { $this->relationships[] = $relationship; }
  public function setRelationshipTargets($relationship_id, $target_id) {
    $this->relationship_targets[$relationship_id] = (array)$target_id;
  }
  public function getRelationshipTargets() { return $this->relationship_targets; }

}


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


class RDFView extends DrupalThing {

  private $path;
  private $browsing_class_curie;
  private $resource;
  private $title_field;
  private $description_field;
  private $required_data_fields;
  private $optional_data_fields;
  private $optional_object_fields;

  public function __construct($machine_name, $label, $path, $browsing_class_curie, $resource, $title_field, $description_field,
      array $required_data_fields = array(), array $optional_data_fields = array(), array $optional_object_fields = array()) {
    parent::__construct($machine_name, $label);
    $this->path = $path;
    $this->browsing_class_curie = $browsing_class_curie;
    $this->resource = $resource;
    $this->title_field = $title_field;
    $this->description_field = $description_field;
    $this->required_data_fields = $required_data_fields;
    $this->optional_data_fields = $optional_data_fields;
    $this->optional_object_fields = $optional_object_fields;
  }

  public function getBrowsingClassCURIE() { return $this->browsing_class_curie; }
  public function getPath() { return $this->path; }
  public function getTitleField() { return $this->title_field; }
  public function getDescriptionField() { return $this->description_field; }
  public function getResource() { return $this->resource; }

  public function getRequiredDataFields() { return $this->required_data_fields; }
  public function getOptionalDataFields() { return $this->optional_data_fields; }
  public function getObjectFields() { return $this->optional_object_fields; }

  public function setOptionalAll() {
    // Data fields.
    foreach ($this->resource->getDataFields() as $rdf_field) {
        // DEBUG:
        if ($rdf_field == NULL) { echo $this->getId() ."\n"; }
      if (!in_array($rdf_field->getMachineName(), $this->required_data_fields)) {
        $this->optional_data_fields[] = $rdf_field->getMachineName();
      }
    }

    // Object fields.
    foreach ($this->resource->getObjectFields() as $rdf_field) {
      $this->optional_object_fields[] = $rdf_field->getMachineName();
    }
  }

  public function getPageDescription() {
    return 'From this page you can browse and search the Hebridean Connections repository.';
  }

}


class LDCMSConfiguration {

  private $endpoints = array();
  private $prefixToNamespaceMap = array();
  private $namespaceToPrefixMap = array();

  private $fields = array();
  private $resources = array();
  private $views = array();
  private $resourceToViewMap = array();

  function getCMSID($ontology_entity) {
    // id function
    return __curios_id_from_uri($ontology_entity, $this);
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

  //function setFields(array $fields) { $this->fields = $fields; }
  //function setResources(array $resources) { $this->resources = $resources; }
  //function setViews(array $views) { $this->views = $views; }

  function addField($field) { $this->fields[$field->getId()] = $field; }
  function addResource($resource) { $this->resources[$resource->getId()] = $resource; }
  function addView($view) { $this->views[$view->getId()] = $view; }

  function getFields() { return $this->fields; }
  function getResources() { return $this->resources; }
  function getViews() { return $this->views; }

  function getField($id) { return $this->fields[$id]; }
  function getResource($id) { return $this->resources[$id]; }
  function getView($id) { return $this->views[$id]; }

  function setResourceToViewMap(array $resourceToViewMap) { $this->resourceToViewMap = $resourceToViewMap; }
  function getResourceToViewMap() { return $this->resourceToViewMap; }
  function getViewForResource($resource_id) { return $this->resourceToViewMap[$resource_id]; }

  function toString_dump() {
    var_dump($this->resourceToViewMap);
    print '<hr/>';
    var_dump($this->resources);
    print '<hr/>';
    var_dump($this->views);
   }

//function addFields(array $fields) { array_merge($this->fields, $fields); }
}
