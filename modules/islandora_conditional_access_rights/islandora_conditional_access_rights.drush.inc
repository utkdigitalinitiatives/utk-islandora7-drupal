<?php
/**
 * @file
 * Functions for batch checking the access rights settings of objects.
 *
 *
 *  Copyright 2017-2019 Leiden University Library
 *
 *  This file is part of islandora_conditional_access_rights.
 *
 *  islandora_conditional_access_rights is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Implements hook_drush_command().
 */
function islandora_conditional_access_rights_drush_command() {
  $items['check_access_rights_settings'] = array(
    'description' => 'Check the access rights configuration and optionally the settings of the children of a specific collection.',
    'options' => array(
      'configuration' => 'Mandatory, the absolute filepath to an ini file.',
      'collection' => 'Optional, one collection ID.',
      'limit_to_object' => 'Optional, limit the access rights finding to the object itself, so do not use its parent or the default settings.',
    ),
    'aliases' => array('cars'),
    'examples' => array(
      'drush --user=admin check_access_rights_settings --configuration=/path/to/a/ini/file',
      'drush --user=admin check_access_rights_settings --configuration=/url/to/a/ini/file',
      'drush --user=admin check_access_rights_settings --collection=islandora:root --configuration=/path/to/a/ini/file',
      'drush --user=admin check_access_rights_settings --collection=islandora:root --configuration=/url/to/a/ini/file',
      'drush --user=admin cars --collection=islandora:root --configuration=/url/to/a/ini/file',
      'drush --user=admin cars --collection=islandora:root --configuration=/url/to/a/ini/file --limit_to_object',
    ),
  );
  return $items;
}

/**
 * Implements drush_hook_COMMAND_validate().
 */
function drush_islandora_conditional_access_rights_check_access_rights_settings_validate() {
  return _islandora_conditional_access_rights_validate_collection_configuration();
}

function _islandora_conditional_access_rights_validate_collection_configuration() {
  module_load_include('inc', 'islandora_conditional_access_rights', 'includes/config');

  $configlocation = drush_get_option('configuration');
  $collectionid = drush_get_option('collection');
  $configdir = '';
  $configspecificfile = '';

  // check configuration option
  if (!isset($configlocation)) {
    return drush_set_error("Argument configuration is mandatory!");
  }
  $error = '';
  if (!islandora_conditional_access_rights_valid_config_file($configlocation, $error)) {
    return drush_set_error($error);
  }

  // check collection option
  if (isset($collectionid)) {
    $collection = islandora_object_load($collectionid);
    if (!($collection && in_array('islandora:collectionCModel', $collection->models))) {
      return drush_set_error("Collection '$collectionid' does not resolve to a collection");
    }
  }

  return TRUE;
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_islandora_conditional_access_rights_check_access_rights_settings() {
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora_conditional_access_rights', 'includes/access_rights_settings');

  $configlocation = drush_get_option('configuration');
  $collectionid = drush_get_option('collection');
  $limittoobject = drush_get_option('limit_to_object');

  $config = islandora_conditional_access_rights_get_configuration($configlocation);
  if (!isset($collectionid)) {
    print "\nConfiguration at $configlocation is checked.\n";
    return;
  }
  $collection = islandora_object_load($collectionid);
  if ($collection && in_array('islandora:collectionCModel', $collection->models)) {
    $accessvalue2objids = array();
    list($count, $colobjs) = islandora_basic_collection_get_member_objects($collection, -1, -1);
    foreach ($colobjs as $colobj) {
      $cid = $colobj['object']['value'];
      $cobj = islandora_object_load($cid);
      if ($cobj) {
        if ($limittoobject) {
          $ars = islandora_conditional_access_rights_access_rights_settings_for_object($cobj, $config);
        }
        else {
          $ars = islandora_conditional_access_rights_get_access_settings_from_object_or_parent($cobj, $config);
        }
        $av = '';
        if (isset($ars['access_text'])) {
          $av = $ars['access_text'];
        }
        else {
          $av = '(access undefined)';
        }
        if (isset($ars['access_usetext'])) {
          $av = $av . ' -- ' . $ars['access_usetext'];
        }
        else {
          $av = $av . ' -- ' . '(use undefined)';
        }
        if (!isset($accessvalue2objids[$av])) {
          $accessvalue2objids[$av] = array();
        }
        $accessvalue2objids[$av][] = $cid;
      }
    }
    print "\nCheck access rights value results:\n";
    print "==================================\n";
    ksort($accessvalue2objids);
    foreach ($accessvalue2objids as $av => $objids) {
      printf("%5d x %s\n", count($objids), $av);
    }
    print "\n";
  }
}
