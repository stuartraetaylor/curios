CURIOS -- LDCMS
===============

Installation Notes
------------------

Requirements:
  * Drupal 7.23 (latest version)
  * Apache, MySQL, PHP 5.3+
  * wget, git, drush

Required modules from Drupal.org version control:
  * Entity        7.x-1.x    https://drupal.org/project/entity
  * Views         7.x-3.x    https://drupal.org/project/views
  * Panels        7.x-3.x    https://drupal.org/project/panels
  * Lightbox2     7.x-1.x    https://drupal.org/project/lightbox2
  * Ckeditor      7.x-1.x    https://drupal.org/project/ckeditor
  * CTools        7.x-1.x    https://drupal.org/project/ctools
  * RDFx          7.x-2.x    https://drupal.org/project/rdfx
  * SPARQL        7.x-2.x    https://drupal.org/project/sparql
  * SPARQL Views  7.x-2.x    https://drupal.org/project/sparql_views
  * Libraries     7.x-2.x    https://drupal.org/project/libraries
  * Views PHP     7.x-2.x    https://drupal.org/project/views_php
  * Views Litepager 7.x-3.x  https://drupal.org/project/views_litepager
  * Devel     latest-version (optional)

Special Requirements:
  * arc2-sparql11 from github:
      $ mkdir -p sites/all/libraries/ARC2
      $ cd sites/all/libraries/ARC2
      $ git clone https://github.com/staylor-abdn/arc2-sparql11.git arc
  * Patch SPARQL module:
      $ cd sites/all/modules/sparql
      $ wget http://www.abdn.ac.uk/~csc363/curios/sparql-module-arc2-sparql11.patch
      $ git apply -v sparql-module-arc2-sparql11.patch
  * SPARQL Views CURIOS branch from Bitbucket:
      $ cd sites/all/modules/sparql_views
      $ git remote add -t curios-7.x-2.x -f curios-bitbucket https://<USERNAME>@bitbucket.org/stuartraetaylor/sparql_views.git
      $ git checkout -b curios-7.x-2.x remotes/curios-bitbucket/curios-7.x-2.x
  * CURIOS module from BitBucket:
      $ cd sites/all/modules
      $ git clone https://<USERNAME>@bitbucket.org/stuartraetaylor/curios.git
  * CURIOS Hebridean Connections theme from BitBucket (optional):
      $ cd sites/all/themes
      $ git clone https://<USERNAME>@bitbucket.org/stuartraetaylor/curios_theme.git

Installation:
  * Install Drupal 7 - typical installation.
  * Install and enable required modules.
  * Follow steps in Special Requirements.
  * Enable CURIOS module and clear cache:
      $ drush -v en curios
      $ drush cc all

