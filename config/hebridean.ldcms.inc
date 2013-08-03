<?php

$namespaces = array(
  'hc' => 'http://www.hebrideanconnections.com/hebridean.owl#',
  'dc' => 'http://purl.org/dc/terms/',
);

$options = array(
  'default_class' => 'hc:Subject',
  'id_property' => 'hc:subjectID',
  'title_property' => 'dc:title',
  'description_property' => 'dc:description',
  'image_class' => 'hc:Imagefile',
  'image_relationship_property' => 'hc:hasFile',
);


/* Literal value fields. */

$fields[] = array(
  'property' => 'hc:alsoKnownAs',
  'label'    => 'AlsoKnownAs',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:bkReference',
  'label'    => 'BkReference',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:born',
  'label'    => 'Born',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:chassis',
  'label'    => 'Chassis',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:createdBySociety',
  'label'    => 'Createdby',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:date',
  'label'    => 'Date',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateBuilt',
  'label'    => 'DateBuilt',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateDemolished',
  'label'    => 'DateDemolished',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateEstablished',
  'label'    => 'DateEstablished',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateFounded',
  'label'    => 'DateFounded',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateLaunched',
  'label'    => 'DateLaunched',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateLotted',
  'label'    => 'DateLotted',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfDeath',
  'label'    => 'DateOfDeath',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfMarriage',
  'label'    => 'DateOfMarriage',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfRegistration',
  'label'    => 'DateOfRegistration',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfSource',
  'label'    => 'DateOfSource',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:description',
  'label'    => 'Description',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:easting',
  'label'    => 'Easting',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:englishName',
  'label'    => 'EnglishName',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:gaelicName',
  'label'    => 'GaelicName',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:geoRef',
  'label'    => 'GeoRef',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:northing',
  'label'    => 'Northing',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:occupation',
  'label'    => 'Occupation',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:period',
  'label'    => 'Period',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:periodOfConstructionUse',
  'label'    => 'PeriodOfConstructionUse',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:registration',
  'label'    => 'Registration',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:sex',
  'label'    => 'Sex',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:SMRRecordID',
  'label'    => 'SMR Record ID',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:sourceType',
  'label'    => 'Source Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:soundexName',
  'label'    => 'Soundexname',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:subjectID',
  'label'    => 'Subjectid',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:title',
  'label'    => 'Title',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:theme',
  'label'    => 'Theme',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:timePeriod',
  'label'    => 'TimePeriod',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:URL',
  'label'    => 'ImageURL',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:fileName',
  'label'    => 'Filename',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfBoat',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfBuildingPublicAmenity',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfBusiness',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfEvent',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfLocation',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfNaturalLandscapeFeature',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfObjectArtefact',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfOrganisation',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfResidence',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfSite',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfStoryReportTradition',
  'label'    => 'Type',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:typeOfVehicle',
  'label'    => 'Type',
  'type'     => 'text',
);

/* Relationship fields. */

