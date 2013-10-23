<?php
/*
 * curios_functions.inc
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
 * Returns a human readble representation of a DateRange.
 */
function curios_format_daterange($dateFrom, $dateTo) {
  return 'Between ' .  curios_format_datetime($dateFrom) . ' and ' . curios_format_datetime($dateTo);
}

/**
 * Format xsd:dateTime to d-M-Y.
 */
function curios_format_datetime($datetime) {
  // (Removes time values to avoid formatting dateTimes ending T24:00:00 as the start of the follwing day.)
  return date('d-M-Y', strtoTime(preg_replace('/T.+$/', '', $datetime)));
}

/**
 * startsWith function using the regex engine.
 */
function startsWith($needle, $haystack) {
  return preg_match('/^'.preg_quote($needle, '/')."/", $haystack);
}

/**
 * startsWith function using strncasecmp.
 */
function startsWith_ncasecmp($needle, $haystack) {
    return !strncasecmp($haystack, $needle, strlen($needle));
}

/**
 * Returns the concatenation of the hash value for an array of values.
 */
function __curios_hash() {
  $args = func_get_args();
  $hash_function = function($value) { return hash('crc32b', $value); };
  $hash_args = array_map($hash_function, $args);

  return join($hash_args);
}

/**
 * Validate the specified subject id.
 */
function __curios_valid_id($id) {
  return preg_match('/^[0-9]+$/', $id);
}

/**
 * Split camel case strings.
 */
function _curios_split_camel_case($text, $delimiter = ' ') {
  $f = function($match) use (&$delimiter) { return $delimiter. $match[0]; };
  return preg_replace_callback('/(?<!\b)[A-Z][a-z]+|(?<=[a-z])[A-Z]/', $f, $text);
}

/**
 * Returns a CURIE as an array from a URI using the namespace definitions in the configuration.
 */
function __curios_split_uri_to_curie($uri, $config) {
  $prefixes = $config->getNamespaceToPrefixMap();

  // Find namespace and local name.
  $hash = strrpos($uri, '#');
  $slash = strrpos($uri, '/');
  $marker = $hash ? $hash : $slash;
  $namespace = substr($uri, 0, $marker+1);
  $lname = substr($uri, $marker+1);

  if (array_key_exists($namespace, $prefixes)) {
    return array($prefixes[$namespace], $lname);
  } else {
    // TODO this should generate a new prefix.
    return array('unknown', $lname);
  }
}

/**
 * Splits a CURIE into prefix and local parts.
 */
function __curios_split_curie($curie) {
  return explode(':', $curie); }

/**
 * Creates a CURIE from a URI using the namespaces mappings defined in the configuration.
 */
function __curios_curie_from_uri($uri, $config) {
  return join(':', __curios_split_uri_to_curie($uri, $config));
}

/**
 * Creates a URI from a CURIE using the namespace mappings definied in the configuration.
 */
function __curios_uri_from_curie($curie, $config) {
  list($prefix, $lname) = __curios_split_curie($curie);
  $namespace = $config->getNamespace($prefix);
  
  return $namespace . $lname;
}

/**
 * Creates a valid CMS identifier (machine name) from a CURIE.
 */
function __curios_cmsid_from_curie_parts($prefix, $lname, $trim = TRUE) {
  $prefix = _curios_split_camel_case($prefix, '_');
  $prefix = strtolower($prefix);
  
  $lname = _curios_split_camel_case($lname, '_');
  $lname = strtolower($lname);

  $id = $prefix.'_'.$lname;

  // Drupal has a 32 character limit for field names.
  if ($trim && strlen($id) > 32) {
    $id = substr($id, 0, 32);
  }

  return $id;
}

/**
 * Creates a valid CMS identifier (machine name) from a CURIE.
 */
function __curios_cmsid_from_curie($curie) {
  list($prefix, $lname) = __curios_split_curie($curie);
  return __curios_cmsid_from_curie_parts($prefix, $lname);
}

/**
 * Creates a valid CMS identifier (machine name) from a URI.
 */
function __curios_cmsid_from_uri($uri, $config) {
  list($prefix, $lname) = __curios_split_uri_to_curie($uri, $config);
  return __curios_cmsid_from_curie_parts($prefix, $lname);
}

/**
 * Creates a valid Drupal path from a CMS identifier.
 */
function __curios_path_from_cmsid($id) {
  $path = $id;
  $path = preg_replace('/^ldcms_/', '', $path);
  $path = str_replace('_', '-', $path);
  
  return $path;
}

/**
 * Creates a valid Drupal path from a CURIE.
 */
function __curios_path_from_curie_parts($prefix, $lname) {
  $prefix = _curios_split_camel_case($prefix, '-');
  $prefix = strtolower($prefix);

  $lname = _curios_split_camel_case($lname, '-');
  $lname = strtolower($lname);

  return $prefix.'/'.$lname;
}

/**
 * Creates a valid Drupal path from a CURIE.
 */
function __curios_path_from_curie($uri, $config) {
  list($prefix, $lname) = __curios_split_curie($uri, $config);
  return __curios_path_from_curie_parts($prefix, $lname);
}

/**
 * Creates a valid Drupal path from a URI.
 */
function __curios_path_from_uri($uri, $config) {
  list($prefix, $lname) = __curios_split_uri_to_curie($uri, $config);
  return __curios_path_from_curie_parts($prefix, $lname);
}

/**
 * Creates a label from the local part of a CURIE.
 */
function __curios_label_from_curie($uri, $config) {
  list( , $lname) = __curios_split_curie($uri, $config);

  $label = _curios_split_camel_case($lname);
  $label = ucfirst($label);

  return $label;
}

/**
 * Creates a label from the local part of a URI.
 */
function __curios_label_from_uri($uri, $config) {
  list( , $lname) = __curios_split_uri_to_curie($uri, $config);

  $label = _curios_split_camel_case($lname);
  $label = ucfirst($label);

  return $label;
}

/**
 * Finds the resource id (CMSID) from a base class URI.
 */
function __curios_resource_id_from_class_uri($base_class, $config) {
  $base_class_curie = __curios_curie_from_uri($base_class, $config);
  $resource_id = $config->getResourceForBaseClass($base_class_curie);
  
  return $resource_id ? $resource_id : FALSE ;
}

/**
 * Sets a block as active.
 */
function __curios_activate_block($module, $block, $region, $theme, $pages, $visibility) {
  db_merge('block')
  ->key(array('theme' => $theme, 'delta' => $block, 'module' => $module))
  ->fields(array(
    'region' => ($region == BLOCK_REGION_NONE ? '' : $region),
    'pages' => trim($pages),
    'status' => (int) ($region != BLOCK_REGION_NONE),
    'visibility' => $visibility,
  ))
  ->execute();
}

/**
 * Outputs each parameter via var_dump and exits.
 */
function curios_debug_exit() {
  foreach (func_get_args() as $arg) {
    var_dump($arg);
  }
  exit;
}