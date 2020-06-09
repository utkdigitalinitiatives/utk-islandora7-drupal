<?php

/**
 * @file
 * utk_users.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function utk_users_user_default_roles() {
  $roles = array();

  // Exported role: Cataloger.
  $roles['Cataloger'] = array(
    'name' => 'Cataloger',
    'weight' => 5,
  );

  // Exported role: Student Assistant.
  $roles['Student Assistant'] = array(
    'name' => 'Student Assistant',
    'weight' => 6,
  );

  // Exported role: Web Developer.
  $roles['Web Developer'] = array(
    'name' => 'Web Developer',
    'weight' => 2,
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 4,
  );

  // Exported role: iadmin.
  $roles['iadmin'] = array(
    'name' => 'iadmin',
    'weight' => 3,
  );

  return $roles;
}