$fields[] = array(
  'property' => 'hc:adoptedBy',
  'label'    => 'AdoptedBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:adoptedPerson',
  'label'    => 'AdoptedPerson',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:associatedWith',
  'label'    => 'AssociatedWith',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:authorOriginatorOf',
  'label'    => 'AuthorOriginatorOf',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:bornIn',
  'label'    => 'BornIn',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:builder',
  'label'    => 'Builder',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:builtBy',
  'label'    => 'BuiltBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:childOf',
  'label'    => 'ChildOf',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:CompiledMaintainedBy',
  'label'    => 'compiledMaintainedBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:compilerOf',
  'label'    => 'CompilerOf',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:composedBy',
  'label'    => 'ComposedBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:composedSong',
  'label'    => 'ComposedSong',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:comprisesSubSite',
  'label'    => 'ComprisesSubSite',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:crewedBy',
  'label'    => 'CrewedBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:diedIn',
  'label'    => 'DiedIn',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:emigratedTo',
  'label'    => 'EmigratedTo',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:employed',
  'label'    => 'Employed',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:employedBy',
  'label'    => 'EmployedBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:fosteredBy',
  'label'    => 'FosteredBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:fosteredPerson',
  'label'    => 'FosteredPerson',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:foundAt',
  'label'    => 'FoundAt',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:foundHere',
  'label'    => 'FoundHere',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:hasFile',
  'label'    => 'HasFile',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:holds',
  'label'    => 'Holds',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:immigrantFrom',
  'label'    => 'ImmigrantFrom',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:informationObtainedFrom',
  'label'    => 'InformationObtainedFrom',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:isPartOfSite',
  'label'    => 'IsPartOfSite',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:isShownHere',
  'label'    => 'IsShownHere',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:livedHere',
  'label'    => 'LivedHere',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:livedAt',
  'label'    => 'LivedAt',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:livedWith',
  'label'    => 'LivedWith',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:locatedAt',
  'label'    => 'LocatedAt',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:locatedHere',
  'label'    => 'LocatedHere',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:locatedNear',
  'label'    => 'LocatedNear',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:married',
  'label'    => 'Married',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:MayBeTheSameAs',
  'label'    => 'mayBeTheSameAs',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:movedFrom',
  'label'    => 'MovedFrom',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:movedTo',
  'label'    => 'MovedTo',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:onCrewOfBoat',
  'label'    => 'OnCrewOfBoat',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:ownedOf',
  'label'    => 'Owned',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:ownedBy',
  'label'    => 'OwnedBy',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:parentOf',
  'label'    => 'ParentOf',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:personBornHere',
  'label'    => 'PersonBornHere',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:personWhoDiedHere',
  'label'    => 'PersonWhoDiedHere',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:relatedTo',
  'label'    => 'RelatedTo',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:siblingOf',
  'label'    => 'SiblingOf',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:sourceOfInformationOn',
  'label'    => 'SourceOfInformationOn',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:usedObject',
  'label'    => 'UsedObject',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:writtenCompiledBy',
  'label'    => 'WrittenCompiledBy',
  'type'     => 'relationship',
);

/* Annotations */

$fields[] = array(
  'property' => 'hc:Approvedby',
  'label'    => 'Approvedby',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Approveddate',
  'label'    => 'Approveddate',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:approvedForPub',
  'label'    => 'ApprovedForPub',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:ownedBySociety',
  'label'    => 'OwnedBySociety',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:maintainedBySociety',
  'label'    => 'MaintainedBySociety',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Approved',
  'label'    => 'Approved',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Caption',
  'label'    => 'Caption',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Compilernotes',
  'label'    => 'Compilernotes',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Copyright',
  'label'    => 'Copyright',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Editedby',
  'label'    => 'Editedby',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Extrainfo',
  'label'    => 'Extrainfo',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Fid',
  'label'    => 'Fid',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Internalsummary',
  'label'    => 'Internalsummary',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Inversecaption',
  'label'    => 'Inversecaption',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Isprimary',
  'label'    => 'Isprimary',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Lochistsoc',
  'label'    => 'Lochistsoc',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Lochistsocref',
  'label'    => 'Lochistsocref',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Originator',
  'label'    => 'Originator',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Origindate',
  'label'    => 'Origindate',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Tobepublished',
  'label'    => 'Tobepublished',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Whencreated',
  'label'    => 'Whencreated',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Whenedited',
  'label'    => 'Whenedited',
  'type'     => 'text',
);

/* Dublin Core fields. */

$fields[] = array(
  'property' => 'dc:title',
  'label'    => 'dc:title',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'dc:description',
  'label'    => 'dc:description',
  'type'     => 'text',
);


/* Browsing class definitions. */

