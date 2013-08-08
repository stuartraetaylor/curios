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
  * SPARQL Views  curios-7.x-2.x - See special requirements below.
  * Libraries     7.x-2.x    https://drupal.org/project/libraries
  * Views Litepager 7.x-3.x  https://drupal.org/project/views_litepager
  * Devel                    https://drupal.org/project/devel

Special Requirements:
  * SPARQL Views CURIOS branch from github:
      $ cd sites/all/modules
      $ git clone https://github.com/stuartraetaylor/sparql_views.git
  * arc2-sparql11 from github:
      $ mkdir -p sites/all/libraries/ARC2
      $ cd sites/all/libraries/ARC2
      $ git clone https://github.com/stuartraetaylor/arc2-sparql11.git arc
  * Patch SPARQL module:
      $ cd sites/all/modules/sparql
      $ wget http://www.abdn.ac.uk/~csc363/curios/sparql-module-arc2-sparql11.patch
      $ git apply -v sparql-module-arc2-sparql11.patch
      $ wget https://drupal.org/files/sparql-registry-strict-errors-2053013-1.patch
      $ git apply -v sparql-registry-strict-errors-2053013-1.patch
  * CURIOS module from BitBucket:
      $ cd sites/all/modules
      $ git clone https://bitbucket.org/stuartraetaylor/curios.git
      $ git checkout tags/current-release
  * CURIOS Hebridean Connections theme from BitBucket (optional):
      $ cd sites/all/themes
      $ git clone https://bitbucket.org/stuartraetaylor/curios_theme.git

Installation:
  1. Install Drupal 7 - standard installation.
  2. Download the required Drupal modules.
  3. Follow the steps in Special Requirements.
  4. Enable CURIOS module:
      $ drush -v en curios
  5. Load configuration via admin/structure/ldcms.
  6. Enable CURIOS Theme via admin/appearance (if required).
  7. Enable 'Description Link Filter' for Filtered HTML and Full HTML via admin/config/content/formats.
  8. Download and install the standalone CKEditor to the libraries folder as described in http://docs.cksource.com/CKEditor_for_Drupal/Open_Source/Drupal_7/Installation
  9. Optional: enable 'Cache pages for anonymous users' via admin/config/development/performance.
 10. Finally, clear Drupal's cache:
      $ drush cc all
