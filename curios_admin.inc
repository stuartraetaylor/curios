<?php

function curios_manage_page() {
  $page = array();

  $base_path = base_path() . 'curios/manage';
  $content = <<<EOT
<p>From this page you can create, edit and delete records in the repository.</p>
<ul>
<li><a href="$base_path/create">Create a new record</a></li>
<li><a href="$base_path/edit">Edit or delete an existing record</a></li>
</ul>
<p>Choose an action from the menu to continue.</p>
<ul>
<li><a href="$base_path/tools">Repository administration tools</a></li>
</ul>
EOT;
  $page[] = array('#markup' => $content);

  return $page;
}

function curios_admin_tools_page() {
  $latest_records = __curios_latest_record_identifiers(15);
  $content = '';

  $content .= '<p>This page contains a selection of admin tools for the Hebridean Connections repository.</p>';
  $content .= '<h2>Recently created records:</h2>';
  $content .= '<ul>';
  foreach ($latest_records as $id=>$title) {
    $content .= "<li>$id &mdash; $title</li>";
  }
  $content .= '</ul>';
  
  return array('#markup' => $content);
}