$browsing_classes[] = array(
  'name'  => 'subjects',
  'label' => 'ALL SUBJECTS',
  'base'  => 'hc:Subject',
);
$browsing_classes[] = array(
  'name'  => 'boats',
  'label' => 'Boats',
  'base'  => 'hc:Boat',
);
$browsing_classes[] = array(
  'name'  => 'buildings_and_public_amenities',
  'label' => 'Buildings and Public Amenities',
  'base'  => 'hc:BuildingOrPublicAmenity',
);
$browsing_classes[] = array(
  'name'  => 'businesses',
  'label' => 'Businesses',
  'base'  => 'hc:Business',
);
$browsing_classes[] = array(
  'name'  => 'crofts_and_residences',
  'label' => 'Crofts and Residences',
  'base'  => 'hc:CroftOrResidence',
);
$browsing_classes[] = array(
  'name'  => 'gaelic_verse',
  'label' => 'Gaelic Verse',
  'base'  => 'hc:GaelicVerse',
);
$browsing_classes[] = array(
  'name'  => 'historical_events',
  'label' => 'Historical Events',
  'base'  => 'hc:HistoricalEvent',
);
$browsing_classes[] = array(
  'name'  => 'landmarks_and_archaeological_sites',
  'label' => 'Landmarks and Archaeological Sites',
  'base'  => 'hc:LandmarkOrArchaeologicalSite',
);
$browsing_classes[] = array(
  'name'  => 'locations',
  'label' => 'Locations',
  'base'  => 'hc:Location',
);
$browsing_classes[] = array(
  'name'  => 'natural_landscape_features',
  'label' => 'Natural Landscape Features',
  'base'  => 'hc:NaturalLandscapeFeature',
);
$browsing_classes[] = array(
  'name'  => 'objects_and_artefacts',
  'label' => 'Objects and Artefacts',
  'base'  => 'hc:ObjectOrArtefact',
);
$browsing_classes[] = array(
  'name'  => 'organisations',
  'label' => 'Organisations',
  'base'  => 'hc:Organisation',
);
$browsing_classes[] = array(
  'name'  => 'people',
  'label' => 'People',
  'base'  => 'hc:Person',
);
$browsing_classes[] = array(
  'name'  => 'resources',
  'label' => 'Resources',
  'base'  => 'hc:Resource',
);
$browsing_classes[] = array(
  'name'  => 'stories_reports_and_traditions',
  'label' => 'Stories, Reports and Traditions',
  'base'  => 'hc:StoryReportOrTradition',
);
$browsing_classes[] = array(
  'name'  => 'vehicles',
  'label' => 'Vehicles',
  'base'  => 'hc:Vehicle',
);
$browsing_classes[] = array(
  'name'  => 'image_details',
  'label' => 'Image Details',
  'base'  => 'hc:Imagefile',
);

/* Field assignments. */

