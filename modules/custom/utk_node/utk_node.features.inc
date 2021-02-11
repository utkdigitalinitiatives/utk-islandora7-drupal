<?php

/**
 * @file
 * utk_node.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function utk_node_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
