<?php

/**
 * Linked Data CMS sample configuration file.
 *
 * The LDCMS mapping uses this configuration to generate a Drupal site that can
 * be used to maintain instances of OWL classes stored in an RDF triple store.
 *
 * The configuration based around a set of entites classed browsing classes.
 * Each browsing class is used to provide a view of a particular OWL class,
 * by mapping a set of object and datatype properties to fields and relationships
 * in Drupal.
 *
 * A field is a literal value, that is mapped to a Drupal field A relationship 
 * is used as a reference to another browsing class in the configuration. The
 * relationships are used to provide links between pages in Drupal.
 *
 * This file provides a sample LDCMS configuration, with some explanation about each
 * entity as they are defined.
 */

// Namespaces used throughout the configuration.
$namespaces = array(
  'ex' => 'http://example.org/example.owl#',
  'dc' => 'http://purl.org/dc/terms/',
);

/* 
 * Options that are used in the mapping.
 * This list can be extended to pass extra options into the LDCMS mapping.
 */
$options = array(
  // The top level class used to provide a default view high level view of
  // all individuals in the triple store. This class  should be a super
  // class of all other classes in the configuration.
  'default_class' => 'ex:Entity',

  // Class of images related via image_relationship_property.
  'image_class' => 'ex:Image',

  // Relationship used to link individuals to image pages.
  'image_relationship_property' => 'ex:hasImage',

  // ID property used for mapping URIs to local identifiers.
  // Currently the system assumes that individuals have a numeric local name,
  // with a matching id property in the dataset.
  'id_property' => 'ex:id',

  // Title property used for all pages.
  // For example, to generate titles from a person's name, add the following 
  // triple to your dataset: ex:yourNameProperty rdfs:subClassOf dc:title.
  'title_property' => 'dc:title',

  // Optional description property used for all pages.
  'description_property' => 'dc:description',
);


/* 
 * Literal values to be mapped to Drupal fields.
 * 
 * Fields have a property URI, that uses the prefixes defined in $namespaces;
 * a human readable label used in the Drupal interface;
 * and a type, which is either 'text' for datatype properties or 'relationship'
 * for object properties (links between pages in Drupal).
 *
 * The properties used in $options must also be defined here.
 */
$fields[] = array(
  'property' => 'dc:title',     // OWL datatype property.
  'label'    => 'Title',        // Human readable label.
  'type'     => 'text',         // Type of field (text or relationship).
);
$fields[] = array(
  'property' => 'dc:description',
  'label'    => 'Description',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'ex:id',
  'label'    => 'Identifier',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'ex:nick',
  'label'    => 'Nickname',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'ex:dateOfBirth',
  'label'    => 'DOB',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'ex:imageURL',
  'label'    => 'URL',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'ex:knows',
  'label'    => 'Knows',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'ex:worksAt',
  'label'    => 'Works At',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'ex:employs',
  'label'    => 'Employs',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'ex:hasImage',
  'label'    => 'Pictures',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'ex:shows',
  'label'    => 'Shows',
  'type'     => 'relationship',
);


/*
 * The browsing classes correspond to sets of pages about specific
 * classes in Drupal. Each browsing class has a base class 'class' 
 * to identify the corresponding class in the ontology.
 * 'name' should be a valid Drupal machine name, i.e., all lower case,
 * underscores can be used between words.
 */

$browsing_classes[] = array(   // Images details browsing class.
  'name'  => 'image_details',  // Name to identify this browsing class.
  'label' => 'Image Details',  // Human readable label used in Drupal.
  'class'  => 'ex:Image',       // Corresponding class in the ontology.
  'title' => 'dc:title',
  'description' => 'dc:description',
);
$browsing_classes[] = array( // The browsing class for ex:Entity used in default_class.
  'name'  => 'entity',
  'label' => 'All Entities',
  'class'  => 'ex:Entity',
  'title' => 'dc:title',
  'description' => 'dc:description',
);
$browsing_classes[] = array(
  'name'  => 'person',
  'label' => 'People',
  'class'  => 'ex:Person',
  'title' => 'dc:title',
  'description' => 'dc:description',
);
$browsing_classes[] = array(
  'name'  => 'business',
  'label' => 'Businesses',
  'class'  => 'ex:Business',
  'title' => 'dc:title',
  'description' => 'dc:description',
);
$browsing_classes[] = array(
  'name'  => 'university',
  'label' => 'Universities',
  'class'  => 'ex:University',
  'title' => 'dc:title',
  'description' => 'dc:description',
);


/**
 * Each item in $field_assignments assigns a set of fields
 * to a particular browsing class. 
 *
 * The name field of the browsing class is used as the key. 
 * Each field should have a corresponding entry in the $field array.
 */
$field_assignments['entity'] = array(
    'dc:title',
    'dc:description',
    'ex:id',
);
$field_assignments['image_details'] = array(
    'dc:title',
    'dc:description',
    'ex:id',
    'ex:imageURL',
);
$field_assignments['person'] = array(
    'dc:title',
    'dc:description',
    'ex:id',
);
$field_assignments['business'] = array(
    'dc:title',
    'dc:description',
    'ex:id',
);
$field_assignments['university'] = array(
    'dc:title',
    'dc:description',
    'ex:id',
);


/**
 * Each item in $relationship_assignments assigns a set of relationships
 * to a particular browsing class. 
 *
 * The name field of the browsing class is used as the key. 
 * Each relationship should have a corresponding entry in the $field array.
 * The target property specifies the target class for the relationship -
 * i.e., there should be a browsing class defined with this class as its base class.
 * The value for target can be a single class name, or an array of class names if
 * the relationship has multiple targets.
 */
$relationship_assignments['person'][] = array(
    'property'  => 'ex:knows',
    'target'    => 'ex:Person',
);
$relationship_assignments['person'][] = array(
    'property'  => 'ex:worksAt',
    'target'    => array('ex:Business', 'ex:University'),
);
$relationship_assignments['person'][] = array(
    'property'  => 'ex:hasImage',
    'target'    => 'ex:Image',
);

$relationship_assignments['business'][] = array(
    'property'  => 'ex:employs',
    'target'    => 'ex:Person',
);

$relationship_assignments['university'][] = array(
    'property'  => 'ex:employs',
    'target'    => 'ex:Person',
);

$relationship_assignments['image_details'][] = array(
    'property'  => 'ex:shows',
    'target'    => 'ex:Person',
);

$relationship_assignments['entity'][] = array(
    'property'  => 'ex:hasImage',
    'target'    => 'ex:Image',
);

