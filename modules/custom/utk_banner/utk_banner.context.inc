<?php

/**
 * @file
 * utk_banner.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function utk_banner_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'utk_banner';
  $context->description = '';
  $context->tag = 'utk_frontend';
  $context->conditions = array(
    'islandora_context_condition_is_islandora_object' => array(
      'values' => array(
        0 => TRUE,
      ),
      'options' => array(
        'islandora_is_islandora_object_types' => 'both',
      ),
    ),
    'node' => array(
      'values' => array(
        'page' => 'page',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'utk_lib_digital_custom-utk_lib_digital_custom_banner' => array(
          'module' => 'utk_lib_digital_custom',
          'delta' => 'utk_lib_digital_custom_banner',
          'region' => 'splashbanner',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('utk_frontend');
  $export['utk_banner'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'utk_digital_header';
  $context->description = '';
  $context->tag = 'utk_frontend';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'utk_lib_digital_custom-utk_lib_digital_custom_header' => array(
          'module' => 'utk_lib_digital_custom',
          'delta' => 'utk_lib_digital_custom_header',
          'region' => 'utk_header',
          'weight' => '-10',
        ),
        'block-3' => array(
          'module' => 'block',
          'delta' => '3',
          'region' => 'utk_header',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('utk_frontend');
  $export['utk_digital_header'] = $context;

  return $export;
}
