<?php

/**
 * @file
 * utk_context_and_blocks.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function utk_context_and_blocks_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'collection_banner';
  $context->description = 'Dynamic Banner for All Collections';
  $context->tag = 'collection';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'islandora/object' => 'islandora/object',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-214' => array(
          'module' => 'block',
          'delta' => '214',
          'region' => 'splashbanner',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Dynamic Banner for All Collections');
  t('collection');
  $export['collection_banner'] = $context;

  return $export;
}
