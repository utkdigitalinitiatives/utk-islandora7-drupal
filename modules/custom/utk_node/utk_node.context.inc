<?php

/**
 * @file
 * utk_node.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function utk_node_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'utk_node';
  $context->description = '';
  $context->tag = 'utk_frontend';
  $context->conditions = array(
    'node' => array(
      'options' => array(
        'node_form' => '1',
      ),
      'values' => array(
        'page' => 'page',
      ),
    ),
    'path' => array(
      'values' => array(
        'wpatva*' => 'wpatva*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-1' => array(
          'delta' => '1',
          'module' => 'menu_block',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('utk_frontend');
  $export['utk_node'] = $context;

  return $export;
}
