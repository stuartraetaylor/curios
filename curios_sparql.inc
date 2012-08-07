<?php

function __curios_subject_update($subject_id, $triples_insert, $triples_delete) {
  $query = '';
  $query .= "PREFIX hc:<http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#>\n";
  $query .= "DELETE {\n";
  $query .= "  ?subject ";
  $query .= $triples_delete;
  $query .= " } \n";
  $query .= "INSERT {\n";
  $query .= "  ?subject ";
  $query .= $triples_insert;
  $query .= " } \n";
  $query .= "WHERE {\n";
  $query .= "  ?subject ?p ?o ;\n";
  $query .= "    a hc:Boat .\n";
  $query .= "  FILTER ( ?subject = hc:$subject_id ) }";

  __curios_execute_sparql($query);
}

function __curios_subject_insert($subject_id, $insert_triples) {
  $query = '';
  $query .= "PREFIX hc:<http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#>\n";
  $query .= "INSERT DATA {\n";
  $query .= "  hc:$subject_id a ". $rdf_mapping['rdftype'][0] .";\n";
  //$query .= "      hc:subjectID \"$identifier\"^^<http://www.w3.org/2001/XMLSchema#string>;\n";
  $query .= $triples_insert;
  $query .= '}';

  __curios_execute_sparql($query);
}

function __curios_subject_delete($subject_id) {
  $query = '';
  $query .= "PREFIX hc: <http://www.csd.abdn.ac.uk/~cmellish/ontologies/hebridean.owl#>\n";
  $query .= "DELETE { ?subject ?p ?o }\n";
  $query .= "WHERE {\n";
  $query .= "  ?subject ?p ?o .\n";
  $query .= "  FILTER ( ?subject = hc:$subject_id ) }";

  __curios_execute_sparql($query);
}

function __curios_execute_sparql($query) {
  $rs = sparql_request($query, (object)array('uri' => 'http://localhost:3030/dataset/update'));

  if ($rs == NULL) {
    dpm('error!');
  } else {
    dpm($rs, 'QUERY RESULT!');
    drupal_set_message(t('The form has been submitted.'));
  }
}
