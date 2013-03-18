<?php

function __curios_escape_sparql($s) {
  return trim(addcslashes($s, "\"\r\n"));
}

function __curios_subject_update($subject_id, $triples_insert, $triples_delete) {
  $query = '';
  $query .= "PREFIX hc:<http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#>\n";

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

  return __curios_execute_sparql($query);
}

function __curios_subject_insert($subject_id, $rdf_type, $triples_insert) {
  $query = '';
  $query .= "PREFIX hc:<http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#>\n";
  $query .= "INSERT DATA {\n";
  $query .= "  hc:$subject_id a ". $rdf_type .";\n";
  //$query .= "      hc:subjectID \"$identifier\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
  $query .= $triples_insert;
  $query .= '}';

  return __curios_execute_sparql($query);
}

function __curios_subject_delete($subject_id) {
  // TODO should use subject id field.
  $subject_id = __curios_escape_sparql($subject_id);
  
  $query = '';
  $query .= "PREFIX hc: <http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#>\n";
  $query .= "DELETE { ?subject ?p ?o }\n";
  $query .= "WHERE {\n";
  $query .= "  ?subject ?p ?o .\n";
  $query .= "  FILTER ( ?subject = hc:$subject_id ) }";

  return __curios_execute_sparql($query);
}

function __curios_fetch_max_identifier() {
    $query = '';
    $query .= "prefix hc:<http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#>\n";
    $query .= "select ?id where {\n";
    $query .= "  [] hc:subjectID ?id .}\n";
    $query .= "order by desc(strlen(?id)) desc(?id)\n";
    $query .= "limit 1";

    $rs = __curios_execute_sparql_select($query);
    if ($rs != NULL) {
      return $rs['result']['rows'][0]['id'];
    } else {
      return -1;
    }
}

function __curios_execute_sparql($query) {
  //dpm($query, "CURIOS update");
  $rs = sparql_request($query, (object)array('uri' => 'http://localhost:3030/dataset/update'));

  return ($rs != NULL);
}

function __curios_execute_sparql_select($query) {
  $rs = sparql_request($query, (object)array('uri' => 'http://localhost:3030/dataset/query'));

  if ($rs != NULL) {
    return $rs;
  } else {
    drupal_set_message("SPARQL endpoint error", 'error');
  }
}
