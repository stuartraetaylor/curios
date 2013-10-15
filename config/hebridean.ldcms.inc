<?php
/*
 * hebridean.ldcms.inc
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

$namespaces = array(
  'hc' => 'http://www.hebrideanconnections.com/hebridean.owl#',
  'dc' => 'http://purl.org/dc/terms/',
);

$options = array(
  // Default/fallback class - is a super class of all base classes.
  'default_class' => 'hc:Subject',

  // Local identifier property and default prefix for new instances.
  'id_property' => 'hc:subjectID',
  'default_prefix' => 'hc',

  // Title and description properties for summary views etc.
  'title_property' => 'dc:title',
  'description_property' => 'dc:description',
    
  // Record metadata properties.
  'owner_property' => 'hc:ownedBySociety',
  'maintainer_property' => 'hc:maintainedBySociety',
  'published_property' => 'hc:approvedForPub',

  // Image details for gallery displays.
  'image_class' => 'hc:ImageFile',
  'image_relationship_property' => 'hc:hasImageFile',
  'url_property' => 'hc:URL',
);


/* Literal value fields. */

$fields[] = array(
  'property' => 'hc:alsoKnownAs',
  'label'    => 'Also Known As',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:bkReference',
  'label'    => 'Bk Reference',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:chassis',
  'label'    => 'Chassis',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:createdBySociety',
  'label'    => 'Created By',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:date',
  'label'    => 'Date',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateBuilt',
  'label'    => 'Date Built',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateDemolished',
  'label'    => 'Date Demolished',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateEstablished',
  'label'    => 'Date Established',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateFounded',
  'label'    => 'Date Founded',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateLaunched',
  'label'    => 'Date Launched',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateLotted',
  'label'    => 'Date Lotted',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:born',
  'label'    => 'Date of Birth',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfDeath',
  'label'    => 'Date of Death',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfMarriage',
  'label'    => 'Date of Marriage',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfRegistration',
  'label'    => 'Date of Registration',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:dateOfSource',
  'label'    => 'Date of Source',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:description',
  'label'    => 'Description',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:englishName',
  'label'    => 'English Name',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:gaelicName',
  'label'    => 'Gaelic Name',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:geoRef',
  'label'    => 'Geo Ref',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:easting',
  'label'    => 'Grid Ref Easting',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:northing',
  'label'    => 'Grid Ref Northing',
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
  'label'    => 'Period of Construction',
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
  'label'    => 'Soundex Name',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:subjectID',
  'label'    => 'Subject Id',
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
  'label'    => 'Time Period',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:URL',
  'label'    => 'URL',
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
  'label'    => 'Adopted By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:adoptedPerson',
  'label'    => 'Adopted Person',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:associatedWith',
  'label'    => 'Associated With',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:authorOriginatorOf',
  'label'    => 'Author Originator Of',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:bornIn',
  'label'    => 'Born In',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:builder',
  'label'    => 'Builder Of',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:builtBy',
  'label'    => 'Built By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:childOf',
  'label'    => 'Child Of',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:CompiledMaintainedBy',
  'label'    => 'compiled Maintained By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:compilerOf',
  'label'    => 'Compiler Of',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:composedBy',
  'label'    => 'Composed By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:composedSong',
  'label'    => 'Composed Song',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:comprisesSubSite',
  'label'    => 'Comprises Subsite',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:crewedBy',
  'label'    => 'Crewed By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:diedIn',
  'label'    => 'Died In',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:emigratedTo',
  'label'    => 'Emigrated To',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:employed',
  'label'    => 'Employed',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:employedBy',
  'label'    => 'Employed By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:fosteredBy',
  'label'    => 'Fostered By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:fosteredPerson',
  'label'    => 'Fostered Person',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:foundAt',
  'label'    => 'Found At',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:foundHere',
  'label'    => 'Found Here',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:holds',
  'label'    => 'Holds',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:immigrantFrom',
  'label'    => 'Immigrant From',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:informationObtainedFrom',
  'label'    => 'Information Obtained From',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:isPartOfSite',
  'label'    => 'Is Part Of Site',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:livedHere',
  'label'    => 'Lived Here',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:livedAt',
  'label'    => 'Lived At',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:livedWith',
  'label'    => 'Lived With',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:locatedAt',
  'label'    => 'Located At',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:locatedHere',
  'label'    => 'Located Here',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:locatedNear',
  'label'    => 'Located Near',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:married',
  'label'    => 'Married',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:MayBeTheSameAs',
  'label'    => 'May Be The Same As',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:movedFrom',
  'label'    => 'Moved From',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:movedTo',
  'label'    => 'Moved To',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:onCrewOfBoat',
  'label'    => 'On Crew Of Boat',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:owned',
  'label'    => 'Owned',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:ownedBy',
  'label'    => 'Owned By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:parentOf',
  'label'    => 'Parent Of',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:personBornHere',
  'label'    => 'Person Born Here',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:personWhoDiedHere',
  'label'    => 'Person Who Died Here',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:relatedTo',
  'label'    => 'Related To',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:siblingOf',
  'label'    => 'Sibling Of',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:sourceOfInformationOn',
  'label'    => 'Source Of Information On',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:usedObject',
  'label'    => 'Used Object',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:writtenCompiledBy',
  'label'    => 'Written Compiled By',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:hasImageFile',
  'label'    => 'Image File',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:isShownHere',
  'label'    => 'Associated With',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:hasSoundFile',
  'label'    => 'Sound File',
  'type'     => 'relationship',
);
$fields[] = array(
  'property' => 'hc:isHeardHere',
  'label'    => 'Associated With',
  'type'     => 'relationship',
);

