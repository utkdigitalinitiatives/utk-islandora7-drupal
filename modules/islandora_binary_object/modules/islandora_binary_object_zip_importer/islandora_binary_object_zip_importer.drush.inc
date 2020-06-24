<?php

/**
 * @file
 * Drush preprocess batch.
 */

/**
 * Implements hook_drush_command().
 */
function islandora_binary_object_zip_importer_drush_command() {
  return array(
    'islandora_binary_object_batch_scan_preprocess' => array(
      'aliases' => array('ibobsp'),
      'description' => 'Preprocess a batch for binary objects.',
      'drupal dependencies' => array('islandora_binary_object_zip_importer'),
      'options' => array(
        'parent' => array(
          'description' => dt('The parent object to which the items should be added. Defaults to the root Islandora repository PID.'),
          'value' => 'optional',
        ),
        'namespace' => array(
          'description' => dt('Namespace to give to created objects. Defaults to the namespace defined in the Fedora configuration.'),
          'value' => 'optional',
        ),
        'scan_target' => array(
          'description' => dt('The full path to the .zip file to scan.'),
          'required' => TRUE,
        ),
      ),
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
    ),
  );
}

/**
 * Command callback for binary object batch scan preprocess.
 */
function drush_islandora_binary_object_zip_importer_islandora_binary_object_batch_scan_preprocess() {
  $file_uri = drush_get_option('scan_target');
  if (!file_exists($file_uri)) {
    drush_set_error('islandora_binary_object_zip_importer', 'No file exists at the given path.');
    return;
  }

  drupal_static_reset('islandora_get_tuque_connection');
  $connection = islandora_get_tuque_connection();

  $parent = drush_get_option('parent', variable_get('islandora_repository_pid', 'islandora:root'));
  module_load_include('inc', 'islandora', 'includes/utilities');
  $file = islandora_temp_file_entry($file_uri);

  // Mimicking the structure/function of the form batch.
  $info_params = array(
    'values' => array(
      'file' => $file,
      'namespace' => drush_get_option('namespace'),
    ),
  );
  $preprocessor = new BinaryObjectZipBatchImporter($connection, BinaryObjectZipBatchImporter::getBatchInfo($info_params), $parent);
  $preprocessor->preprocess();
  drush_log(t('SetId: @s', array('@s' => $preprocessor->getSetId())), 'ok');
}
