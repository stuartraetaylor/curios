<?php

abstract class DrupalThing {
  
  private $machine_name;
  private $label;
  
  public function __construct($machine_name, $label) {
    $this->machine_name = $machine_name;
    $this->label = $label;
  }
  
  public function getMachineName() { return $this->machine_name; }
  public function getLabel() { return $this->label; }
  
}


class RDFResource extends DrupalThing {

  private $rdf_type;
  private $data_fields;
  private $object_fields;
  private $object_field_ranges; // field_name => resource_name

  public function __construct($machine_name, $label, $rdf_type, array $data_fields = array(), array $object_fields = array(), array $object_field_ranges = array()) {
    parent::__construct($machine_name, $label);
    $this->rdf_type = $rdf_type;
    $this->data_fields = $data_fields;
    $this->object_fields = $object_fields;
    $this->object_field_ranges = $object_field_ranges;
  }

  public function getRDFType() { return $this->rdf_type; }
  public function getDataFields() { return $this->data_fields; }
  public function getObjectFields() { return $this->object_fields; }
  public function getObjectFieldRanges() { return $this->object_field_ranges; }
  public function getFields() { return array_merge($this->data_fields, $this->object_fields); }

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
  private $resource;
  private $required_data_fields;
  private $optional_data_fields;
  private $optional_object_fields;
  
  public function __construct($machine_name, $label, $path, $resource, 
      array $required_data_fields = array(), array $optional_data_fields = array(), array $optional_object_fields = array()) {
    parent::__construct($machine_name, $label);
    $this->path = $path;
    $this->resource = $resource;
    $this->required_data_fields = $required_data_fields;
    $this->optional_data_fields = $optional_data_fields;
    $this->optional_object_fields = $optional_object_fields;
  }
  
  public function getPath() { return $this->path; }
  public function getResource() { return $this->resource; }
  public function getRequiredDataFields() { return $this->required_data_fields; }
  public function getOptionalDataFields() { return $this->optional_data_fields; }
  public function getObjectFields() { return $this->optional_object_fields; }
  
  public function setOptionalAll() {
    // Data fields.
    foreach ($this->resource->getDataFields() as $rdf_field) {
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
    return 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor, nisi id ultrices feugiat, enim eros auctor massa, et dictum lectus lorem mollis neque.';
  }
  
}