/* Record metadata fields */
$fields[] = array(
  'property' => 'hc:approvedForPub',
  'label'    => 'Published',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:ownedBySociety',
  'label'    => 'Record Owner',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:maintainedBySociety',
  'label'    => 'Record Maintainers',
  'type'     => 'text',
);

/* Annotations */

$fields[] = array(
  'property' => 'hc:Approvedby',
  'label'    => 'Approved by',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Approveddate',
  'label'    => 'Approved date',
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
  'label'    => 'Compiler notes',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:copyright',
  'label'    => 'Copyright',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Editedby',
  'label'    => 'Edited by',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Extrainfo',
  'label'    => 'Extra info',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Fid',
  'label'    => 'Fid',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Internalsummary',
  'label'    => 'Internal summary',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Inversecaption',
  'label'    => 'Inverse caption',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Isprimary',
  'label'    => 'Is primary',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Lochistsoc',
  'label'    => 'Lochistsoc',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Lochistsocref',
  'label'    => 'Lochistsoc ref',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:originator',
  'label'    => 'Originator',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:originDate',
  'label'    => 'Date',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Tobepublished',
  'label'    => 'To be published',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Whencreated',
  'label'    => 'When created',
  'type'     => 'text',
);
$fields[] = array(
  'property' => 'hc:Whenedited',
  'label'    => 'When edited',
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
  'label' => 'All Records',
  'class' => 'hc:Subject',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'boats',
  'label' => 'Boats',
  'class' => 'hc:Boat',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'buildings_and_public_amenities',
  'label' => 'Buildings and Public Amenities',
  'class' => 'hc:BuildingOrPublicAmenity',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'businesses',
  'label' => 'Businesses',
  'class' => 'hc:Business',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'crofts_and_residences',
  'label' => 'Crofts and Residences',
  'class' => 'hc:CroftOrResidence',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'gaelic_verse',
  'label' => 'Gaelic Verse',
  'class' => 'hc:GaelicVerse',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'historical_events',
  'label' => 'Historical Events',
  'class' => 'hc:HistoricalEvent',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'landmarks_and_archaeological_sites',
  'label' => 'Landmarks and Archaeological Sites',
  'class' => 'hc:LandmarkOrArchaeologicalSite',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'locations',
  'label' => 'Locations',
  'class' => 'hc:Location',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'natural_landscape_features',
  'label' => 'Natural Landscape Features',
  'class' => 'hc:NaturalLandscapeFeature',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'objects_and_artefacts',
  'label' => 'Objects and Artefacts',
  'class' => 'hc:ObjectOrArtefact',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'organisations',
  'label' => 'Organisations',
  'class' => 'hc:Organisation',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'people',
  'label' => 'People',
  'class' => 'hc:Person',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'resources',
  'label' => 'Resources',
  'class' => 'hc:Resource',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'stories_reports_and_traditions',
  'label' => 'Stories, Reports and Traditions',
  'class' => 'hc:StoryReportOrTradition',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'vehicles',
  'label' => 'Vehicles',
  'class' => 'hc:Vehicle',
  'title' => 'hc:englishName',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'image_details',
  'label' => 'Image Details',
  'class' => 'hc:ImageFile',
  'title' => 'hc:title',
  'description' => 'hc:description',
);
$browsing_classes[] = array(
  'name'  => 'sound_files',
  'label' => 'Sound Files',
  'class' => 'hc:SoundFile',
  'title' => 'hc:title',
  'description' => 'hc:description',
);

