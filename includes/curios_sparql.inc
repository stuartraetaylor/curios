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
  $prefixes .= "prefix rdfs:<http://www.w3.org/2000/01/rdf-schema#>\n";
  $prefixes .= "prefix owl:<http://www.w3.org/2002/07/owl#>\n";
  $prefixes .= "prefix xsd:<http://www.w3.org/2001/XMLSchema#>\n";

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
 *
 * $triples_insert and $triples_delete are expected to be a predicate-object list, for the subject being updated.
 * $triples_delete_append and $triples_where_append are expected to be individual triple patterns which are appended
 * to the end of the relevant triples block.
 */
function _curios_subject_update($subject_id, $triples_insert, $triples_delete, $triples_delete_append = '', $triples_where_append = '') {
  $config = curios_configuration();
  $prefix = $config->getPrefix($config->getDefaultNamespace());
  $record = "$prefix:$subject_id";

  $query = '';

  if (!empty($triples_delete)) {
    $query .= "DELETE {\n";
    $query .= "  ?s ";
    $query .= $triples_delete;
    $query .= " .\n";
    $query .= $triples_delete_append;
    $query .= " } \n";
  }

  if (!empty($triples_insert)) {
    $query .= "INSERT {\n";
    $query .= "  ?s ";
    $query .= $triples_insert;
    $query .= " } \n";
  }

  $query .= "WHERE {\n";
  $query .= "  BIND($record as ?s)\n";
  $query .= $triples_where_append;
  $query .= " }";

  return __curios_sparql_update($query);
}

/**
 * Removes an individual.
 */
function _curios_subject_delete($subject_id) {
  $config = curios_configuration();
  $prefix = $config->getPrefix($config->getDefaultNamespace());
  $record = "$prefix:$subject_id";

  $query = '';
  $query .= "DELETE { ?subject ?p ?o }\n";
  $query .= "WHERE {\n";
  $query .= "  ?subject ?p ?o .\n";
  $query .= "  FILTER ( ?subject = $record ) }";

  return __curios_sparql_update($query);
}

/**
 * Creates a new record.
 */
function _curios_subject_insert($rdf_type, $triples_insert) {
  $config = curios_configuration();
  $namespace = $config->getDefaultNamespace();

  $id_field = $config->getField($config->getIdentifierFieldId());
  $id_property = $id_field->getRDFPredicate();

  $default_browsing_class = $config->getResource($config->getDefaultBrowsingClassId());
  $default_class = $default_browsing_class->getBaseClass();

  $query = <<<EOT
INSERT {
  ?uri a {$rdf_type} ;
    {$id_property} ?id ;
{$triples_insert} .
} WHERE {
  SELECT ?uri ?id {
    {
      SELECT ((MAX(?n) + 1) AS ?id) {
        [] {$id_property} ?n ; a {$default_class} .
      }
    }
    BIND(URI(CONCAT("{$namespace}", STR(?id))) as ?uri) .
  }
}
EOT;

  return __curios_sparql_update($query);
}

function _curios_fetch_max_identifier() {
  $config = curios_configuration();
  $id_field = $config->getField($config->getIdentifierFieldId());
  $id_property = $id_field->getRDFPredicate();
  $default_browsing_class = $config->getResource($config->getDefaultBrowsingClassId());
  $default_class = $default_browsing_class->getBaseClass();
  
$query = <<<EOT
SELECT (MAX(?n) AS ?id) {
  [] {$id_property} ?n ; a {$default_class} .
}
EOT;

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
  $config = curios_configuration();
  $id_field = $config->getField($config->getIdentifierFieldId());
  $id_property = $id_field->getRDFPredicate();
  $title_field = $config->getField($config->getTitleFieldId())
  $title_property = $title_field->getRDFPredicate();
  
  $query = <<<EOT
select ?id ?title where {
  [] {$id_property} ?id ; {$title_property} ?title .
} order by desc(?id) limit {$n}
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
  $config = curios_configuration();
  $prefix = $config->getPrefix($config->getDefaultNamespace());
  $record = "$prefix:$subject_id";
  
  $query = "select ?type where { $record a ?type . ?type a owl:Class }";
  $rs = __curios_sparql_query($query);

  $classes = array();
  foreach ($rs['result']['rows'] as $row) {
    $classes[] = $row['type'];
  }

  return $classes;
}

///**
// * Creates a new individiual.
// */
//function _curios_subject_insert($subject_id, $rdf_type, $triples_insert) {
//  $query = '';
//  $query .= "INSERT DATA {\n";
//  $query .= "  hc:$subject_id a ". $rdf_type .";\n";
//  $query .= $triples_insert;
//  $query .= '}';
//
//  return __curios_sparql_update($query);
//}
//
///**
// * Finds the highest subject_id used in the triple stores.
// */
//function _curios_fetch_max_identifier() {
//  $query = '';
//  $query .= "select ?id where {\n";
//  $query .= "  [] hc:subjectID ?id .}\n";
//  $query .= "order by desc(strlen(?id)) desc(?id)\n";
//  $query .= "limit 1";
//
//  $rs = __curios_sparql_query($query);
//  if ($rs != NULL) {
//    return $rs['result']['rows'][0]['id'];
//  } else {
//    return -1;
//  }
//}
//
///**
// * Returns an array of recently inserted subject_id's.
// */
//function _curios_latest_record_identifiers($n = 10) {
//  $query = <<<EOT
//select ?id ?title where {
//  [] dsubjectID ?id ;
//     dc:title ?title .
//}
//order by desc(strlen(?id)) desc(?id)
//limit $n
//EOT;
//
//  $rs = __curios_sparql_query($query);
//  $identifiers = array();
//
//  if ($rs != NULL) {
//    foreach ($rs['result']['rows'] as $row) {
//      $identifiers[$row['id']] = $row['title'];
//    }
//  }
//
//  return $identifiers;
//}

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
