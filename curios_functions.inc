<?php

function startsWith($needle, $haystack) {
  return preg_match('/^'.preg_quote($needle, '/')."/", $haystack);
}

function startsWith_ncasecmp($needle, $haystack) {
    return !strncasecmp($haystack, $needle, strlen($needle));
}

function __curios_hash() {
  $args = func_get_args();
  $hash_function = function($value) { return hash('crc32b', $value); };
  $hash_args = array_map($hash_function, $args);

  return join($hash_args);
}

function __curios_valid_id($id) {
  return preg_match('/^[0-9]+$/', $id);
}

function _curios_split_camel_case($text, $delimiter = ' ') {
  $f = function($match) use (&$delimiter) { return $delimiter. $match[0]; };
  return preg_replace_callback('/(?<!\b)[A-Z][a-z]+|(?<=[a-z])[A-Z]/', $f, $text);
}

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

function __curios_split_curie($curie) {
  return explode(':', $curie); }

function __curios_curie_from_uri($uri, $config) {
  return join(':', __curios_split_uri_to_curie($uri, $config));
}

function __curios_uri_from_curie($curie, $config) {
  list($prefix, $lname) = __curios_split_curie($curie);
  $namespace = $config->getNamespace($prefix);
  
  return $namespace . $lname;
}

function __curios_id_from_curie_parts($prefix, $lname) {
  $prefix = _curios_split_camel_case($prefix, '_');
  $prefix = strtolower($prefix);
  
  $lname = _curios_split_camel_case($lname, '_');
  $lname = strtolower($lname);

  return $prefix.'_'.$lname;
}

function __curios_id_from_curie($curie) {
  list($prefix, $lname) = __curios_split_curie($curie);
  return __curios_id_from_curie_parts($prefix, $lname);
}

function __curios_id_from_uri($uri, $config) {
  list($prefix, $lname) = __curios_split_uri_to_curie($uri, $config);
  return __curios_id_from_curie_parts($prefix, $lname);
}

function __curios_path_from_id($id) {
  $path = $id;
  $path = preg_replace('/^ldcms_/', '', $path);
  $path = str_replace('_', '-', $path);
  
  return $path;
}

function __curios_path_from_curie_parts($prefix, $lname) {
  $prefix = _curios_split_camel_case($prefix, '-');
  $prefix = strtolower($prefix);

  $lname = _curios_split_camel_case($lname, '-');
  $lname = strtolower($lname);

  return $prefix.'/'.$lname;
}

function __curios_path_from_curie($uri, $config) {
  list($prefix, $lname) = __curios_split_curie($uri, $config);
  return __curios_path_from_curie_parts($prefix, $lname);
}

function __curios_path_from_uri($uri, $config) {
  list($prefix, $lname) = __curios_split_uri_to_curie($uri, $config);
  return __curios_path_from_curie_parts($prefix, $lname);
}

function __curios_label_from_curie($uri, $config) {
  list( , $lname) = __curios_split_curie($uri, $config);

  $label = _curios_split_camel_case($lname);
  $label = ucfirst($label);

  return $label;
}

function __curios_label_from_uri($uri, $config) {
  list( , $lname) = __curios_split_uri_to_curie($uri, $config);

  $label = _curios_split_camel_case($lname);
  $label = ucfirst($label);

  return $label;
}

function __curios_resource_id_from_class_uri($base_class, $config) {
  $base_class_curie = __curios_curie_from_uri($base_class, $config);
  $resource_id = $config->getResourceForBaseClass($base_class_curie);
  
  return $resource_id ? $resource_id : FALSE ;
}

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