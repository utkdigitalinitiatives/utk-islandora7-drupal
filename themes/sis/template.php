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

function sis_process_html(&$variables) {
    $variables['styles'] = preg_replace('/\.css\?[^"]+/','.css', $variables['styles']);
}

/**
function example_preprocess_html(&$variables) {
   
   $options = array(
     'group' => JS_THEME,
   );
   drupal_add_js('collections/sites/all/themes/sis/js/mark.js');
 }
*/

function sis_preprocess_html(&$variables) {
    $variables['utk_header'] = block_get_blocks_by_region('utk_header');

    return $variables;
}

function sis_preprocess_page(&$variables) {

   $title = drupal_set_title();
   if (strpos(current_path(), 'islandora/') !== 0 ) {
      drupal_add_css('#page-title {visibility: hidden; position: absolute;}', array('group' => CSS_THEME, 'type' => 'inline'));
   }
   if (strpos(current_path(), 'islandora/object/') !== 0 ) {
     $block = module_invoke_all('detail_tools_block_view');

     $block['list']['#type'] = 'ul';
     $block['list']['#theme'] = 'item_list';

     if (isset($block['list']['#attributes']['class'])) {
       $block['list']['#attributes']['class'] = array_unique($block['list']['#attributes']['class']);
     }
     print render($block);
   }
//   if (strpos(current_path(), 'islandora/object/bakerav') !== 0 ) {
     // dsm($variables);
  // }
//   if ($title == "hbscollection") {
//     drupal_add_css('#page-title {visibility: hidden;}', array('group' => CSS_THEME, 'type' => 'inline'));
//   }

// }

}
