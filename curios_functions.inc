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
  return join($delimiter, array_filter(preg_split('/(?=[A-Z])/', $text)));
}

function __curios_split_uri($uri, $config) {
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

function __curios_curie_from_uri($uri, $config) {
  return join(':', __curios_split_uri($uri, $config));
}

function __curios_id_from_uri($uri, $config) {
  $uri_parts = __curios_split_uri($uri, $config);

  // Format identifier.
  $prefix = $uri_parts[0];
  $lname = $uri_parts[1];
  $lname = _curios_split_camel_case($lname, '_');
  $lname = strtolower($lname);

  return $prefix.'_'.$lname;
}

function __curios_path_from_uri($uri, $config) {
  $uri_parts = __curios_split_uri($uri, $config);

  $prefix = $uri_parts[0];
  $lname = $uri_parts[1];
  $lname = _curios_split_camel_case($lname, '-');
  $lname = strtolower($lname);

  return $prefix.'/'.$lname;
}


function __curios_label_from_uri($uri, $config) {
  $uri_parts = __curios_split_uri($uri, $config);

  $label = _curios_split_camel_case($uri_parts[1]);
  $label = ucfirst($label);

  return $label;
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