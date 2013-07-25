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