$field_assignments['subjects'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:alsoKnownAs',
    'hc:born',
    'hc:chassis',
    'hc:createdBySociety',
    'hc:date',
    'hc:dateBuilt',
    'hc:dateDemolished',
    'hc:dateEstablished',
    'hc:dateFounded',
    'hc:dateLaunched',
    'hc:dateLotted',
    'hc:dateOfDeath',
    'hc:dateOfMarriage',
    'hc:dateOfRegistration',
    'hc:dateOfSource',
    'hc:URL',
    'hc:fileName',
    'hc:geoRef',
    'hc:northing',
    'hc:occupation',
    'hc:period',
    'hc:periodOfConstructionUse',
    'hc:registration',
    'hc:sex',
    'hc:title',
    'hc:theme',
    'hc:timePeriod',
    'hc:ownedBySociety',
    'hc:subjectID',
    'hc:SMRRecordID',
    'hc:soundexName',
);
$field_assignments['boats'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:alsoKnownAs',
    'hc:typeOfBoat',
    'hc:dateLaunched',
    'hc:dateOfRegistration',
    'hc:registration',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['buildings_and_public_amenities'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfBuildingPublicAmenity',
    'hc:dateBuilt',
    'hc:dateEstablished',
    'hc:dateFounded',
    'hc:geoRef',
    'hc:period',
    'hc:periodOfConstructionUse',
    'hc:SMRRecordID',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['businesses'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfBusiness',
    'hc:dateFounded',
    'hc:period',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['crofts_and_residences'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfLocation',
    'hc:dateBuilt',
    'hc:dateDemolished',
    'hc:dateFounded',
    'hc:dateLotted',
    'hc:geoRef',
    'hc:period',
    'hc:periodOfConstructionUse',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['gaelic_verse'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:date',
    'hc:theme',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['historical_events'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfEvent',
    'hc:date',
    'hc:dateEstablished',
    'hc:geoRef',
    'hc:timePeriod',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['landmarks_and_archaeological_sites'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfSite',
    'hc:period',
    'hc:periodOfConstructionUse',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:SMRRecordID',
    'hc:subjectID',
);
$field_assignments['locations'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:alsoKnownAs',
    'hc:typeOfLocation',
    'hc:geoRef',
    'hc:periodOfConstructionUse',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['natural_landscape_features'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:alsoKnownAs',
    'hc:typeOfNaturalLandscapeFeature',
    'hc:geoRef',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['objects_and_artefacts'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfObjectArtefact',
    'hc:period',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:SMRRecordID',
    'hc:subjectID',
);
$field_assignments['organisations'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfOrganisation',
    'hc:dateEstablished',
    'hc:dateOfSource',
    'hc:geoRef',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['people'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:alsoKnownAs',
    'hc:born',
    'hc:date',
    'hc:dateOfDeath',
    'hc:dateOfMarriage',
    'hc:geoRef',
    'hc:occupation',
    'hc:sex',
    'hc:northing',
    'hc:easting',
    'hc:ownedBySociety',
    'hc:bkReference',
    'hc:subjectID',
);
$field_assignments['resources'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:date',
    'hc:dateEstablished',
    'hc:dateOfSource',
    'hc:geoRef',
    'hc:occupation',
    'hc:period',
    'hc:sex',
    'hc:sourceType',
    'hc:ownedBySociety',
    'hc:bkReference',
    'hc:subjectID',
);
$field_assignments['stories_reports_and_traditions'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfStoryReportTradition',
    'hc:date',
    'hc:dateEstablished',
    'hc:dateOfSource',
    'hc:geoRef',
    'hc:periodOfConstructionUse',
    'hc:theme',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['vehicles'] = array(
    'dc:title',
    'dc:description',
    'hc:englishName',
    'hc:gaelicName',
    'hc:typeOfVehicle',
    'hc:chassis',
    'hc:registration',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['image_details'] = array(
    'dc:title',
    'dc:description',
    'hc:URL',
    'hc:ownedBySociety',
    'hc:subjectID',
);


/* Relationship assignments. */

$all_classes = array(
    'hc:LandmarkOrArchaeologicalSite',
    'hc:Business',
    'hc:HistoricalEvent',
    'hc:Location',
    'hc:GaelicVersebRdachd',
    'hc:ObjectOrArtefact',
    'hc:NaturalLandscapeFeature',
    'hc:StoryReportOrTradition',
    'hc:Boat',
    'hc:Person',
    'hc:CroftOrResidence',
    'hc:Organisation',
    'hc:Person',
    'hc:BuildingOrPublicAmenity',
    'hc:Resource',
    'hc:Vehicle',
);

/* Subjects */
$relationship_assignments['subjects'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_classes,
);
$relationship_assignments['subjects'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Imagefile',
);
$relationship_assignments['subjects'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);

/* Boats */
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:HistoricalEvent',
          'hc:Location',
          'hc:NaturalLandscapeFeature',
          'hc:Organisation',
          'hc:Person',
          'hc:Business',
          'hc:StoryReportOrTradition',
          'hc:Boat',
          'hc:CroftOrResidence',
      ),
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:builtBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:crewedBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:ownedBy',
    'target'    => 'hc:Person',
);

/* Buildings and public amenities */
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:HistoricalEvent',
          'hc:ObjectOrArtefact',
          'hc:Organisation',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:CroftOrResidence',
          'hc:Location',
          'hc:BuildingOrPublicAmenity',
          'hc:Person',
          'hc:StoryReportOrTradition',
      ),
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:livedHere',
    'target'    => 'hc:Person',
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => array(
          'hc:BuildingOrPublicAmenity',
          'hc:Location',
      ),
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:locatedHere',
    'target'    => 'hc:Subject',
);

/* Businesses */
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:StoryReportOrTradition',
          'hc:Person',
          'hc:Business',
          'hc:Business',
          'hc:Organisation',
          'hc:Location',
          'hc:Boat',
      ),
);
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
);
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:ownedBy',
    'target'    => 'hc:Person',
);

/* Crofts and residences */
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:HistoricalEvent',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:Business',
          'hc:Person',
          'hc:StoryReportOrTradition',
          'hc:CroftOrResidence',
          'hc:ObjectOrArtefact',
      ),
);
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Organisation',
);
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:livedHere',
    'target'    => 'hc:Person',
);
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
);
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:locatedHere',
    'target'    => array(
          'hc:BuildingOrPublicAmenity',
          'hc:LandmarkOrArchaeologicalSite',
      ),
);

