<?php

/**
 * @file
 * utk_header.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function utk_header_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'utk_header';
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
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('utk_frontend');
  $export['utk_header'] = $context;

  return $export;
}
