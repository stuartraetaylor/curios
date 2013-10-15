<?php
/*
 * curios_sparql.inc
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
 * Global SPARQL endpoints declaration.
 */
function curios_endpoints() {
  $endpoints = array(
    'dataset' => array(
      'query' => 'http://localhost:3030/dataset/query',
      'update' => 'http://localhost:3030/dataset/update',
    ),
    //'config' => array(
    //  'query' => 'http://localhost:3030/ldcms-config/query',
    //  'update' => 'http://localhost:3030/ldcms-config/update',
    //),
  );

  return $endpoints;
}

/**
 * Queries the SPARQL endpoint.
 */
function __curios_sparql_query($query, $endpoint = 'dataset') {
  $endpoints = curios_endpoints();
  $query = __curios_sparql_append_prefixes($query);
  $rs = sparql_request($query, (object)array('uri' => $endpoints[$endpoint]['query']));

  if ($rs != NULL) {
    return $rs;
  } else {
    drupal_set_message("SPARQL endpoint error", 'error');
  }
}

/**
 * Updates the SPARQL endpoint.
 */
function __curios_sparql_update($query, $endpoint = 'dataset') {
  $endpoints = curios_endpoints();
  $query = __curios_sparql_append_prefixes($query);
  $rs = sparql_request($query, (object)array('uri' => $endpoints[$endpoint]['update']));

  return ($rs != NULL);
}

/**
 * Appends the prefixes defined in the configuration to a SPARQL query.
 */
function __curios_sparql_prefixes() {
  $config = curios_configuration();
  
  $prefixes = '';
  $prefixes .= "prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n";
  $prefixes .= "prefix owl:<http://www.w3.org/2002/07/owl#>\n";

  foreach ($config->getPrefixToNamespaceMap() as $prefix=>$ns) {
    $prefixes .= "prefix $prefix: <$ns>\n";
  }

  return $prefixes;
}

function __curios_sparql_append_prefixes($query) {
  return __curios_sparql_prefixes() . $query;
}

function __curios_escape_sparql($s) {
  return trim(addcslashes($s, "\"\r\n"));
}

/**
 * Inserts and deletes triples for an individual.
 */
function _curios_subject_update($subject_id, $triples_insert, $triples_delete) {
  $query = '';

  if (!empty ($triples_delete)) {
    $query .= "DELETE {\n";
    $query .= "  ?subject ";
    $query .= $triples_delete;
    $query .= " } \n";
  }

  if (!empty ($triples_insert)) {
    $query .= "INSERT {\n";
    $query .= "  ?subject ";
    $query .= $triples_insert;
    $query .= " } \n";
  }

  $query .= "WHERE {\n";
  $query .= "  ?subject ?p ?o \n";
  $query .= "  FILTER ( ?subject = hc:$subject_id ) }";

  return __curios_sparql_update($query);
}

/**
 * Creates a new individiual.
 */
function _curios_subject_insert($subject_id, $rdf_type, $triples_insert) {
  $query = '';
  $query .= "INSERT DATA {\n";
  $query .= "  hc:$subject_id a ". $rdf_type .";\n";
  //$query .= "      hc:subjectID \"$identifier\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
  $query .= $triples_insert;
  $query .= '}';

  return __curios_sparql_update($query);
}

/**
 * Removes an individual.
 */
function _curios_subject_delete($subject_id) {
  // TODO should use subject id field.
  $subject_id = __curios_escape_sparql($subject_id);

  $query = '';
  $query .= "DELETE { ?subject ?p ?o }\n";
  $query .= "WHERE {\n";
  $query .= "  ?subject ?p ?o .\n";
  $query .= "  FILTER ( ?subject = hc:$subject_id ) }";

  return __curios_sparql_update($query);
}

/**
 * Finds the highest subject_id used in the triple stores.
 */
function _curios_fetch_max_identifier() {
  $query = '';
  $query .= "select ?id where {\n";
  $query .= "  [] hc:subjectID ?id .}\n";
  $query .= "order by desc(strlen(?id)) desc(?id)\n";
  $query .= "limit 1";

  $rs = __curios_sparql_query($query);
  if ($rs != NULL) {
    return $rs['result']['rows'][0]['id'];
  } else {
    return -1;
  }
}

