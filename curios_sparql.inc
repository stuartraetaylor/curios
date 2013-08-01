<?php

function __curios_sparql_query($query, $endpoint, $config = NULL) {
  $endpoints = __curios_endpoints();
  $query = __curios_sparql_append_prefixes($query, $config);
  $rs = sparql_request($query, (object)array('uri' => $endpoints[$endpoint]['query']));

  if ($rs != NULL) {
    return $rs;
  } else {
    drupal_set_message("SPARQL endpoint error", 'error');
  }
}

function __curios_sparql_update($query) {
  $endpoints = __curios_endpoints();
  $rs = sparql_request($query, (object)array('uri' => $endpoints['dataset']['update']));

  return ($rs != NULL);
}

function __curios_sparql_prefixes($config = NULL) {
  $prefixes = "prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n";

  if (isset($config)) {
    foreach ($config->getPrefixToNamespaceMap() as $prefix=>$ns) {
      $prefixes .= "prefix $prefix: <$ns>\n";
    }
  }

  return $prefixes;
}

function __curios_sparql_append_prefixes($query, $config) {
  return __curios_sparql_prefixes($config) . $query;
}

function __curios_escape_sparql($s) {
  return trim(addcslashes($s, "\"\r\n"));
}

function __curios_endpoints() {
  $endpoints = array(
    'dataset' => array(
      'query' => 'http://localhost:3030/dataset/query',
      'update' => 'http://localhost:3030/dataset/update',
    ),
    'config' => array(
      'query' => 'http://localhost:3030/ldcms-config/query',
      'update' => 'http://localhost:3030/ldcms-config/update',
    ),
  );

  return $endpoints;
}

function __curios_subject_update($subject_id, $triples_insert, $triples_delete) {
  $config = _curios_configuration();

  $query = '';
  $query .= "PREFIX hc:<". $config['namespaces']['hc'] .">\n";

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

  return __curios_sparql_update($query, 'dataset');
}

function __curios_subject_insert($subject_id, $rdf_type, $triples_insert) {
  $config = _curios_configuration();

  $query = '';
  $query .= "PREFIX hc:<". $config['namespaces']['hc'] .">\n";
  $query .= "INSERT DATA {\n";
  $query .= "  hc:$subject_id a ". $rdf_type .";\n";
  //$query .= "      hc:subjectID \"$identifier\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
  $query .= $triples_insert;
  $query .= '}';

  return __curios_sparql_update($query, 'dataset');
}

function __curios_subject_delete($subject_id) {
  $config = _curios_configuration();
  // TODO should use subject id field.
  $subject_id = __curios_escape_sparql($subject_id);

  $query = '';
  $query .= "PREFIX hc:<". $config['namespaces']['hc'] .">\n";
  $query .= "DELETE { ?subject ?p ?o }\n";
  $query .= "WHERE {\n";
  $query .= "  ?subject ?p ?o .\n";
  $query .= "  FILTER ( ?subject = hc:$subject_id ) }";

  return __curios_sparql_update($query, 'dataset');
}

function __curios_fetch_max_identifier() {
  $config = _curios_configuration();

  $query = '';
  $query .= "PREFIX hc:<". $config['namespaces']['hc'] .">\n";
  $query .= "select ?id where {\n";
  $query .= "  [] hc:subjectID ?id .}\n";
  $query .= "order by desc(strlen(?id)) desc(?id)\n";
  $query .= "limit 1";

  $rs = __curios_sparql_query($query, 'dataset');
  if ($rs != NULL) {
    return $rs['result']['rows'][0]['id'];
  } else {
    return -1;
  }
}

function __curios_latest_record_identifiers($n = 10) {
  $config = _curios_configuration();

  $query = <<<EOT
PREFIX hc:<{$config['namespaces']['hc']}>
select ?id ?title where {
  [] hc:subjectID ?id ;
     hc:englishName ?title .
}
order by desc(strlen(?id)) desc(?id)
limit $n
EOT;

  $rs = __curios_sparql_query($query, 'dataset');
  $identifiers = array();

  if ($rs != NULL) {
    foreach ($rs['result']['rows'] as $row) {
      $identifiers[$row['id']] = $row['title'];
    }
  }

  return $identifiers;
}

function __curios_is_valid_property_assertion($domain_class, $property, $range_individual) {
  $config = _curios_configuration();

  $query = <<<EOT
# Check individual is in the range of the specified property for the specified class.
prefix owl:<http://www.w3.org/2002/07/owl#>
prefix rdfs:<http://www.w3.org/2000/01/rdf-schema#>
PREFIX hc:<{$config['namespaces']['hc']}>
select ?range where  {
  [] a owl:ObjectProperty ;
      rdfs:subPropertyOf $property ;
      rdfs:domain $domain_class ;
      rdfs:range ?range .
  hc:$range_individual a ?range .
} limit 1
EOT;

    $rs = __curios_sparql_query($query, 'dataset');
    return ($rs != NULL && !empty($rs['result']['rows']));
}

function __curios_fetch_property_values($class, $property) {
  $config = _curios_configuration();

  $query = '';
  $query .= "PREFIX hc:<". $config['namespaces']['hc'] .">\n";
  $query .= "select distinct ?value where { \n";
  $query .= "[] a $class ; \n";
  $query .= "  $property ?value . \n";
  $query .= "} limit 500";

    return __curios_sparql_query($query, 'dataset');
}




// -- CONFIGURATION --

function __curios_sparql_fetch_browsing_classes($config) {
  $sparql = <<<EOT
# Get all Browsing Classes
select ?b ?base ?label ?titleField ?descriptionField where {
  ?b a cms:BrowsingClass ;
    cms:baseClass ?base ;
    rdfs:label ?label ;
    cms:field [
      a cms:Title ;
      cms:property ?titleField ] ;
    cms:field [
      a cms:Description ;
      cms:property ?descriptionField ] .
}
EOT;

  return __curios_sparql_query($sparql, 'config', $config);
}

function __curios_sparql_fetch_unique_fields_relationships($config) {
  $sparql = <<<EOT
# Fetch all UNIQUE fields and relationships.
select distinct ?p ?label ?type where {
  {
    [] a cms:Field ;
      cms:property ?p .
    BIND('text' AS ?type)
    #optional { ?p rdfs:label ?label  }
  } UNION {
    [] a cms:Relationship ;
      cms:property ?p .
    BIND('sparql_views_related_resource' AS ?type)
    #optional { ?p rdfs:label ?label  }
  }
}
EOT;

  return __curios_sparql_query($sparql, 'config', $config);
}


function __curios_sparql_fetch_fields($browsing_class, $config) {
  $sparql = <<<EOT
# Fetch distinct fields for a specific browsing class.
select distinct ?p ?label where {
  $browsing_class a cms:BrowsingClass ;
    cms:field _:f .
  _:f a cms:Field ;
      cms:property ?p ;
      rdfs:label ?label .
}
EOT;

  return __curios_sparql_query($sparql, 'config', $config);
}

function __curios_sparql_fetch_relationships($browsing_class, $config) {
  $sparql = <<<EOT
# Fetch distinct relationships for a specific browsing class.
select distinct ?p ?target ?label where {
  $browsing_class a cms:BrowsingClass ;
    cms:relationship _:r .
  _:r a cms:Relationship ;
    rdfs:label ?label ;
    cms:property ?p ;
    cms:target ?target .
}
EOT;

  return __curios_sparql_query($sparql, 'config', $config);
}