<?php
require_once('curios_ldcms.inc');

//function _curios_configuration_spec() {
function _curios_configuration() {
  $config = &drupal_static(__FUNCTION__);

  //_curios_configuration_TEST(); exit;

  if (!isset($config)) {
    $config = array();

    $config['namespaces'] = array(
      'cms' => 'http://www.abdn.ac.uk/~csc363/ldcms.owl#',
      'hc'  => 'http://www.hebrideanconnections.com/hebridean.owl#',
      'dc'  => 'http://purl.org/dc/terms/',
    );

    // Namespace shortcuts.
    $cms = $config['namespaces']['cms'];
    $hc  = $config['namespaces']['hc'];
    $dc  = $config['namespaces']['dc'];

    $config['image_relationship_field'] = 'hc_has_file';

    $config['rdf_fields'] = array(
      // Data properties.
      'hc_also_known_as'        => new RDFField('hc_also_known_as', 'AlsoKnownAs', 'hc:alsoKnownAs', 'text'),
      'hc_bk_reference'         => new RDFField('hc_bk_reference', 'BkReference', 'hc:bkReference', 'text'),
      'hc_born'                 => new RDFField('hc_born', 'Born', 'hc:born', 'text'),
      'hc_chassis'              => new RDFField('hc_chassis', 'Chassis', 'hc:chassis', 'text'),
      'hc_created_by'           => new RDFField('hc_created_by', 'Createdby', 'hc:createdBySociety', 'text'),
      'hc_date'                 => new RDFField('hc_date', 'Date', 'hc:date', 'text'),
      'hc_date_built'           => new RDFField('hc_date_built', 'DateBuilt', 'hc:dateBuilt', 'text'),
      'hc_date_demolished'      => new RDFField('hc_date_demolished', 'DateDemolished', 'hc:dateDemolished', 'text'),
      'hc_date_established'     => new RDFField('hc_date_established', 'DateEstablished','hc:dateEstablished', 'text'),
      'hc_date_founded'         => new RDFField('hc_date_founded', 'DateFounded', 'hc:dateFounded', 'text'),
      'hc_date_launched'        => new RDFField('hc_date_launched', 'DateLaunched', 'hc:dateLaunched', 'text'),
      'hc_date_lotted'          => new RDFField('hc_date_lotted', 'DateLotted', 'hc:dateLotted', 'text'),
      'hc_date_of_death'        => new RDFField('hc_date_of_death', 'DateOfDeath', 'hc:dateOfDeath', 'text'),  
      'hc_date_of_marriage'     => new RDFField('hc_date_of_marriage', 'DateOfMarriage', 'hc:dateOfMarriage', 'text'),  
      'hc_date_of_registration' => new RDFField('hc_date_of_registration', 'DateOfRegistration', 'hc:dateOfRegistration', 'text'),
      'hc_date_of_source'       => new RDFField('hc_date_of_source', 'DateOfSource', 'hc:dateOfSource', 'text'),
      'hc_description'          => new RDFField('hc_description', 'Description', 'hc:description', 'text'),
      'hc_easting'              => new RDFField('hc_easting', 'Easting', 'hc:easting', 'text'),
      'hc_english_name'         => new RDFField('hc_english_name', 'EnglishName', 'hc:englishName', 'text'),
      'hc_gaelic_name'          => new RDFField('hc_gaelic_name', 'GaelicName', 'hc:gaelicName', 'text'),
      'hc_geo_ref'              => new RDFField('hc_geo_ref', 'GeoRef', 'hc:geoRef', 'text'),
      'hc_northing'             => new RDFField('hc_northing', 'Northing', 'hc:northing', 'text'),
      'hc_occupation'           => new RDFField('hc_occupation', 'Occupation', 'hc:occupation', 'text'),   
      'hc_period'               => new RDFField('hc_period', 'Period', 'hc:period', 'text'),
      'hc_period_of_construction_use' => new RDFField('hc_period_of_construction_use', 'PeriodOfConstructionUse', 'hc:periodOfConstructionUse', 'text'),
      'hc_registration'         => new RDFField('hc_registration', 'Registration', 'hc:registration', 'text'),
      'hc_sex'                  => new RDFField('hc_sex', 'Sex', 'hc:sex', 'text'),
      'hc_smr_record_id'        => new RDFField('hc_smr_record_id', 'SMR Record ID', 'hc:SMRRecordID', 'text'),
      'hc_source_type'          => new RDFField('hc_source_type', 'Source Type', 'hc:sourceType', 'text'),
      'hc_soundex_name'         => new RDFField('hc_soundex_name', 'Soundexname', 'hc:soundexName', 'text'),      
      'hc_subject_id'           => new RDFField('hc_subject_id', 'Subjectid', 'hc:subjectID', 'text'),      
      'hc_title'                => new RDFField('hc_title', 'Title', 'hc:title', 'text'),
      'hc_theme'                => new RDFField('hc_theme', 'Theme', 'hc:theme', 'text'),
      'hc_time_period'          => new RDFField('hc_time_period', 'TimePeriod', 'hc:timePeriod', 'text'),

       // Images.
      'hc_title'                => new RDFField('hc_title', 'Title', 'hc:title', 'text'),
      'hc_url'                  => new RDFField('hc_url', 'ImageURL', 'hc:URL', 'text'),
      'hc_file_name'            => new RDFField('hc_file_name', 'Filename', 'hc:fileName', 'text'),

      // TypeOf.
      'hc_type_of_boat'                     => new RDFField('hc_type_of_boat', 'Type', 'hc:typeOfBoat', 'text'),
      'hc_type_of_building_public_ameni'    => new RDFField('hc_type_of_building_public_ameni', 'Type', 'hc:typeOfBuildingPublicAmenity', 'text'),
      'hc_type_of_business'                 => new RDFField('hc_type_of_business', 'Type', 'hc:typeOfBusiness', 'text'),
      'hc_type_of_event'                    => new RDFField('hc_type_of_event', 'Type', 'hc:typeOfEvent', 'text'),
      'hc_type_of_location'                 => new RDFField('hc_type_of_location', 'Type', 'hc:typeOfLocation', 'text'),
      'hc_type_of_natural_landscape_fea'    => new RDFField('hc_type_of_natural_landscape_fea', 'Type', 'hc:typeOfNaturalLandscapeFeature', 'text'),
      'hc_type_of_object_artefact'          => new RDFField('hc_type_of_object_artefact', 'Type', 'hc:typeOfObjectArtefact', 'text'),
      'hc_type_of_organisation'             => new RDFField('hc_type_of_organisation', 'Type', 'hc:typeOfOrganisation', 'text'),
      'hc_type_of_residence'                => new RDFField('hc_type_of_residence', 'Type', 'hc:typeOfResidence', 'text'),
      'hc_type_of_site'                     => new RDFField('hc_type_of_site', 'Type', 'hc:typeOfSite', 'text'),
      'hc_type_of_story_report_traditio'    => new RDFField('hc_type_of_story_report_traditio', 'Type', 'hc:typeOfStoryReportTradition', 'text'),
      'hc_type_of_vehicle'                  => new RDFField('hc_type_of_vehicle', 'Type', 'hc:typeOfVehicle', 'text'),

      // Object Properties
      'hc_adopted_by'           => new RDFField('hc_adopted_by', 'AdoptedBy',  'hc:adoptedBy', 'sparql_views_related_resource'),
      'hc_adopted_person'       => new RDFField('hc_adopted_person', 'AdoptedPerson',  'hc:adoptedPerson', 'sparql_views_related_resource'),
      'hc_associated_with'      => new RDFField('hc_associated_with', 'AssociatedWith',  'hc:associatedWith', 'sparql_views_related_resource'),
      'hc_author_originator_of' => new RDFField('hc_author_originator_of', 'AuthorOriginatorOf',  'hc:authorOriginatorOf', 'sparql_views_related_resource'),
      'hc_born_in'              => new RDFField('hc_born_in', 'BornIn',  'hc:hasPlaceOfBirth', 'sparql_views_related_resource'),
      'hc_builder'              => new RDFField('hc_builder', 'Builder',  'hc:hasBuilder', 'sparql_views_related_resource'),
      'hc_built_by'             => new RDFField('hc_built_by', 'BuiltBy',  'hc:builtBy', 'sparql_views_related_resource'),
      'hc_child_of'             => new RDFField('hc_child_of', 'ChildOf',  'hc:childOf', 'sparql_views_related_resource'),      
      'hc_compiled_maintained_by' => new RDFField('hc_compiled_maintained_by', 'compiledMaintainedBy',  'hc:CompiledMaintainedBy', 'sparql_views_related_resource'),
      'hc_compiler_of'          => new RDFField('hc_compiler_of', 'CompilerOf',  'hc:compilerOf', 'sparql_views_related_resource'),
      'hc_composed_by'          => new RDFField('hc_composed_by', 'ComposedBy',  'hc:composedBy', 'sparql_views_related_resource'),
      'hc_composed_song'        => new RDFField('hc_composed_song', 'ComposedSong',  'hc:composedSong', 'sparql_views_related_resource'),
      'hc_comprises_sub_site'   => new RDFField('hc_comprises_sub_site', 'ComprisesSubSite',  'hc:comprisesSubSite', 'sparql_views_related_resource'),
      'hc_crewed_by'            => new RDFField('hc_crewed_by', 'CrewedBy',  'hc:crewedBy', 'sparql_views_related_resource'),
      'hc_died_in'              => new RDFField('hc_died_in', 'DiedIn',  'hc:hasPlaceOfDeath', 'sparql_views_related_resource'),
      'hc_emigrated_to'         => new RDFField('hc_emigrated_to', 'EmigratedTo',  'hc:emigratedTo', 'sparql_views_related_resource'),
      'hc_employed'             => new RDFField('hc_employed', 'Employed',  'hc:employed', 'sparql_views_related_resource'),      
      'hc_employed_by'          => new RDFField('hc_employed_by', 'EmployedBy',  'hc:employedBy', 'sparql_views_related_resource'),      
      'hc_fostered_by'          => new RDFField('hc_fostered_by', 'FosteredBy',  'hc:fosteredBy', 'sparql_views_related_resource'),      
      'hc_fostered_person'      => new RDFField('hc_fostered_person', 'FosteredPerson',  'hc:fosteredPerson', 'sparql_views_related_resource'),      
      'hc_found_at'             => new RDFField('hc_found_at', 'FoundAt',  'hc:foundAt', 'sparql_views_related_resource'),      
      'hc_found_here'           => new RDFField('hc_found_here', 'FoundHere',  'hc:foundHere', 'sparql_views_related_resource'),      
      'hc_has_file'             => new RDFField('hc_has_file', 'HasFile',  'hc:hasFile', 'sparql_views_related_resource'),      
      'hc_holds'                => new RDFField('hc_holds', 'Holds',  'hc:holds', 'sparql_views_related_resource'),      
      'hc_immigrant_from'       => new RDFField('hc_immigrant_from', 'ImmigrantFrom',  'hc:immigrantFrom', 'sparql_views_related_resource'),      
      'hc_information_obtained_from' => new RDFField('hc_information_obtained_from', 'InformationObtainedFrom',  'hc:informationObtainedFrom', 'sparql_views_related_resource'),      
      'hc_is_part_of_site'      => new RDFField('hc_is_part_of_site', 'IsPartOfSite',  'hc:isPartOfSite', 'sparql_views_related_resource'),
      'hc_is_shown_here'        => new RDFField('hc_is_shown_here', 'IsShownHere',  'hc:isShownHere', 'sparql_views_related_resource'),
      'hc_lived_here'           => new RDFField('hc_lived_here', 'LivedHere',  'hc:livedHere', 'sparql_views_related_resource'),      
      'hc_lived_at'             => new RDFField('hc_lived_at', 'LivedAt',  'hc:livedAt', 'sparql_views_related_resource'),
      'hc_lived_with'           => new RDFField('hc_lived_with', 'LivedWith',  'hc:livedWith', 'sparql_views_related_resource'),
      'hc_located_at'           => new RDFField('hc_located_at', 'LocatedAt',  'hc:locatedAt', 'sparql_views_related_resource'),
      'hc_located_here'         => new RDFField('hc_located_here', 'LocatedHere',  'hc:locatedHere', 'sparql_views_related_resource'),
      'hc_located_near'         => new RDFField('hc_located_near', 'LocatedNear',  'hc:locatedNear', 'sparql_views_related_resource'),
      'hc_married'              => new RDFField('hc_married', 'Married',  'hc:married', 'sparql_views_related_resource'),
      'hc_may_be_the_same_as'   => new RDFField('hc_may_be_the_same_as', 'mayBeTheSameAs',  'hc:MayBeTheSameAs', 'sparql_views_related_resource'),
      'hc_moved_from'           => new RDFField('hc_moved_from', 'MovedFrom',  'hc:movedFrom', 'sparql_views_related_resource'),      
      'hc_moved_to'             => new RDFField('hc_moved_to', 'MovedTo',  'hc:movedTo', 'sparql_views_related_resource'),
      'hc_on_crew_of_boat'      => new RDFField('hc_on_crew_of_boat', 'OnCrewOfBoat',  'hc:onCrewOfBoat', 'sparql_views_related_resource'),
      'hc_owned'                => new RDFField('hc_owned', 'Owned',  'hc:ownedOf', 'sparql_views_related_resource'),
      'hc_owned_by'             => new RDFField('hc_owned_by', 'OwnedBy',  'hc:ownedBy', 'sparql_views_related_resource'),
      'hc_parent_of'            => new RDFField('hc_parent_of', 'ParentOf',  'hc:parentOf', 'sparql_views_related_resource'),
      'hc_person_born_here'     => new RDFField('hc_person_born_here', 'PersonBornHere',  'hc:personBornHere', 'sparql_views_related_resource'),
      'hc_person_who_died_here' => new RDFField('hc_person_who_died_here', 'PersonWhoDiedHere',  'hc:hasPersonWhoDiedHere', 'sparql_views_related_resource'),   
      'hc_related_to'           => new RDFField('hc_related_to', 'RelatedTo',  'hc:relatedTo', 'sparql_views_related_resource'),
      'hc_sibling_of'           => new RDFField('hc_sibling_of', 'SiblingOf',  'hc:siblingOf', 'sparql_views_related_resource'),
      'hc_source_of_information_on' => new RDFField('hc_source_of_information_on', 'SourceOfInformationOn',  'hc:sourceOfInformationOn', 'sparql_views_related_resource'),
      'hc_used_object'          => new RDFField('hc_used_object', 'UsedObject',  'hc:usedObject', 'sparql_views_related_resource'),
      'hc_written_compiled_by'  => new RDFField('hc_written_compiled_by', 'WrittenCompiledBy',  'hc:writtenCompiledBy', 'sparql_views_related_resource'),

      // Validation / provenance.
      'hc_approved_by'          => new RDFField('hc_approved_by', 'Approvedby', 'hc:Approvedby', 'text'),      
      'hc_approved_date'        => new RDFField('hc_approved_date', 'Approveddate', 'hc:Approveddate', 'text'),      
      'hc_approved_for_pub'     => new RDFField('hc_approved_for_pub', 'ApprovedForPub', 'hc:approvedForPub', 'text'),
      'hc_owned_by_society'     => new RDFField('hc_owned_by_society', 'OwnedBySociety', 'hc:ownedBySociety', 'text'),
      'hc_maintained_by_society'=> new RDFField('hc_maintained_by_society', 'MaintainedBySociety', 'hc:maintainedBySociety', 'text'),

      // Unused?
      'hc_approved'             => new RDFField('hc_approved', 'Approved', 'hc:Approved', 'text'),
      'hc_caption'              => new RDFField('hc_caption', 'Caption', 'hc:Caption', 'text'),
      'hc_compiler_notes'       => new RDFField('hc_compiler_notes', 'Compilernotes', 'hc:Compilernotes', 'text'),
      'hc_copyright'            => new RDFField('hc_copyright', 'Copyright', 'hc:Copyright', 'text'),
      'hc_edited_by'            => new RDFField('hc_edited_by', 'Editedby', 'hc:Editedby', 'text'),
      'hc_extra_info'           => new RDFField('hc_extra_info', 'Extrainfo', 'hc:Extrainfo', 'text'),
      'hc_fid'                  => new RDFField('hc_fid', 'Fid', 'hc:Fid', 'text'),      
      'hc_internal_summary'     => new RDFField('hc_internal_summary', 'Internalsummary', 'hc:Internalsummary', 'text'),
      'hc_inverse_caption'      => new RDFField('hc_inverse_caption', 'Inversecaption', 'hc:Inversecaption', 'text'),
      'hc_is_primary'           => new RDFField('hc_is_primary', 'Isprimary', 'hc:Isprimary', 'text'),
      'hc_lochistsoc'           => new RDFField('hc_lochistsoc', 'Lochistsoc', 'hc:Lochistsoc', 'text'),
      'hc_lochistsocref'        => new RDFField('hc_lochistsocref', 'Lochistsocref', 'hc:Lochistsocref', 'text'),
      'hc_originator'           => new RDFField('hc_originator', 'Originator', 'hc:Originator', 'text'),
      'hc_origin_date'          => new RDFField('hc_origin_date', 'Origindate', 'hc:Origindate', 'text'),
      'hc_to_be_published'      => new RDFField('hc_to_be_published', 'Tobepublished', 'hc:Tobepublished', 'text'),
      'hc_when_created'         => new RDFField('hc_when_created', 'Whencreated', 'hc:Whencreated', 'text'),
      'hc_when_edited'          => new RDFField('hc_when_edited', 'Whenedited', 'hc:Whenedited', 'text'),

      // Dublin core.
      'dc_title'                => new RDFField('dc_title', 'dc:title', 'dc:title', 'text'),
      'dc_description'          => new RDFField('dc_description', 'dc:description', 'dc:description', 'text'),
    );

  $config['rdf_resources'] = array();

  $config['rdf_resources']['hc_subject'] = new RDFResource('hc_subject', 'Subject', 'hc:Subject',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],


        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],
        $config['rdf_fields']['hc_also_known_as'],

        $config['rdf_fields']['hc_born'],
        $config['rdf_fields']['hc_chassis'],
        $config['rdf_fields']['hc_created_by'],
        $config['rdf_fields']['hc_date'],
        $config['rdf_fields']['hc_date_built'],
        $config['rdf_fields']['hc_date_demolished'],
        $config['rdf_fields']['hc_date_established'],
        $config['rdf_fields']['hc_date_founded'],
        $config['rdf_fields']['hc_date_launched'],
        $config['rdf_fields']['hc_date_lotted'],
        $config['rdf_fields']['hc_date_of_death'],
        $config['rdf_fields']['hc_date_of_marriage' ],
        $config['rdf_fields']['hc_date_of_registration'],
        $config['rdf_fields']['hc_date_of_source'],
        //$config['rdf_fields']['hc_easting'],
        $config['rdf_fields']['hc_url'],
        $config['rdf_fields']['hc_file_name'],
        $config['rdf_fields']['hc_geo_ref'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_occupation'],
        $config['rdf_fields']['hc_period'],
        $config['rdf_fields']['hc_period_of_construction_use'],
        $config['rdf_fields']['hc_registration'],
        $config['rdf_fields']['hc_sex'],
        $config['rdf_fields']['hc_title'],
        $config['rdf_fields']['hc_theme'],
        $config['rdf_fields']['hc_time_period'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
        $config['rdf_fields']['hc_smr_record_id'],
        $config['rdf_fields']['hc_soundex_name'],
      ),
      array( // Object fields.
        //$config['rdf_fields']['hc_adopted_by'],
        //$config['rdf_fields']['hc_adopted_person'],
        $config['rdf_fields']['hc_associated_with'],
        //$config['rdf_fields']['hc_author_originator_of'],
        //$config['rdf_fields']['hc_born_in'],
        //$config['rdf_fields']['hc_builder'],
        //$config['rdf_fields']['hc_built_by'],
        //$config['rdf_fields']['hc_child_of'],
        //$config['rdf_fields']['hc_compiled_maintained_by'],
        //$config['rdf_fields']['hc_compiler_of'],
        //$config['rdf_fields']['hc_composed_by'],
        //$config['rdf_fields']['hc_composed_song'],
        //$config['rdf_fields']['hc_comprises_sub_site'],
        //$config['rdf_fields']['hc_crewed_by'],
        //$config['rdf_fields']['hc_died_in'],
        //$config['rdf_fields']['hc_emigrated_to'],
        //$config['rdf_fields']['hc_employed'],
        //$config['rdf_fields']['hc_employed_by'],
        //$config['rdf_fields']['hc_fostered_by'],
        //$config['rdf_fields']['hc_fostered_person'],
        //$config['rdf_fields']['hc_found_at'],
        //$config['rdf_fields']['hc_found_here'],
        $config['rdf_fields']['hc_has_file'],
        //$config['rdf_fields']['hc_holds'],
        //$config['rdf_fields']['hc_immigrant_from'],
        $config['rdf_fields']['hc_information_obtained_from'],
        //$config['rdf_fields']['hc_is_part_of_site'],
        //$config['rdf_fields']['hc_lived_here'],
        //$config['rdf_fields']['hc_lived_at'],
        //$config['rdf_fields']['hc_lived_with'],
        //$config['rdf_fields']['hc_located_at'],
        //$config['rdf_fields']['hc_located_here'],
        //$config['rdf_fields']['hc_located_near'],
        //$config['rdf_fields']['hc_married'],
        //$config['rdf_fields']['hc_may_be_the_same_as'],
        //$config['rdf_fields']['hc_moved_from'],
        //$config['rdf_fields']['hc_moved_to'],
        //$config['rdf_fields']['hc_on_crew_of_boat'],
        //$config['rdf_fields']['hc_owned'],
        //$config['rdf_fields']['hc_owned_by'],
        //$config['rdf_fields']['hc_parent_of'],
        //$config['rdf_fields']['hc_person_born_here'],
        //$config['rdf_fields']['hc_person_who_died_here'],
        //$config['rdf_fields']['hc_related_to'],
        //$config['rdf_fields']['hc_sibling_of'],
        //$config['rdf_fields']['hc_source_of_information_on'],
        //$config['rdf_fields']['hc_used_object'],
        //$config['rdf_fields']['hc_written_compiled_by'],
      ),
      array( // Object field ranges.
        'hc_information_obtained_from' => 'hc_resource',
      )
    );

    $config['rdf_resources']['hc_boat'] = new RDFResource('hc_boat', 'Boat', 'hc:Boat', 
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],
        $config['rdf_fields']['hc_also_known_as'],

        $config['rdf_fields']['hc_type_of_boat'],
        $config['rdf_fields']['hc_date_launched'],
        $config['rdf_fields']['hc_date_of_registration'],
        $config['rdf_fields']['hc_registration'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_built_by'],
        $config['rdf_fields']['hc_crewed_by'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_owned_by'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array( // Array indicates there are multiple possible targets.
            'hc_historical_event',
            'hc_location',
            'hc_natural_landscape_feature',
            'hc_organisation',
            'hc_person',
            'hc_business',
            'hc_story_report_or_tradition',
            'hc_boat',
            'hc_croft_or_residence',
        ),
        'hc_built_by' => 'hc_person',
        'hc_crewed_by' => 'hc_person',
        'hc_information_obtained_from' => 'hc_resource',
        'hc_owned_by' => 'hc_person',
      ),
      array( // Sub types.
        'AircraftCarrier' => 'hc:AircraftCarrier',
        'ArmedBoardingSteamer' => 'hc:ArmedBoardingSteamer',
        'ArmedMerchantCruiser' => 'hc:ArmedMerchantCruiser',
        'AswTrawler' => 'hc:AswTrawler',
        'AuxiliaryLugsail' => 'hc:AuxiliaryLugsail',
        'Barge' => 'hc:Barge',
        'Barque' => 'hc:Barque',
        'BattleCruiser' => 'hc:BattleCruiser',
        'Battleship' => 'hc:Battleship',
        'Clipper' => 'hc:Clipper',
        'CreelBoat' => 'hc:CreelBoat',
        'Destroyer' => 'hc:Destroyer',
        'Dreadnought' => 'hc:Dreadnought',
        'EscortCarrier' => 'hc:EscortCarrier',
        'EscortDestroyer' => 'hc:EscortDestroyer',
        'EscortShip' => 'hc:EscortShip',
        'FishingBoat' => 'hc:FishingBoat',
        'FleetAircraftCarrier' => 'hc:FleetAircraftCarrier',
        'GuidedMissileDestroyer' => 'hc:GuidedMissileDestroyer',
        'KiteBalloonShip' => 'hc:KiteBalloonShip',
        'LargeFishingBoat' => 'hc:LargeFishingBoat',
        'LightCruiser' => 'hc:LightCruiser',
        'Liner' => 'hc:Liner',
        'Lugger' => 'hc:Lugger',
        'MerchantShip' => 'hc:MerchantShip',
        'Minehunter' => 'hc:Minehunter',
        'Minelayer' => 'hc:Minelayer',
        'MotorDrifter' => 'hc:MotorDrifter',
        'MotorFishingVessel' => 'hc:MotorFishingVessel',
        'MotorLaunch' => 'hc:MotorLaunch',
        'MsTrawler' => 'hc:MsTrawler',
        'MvTrawler' => 'hc:MvTrawler',
        'PassengerCargoVessel' => 'hc:PassengerCargoVessel',
        'PatrolVessel' => 'hc:PatrolVessel',
        'PirateVessel' => 'hc:PirateVessel',
        'Puffer' => 'hc:Puffer',
        'RescueTug' => 'hc:RescueTug',
        'SailBoat' => 'hc:SailBoat',
        'Schooner' => 'hc:Schooner',
        'Sloop' => 'hc:Sloop',
        'SmallFishingBoat' => 'hc:SmallFishingBoat',
        'SteamDrifter' => 'hc:SteamDrifter',
        'Steamer' => 'hc:Steamer',
        'Steamship' => 'hc:Steamship',
        'SubmarineDepotShip' => 'hc:SubmarineDepotShip',
        'Tanker' => 'hc:Tanker',
        'Trawler' => 'hc:Trawler',
        'TroopCarrier' => 'hc:TroopCarrier',
        'Yacht' => 'hc:Yacht',
      )
    );

    $config['rdf_resources']['hc_building_or_public_amenity'] = new RDFResource('hc_building_or_public_amenity', 'BuildingOrPublicAmenity', 'hc:BuildingOrPublicAmenity',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_building_public_ameni'],
        $config['rdf_fields']['hc_date_built'],
        $config['rdf_fields']['hc_date_established'],
        $config['rdf_fields']['hc_date_founded'],
        $config['rdf_fields']['hc_geo_ref'],
        //$config['rdf_fields']['hc_location_type'],
        $config['rdf_fields']['hc_period'],
        $config['rdf_fields']['hc_period_of_construction_use'],
        //$config['rdf_fields']['hc_residence_type'],
        //$config['rdf_fields']['hc_site_type'],
        $config['rdf_fields']['hc_smr_record_id'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_lived_here'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_located_here'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_historical_event',
            'hc_object_or_artefact',
            'hc_organisation',
            'hc_landmark_or_archaeological_site',
            'hc_croft_or_residence',
            'hc_location',
            'hc_building_or_public_amenity',
            'hc_person',
            'hc_story_report_or_tradition',
        ),
        'hc_information_obtained_from' => 'hc_resource',
        'hc_lived_here' => 'hc_person',
        'hc_located_at' => array('hc_building_or_public_amenity', 'hc_location'),
      ),
      array( // Sub types.
        'Airport' => 'hc:Airport',
        'Bakery' => 'hc:Bakery',
        'Caf' => 'hc:Caf',
        'Castle' => 'hc:Castle',
        'Cemetery' => 'hc:Cemetery',
        'Church' => 'hc:Church',
        'College' => 'hc:College',
        'EstateLodge' => 'hc:EstateLodge',
        'Factory' => 'hc:Factory',
        'Hospice' => 'hc:Hospice',
        'Hospital' => 'hc:Hospital',
        'Hotel' => 'hc:Hotel',
        'House' => 'hc:House',
        'LocalSurgery' => 'hc:LocalSurgery',
        'Manse' => 'hc:Manse',
        'MissionHall' => 'hc:MissionHall',
        'Museum' => 'hc:Museum',
        'NursingHome' => 'hc:NursingHome',
        'Palace' => 'hc:Palace',
        'Pier' => 'hc:Pier',
        'PostOffice' => 'hc:PostOffice',
        'PresidentialOffice' => 'hc:PresidentialOffice',
        'Reconstruction' => 'hc:Reconstruction',
        'School' => 'hc:School',
        'Shop' => 'hc:Shop',
        'Smithy' => 'hc:Smithy',
        'TownHall' => 'hc:TownHall',
        'University' => 'hc:University',
        'VisitorCentre>' => 'hc:VisitorCentre',
      )
    );

    $config['rdf_resources']['hc_business'] = new RDFResource('hc_business', 'Business', 'hc:Business',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_business'],
        $config['rdf_fields']['hc_date_founded'],
        $config['rdf_fields']['hc_period'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_owned_by'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_story_report_or_tradition',
            'hc_person',
            'hc_business',
            'hc_business',
            'hc_organisation',
            'hc_location',
            'hc_boat',
        ),
        'hc_information_obtained_from' => 'hc_resource',
        'hc_located_at' => 'hc_location',
        'hc_owned_by' => 'hc_person',
      ),
      array( // Sub types.
        'BoatBuildingAndMending' => 'hc:BoatBuildingAndMending',
        'BuilderSMerchants' => 'hc:BuilderSMerchants',
        'Butcher' => 'hc:Butcher',
        'Chandler' => 'hc:Chandler',
        'Engineering' => 'hc:Engineering',
        'FerryOperators' => 'hc:FerryOperators',
        'FinancialServicesOrganization' => 'hc:FinancialServicesOrganization',
        'FishProcessing' => 'hc:FishProcessing',
        'Fishing' => 'hc:Fishing',
        'Garage' => 'hc:Garage',
        'GroceryShop' => 'hc:GroceryShop',
        'HarrisTweedManufacturers' => 'hc:HarrisTweedManufacturers',
        'Haulage' => 'hc:Haulage',
        'InformationTechnology' => 'hc:InformationTechnology',
        'Manufacturing' => 'hc:Manufacturing',
        'OilProduction' => 'hc:OilProduction',
        'PainterDecorator' => 'hc:PainterDecorator',
        'Pharmacy' => 'hc:Pharmacy',
        'PrinterAndPublisher' => 'hc:PrinterAndPublisher',
        'PublicHouse' => 'hc:PublicHouse',
        'PublicTransport' => 'hc:PublicTransport',
        'PublishingCompany' => 'hc:PublishingCompany',
        'Retail' => 'hc:Retail',
        'SalmonFarm' => 'hc:SalmonFarm',
        'SeaweedHarvestingAndDrying' => 'hc:SeaweedHarvestingAndDrying',
        'ShippingCompany' => 'hc:ShippingCompany',
        'Shoemaker' => 'hc:Shoemaker',
        'TeaRoom' => 'hc:TeaRoom',
        'Transportation' => 'hc:Transportation',
        'Undertaker' => 'hc:Undertaker',
        'Weaving' => 'hc:Weaving',
        'Wholesaler' => 'hc:Wholesaler',
      )
    );

    $config['rdf_resources']['hc_croft_or_residence'] = new RDFResource('hc_croft_or_residence', 'CroftOrResidence', 'hc:CroftOrResidence',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_location'],
        $config['rdf_fields']['hc_date_built'],
        $config['rdf_fields']['hc_date_demolished'],
        $config['rdf_fields']['hc_date_founded'],
        $config['rdf_fields']['hc_date_lotted'],
        $config['rdf_fields']['hc_geo_ref'],
        $config['rdf_fields']['hc_period'],
        $config['rdf_fields']['hc_period_of_construction_use'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_lived_here'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_located_here'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_historical_event',
            'hc_landmark_or_archaeological_site',
            'hc_business',
            'hc_person',
            'hc_story_report_or_tradition',
            'hc_croft_or_residence',
            'hc_object_or_artefact', // not in may2012 ontology
        ),
        'hc_information_obtained_from' => 'hc_organisation',
        'hc_lived_here' => 'hc_person',
        'hc_located_at' => 'hc_location',
        'hc_located_here' => array('hc_building_or_public_amenity', 'hc_landmark_or_archaeological_site'),
      ),
      array( // Sub type.
        'Croft' => 'hc:Croft',
        'Estate' => 'hc:Estate',
        'EstateLodge' => 'hc:EstateLodge',
        'FarmTack' => 'hc:FarmTack',
        'Feu' => 'hc:Feu',
        'Field' => 'hc:Field',
        'Flat' => 'hc:Flat',
        'Hotel' => 'hc:Hotel',
        'House' => 'hc:House',
        'Inn' => 'hc:Inn',
        'Manse' => 'hc:Manse',
        'MissionHouse' => 'hc:MissionHouse',
        'PoliceStation' => 'hc:PoliceStation',
        'SmallHouseOnCroft' => 'hc:SmallHouseOnCroft',
        'Smallholding' => 'hc:Smallholding',
      )
    );

    $config['rdf_resources']['hc_gaelic_verse'] = new RDFResource('hc_gaelic_verse', 'GaelicVerse', 'hc:GaelicVersebRdachd',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_date'],
        $config['rdf_fields']['hc_theme'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_composed_by'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_has_file'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_person',
            'hc_building_or_public_amenity',
            'hc_story_report_or_tradition',
            'hc_croft_or_residence',
            'hc_natural_landscape_feature',
            'hc_historical_event',
            'hc_croft_or_residence',
            'hc_boat',
            'hc_location',
        ),
        'hc_composed_by' => 'hc_person',
        'hc_information_obtained_from' => 'hc_resource',
      )
    );

    $config['rdf_resources']['hc_historical_event'] = new RDFResource('hc_historical_event', 'HistoricalEvent', 'hc:HistoricalEvent',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_event'],
        $config['rdf_fields']['hc_date'],
        $config['rdf_fields']['hc_date_established'],
        $config['rdf_fields']['hc_geo_ref'],
        //$config['rdf_fields']['hc_location_type'],
        //$config['rdf_fields']['hc_source_type'],
        //$config['rdf_fields']['hc_subject'],
        $config['rdf_fields']['hc_time_period'],
        //$config['rdf_fields']['hc_type'],
        //$config['rdf_fields']['hc_type_of_organisation'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_source_of_information_on'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_croft_or_residence',
            'hc_boat',
            'hc_building_or_public_amenity',
            'hc_person',
            'hc_business',
            'hc_organisation',
            'hc_natural_landscape_feature',
            'hc_historical_event',
            'hc_historical_event',
            'hc_location',
            'hc_landmark_or_archaeological_site',
            'hc_story_report_or_tradition',
        ),
        'hc_information_obtained_from' => 'hc_resource',
      ),
      array( // Sub type.
        'Battle' => 'hc:Battle',
        'Conflict' => 'hc:Conflict',
        'Education' => 'hc:Education',
        'Emigration' => 'hc:Emigration',
        'Fishing' => 'hc:Fishing',
        'GovernmentLegislation' => 'hc:GovernmentLegislation',
        'LandIssues' => 'hc:LandIssues',
        'NationalEvent' => 'hc:NationalEvent',
        'NaturalDisaster' => 'hc:NaturalDisaster',
        'OtherMilitary' => 'hc:OtherMilitary',
        'PeriodOfOwnership' => 'hc:PeriodOfOwnership',
        'Rebellion' => 'hc:Rebellion',
      )
    );

    $config['rdf_resources']['hc_landmark_or_archaeological_site'] = new RDFResource('hc_landmark_or_archaeological_site', 'LandmarkOrArchaeologicalSite', 'hc:LandmarkOrArchaeologicalSite',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_site'],
        //$config['rdf_fields']['hc_natural_landmark_type'],
        $config['rdf_fields']['hc_period'],
        $config['rdf_fields']['hc_period_of_construction_use'],
        //$config['rdf_fields']['hc_residence_type'],
        //$config['rdf_fields']['hc_site_type'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_smr_record_id'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_source_of_information_on'],
        $config['rdf_fields']['hc_comprises_sub_site'],
        $config['rdf_fields']['hc_is_part_of_site'],
        $config['rdf_fields']['hc_lived_here'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_located_here'],
      ),
      array( // Object field ranges.
          'hc_associated_with' => array(
              'hc_story_report_or_tradition',
              'hc_person',
              'hc_croft_or_residence',
              'hc_building_or_public_amenity',
              'hc_natural_landscape_feature',
              'hc_landmark_or_archaeological_site',
              'hc_location',
              'hc_historical_event',
          ),
          'hc_comprises_sub_site' => 'hc_landmark_or_archaeological_site',
          'hc_is_part_of_site' => 'hc_landmark_or_archaeological_site',
          'hc_information_obtained_from' => 'hc_resource',
          'hc_lived_here' => 'hc_person',
          'hc_located_at' => array('hc_croft_or_residence', 'hc_natural_landscape_feature', 'hc_location'),
      ),
      array( // Sub type.
        'Altar' => 'hc:Altar',
        'Arch' => 'hc:Arch',
        'ArmyCamp' => 'hc:ArmyCamp',
        'AtlanticRoundHouse' => 'hc:AtlanticRoundHouse',
        'BankEarthwork' => 'hc:BankEarthwork',
        'Barn' => 'hc:Barn',
        'Battlefield' => 'hc:Battlefield',
        'BlackHouse' => 'hc:BlackHouse',
        'BlacksmithsWorkshop' => 'hc:BlacksmithsWorkshop',
        'BoatStore' => 'hc:BoatStore',
        'Bothan' => 'hc:Bothan',
        'Bothy' => 'hc:Bothy',
        'BoundaryMarker' => 'hc:BoundaryMarker',
        'Breakwater' => 'hc:Breakwater',
        'Bridge' => 'hc:Bridge',
        'Broch' => 'hc:Broch',
        'Building' => 'hc:Building',
        'Bungalow' => 'hc:Bungalow',
        'Burial' => 'hc:Burial',
        'BurialCairn' => 'hc:BurialCairn',
        'BurialGround' => 'hc:BurialGround',
        'Cairn' => 'hc:Cairn',
        'Cairnfield' => 'hc:Cairnfield',
        'Canal' => 'hc:Canal',
        'CarvedStone' => 'hc:CarvedStone',
        'Castle' => 'hc:Castle',
        'Causeway' => 'hc:Causeway',
        'Cave' => 'hc:Cave',
        'Cell' => 'hc:Cell',
        'Cemetery' => 'hc:Cemetery',
        'ChamberedCairn' => 'hc:ChamberedCairn',
        'Chapel' => 'hc:Chapel',
        'Church' => 'hc:Church',
        'CineraryUrn' => 'hc:CineraryUrn',
        'Cist' => 'hc:Cist',
        'ClapperBridge' => 'hc:ClapperBridge',
        'ClearanceCairn' => 'hc:ClearanceCairn',
        'ClearanceSettlement' => 'hc:ClearanceSettlement',
        'CommemorativeMonument' => 'hc:CommemorativeMonument',
        'CornDryingKiln' => 'hc:CornDryingKiln',
        'CornMill' => 'hc:CornMill',
        'CorralOrFank' => 'hc:CorralOrFank',
        'CowHouse' => 'hc:CowHouse',
        'Crannog' => 'hc:Crannog',
        'Cross' => 'hc:Cross',
        'CultivationMarks' => 'hc:CultivationMarks',
        'CupMarkedStone' => 'hc:CupMarkedStone',
        'CurvilinearEnclosure' => 'hc:CurvilinearEnclosure',
        'Dam' => 'hc:Dam',
        'Distillery' => 'hc:Distillery',
        'Dock' => 'hc:Dock',
        'Drain' => 'hc:Drain',
        'DrainageDitch' => 'hc:DrainageDitch',
        'DrainageSystem' => 'hc:DrainageSystem',
        'Dun' => 'hc:Dun',
        'Dwelling' => 'hc:Dwelling',
        'Dyke' => 'hc:Dyke',
        'DykeDefence' => 'hc:DykeDefence',
        'Enclosure' => 'hc:Enclosure',
        'Engine' => 'hc:Engine',
        'Farmstead' => 'hc:Farmstead',
        'Feannagen' => 'hc:Feannagen',
        'Field' => 'hc:Field',
        'FieldBoundary' => 'hc:FieldBoundary',
        'FieldDyke' => 'hc:FieldDyke',
        'FieldSystem' => 'hc:FieldSystem',
        'Findspot' => 'hc:Findspot',
        'FishGarth' => 'hc:FishGarth',
        'FishProcessingSite' => 'hc:FishProcessingSite',
        'FishTrap' => 'hc:FishTrap',
        'FishingSite' => 'hc:FishingSite',
        'Fishtrap' => 'hc:Fishtrap',
        'FloodDefences' => 'hc:FloodDefences',
        'Font' => 'hc:Font',
        'Footbridge' => 'hc:Footbridge',
        'Footpath' => 'hc:Footpath',
        'Fort' => 'hc:Fort',
        'Garden' => 'hc:Garden',
        'Gate' => 'hc:Gate',
        'Grave' => 'hc:Grave',
        'GraveMarker' => 'hc:GraveMarker',
        'GraveSlab' => 'hc:GraveSlab',
        'Gravestone' => 'hc:Gravestone',
        'Harbour' => 'hc:Harbour',
        'HeadDyke' => 'hc:HeadDyke',
        'HorizontalMill' => 'hc:HorizontalMill',
        'House' => 'hc:House',
        'HumanRemains' => 'hc:HumanRemains',
        'HuntingLodge' => 'hc:HuntingLodge',
        'Hut' => 'hc:Hut',
        'HutCircle' => 'hc:HutCircle',
        'Island' => 'hc:Island',
        'Jetty' => 'hc:Jetty',
        'KelpKiln' => 'hc:KelpKiln',
        'KerbCairn' => 'hc:KerbCairn',
        'Kiln' => 'hc:Kiln',
        'Kitchen' => 'hc:Kitchen',
        'LandingPier' => 'hc:LandingPier',
        'LandingPoint' => 'hc:LandingPoint',
        'LandingStage' => 'hc:LandingStage',
        'Leat' => 'hc:Leat',
        'LinearClearanceCairn' => 'hc:LinearClearanceCairn',
        'LithicWorkingSite' => 'hc:LithicWorkingSite',
        'LobsterPool' => 'hc:LobsterPool',
        'Lodge' => 'hc:Lodge',
        'Longhouse' => 'hc:Longhouse',
        'Manse' => 'hc:Manse',
        'MarchDyke' => 'hc:MarchDyke',
        'MarkerCairn' => 'hc:MarkerCairn',
        'Mausoleum' => 'hc:Mausoleum',
        'Midden' => 'hc:Midden',
        'MilitaryBuilding' => 'hc:MilitaryBuilding',
        'Mill' => 'hc:Mill',
        'MillDam' => 'hc:MillDam',
        'MillRace' => 'hc:MillRace',
        'MissionHall' => 'hc:MissionHall',
        'Monastery' => 'hc:Monastery',
        'Monument' => 'hc:Monument',
        'Mound' => 'hc:Mound',
        'Naust' => 'hc:Naust',
        'NetStore' => 'hc:NetStore',
        'NorseMill' => 'hc:NorseMill',
        'Nunnery' => 'hc:Nunnery',
        'OccupationSite' => 'hc:OccupationSite',
        'Path' => 'hc:Path',
        'Pier' => 'hc:Pier',
        'Pit' => 'hc:Pit',
        'Platform' => 'hc:Platform',
        'PostOffice' => 'hc:PostOffice',
        'PotteryWorkshop' => 'hc:PotteryWorkshop',
        'PowerStation' => 'hc:PowerStation',
        'PrefabricatedBuilding' => 'hc:PrefabricatedBuilding',
        'PromontoryEnclosure' => 'hc:PromontoryEnclosure',
        'Quarry' => 'hc:Quarry',
        'RectilinearEnclosure' => 'hc:RectilinearEnclosure',
        'ReligiousHouse' => 'hc:ReligiousHouse',
        'Revetment' => 'hc:Revetment',
        'Road' => 'hc:Road',
        'RoadBridge' => 'hc:RoadBridge',
        'RockCarving' => 'hc:RockCarving',
        'RockShelter' => 'hc:RockShelter',
        'RoundHouseComplexAtlantic' => 'hc:RoundHouseComplexAtlantic',
        'School' => 'hc:School',
        'SchoolHouse' => 'hc:SchoolHouse',
        'SeaDefences' => 'hc:SeaDefences',
        'Settlement' => 'hc:Settlement',
        'SettlementMound' => 'hc:SettlementMound',
        'Shed' => 'hc:Shed',
        'SheepDip' => 'hc:SheepDip',
        'SheepFold' => 'hc:SheepFold',
        'SheepHouse' => 'hc:SheepHouse',
        'ShellMidden' => 'hc:ShellMidden',
        'Shelter' => 'hc:Shelter',
        'Shieling' => 'hc:Shieling',
        'ShielingHut' => 'hc:ShielingHut',
        'Shop' => 'hc:Shop',
        'Site' => 'hc:Site',
        'Slipway' => 'hc:Slipway',
        'SmokeHouse' => 'hc:SmokeHouse',
        'Souterrain' => 'hc:Souterrain',
        'Spring' => 'hc:Spring',
        'StackYard' => 'hc:StackYard',
        'StandingStone' => 'hc:StandingStone',
        'SteppingStones' => 'hc:SteppingStones',
        'Steps' => 'hc:Steps',
        'StillHouse' => 'hc:StillHouse',
        'StillingHouse' => 'hc:StillingHouse',
        'StockEnclosure' => 'hc:StockEnclosure',
        'Stone' => 'hc:Stone',
        'StoneAlignment' => 'hc:StoneAlignment',
        'StoneCircle' => 'hc:StoneCircle',
        'StoneSetting' => 'hc:StoneSetting',
        'Structure' => 'hc:Structure',
        'TeachersHouse' => 'hc:TeachersHouse',
        'Toilet' => 'hc:Toilet',
        'TownVillage' => 'hc:TownVillage',
        'Township' => 'hc:Township',
        'UndergroundStructure' => 'hc:UndergroundStructure',
        'VegetableGarden' => 'hc:VegetableGarden',
        'Wall' => 'hc:Wall',
        'WarMemorial' => 'hc:WarMemorial',
        'Watercourse' => 'hc:Watercourse',
        'Watermill' => 'hc:Watermill',
        'Well' => 'hc:Well',
        'WheelHouse' => 'hc:WheelHouse',
        'Wreck' => 'hc:Wreck',
      )
    );

    $config['rdf_resources']['hc_location'] = new RDFResource('hc_location', 'Location', 'hc:Location',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],
        $config['rdf_fields']['hc_also_known_as'],

        $config['rdf_fields']['hc_type_of_location'],
        $config['rdf_fields']['hc_geo_ref'],
        $config['rdf_fields']['hc_period_of_construction_use'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_found_here'],
        $config['rdf_fields']['hc_lived_here'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_located_here'],
        $config['rdf_fields']['hc_located_near'],
        $config['rdf_fields']['hc_person_born_here'],
        $config['rdf_fields']['hc_person_who_died_here'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_story_report_or_tradition',
            'hc_organisation',
            'hc_boat',
            'hc_person',
            'hc_business',
            'hc_location',
            'hc_object_or_artefact',
            'hc_natural_landscape_feature',
            'hc_historical_event',
            'hc_building_or_public_amenity',
            'hc_landmark_or_archaeological_site',
        ),
        'hc_information_obtained_from' => 'hc_resource',
        'hc_found_here' => 'hc_object_or_artefact',
        'hc_lived_here' => 'hc_person',
        'hc_located_at' => 'hc_location',
        'hc_located_here' => array('hc_business', 'hc_croft_or_residence', 'hc_landmark_or_archaeological_site'),
        'hc_located_near' => 'hc_natural_landscape_feature',
        'hc_person_who_died_here' => 'hc_person',
        'hc_person_born_here' => 'hc_person',
      ),
      array( // Sub types.
        'Archipelago' => 'hc:Archipelago',
        'Borough' => 'hc:Borough',
        'City' => 'hc:City',
        'Clachan' => 'hc:Clachan',
        'ColonialTerritory' => 'hc:ColonialTerritory',
        'Continent' => 'hc:Continent',
        'Country' => 'hc:Country',
        'County' => 'hc:County',
        'Croft' => 'hc:Croft',
        'DistrictWard' => 'hc:DistrictWard',
        'EnglishCounty' => 'hc:EnglishCounty',
        'Estate' => 'hc:Estate',
        'FarmTack' => 'hc:FarmTack',
        'Glen' => 'hc:Glen',
        'GrazingMoor' => 'hc:GrazingMoor',
        'GroupOfIslands' => 'hc:GroupOfIslands',
        'Hamlet' => 'hc:Hamlet',
        'Headland' => 'hc:Headland',
        'Hillock' => 'hc:Hillock',
        'House' => 'hc:House',
        'HousingScheme' => 'hc:HousingScheme',
        'Island' => 'hc:Island',
        'MilitaryBase' => 'hc:MilitaryBase',
        'NavalBase' => 'hc:NavalBase',
        'Parish' => 'hc:Parish',
        'Province' => 'hc:Province',
        'Region' => 'hc:Region',
        'Road' => 'hc:Road',
        'RuralArea' => 'hc:RuralArea',
        'ScottishCounty' => 'hc:ScottishCounty',
        'SeaLoch' => 'hc:SeaLoch',
        'Settlement' => 'hc:Settlement',
        'ShielingCluster' => 'hc:ShielingCluster',
        'State' => 'hc:State',
        'Strait' => 'hc:Strait',
        'Street' => 'hc:Street',
        'Territory' => 'hc:Territory',
        'Town' => 'hc:Town',
        'Township' => 'hc:Township',
        'VillageTownship' => 'hc:VillageTownship',
      )
    );

    $config['rdf_resources']['hc_natural_landscape_feature'] = new RDFResource('hc_natural_landscape_feature', 'NaturalLandscapeFeature', 'hc:NaturalLandscapeFeature',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],
        $config['rdf_fields']['hc_also_known_as'],

        $config['rdf_fields']['hc_type_of_natural_landscape_fea'],
        $config['rdf_fields']['hc_geo_ref'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_found_here'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_located_here'],
        $config['rdf_fields']['hc_located_near'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_story_report_or_tradition',
            'hc_boat',
            'hc_person',
            'hc_historical_event',
            'hc_croft_or_residence',
            'hc_landmark_or_archaeological_site',
            'hc_gaelic_verse',
            'hc_building_or_public_amenity',
            'hc_location', // not in may2012-ontology (TODO check reasoner output)
        ),
        'hc_found_here' => 'hc_object_or_artefact',
        'hc_information_obtained_from' => 'hc_resource',
        'hc_located_at' => 'hc_location',
        'hc_located_here' => 'hc_landmark_or_archaeological_site',
        'hc_located_near' => array('hc_location', 'hc_natural_landscape_feature'),
      ),
      array( // Sub type.
        'Archipelago' => 'hc:Archipelago',
        'Bay' => 'hc:Bay',
        'Beach' => 'hc:Beach',
        'Burn' => 'hc:Burn',
        'Fiord' => 'hc:Fiord',
        'Glen' => 'hc:Glen',
        'Headland' => 'hc:Headland',
        'Hill' => 'hc:Hill',
        'Island' => 'hc:Island',
        'Knoll' => 'hc:Knoll',
        'LochFreshwater' => 'hc:LochFreshwater',
        'Machair' => 'hc:Machair',
        'Mountain' => 'hc:Mountain',
        'Other' => 'hc:Other',
        'Peak' => 'hc:Peak',
        'Point' => 'hc:Point',
        'River' => 'hc:River',
        'Rock' => 'hc:Rock',
        'SaltwaterChannel' => 'hc:SaltwaterChannel',
        'SeaLoch' => 'hc:SeaLoch',
        'SeaRock' => 'hc:SeaRock',
        'SeaStack' => 'hc:SeaStack',
        'Skerry' => 'hc:Skerry',
        'Spring' => 'hc:Spring',
        'Valley' => 'hc:Valley',
        'Woodland' => 'hc:Woodland',
      )
    );

    $config['rdf_resources']['hc_object_or_artefact'] = new RDFResource('hc_object_or_artefact', 'ObjectOrArtefact', 'hc:ObjectOrArtefact',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_object_artefact'],
        $config['rdf_fields']['hc_period'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_smr_record_id'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_found_at'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
          'hc_boat',
          'hc_building_or_public_amenity',
          'hc_story_report_or_tradition',
          'hc_person',
          'hc_location',
          'hc_historical_event',
          'hc_resource',
          'hc_object_or_artefact',
          'hc_croft_or_residence',
        ),
        'hc_information_obtained_from' => 'hc_resource',
        'hc_found_at' => array('hc_location', 'hc_natural_landscape_feature', 'hc_landmark_or_archaeological_site'),
      ),
      array( // Sub type.
        'Arrowhead' => 'hc:Arrowhead',
        'Axe' => 'hc:Axe',
        'BallRitual' => 'hc:BallRitual',
        'Bead' => 'hc:Bead',
        'Beaker' => 'hc:Beaker',
        'Bench' => 'hc:Bench',
        'Boat' => 'hc:Boat',
        'Book' => 'hc:Book',
        'Bowl' => 'hc:Bowl',
        'Brooch' => 'hc:Brooch',
        'Buoy' => 'hc:Buoy',
        'BurntFlint' => 'hc:BurntFlint',
        'ButterChurn' => 'hc:ButterChurn',
        'ButterMarker' => 'hc:ButterMarker',
        'CarpentersTool' => 'hc:CarpentersTool',
        'CartLamp' => 'hc:CartLamp',
        'ChessPieces' => 'hc:ChessPieces',
        'CineraryUrn' => 'hc:CineraryUrn',
        'Clock' => 'hc:Clock',
        'CoffinPlane' => 'hc:CoffinPlane',
        'CoinHoard' => 'hc:CoinHoard',
        'Comb' => 'hc:Comb',
        'CommunionToken' => 'hc:CommunionToken',
        'Compass' => 'hc:Compass',
        'Core' => 'hc:Core',
        'CreelMaking' => 'hc:CreelMaking',
        'CuppingHorn' => 'hc:CuppingHorn',
        'Desk' => 'hc:Desk',
        'Documents' => 'hc:Documents',
        'DrinkingVessel' => 'hc:DrinkingVessel',
        'DyeingVessel' => 'hc:DyeingVessel',
        'FishFinder' => 'hc:FishFinder',
        'FishTrap' => 'hc:FishTrap',
        'FishingBuoy' => 'hc:FishingBuoy',
        'FishingEquipment' => 'hc:FishingEquipment',
        'FishingFloats' => 'hc:FishingFloats',
        'FishingHandLine' => 'hc:FishingHandLine',
        'FishingNet' => 'hc:FishingNet',
        'FlounderLine' => 'hc:FlounderLine',
        'FogHorn' => 'hc:FogHorn',
        'GamingPiece' => 'hc:GamingPiece',
        'GasMask' => 'hc:GasMask',
        'GreatLine' => 'hc:GreatLine',
        'Gunflint' => 'hc:Gunflint',
        'HarpoonShipsLog' => 'hc:HarpoonShipsLog',
        'HerringScuttle' => 'hc:HerringScuttle',
        'HolyWaterVessel' => 'hc:HolyWaterVessel',
        'HotWaterBottle' => 'hc:HotWaterBottle',
        'HumanRemains' => 'hc:HumanRemains',
        'JackPlane' => 'hc:JackPlane',
        'Jug' => 'hc:Jug',
        'LandingNet' => 'hc:LandingNet',
        'LanternGlass' => 'hc:LanternGlass',
        'Loom' => 'hc:Loom',
        'Loomweight' => 'hc:Loomweight',
        'Mace' => 'hc:Mace',
        'Mangle' => 'hc:Mangle',
        'Mast' => 'hc:Mast',
        'Matchbox' => 'hc:Matchbox',
        'MealChest' => 'hc:MealChest',
        'Medal' => 'hc:Medal',
        'MobilePulpit' => 'hc:MobilePulpit',
        'ModelBoat' => 'hc:ModelBoat',
        'MushroomPuffball' => 'hc:MushroomPuffball',
        'Oar' => 'hc:Oar',
        'OilLamp' => 'hc:OilLamp',
        'Ornament' => 'hc:Ornament',
        'PeatIron' => 'hc:PeatIron',
        'Pendant' => 'hc:Pendant',
        'Pin' => 'hc:Pin',
        'Pointer' => 'hc:Pointer',
        'Pot' => 'hc:Pot',
        'Rifle' => 'hc:Rifle',
        'Rope' => 'hc:Rope',
        'Ruler' => 'hc:Ruler',
        'Scales' => 'hc:Scales',
        'ScraperTool' => 'hc:ScraperTool',
        'Scythe' => 'hc:Scythe',
        'ShipRegistrationPlate' => 'hc:ShipRegistrationPlate',
        'ShipwrightSTool' => 'hc:ShipwrightSTool',
        'Shirt' => 'hc:Shirt',
        'ShoemakerTools' => 'hc:ShoemakerTools',
        'Shoes' => 'hc:Shoes',
        'Slag' => 'hc:Slag',
        'Slate' => 'hc:Slate',
        'SmallBasket' => 'hc:SmallBasket',
        'SnakeStone' => 'hc:SnakeStone',
        'SovereignCase' => 'hc:SovereignCase',
        'Spoon' => 'hc:Spoon',
        'StKildaMailBoat' => 'hc:StKildaMailBoat',
        'StrapFitting' => 'hc:StrapFitting',
        'SwaggerStick' => 'hc:SwaggerStick',
        'TilleyLamp' => 'hc:TilleyLamp',
        'TinPail' => 'hc:TinPail',
        'UnidentifiedObject' => 'hc:UnidentifiedObject',
        'UnknownItem' => 'hc:UnknownItem',
        'Vessel' => 'hc:Vessel',
        'Wall' => 'hc:Wall',
        'WashBasin' => 'hc:WashBasin',
        'WashBasinStand' => 'hc:WashBasinStand',
        'WeftWinder' => 'hc:WeftWinder',
        'WoodenChest' => 'hc:WoodenChest',
      )
    );

    $config['rdf_resources']['hc_organisation'] = new RDFResource('hc_organisation', 'Organisation', 'hc:Organisation',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_organisation'],
        $config['rdf_fields']['hc_date_established'],
        $config['rdf_fields']['hc_date_of_source'],
        $config['rdf_fields']['hc_geo_ref'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
        //$config['rdf_fields']['hc_source_type'],
        //$config['rdf_fields']['hc_type_of_building_public_amty'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_compiler_of'],
        $config['rdf_fields']['hc_holds'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_source_of_information_on'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_location',
            'hc_historical_event',
            'hc_story_report_or_tradition',
            'hc_boat',
            'hc_building_or_public_amenity',
            'hc_person',
            'hc_croft_or_residence',
            'hc_organisation',
        ),
        'hc_compiler_of' => 'hc_resource',
        'hc_information_obtained_from' => 'hc_resource',
        'hc_holds' => 'hc_resource',
        'hc_located_at' => 'hc_location', // not in may2012-ontology
        'hc_source_of_information_on' => array('hc_location', 'hc_person'), // not in may2012-ontology
      ),
      array( // Sub type.
        '1847' => 'hc:1847',
        'Charity' => 'hc:Charity',
        'ClanSociety' => 'hc:ClanSociety',
        'Educational' => 'hc:Educational',
        'HistoricalSociety' => 'hc:HistoricalSociety',
        'LandManagemenrt' => 'hc:LandManagemenrt',
        'LandOwningTrust' => 'hc:LandOwningTrust',
        'LawEnforcement' => 'hc:LawEnforcement',
        'LocalGovernment' => 'hc:LocalGovernment',
        'MasonicLodge' => 'hc:MasonicLodge',
        'Military' => 'hc:Military',
        'NationalGovernment' => 'hc:NationalGovernment',
        'OtherPublicBody' => 'hc:OtherPublicBody',
        'Political' => 'hc:Political',
        'Recreational' => 'hc:Recreational',
        'Religious' => 'hc:Religious',
        'Utility' => 'hc:Utility',
        'Voluntary' => 'hc:Voluntary',
      )
    );

    $config['rdf_resources']['hc_person'] = new RDFResource('hc_person', 'Person', 'hc:Person',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],
        $config['rdf_fields']['hc_also_known_as'],

        $config['rdf_fields']['hc_born'],
        $config['rdf_fields']['hc_date'],
        $config['rdf_fields']['hc_date_of_death'],
        $config['rdf_fields']['hc_date_of_marriage'],
        $config['rdf_fields']['hc_geo_ref'],
        $config['rdf_fields']['hc_occupation'],
        $config['rdf_fields']['hc_sex'],
        $config['rdf_fields']['hc_northing'],
        $config['rdf_fields']['hc_easting'],

        $config['rdf_fields']['hc_owned_by_society'],
      	$config['rdf_fields']['hc_bk_reference'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_adopted_by'],
        $config['rdf_fields']['hc_adopted_person'],
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_author_originator_of'],
        $config['rdf_fields']['hc_born_in'],
        $config['rdf_fields']['hc_builder'],
        $config['rdf_fields']['hc_child_of'],
        $config['rdf_fields']['hc_composed_song'],
        $config['rdf_fields']['hc_died_in'],
        $config['rdf_fields']['hc_emigrated_to'],
        $config['rdf_fields']['hc_employed'],
        $config['rdf_fields']['hc_employed_by'],
        $config['rdf_fields']['hc_fostered_by'],
        $config['rdf_fields']['hc_fostered_person'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_immigrant_from'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_lived_at'],
        $config['rdf_fields']['hc_lived_with'],
        $config['rdf_fields']['hc_married'],
        $config['rdf_fields']['hc_may_be_the_same_as'],
        $config['rdf_fields']['hc_moved_from'],
        $config['rdf_fields']['hc_moved_to'],
        $config['rdf_fields']['hc_on_crew_of_boat'],
        $config['rdf_fields']['hc_owned'],
        $config['rdf_fields']['hc_parent_of'],
        $config['rdf_fields']['hc_related_to'],
        $config['rdf_fields']['hc_sibling_of'],
        $config['rdf_fields']['hc_used_object'],
      ),
      array( // Object field ranges.
        'hc_adopted_by' => 'hc_person',
        'hc_adopted_person' => 'hc_person',
        'hc_associated_with' => array(
            'hc_landmark_or_archaeological_site',
            'hc_business',
            'hc_historical_event',
            'hc_location',
            'hc_gaelic_verse',
            'hc_object_or_artefact',
            'hc_natural_landscape_feature',
            'hc_story_report_or_tradition',
            'hc_boat',
            'hc_person',
            'hc_croft_or_residence',
            'hc_organisation',
            'hc_person',
            'hc_building_or_public_amenity',
            'hc_resource',
        ),
        'hc_author_originator_of' => 'hc_resource',
        'hc_born_in' => 'hc_location',
        'hc_builder' => 'hc_boat',
        'hc_child_of' => 'hc_person',
        'hc_composed_song' => 'hc_gaelic_verse',
        'hc_died_in' => 'hc_location',
        'hc_emigrated_to' => 'hc_location',
        'hc_employed' => 'hc_person',
        'hc_employed_by' => array('hc_person', 'hc_business'),
        'hc_fostered_by' => 'hc_person',
        'hc_fostered_person' => 'hc_person',
        'hc_immigrant_from' => 'hc_location',
        'hc_information_obtained_from' => 'hc_resource',
        'hc_lived_at' => array('hc_landmark_or_archaeological_site', 'hc_location', 'hc_croft_or_residence'),
        'hc_lived_with' => 'hc_person',
        'hc_married' => 'hc_person',
        'hc_may_be_the_same_as' => 'hc_person',
        'hc_moved_from' => 'hc_person',
        'hc_moved_to' => 'hc_person',
        'hc_on_crew_of_boat' => 'hc_boat',
        'hc_owned' => array('hc_business', 'hc_boat'),
        'hc_parent_of' => 'hc_person',
        'hc_related_to' => 'hc_person',
        'hc_sibling_of' => 'hc_person',
        'hc_used_object' => 'hc_object_or_artefact',
      )
    );

    $config['rdf_resources']['hc_resource'] = new RDFResource('hc_resource', 'Resource', 'hc:Resource',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_date'],
        $config['rdf_fields']['hc_date_established'],
        $config['rdf_fields']['hc_date_of_source'],
        $config['rdf_fields']['hc_geo_ref'],
        $config['rdf_fields']['hc_occupation'],
        $config['rdf_fields']['hc_period'],
        $config['rdf_fields']['hc_sex'],
        $config['rdf_fields']['hc_source_type'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_bk_reference'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_compiled_maintained_by'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_source_of_information_on'],
        $config['rdf_fields']['hc_written_compiled_by'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array('hc_person', 'hc_resource', 'hc_location'),
        'hc_compiled_maintained_by' => 'hc_organisation',
        'hc_information_obtained_from' => 'hc_resource',
        //'hc_located_at'
        'hc_source_of_information_on' => array(
            'hc_building_or_public_amenity',
            'hc_historical_event',
            'hc_landmark_or_archaeological_site',
            'hc_story_report_or_tradition',
            'hc_croft_or_residence',
            'hc_boat',
            'hc_location',
            'hc_organisation',
            'hc_person',
        ),
        'hc_written_compiled_by' => 'hc_person',
      )
    );

    $config['rdf_resources']['hc_story_report_or_tradition'] = new RDFResource('hc_story_report_or_tradition', 'StoryReportOrTradition', 'hc:StoryReportOrTradition',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_story_report_traditio'],
        $config['rdf_fields']['hc_date'],
        $config['rdf_fields']['hc_date_established'],
        $config['rdf_fields']['hc_date_of_source'],
        $config['rdf_fields']['hc_geo_ref'],
        $config['rdf_fields']['hc_period_of_construction_use'],
        $config['rdf_fields']['hc_theme'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_composed_by'],
        $config['rdf_fields']['hc_has_file'],
        $config['rdf_fields']['hc_information_obtained_from'],
        $config['rdf_fields']['hc_located_at'],
        $config['rdf_fields']['hc_source_of_information_on'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array(
            'hc_landmark_or_archaeological_site',
            'hc_location',
            'hc_business',
            'hc_natural_landscape_feature',
            'hc_object_or_artefact',
            'hc_organisation',
            'hc_gaelic_verse',
            'hc_person',
            'hc_boat',
            'hc_croft_or_residence',
            'hc_story_report_or_tradition',
            'hc_historical_event',
            'hc_building_or_public_amenity',
            'hc_croft_or_residence',
        ),
        'hc_information_obtained_from' => 'hc_resource',
        'hc_composed_by' => 'hc_person', // none of these are in may2012-ontology
//        'hc_located_at'
//        'hc_source_of_information_on'
      ),
      array( // Sub types.
        'Advert' => 'hc:Advert',
        'Bardachd' => 'hc:Bardachd',
        'Book' => 'hc:Book',
        'Commission' => 'hc:Commission',
        'ExtractFromBook' => 'hc:ExtractFromBook',
        'FamilyHistory' => 'hc:FamilyHistory',
        'Interview' => 'hc:Interview',
        'KirkSessionRecords' => 'hc:KirkSessionRecords',
        'Legend' => 'hc:Legend',
        'Letter' => 'hc:Letter',
        'LetterToNewspaper' => 'hc:LetterToNewspaper',
        'MagazineArticle' => 'hc:MagazineArticle',
        'Manuscript' => 'hc:Manuscript',
        'Meeting' => 'hc:Meeting',
        'NewspaperArticle' => 'hc:NewspaperArticle',
        'Obituary' => 'hc:Obituary',
        'OralTradition' => 'hc:OralTradition',
        'Other' => 'hc:Other',
        'PersonalHistory' => 'hc:PersonalHistory',
        'Poem' => 'hc:Poem',
        'PressCutting' => 'hc:PressCutting',
        'Radio' => 'hc:Radio',
        'Reminiscences' => 'hc:Reminiscences',
        'Report' => 'hc:Report',
        'StatisticalAccount' => 'hc:StatisticalAccount',
        'Story' => 'hc:Story',
        'TapeTranscription' => 'hc:TapeTranscription',
        'TestimonyOrEvidence' => 'hc:TestimonyOrEvidence',
        'Tradition' => 'hc:Tradition',
        'Travels' => 'hc:Travels',
      )
    );

    $config['rdf_resources']['hc_vehicle'] = new RDFResource('hc_vehicle', 'Vehicle', 'hc:Vehicle',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        $config['rdf_fields']['hc_english_name'],
        $config['rdf_fields']['hc_gaelic_name'],

        $config['rdf_fields']['hc_type_of_vehicle'],
        $config['rdf_fields']['hc_chassis'],
        $config['rdf_fields']['hc_registration'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_associated_with'],
        $config['rdf_fields']['hc_has_file'],
      ),
      array( // Object field ranges.
        'hc_associated_with' => array('hc_location', 'hc_business', 'hc_person', 'hc_croft_or_residence'),
      ),
      array( // Sub types.
        'Bus' => 'hc:Bus',
        'Car' => 'hc:Car',
        'GoodsVehicle' => 'hc:GoodsVehicle',
      )
    );

    $config['rdf_resources']['hc_image_file'] = new RDFResource('hc_image_file', 'Imagefile', 'hc:Imagefile',
      array( // Data fields.
        $config['rdf_fields']['dc_title'],
        $config['rdf_fields']['dc_description'],

        //$config['rdf_fields']['hc_title'],
        //$config['rdf_fields']['hc_description'],

        //$config['rdf_fields']['hc_copyright'],
        $config['rdf_fields']['hc_url'],
        //$config['rdf_fields']['hc_file_name'],
        //$config['rdf_fields']['hc_origin_date'],

        $config['rdf_fields']['hc_owned_by_society'],
        $config['rdf_fields']['hc_subject_id'],
      ),
      array( // Object fields.
        $config['rdf_fields']['hc_is_shown_here'],
      ),
      array( // Object field ranges.
        'hc_is_shown_here' => array(
          'hc_landmark_or_archaeological_site',
          'hc_business',
          'hc_historical_event',
          'hc_location',
          'hc_gaelic_verse',
          'hc_object_or_artefact',
          'hc_natural_landscape_feature',
          'hc_story_report_or_tradition',
          'hc_boat',
          'hc_person',
          'hc_croft_or_residence',
          'hc_organisation',
          'hc_person',
          'hc_building_or_public_amenity',
          'hc_resource',
      ))
    );



    $config['rdf_views'] = array();

    // General Subject
    $config['rdf_views']['hc_subjects'] = new RDFView('hc_subjects', 'ALL SUBJECTS', 'subjects', NULL,
      $config['rdf_resources']['hc_subject'], NULL, NULL);
    $config['rdf_views']['hc_subjects']->setOptionalAll();

    // People
    $config['rdf_views']['hc_people'] = new RDFView('hc_people', 'People', 'people', NULL,
      $config['rdf_resources']['hc_person'], NULL, NULL);
    $config['rdf_views']['hc_people']->setOptionalAll();

    // Organisations
    $config['rdf_views']['hc_organisations'] = new RDFView('hc_organisations', 'Organisations', 'organisations', NULL,
      $config['rdf_resources']['hc_organisation'], NULL, NULL);
    $config['rdf_views']['hc_organisations']->setOptionalAll();

    // Resources
    $config['rdf_views']['hc_resources'] = new RDFView('hc_resources', 'Resources', 'resources', NULL,
      $config['rdf_resources']['hc_resource'], NULL, NULL);
    $config['rdf_views']['hc_resources']->setOptionalAll();

    // Vehicles
    $config['rdf_views']['hc_vehicles'] = new RDFView('hc_vehicles', 'Vehicles', 'vehicles', NULL,
      $config['rdf_resources']['hc_vehicle'], NULL, NULL);
    $config['rdf_views']['hc_vehicles']->setOptionalAll();
    
    // Boats
    $config['rdf_views']['hc_boats'] = new RDFView('hc_boats', 'Boats', 'boats', NULL,
      $config['rdf_resources']['hc_boat'], NULL, NULL);
    $config['rdf_views']['hc_boats']->setOptionalAll();

    // Buildings and Public Amenities
    $config['rdf_views']['hc_buildings_and_public_amenities'] = new RDFView('hc_buildings_and_public_amenities', 'Buildings and Public Amenities', 'buildings-and-public-amenities', NULL,
      $config['rdf_resources']['hc_building_or_public_amenity'], NULL, NULL);
    $config['rdf_views']['hc_buildings_and_public_amenities']->setOptionalAll();

    // Businesses
    $config['rdf_views']['hc_businesses'] = new RDFView('hc_businesses', 'Businesses', 'businesses', NULL,
      $config['rdf_resources']['hc_business'], NULL, NULL);
    $config['rdf_views']['hc_businesses']->setOptionalAll();

    // Crofts and Residences
    $config['rdf_views']['hc_crofts_and_residences'] = new RDFView('hc_crofts_and_residences', 'Crofts and Residences', 'crofts-and-residences', NULL,
      $config['rdf_resources']['hc_croft_or_residence'], NULL, NULL);
    $config['rdf_views']['hc_crofts_and_residences']->setOptionalAll();

    // GaelicVersebRdachd
    $config['rdf_views']['hc_gaelic_verses'] = new RDFView('hc_gaelic_verses', 'Gaelic Verse', 'gaelic-verses', NULL,
      $config['rdf_resources']['hc_gaelic_verse'], NULL, NULL);
    $config['rdf_views']['hc_gaelic_verses']->setOptionalAll();

    // Historical Events
    $config['rdf_views']['hc_historical_events'] = new RDFView('hc_historical_events', 'Historical Events', 'historical-events', NULL,
      $config['rdf_resources']['hc_historical_event'], NULL, NULL);
    $config['rdf_views']['hc_historical_events']->setOptionalAll();

    // Landmarks and Archaeological Sites
    $config['rdf_views']['hc_landmarks_and_archaeological_sites'] = new RDFView('hc_landmarks_and_archaeological_sites', 'Landmarks and Archaeological Sites', 'landmarks-and-archaeological-sites', NULL,
      $config['rdf_resources']['hc_landmark_or_archaeological_site'], NULL, NULL);
    $config['rdf_views']['hc_landmarks_and_archaeological_sites']->setOptionalAll();

    // Location
    $config['rdf_views']['hc_locations'] = new RDFView('hc_locations', 'Locations', 'locations', NULL,
      $config['rdf_resources']['hc_location'], NULL, NULL);
    $config['rdf_views']['hc_locations']->setOptionalAll();

    // Natural Landscape Features
    $config['rdf_views']['hc_natural_landscape_features'] = new RDFView('hc_natural_landscape_features', 'Natural Landscape Features', 'natural-landscape-features', NULL,
      $config['rdf_resources']['hc_natural_landscape_feature'], NULL, NULL);
    $config['rdf_views']['hc_natural_landscape_features']->setOptionalAll();
    
    // Objects and Artefacts
    $config['rdf_views']['hc_objects_and_artefacts'] = new RDFView('hc_objects_and_artefacts', 'Objects and Artefacts', 'objects-and-artefacts', NULL,
      $config['rdf_resources']['hc_object_or_artefact'], NULL, NULL);
    $config['rdf_views']['hc_objects_and_artefacts']->setOptionalAll();

    // Oral Traditionbeul Aithrises
//    $config['rdf_views']['hc_oral_traditionbeul_aithrises'] = new RDFView('hc_oral_traditionbeul_aithrises', 'Oral Traditionbeul Aithrises', 'oral-traditionbeul-aithrises',
//      $config['rdf_resources']['hc_oral_traditionbeul_aithris']);
//    $config['rdf_views']['hc_oral_traditionbeul_aithrises']->setOptionalAll();

    // Story Reports and Traditions
    $config['rdf_views']['hc_stories_reports_and_traditions'] = new RDFView('hc_stories_reports_and_traditions', 'Stories, Reports and Traditions', 'stories-reports-and-traditions', NULL,
      $config['rdf_resources']['hc_story_report_or_tradition'], NULL, NULL);
    $config['rdf_views']['hc_stories_reports_and_traditions']->setOptionalAll();

    $config['rdf_views']['hc_image_details'] = new RDFView('hc_image_details', 'Image Details', 'images-details', NULL,
      $config['rdf_resources']['hc_image_file'], NULL, NULL);
    $config['rdf_views']['hc_image_details']->setOptionalAll();

    // DEBUG: remove unused resources.
    // $keep = array('hc_image_file', 'hc_person', 'hc_organisation', 'hc_resource', 'hc_vehicle');
    // foreach ($config['rdf_resources'] as $id=>$r) {
    //   if (!in_array($id, $keep)) {
    //     unset($config['rdf_resources'][$id]);
    //   }
    // }
    //print($config['rdf_resources']);

/*
echo <<<EOT
\$namespaces = array(
  'cms' => 'http://www.abdn.ac.uk/~csc363/ldcms.owl#',
  'hc'  => 'http://www.hebrideanconnections.com/hebridean.owl#',
  'dc'  => 'http://purl.org/dc/terms/',
);

\$cms = \$namespaces['cms'];
\$hc  = \$namespaces['hc'];
\$dc  = \$namespaces['dc'];
EOT;
echo "\n\n";

foreach ($config['rdf_fields'] as $field) {
  $curie = $field->getRDFPredicate();
  $uri = '';
  if (startsWith('hc:', $curie)) {
    $uri = str_replace('hc:','$hc.\'',$curie) . '\'';
  } else {
    $uri = str_replace('dc:','$dc.\'',$curie) . '\'';
  }

  echo "\$fields[] = array(\n";
  echo "  'property' => $uri,\n";
  echo "  'label'    => '{$field->getLabel()}',\n";
  echo "  'type'     => '{$field->getType()}',\n";
  echo ");\n";
}
echo "\n";


foreach ($config['rdf_resources'] as $resource) {
  $view = _curios_get_view($resource->getId());
  $id = str_replace('hc_','',$view->getId());
  $label = $view->getLabel();
  $base = $uri = str_replace('hc:','',$resource->getRDFType());

  echo <<<EOT
\$browsing_classes[] = array(
  'uri'   => \$cms.'$id',
  'label' => '$label',
  'base'  => \$hc.'$base',
);
EOT;
  echo "\n";
}
echo "\n";


foreach ($config['rdf_resources'] as $resource) {
  $view = _curios_get_view($resource->getId());
  $id = str_replace('hc_','',$view->getId());
  $label = $view->getLabel();
  $base = $uri = str_replace('hc:','',$resource->getRDFType());

  echo "\$field_assignments['cms:$id'] = array(\n";

  foreach ($resource->getDataFields() as $field) {
    $curie = $field->getRDFPredicate();
    $uri = '';
    if (startsWith('hc:', $curie)) {
      $uri = str_replace('hc:','$hc.\'',$curie) . '\'';
    } else {
      $uri = str_replace('dc:','$dc.\'',$curie) . '\'';
    }

  echo '    ' . $uri . ",\n";

  }

  echo ");\n";
}
echo "\n";

foreach ($config['rdf_resources'] as $resource) {
  $view = _curios_get_view($resource->getId());
  $id = str_replace('hc_','',$view->getId());
  $label = $view->getLabel();
  $base = str_replace('hc:','',$resource->getRDFType());
  $targets = $resource->getRelationshipTargets();

  foreach ($resource->getObjectFields() as $field) {
    $propUri = $uri = str_replace('hc:','',$field->getRDFPredicate());
    $target_resource = $targets[$field->getId()];

    echo "\$relationship_assignments['cms:$id'][] = array(\n";

    $rel_targets = '';
    if (!isset($target_resource)) {
       $uri = $config['rdf_resources']['hc_subject']->getRDFType();
      $target_class =  str_replace('hc:','',$uri);
      $rel_targets = "\$hc.'$target_class',";
    } elseif (!is_array($target_resource)) {
      $uri = $config['rdf_resources'][$target_resource]->getRDFType();
      $target_class =  str_replace('hc:','',$uri);
      $rel_targets = "\$hc.'$target_class',";
    } else {
      $rel_targets = "array(\n";
      $count = 0;
      foreach ($target_resource as $item) {
        if ($config['rdf_resources'][$item] == NULL) { echo "\n $item : " . $resource->getId() . '    ' . $field->getId() . "\n"; exit; }
        $uri = $config['rdf_resources'][$item]->getRDFType();
        $target_class =  str_replace('hc:','',$uri);
        $rel_targets .= "          \$hc.'$target_class',\n";
      }
      $rel_targets .= "      ),";
    }


  echo <<<EOT
    'property'  => \$hc.'$propUri',
    'target'    => $rel_targets
EOT;
  echo "\n);\n";
  }

  echo "\n";
}

exit;
*/



  }
  
  // Resource to View mapping.
  $config['resource_views'] = array(
    'hc_subject' => 'hc_subjects',
    'hc_person' => 'hc_people',
    'hc_organisation' => 'hc_organisations',
    'hc_resource' => 'hc_resources',
    'hc_vehicle' => 'hc_vehicles',
    'hc_boat' => 'hc_boats',
    'hc_building_or_public_amenity' => 'hc_buildings_and_public_amenities',
    'hc_business' => 'hc_businesses',
    'hc_croft_or_residence' => 'hc_crofts_and_residences',
    'hc_gaelic_verse' => 'hc_gaelic_verses',
    'hc_historical_event' => 'hc_historical_events',
    'hc_landmark_or_archaeological_site' => 'hc_landmarks_and_archaeological_sites',
    'hc_location' => 'hc_locations',
    'hc_natural_landscape_feature' => 'hc_natural_landscape_features',
    'hc_object_or_artefact' => 'hc_objects_and_artefacts',
    'hc_story_report_or_tradition' => 'hc_stories_reports_and_traditions',
    'hc_image_file' => 'hc_image_details',
  );


  // RDF class to resource name mapping.
  $config['rdf_class_resources'] = array(
    'hc:Subject' => 'hc_subject',
    'hc:Person' => 'hc_person',
    'hc:Organisation' => 'hc_organisation',
    'hc:Resource' => 'hc_resource',
    'hc:Vehicle' => 'hc_vehicle',
    'hc:Boat' => 'hc_boat',
    'hc:BuildingOrPublicAmenity' => 'hc_building_or_public_amenity',
    'hc:Business' => 'hc_business',
    'hc:CroftOrResidence' => 'hc_croft_or_residence',
    'hc:GaelicVersebRdachd' => 'hc_gaelic_verse',
    'hc:HistoricalEvent' => 'hc_historical_event',
    'hc:LandmarkOrArchaeologicalSite' => 'hc_landmark_or_archaeological_site',
    'hc:Location' => 'hc_location',
    'hc:NaturalLandscapeFeature' => 'hc_natural_landscape_feature',
    'hc:ObjectOrArtefact' => 'hc_object_or_artefact',
    'hc:StoryReportOrTradition' => 'hc_story_report_or_tradition',
    'hc:Imagefile' => 'hc_image_file',
  );
 
  return $config;
}

function _curios_get_view($resource_name) {
  $config = _curios_configuration();
  $view_name = $config['resource_views'][$resource_name];
  return $config['rdf_views'][$view_name];
}

function __curios_resource_name_from_class_uri($rdf_class) {
  $config = _curios_configuration();
  $class_name = 'hc:'.str_replace($config['namespaces']['hc'], '', $rdf_class);
  return !empty($config['rdf_class_resources'][$class_name]) ? $config['rdf_class_resources'][$class_name] : FALSE ;
}