/**
 * Returns an array of recently inserted subject_id's.
 */
function _curios_latest_record_identifiers($n = 10) {
  $query = <<<EOT
select ?id ?title where {
  [] hc:subjectID ?id ;
     dc:title ?title .
}
order by desc(strlen(?id)) desc(?id)
limit $n
EOT;

  $rs = __curios_sparql_query($query);
  $identifiers = array();

  if ($rs != NULL) {
    foreach ($rs['result']['rows'] as $row) {
      $identifiers[$row['id']] = $row['title'];
    }
  }

  return $identifiers;
}

/**
 * Returns all values for the specified property. 
 */
function _curios_fetch_property_values($class, $property) {
  $query = '';
  $query .= "select distinct ?value where { \n";
  $query .= "[] a $class ; \n";
  $query .= "  $property ?value . \n";
  $query .= "} limit 500";

    return __curios_sparql_query($query);
}

/**
 * Returns all types for a specified individual.
 */
function _curios_fetch_subject_types($subject_id) {
  $query = "select ?type where { hc:$subject_id a ?type . ?type a owl:Class }";
  $rs = __curios_sparql_query($query);

  $classes = array();
  foreach ($rs['result']['rows'] as $row) {
    $classes[] = $row['type'];
  }

  return $classes;
}

//function _curios_is_valid_property_assertion($domain_class, $property, $range_individual) {
//  $query = <<<EOT
//# Check individual is in the range of the specified property for the specified class.
//select ?range where  {
//  [] a owl:ObjectProperty ;
//      rdfs:subPropertyOf $property ;
//      rdfs:domain $domain_class ;
//      rdfs:range ?range .
//  hc:$range_individual a ?range .
//} limit 1
//EOT;
//
//    $rs = __curios_sparql_query($query, 'dataset');
//    return ($rs != NULL && !empty($rs['result']['rows']));
//}
//
//// -- CONFIGURATION --
//
//function __curios_sparql_fetch_browsing_classes() {
//  $sparql = <<<EOT
//# Get all Browsing Classes
//select ?b ?base ?label ?titleField ?descriptionField where {
//  ?b a cms:BrowsingClass ;
//    cms:baseClass ?base ;
//    rdfs:label ?label ;
//    cms:field [
//      a cms:Title ;
//      cms:property ?titleField ] ;
//    cms:field [
//      a cms:Description ;
//      cms:property ?descriptionField ] .
//}
//EOT;
//
//  return __curios_sparql_query($sparql, 'config');
//}
//
//function __curios_sparql_fetch_unique_fields_relationships() {
//  $sparql = <<<EOT
//# Fetch all UNIQUE fields and relationships.
//select distinct ?p ?label ?type where {
//  {
//    [] a cms:Field ;
//      cms:property ?p .
//    BIND('text' AS ?type)
//    #optional { ?p rdfs:label ?label  }
//  } UNION {
//    [] a cms:Relationship ;
//      cms:property ?p .
//    BIND('sparql_views_related_resource' AS ?type)
//    #optional { ?p rdfs:label ?label  }
//  }
//}
//EOT;
//
//  return __curios_sparql_query($sparql, 'config');
//}
//
//
//function __curios_sparql_fetch_fields($browsing_class) {
//  $sparql = <<<EOT
//# Fetch distinct fields for a specific browsing class.
//select distinct ?p ?label where {
//  $browsing_class a cms:BrowsingClass ;
//    cms:field _:f .
//  _:f a cms:Field ;
//      cms:property ?p ;
//      rdfs:label ?label .
//}
//EOT;
//
//  return __curios_sparql_query($sparql, 'config');
//}
//
//function __curios_sparql_fetch_relationships($browsing_class) {
//  $sparql = <<<EOT
//# Fetch distinct relationships for a specific browsing class.
//select distinct ?p ?target ?label where {
//  $browsing_class a cms:BrowsingClass ;
//    cms:relationship _:r .
//  _:r a cms:Relationship ;
//    rdfs:label ?label ;
//    cms:property ?p ;
//    cms:target ?target .
//}
//EOT;
//
//  return __curios_sparql_query($sparql, 'config');
//}