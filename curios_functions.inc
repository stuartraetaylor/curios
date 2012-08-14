<?php

function startsWith($needle, $haystack) {
  return preg_match('/^'.preg_quote($needle)."/", $haystack);
}