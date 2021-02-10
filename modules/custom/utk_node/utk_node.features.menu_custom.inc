<?php

/**
 * @file
 * utk_node.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function utk_node_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-wpa-tva.
  $menus['menu-wpa-tva'] = array(
    'menu_name' => 'menu-wpa-tva',
    'title' => 'WPA/TVA',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('WPA/TVA');

  return $menus;
}