/* Gaelic verse */
$relationship_assignments['gaelic_verse'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:Person',
          'hc:BuildingOrPublicAmenity',
          'hc:StoryReportOrTradition',
          'hc:CroftOrResidence',
          'hc:NaturalLandscapeFeature',
          'hc:HistoricalEvent',
          'hc:CroftOrResidence',
          'hc:Boat',
          'hc:Location',
      ),
);
$relationship_assignments['gaelic_verse'][] = array(
    'property'  => 'hc:composedBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['gaelic_verse'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['gaelic_verse'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);

/* Historical events */
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:CroftOrResidence',
          'hc:Boat',
          'hc:BuildingOrPublicAmenity',
          'hc:Person',
          'hc:Business',
          'hc:Organisation',
          'hc:NaturalLandscapeFeature',
          'hc:HistoricalEvent',
          'hc:HistoricalEvent',
          'hc:Location',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:StoryReportOrTradition',
      ),
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Subject',
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => 'hc:Subject',
);

/* Landmarks and archaeological sites */
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:StoryReportOrTradition',
          'hc:Person',
          'hc:CroftOrResidence',
          'hc:BuildingOrPublicAmenity',
          'hc:NaturalLandscapeFeature',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:Location',
          'hc:HistoricalEvent',
      ),
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => 'hc:Subject',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:comprisesSubSite',
    'target'    => 'hc:LandmarkOrArchaeologicalSite',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:isPartOfSite',
    'target'    => 'hc:LandmarkOrArchaeologicalSite',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:livedHere',
    'target'    => 'hc:Person',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => array(
          'hc:CroftOrResidence',
          'hc:NaturalLandscapeFeature',
          'hc:Location',
      ),
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:locatedHere',
    'target'    => 'hc:Subject',
);

/* Locations */
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:StoryReportOrTradition',
          'hc:Organisation',
          'hc:Boat',
          'hc:Person',
          'hc:Business',
          'hc:Location',
          'hc:ObjectOrArtefact',
          'hc:NaturalLandscapeFeature',
          'hc:HistoricalEvent',
          'hc:BuildingOrPublicAmenity',
          'hc:LandmarkOrArchaeologicalSite',
      ),
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:foundHere',
    'target'    => 'hc:ObjectOrArtefact',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:livedHere',
    'target'    => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:locatedHere',
    'target'    => array(
          'hc:Business',
          'hc:CroftOrResidence',
          'hc:LandmarkOrArchaeologicalSite',
      ),
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:locatedNear',
    'target'    => 'hc:NaturalLandscapeFeature',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:personBornHere',
    'target'    => 'hc:Person',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:personWhoDiedHere',
    'target'    => 'hc:Person',
);

/* Natural landscape features */
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:StoryReportOrTradition',
          'hc:Boat',
          'hc:Person',
          'hc:HistoricalEvent',
          'hc:CroftOrResidence',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:GaelicVersebRdachd',
          'hc:BuildingOrPublicAmenity',
          'hc:Location',
      ),
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:foundHere',
    'target'    => 'hc:ObjectOrArtefact',
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:locatedHere',
    'target'    => 'hc:LandmarkOrArchaeologicalSite',
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:locatedNear',
    'target'    => array(
          'hc:Location',
          'hc:NaturalLandscapeFeature',
      ),
);

