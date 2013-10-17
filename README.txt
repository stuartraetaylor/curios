CURIOS -- LDCMS
===============

Installation Notes
------------------

Requirements:
  * Drupal 7.23+
  * Apache, MySQL, PHP 5.3+
  * wget, git, drush
  * msysgit (for Microsoft Windows installation) - http://msysgit.github.io/
  * Jena Fuseki 1.0.0+ - http://jena.apache.org/documentation/serving_data/

Required modules, stable releases:
  * Entity        7.x-1.2         https://drupal.org/project/entity
  * Views         7.x-3.7         https://drupal.org/project/views
  * CTools        7.x-1.3         https://drupal.org/project/ctools
  * Lightbox2     7.x-1.0         https://drupal.org/project/lightbox2
  * Ckeditor      7.x-1.13        https://drupal.org/project/ckeditor
  * Libraries     7.x-2.1         https://drupal.org/project/libraries
  * Views Litepager 7.x-3.0       https://drupal.org/project/views_litepager
  * Devel                         https://drupal.org/project/devel

Required modules, development releases:
  * Panels        7.x-3.x-dev     https://drupal.org/project/panels
  * RDFx          7.x-2.x-dev     https://drupal.org/project/rdfx
  * SPARQL        7.x-2.x-dev     https://drupal.org/project/sparql
  * SPARQL Views  curios-7.x-2.x  https://github.com/stuartraetaylor/sparql_views.git

Special Requirements:
  1. SPARQL Views CURIOS branch from github:
      $ cd sites/all/modules
      $ git clone https://github.com/stuartraetaylor/sparql_views.git
  2. arc2-sparql11 from github:
      $ mkdir -p sites/all/libraries/ARC2
      $ cd sites/all/libraries/ARC2
      $ git clone https://github.com/stuartraetaylor/arc2-sparql11.git arc
  3. Patch SPARQL module:
      $ cd sites/all/modules/sparql
      $ wget http://homepages.abdn.ac.uk/s.taylor/pages/curios/sparql-module-arc2-sparql11.patch
      $ git apply -v sparql-module-arc2-sparql11.patch
      $ wget https://drupal.org/files/sparql-registry-strict-errors-2053013-1.patch
      $ git apply -v sparql-registry-strict-errors-2053013-1.patch
  4. CURIOS module from BitBucket:
      $ cd sites/all/modules
      $ git clone https://bitbucket.org/stuartraetaylor/curios.git
  5. CURIOS Hebridean Connections theme from BitBucket:
      $ cd sites/all/themes
      $ git clone https://bitbucket.org/stuartraetaylor/curios_theme.git

Installation:
  1. Install Drupal 7 - standard installation.
  2. Download the required Drupal modules.
  3. Follow the steps in Special Requirements.
  4. Enable CURIOS module:
      $ drush -v en curios
  5. Load configuration and install CMS entities:
      * Navigate to 'Structure > Linked Data CMS settings' (admin/structure/ldcms),
      * Click 'Load Configuration'.
  6. Enable CURIOS Theme and set as default via admin/appearance.
  7. Enable 'Description Link Filter' for Filtered HTML and Full HTML via admin/config/content/formats.
  8. Download and install the standalone CKEditor to the libraries folder as described in:
       http://docs.cksource.com/CKEditor_for_Drupal/Open_Source/Drupal_7/Installation
  9. Optional: enable 'Cache pages for anonymous users' via admin/config/development/performance.
 10. Finally, clear Drupal's cache:
      $ drush cc all

Major update (changes to dataset or module structure):
 [Steps 1-2 should be performed before updating the module]
  1. Uninstall CMS entities:
      * Navigate to 'Structure > Linked Data CMS settings' (admin/structure/ldcms),
      * Under 'Advanced Options', check 'Remove fields only',
      * Click 'Load Configuration'.
  2. Disable and uninstall the curios module:
      $ drush dis curios
      $ drush pm-uninstall curios
  3. Pull latest CURIOS module from BitBucket:
      $ cd sites/all/modules/curios
      $ git pull https://bitbucket.org/stuartraetaylor/curios.git
  4. Enable CURIOS module:
      $ drush en curios
  5. Load configuration and install CMS entities:
      * Navigate to 'Structure > Linked Data CMS settings' (admin/structure/ldcms),
      * Click 'Load Configuration'.
  6. Clear cache:
      $ drush cc all