/* Field assignments. */

$field_assignments['subjects'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
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
    'hc:easting',
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
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:alsoKnownAs',
    'hc:typeOfBoat',
    'hc:dateLaunched',
    'hc:dateOfRegistration',
    'hc:registration',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['buildings_and_public_amenities'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfBuildingPublicAmenity',
    'hc:dateBuilt',
    'hc:dateEstablished',
    'hc:dateFounded',
    'hc:period',
    'hc:periodOfConstructionUse',
    'hc:SMRRecordID',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['businesses'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfBusiness',
    'hc:dateFounded',
    'hc:period',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['crofts_and_residences'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfLocation',
    'hc:dateBuilt',
    'hc:dateDemolished',
    'hc:dateFounded',
    'hc:dateLotted',
    'hc:period',
    'hc:periodOfConstructionUse',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['gaelic_verse'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:date',
    'hc:theme',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['historical_events'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfEvent',
    'hc:date',
    'hc:dateEstablished',
    'hc:timePeriod',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['landmarks_and_archaeological_sites'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfSite',
    'hc:period',
    'hc:periodOfConstructionUse',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:SMRRecordID',
    'hc:subjectID',
);
$field_assignments['locations'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:alsoKnownAs',
    'hc:typeOfLocation',
    'hc:periodOfConstructionUse',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['natural_landscape_features'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:alsoKnownAs',
    'hc:typeOfNaturalLandscapeFeature',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['objects_and_artefacts'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfObjectArtefact',
    'hc:period',
    'hc:easting',
    'hc:northing',
    'hc:ownedBySociety',
    'hc:SMRRecordID',
    'hc:subjectID',
);
$field_assignments['organisations'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfOrganisation',
    'hc:dateEstablished',
    'hc:dateOfSource',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['people'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:alsoKnownAs',
    'hc:born',
    'hc:dateOfDeath',
    'hc:dateOfMarriage',
    'hc:occupation',
    'hc:sex',
    'hc:ownedBySociety',
    'hc:bkReference',
    'hc:subjectID',
);
$field_assignments['resources'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:date',
    'hc:dateEstablished',
    'hc:dateOfSource',
    'hc:occupation',
    'hc:period',
    'hc:sex',
    'hc:sourceType',
    'hc:ownedBySociety',
    'hc:bkReference',
    'hc:subjectID',
);
$field_assignments['stories_reports_and_traditions'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfStoryReportTradition',
    'hc:date',
    'hc:dateEstablished',
    'hc:dateOfSource',
    'hc:periodOfConstructionUse',
    'hc:theme',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['vehicles'] = array(
    'hc:englishName',
    'hc:gaelicName',
    'hc:description',
    'hc:typeOfVehicle',
    'hc:chassis',
    'hc:registration',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['image_details'] = array(
    'hc:title',
    'hc:description',
    'hc:URL',
    'hc:copyright',
    'hc:originator',
    'hc:originDate',
    'hc:ownedBySociety',
    'hc:subjectID',
);
$field_assignments['sound_files'] = array(
    'hc:title',
    'hc:description',
    'hc:URL',
    'hc:copyright',
    'hc:originator',
    'hc:originDate',
    'hc:ownedBySociety',
    'hc:subjectID',
);


/* Relationship assignments. */

$all_records = array(
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
    'target'    => $all_records,
);
$relationship_assignments['subjects'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);

/* Boats */
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_records,
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
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:ownedBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['boats'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
);

/* Buildings and public amenities */
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_records,
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['buildings_and_public_amenities'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
    'target'    => array(
          'hc:Business',
          'hc:BuildingOrPublicAmenity',
          'hc:CroftOrResidence',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:Location',
          'hc:NaturalLandscapeFeature',
          'hc:Organisation',
      ),
);

/* Businesses */
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_records,
);
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['businesses'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
    'target'    => $all_records,
);
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['crofts_and_residences'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
    'target'    => $all_records,
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
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['gaelic_verse'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
);

/* Historical events */
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_records,
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
);
$relationship_assignments['historical_events'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => $all_records,
);

/* Landmarks and archaeological sites */
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_records,
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
);
$relationship_assignments['landmarks_and_archaeological_sites'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => $all_records,
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
    'target'    => array(
          'hc:Business',
          'hc:BuildingOrPublicAmenity',
          'hc:CroftOrResidence',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:Location',
          'hc:NaturalLandscapeFeature',
          'hc:Organisation',
      ),
);

/* Locations */
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_records,
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['locations'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
          'hc:BuildingOrPublicAmenity',
          'hc:CroftOrResidence',
          'hc:LandmarkOrArchaeologicalSite',
          'hc:Location',
          'hc:NaturalLandscapeFeature',
          'hc:Organisation',
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
    'target'    => $all_records,
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['natural_landscape_features'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
    'target'    => $all_records,
);
$relationship_assignments['objects_and_artefacts'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['objects_and_artefacts'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['objects_and_artefacts'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
    'target'    => $all_records,
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['organisations'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
    'target'    => $all_records,
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
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['people'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
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
    'property'  => 'hc:owned',
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
    'target'    => $all_records,
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:CompiledMaintainedBy',
    'target'    => 'hc:Organisation',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['resources'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
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
    'target'    => $all_records,
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:composedBy',
    'target'    => 'hc:Person',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:informationObtainedFrom',
    'target'    => 'hc:Resource',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:locatedAt',
    'target'    => 'hc:Location',
);
$relationship_assignments['stories_reports_and_traditions'][] = array(
    'property'  => 'hc:sourceOfInformationOn',
    'target'    => $all_records,
);

/* Vehicles */
$relationship_assignments['vehicles'][] = array(
    'property'  => 'hc:associatedWith',
    'target'    => $all_records,
);
$relationship_assignments['vehicles'][] = array(
    'property'  => 'hc:hasImageFile',
    'target'    => 'hc:ImageFile',
);
$relationship_assignments['vehicles'][] = array(
    'property'  => 'hc:hasSoundFile',
    'target'    => 'hc:SoundFile',
);

/* Images */
$relationship_assignments['image_details'][] = array(
    'property'  => 'hc:isShownHere',
    'target'    => $all_records,
);

/* Sound Files */
$relationship_assignments['sound_files'][] = array(
    'property'  => 'hc:isHeardHere',
    'target'    => $all_records,
);