/* Objects and artefacts */
$relationship_assignments['objects_and_artefacts'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:Boat',
          'hc:BuildingOrPublicAmenity',
          'hc:StoryReportOrTradition',
          'hc:Person',
          'hc:Location',
          'hc:HistoricalEvent',
          'hc:Resource',
          'hc:ObjectOrArtefact',
          'hc:CroftOrResidence',
      ),
);
$relationship_assignments['objects_and_artefacts'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['objects_and_artefacts'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['objects_and_artefacts'][] = array(
    'property'  => 'hc:foundAt',
    'target'    => array(
          'hc:Location',
          'hc:NaturalLandscapeFeature',
          'hc:LandmarkOrArchaeologicalSite',
      ),
);

/* Organisations */
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:Location',
          'hc:HistoricalEvent',
          'hc:StoryReportOrTradition',
          'hc:Boat',
          'hc:BuildingOrPublicAmenity',
          'hc:Person',
          'hc:CroftOrResidence',
          'hc:Organisation',
      ),
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:compilerOf',
    'target'    => 'hc:Resource',
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:holds',
    'target'    => 'hc:Resource',
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => array(
          'hc:Location',
          'hc:Person',
      ),
);

/* People */
$relationship_assignments['people'][] = array(
    'property'  => 'hc:adoptedBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:adoptedPerson',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_classes,
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:authorOriginatorOf',
    'target'    => 'hc:Resource',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:bornIn',
    'target'    => 'hc:Location',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:builder',
    'target'    => 'hc:Boat',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:childOf',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:composedSong',
    'target'    => 'hc:GaelicVersebRdachd',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:diedIn',
    'target'    => 'hc:Location',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:emigratedTo',
    'target'    => 'hc:Location',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:employed',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:employedBy',
    'target'    => array(
          'hc:Person',
          'hc:Business',
      ),
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:fosteredBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:fosteredPerson',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:immigrantFrom',
    'target'    => 'hc:Location',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:livedAt',
    'target'    => array(
          'hc:LandmarkOrArchaeologicalSite',
          'hc:Location',
          'hc:CroftOrResidence',
      ),
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:livedWith',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:married',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:MayBeTheSameAs',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:movedFrom',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:movedTo',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:onCrewOfBoat',
    'target'    => 'hc:Boat',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:ownedOf',
    'target'    => array(
          'hc:Business',
          'hc:Boat',
      ),
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:parentOf',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:relatedTo',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:siblingOf',
    'target'    => 'hc:Person',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:usedObject',
    'target'    => 'hc:ObjectOrArtefact',
);

/* Resources */
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:Person',
          'hc:Resource',
          'hc:Location',
      ),
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:CompiledMaintainedBy',
    'target'    => 'hc:Organisation',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Subject',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => array(
          'hc:BuildingOrPublicAmenity',
          'hc:HistoricalEvent',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:StoryReportOrTradition',
          'hc:CroftOrResidence',
          'hc:Boat',
          'hc:Location',
          'hc:Organisation',
          'hc:Person',
      ),
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:writtenCompiledBy',
    'target'    => 'hc:Person',
);

/* Stories reports and traditions */
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_classes,
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:composedBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Subject',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => 'hc:Subject',
);

/* Vehicles */
$relationship_assignments['vehicles'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => array(
          'hc:Location',
          'hc:Business',
          'hc:Person',
          'hc:CroftOrResidence',
      ),
);
$relationship_assignments['vehicles'][] = array(
    'property'  => 'hc:hasFile',
    'target'    => 'hc:Subject',
);

/* Images */
$relationship_assignments['image_details'][] = array(
    'property'  => 'hc:isShownHere',
    'target'    => $all_classes,
);

