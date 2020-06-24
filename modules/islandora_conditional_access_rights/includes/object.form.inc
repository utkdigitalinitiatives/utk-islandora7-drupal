<?php

/**
 * @file
 * Contains form functions for displaying the access rights for one object.
 *
 *
 *  Copyright 2017 Leiden University Library
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
 * Implements hook_form().
 */
function access_rights_view_form(array $form, array &$form_state, AbstractObject $object) {
  module_load_include('inc', 'islandora_conditional_access_rights', 'includes/config');
  module_load_include('inc', 'islandora_conditional_access_rights', 'includes/access_rights_settings');

  $form['islandora_conditional_access_rights'] = array(
    '#type' => 'fieldset',
    '#title' => t('Islandora conditional access rights'),
  );

  $configlocation = variable_get('islandora_conditional_access_rights_config_location');
  if ($configlocation) {
    $disregard = array();

    if (isset($form_state["input"]["conditionsmet"])) {
      $conditionsmet = explode(',', $form_state["input"]["conditionsmet"]);
      foreach ($conditionsmet as $cond) {
        $cwop = str_replace('.', '_', $cond);
        if (!isset($form_state["input"][$cwop]) || ($form_state["input"][$cwop] !== 'on')) {
          $disregard[$cond] = TRUE;
        }
      }
    }
    $config = islandora_conditional_access_rights_get_configuration($configlocation);
    $accesssettings = islandora_conditional_access_rights_get_access_settings_from_object_or_parent($object, $config, $disregard);

    $table = '<TR><TH>' . t('Conditions met') . '</TH><TD>';
    if(empty($accesssettings['_conditions_met'])) {
      $table .= "<em>(none)</em>";
    }
    else {
      foreach ($accesssettings['_conditions_met'] as $cond => $isaccesscond) {
        $cwop = str_replace('.', '_', $cond);
        if ($isaccesscond) {
          $table .= '<strong>' . '<input type="checkbox" name="' . $cwop . '" onchange="this.form.submit();"';
          if (!isset($form_state["input"]["conditionsmet"]) || (isset($form_state["input"][$cwop]) && ($form_state["input"][$cwop] === 'on'))) {
            $table .= ' checked';
          }
          $table .= '> ' . $cond . '</strong>';
        }
        else {
          $table .= '<input type="checkbox" name="' . $cond . '" checked disabled> ' . $cond;
        }
        $table .= '</BR>';
      }
      $table .= '<INPUT type="hidden" name="conditionsmet" value="' . implode(',', array_keys($accesssettings['_conditions_met'])) . '">';
    } 
    $table .= '</TD></TR>';

    $accessible = islandora_conditional_access_rights_accessible_object($object, $disregard);
    $accessible = (($accessible !== NULL)?($accessible?"FALSE":"TRUE"):'<em>' . t('Undefined') . '</em>');
    $accessible .= ' ' . _access_rights_view_reason($accesssettings, 'deny_viewing', $object->id);
    $table .= '<TR><TH>' . t('Deny viewing') . '</TH><TD>' . $accessible . '</TD></TR>';

    $accessible = islandora_conditional_access_rights_accessible_dsids($object, $disregard);
    $accessible = (count($accessible) > 0)?implode(', ', $accessible):'<em>' . t('None') . '</em>';
    $accessible .= ' ' . _access_rights_view_reason($accesssettings, 'allow_access_to_dsid', $object->id);
    $table .= '<TR><TH>' . t('Accessible datastreams') . '</TH><TD>' . $accessible . '</TD></TR>';
     
    $fromobjid = '';
    $restricted = islandora_conditional_access_rights_restricted_dsids($object, $disregard);
    $restricted = (count($restricted) > 0)?implode(', ', $restricted):'<em>' . t('None') . '</em>';
    $restricted .= ' ' . _access_rights_view_reason($accesssettings, 'deny_access_to_dsid', $object->id);
    $table .= '<TR><TH>' . t('Restricted datastreams') . '</TH><TD>' . $restricted . '</TD></TR>';
     
    $fromobjid = '';
    $downloadable = islandora_conditional_access_rights_downloadable_dsids_with_label($object, $disregard);
    $table .= '<TR><TH>' . t('Downloadable datastreams') . '</TH>';
    if (count($downloadable) > 0) {
      $table .= '<TD>';
      foreach ($downloadable as $dsid => $text) {
        $table .= $dsid . ' => ' . $text . '<BR/>'; 
      }
      $table .= ' ' . _access_rights_view_reason($accesssettings, 'provide_download_of_dsid', $object->id);
      $table .= '</TD>';
    }
    else {
      $table .= '<TD><em>' . t('None') . '</em>';
      $table .= ' ' . _access_rights_view_reason($accesssettings, 'provide_download_of_dsid', $object->id);
      $table .= '</TD>';
    }
    $table .= '</TR>';

    $fromobjid = '';
    $accessdesc = islandora_conditional_access_rights_access_description($object, $disregard);
    $from = _access_rights_view_reason($accesssettings, 'access_text', $object->id);
    $table .= '<TR><TH>' . t('Access text') . '</TH><TD>' . $accessdesc['accesstext'] . $from . '</TD></TR>';
    $from = _access_rights_view_reason($accesssettings, 'access_usetext', $object->id);
    $table .= '<TR><TH>' . t('Access use text') . '</TH><TD>' . $accessdesc['accessusetext'] . $from . '</TD></TR>';
    $from = _access_rights_view_reason($accesssettings, 'access_link', $object->id);
    $table .= '<TR><TH>' . t('Access link') . '</TH><TD>' . $accessdesc['accesslink'] . $from . '</TD></TR>';
    $from = _access_rights_view_reason($accesssettings, 'access_image', $object->id);
    $table .= '<TR><TH>' . t('Access image') . '</TH><TD><IMG src="' . $accessdesc['accessimage'] .'" style="max-height:2em;"/> ' . $accessdesc['accessimage'] . $from . '</TD></TR>';
    $ipdependent = (isset($accesssettings['_ip_dependent']) && $accesssettings['_ip_dependent'])?t('yes'):t('no');
    $table .= '<TR><TH>' . t('IP dependent') . '</TH><TD>' . $ipdependent . ' (current ip address is: ' . ip_address() . ')</TD></TR>';
  }
  else {
    $table = '<TR><TD>' . t('No configuration location') . '</TD></TR>';
  }
  
  $form['islandora_conditional_access_rights']['info'] = array(
    '#markup' => '<TABLE>' . $table . '</TABLE>',
  );

  return $form;
}


function _access_rights_view_reason($accesssettings, $type, $forobjectid) {
  $reason = '';
  if (isset($accesssettings['_reasons'][$type])) {
    foreach ($accesssettings['_reasons'][$type] as $condition => $objectid) {
      if (strlen($reason) > 0) {
        $reason .= ', ';
      }
      if ($objectid === 'default') {
        $reason .= t('of default value');
      }
      else {
        if ($objectid === $forobjectid) {
          $reason .= t('condition "%condition" is met', array('%condition' => $condition));
        }
        else {
          $reason .= t('condition "%condition" is met for object "%object"', array('%condition' => $condition, '%object' => $objectid));
        }
      } 
    }
    if (strlen($reason) > 0) {
      $reason = ' (<em>' . t('because') . ' ' . $reason . '</em>)';
    }
  }
  return $reason;
}
