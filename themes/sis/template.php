<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */
function example_preprocess_html(&$variables) {
   $options = array(
     'group' => JS_THEME,
   );
   drupal_add_js('collections/sites/all/themes/sis/js/mark.js');
 }



function sis_preprocess_page(&$variables) {
  if ( !empty($variables['node']) ) {
    // Add a template suggest based on node type
    $variables['template_files'][] = "page-node-" . $variables['node']->type;
  }
  if ( arg(0) == 'image' && arg(1) == 'tid' && arg(2) == '7' ) {
    $variables['template_files'][] = "page-your-suggestion";
  }

// drupal_match_path(current_path(), 'islandora/object/smhc:*')


$alias = drupal_get_path_alias(current_path());

$urls = array(
  'islandora/object/smhc:*',
);

$patterns = implode("\n", $urls);

if (drupal_match_path($alias, $patterns)) {

$variables['download-content-file'] = 1;
$variables['download-content'] = "";

// dsm($variables);
 if ( !empty(arg(2)) ) {
//    dsm(arg(2)->type);
    // Add a template suggest based on node type
    $variables['template_files'][] = "page-node-" . $variables['node']->type;
  }
  if ( arg(0) == 'image' && arg(1) == 'tid' && arg(2) == '7' ) {
        dsm("2nd fired");
        $variables['template_files'][] = "page--voloh--islandora--object";
  }


}
dsm($variables);
}




