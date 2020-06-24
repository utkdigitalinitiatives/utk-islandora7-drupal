<?php

/**
 * @file
 * Retrieve the metadata value from an object, using caching.
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
 */

function islandora_conditional_access_rights_get_metadata_values($obj, $config, $neededmdkey, $rebuildcache = FALSE) {
  $id2mdvalue = &drupal_static(__FUNCTION__, array());
  $id = $obj->id;
  $lastchangedate = (string)$obj->lastModifiedDate;
  if ($rebuildcache) {
    unset($id2mdvalue[$id]);
  }
  if (!isset($id2mdvalue[$id][$neededmdkey])) {
    $cachename = $id;
    $cachebin = 'cache_islandora_conditional_access_rights_md_value';
    if (!$rebuildcache) {
      if ($cache = cache_get($cachename, $cachebin)) {
        $found = $cache->data;
        if ($found['_date'] === $lastchangedate) {
          $id2mdvalue[$id] = $found;
        }
      }
    }
    if (!isset($id2mdvalue[$id])) {
      $id2mdvalue[$id] = array('_date' => $lastchangedate);
      $mdsettings = $config['metadata'];
      foreach ($mdsettings as $mdkey => $mdvalues) {
        $dsid = $mdvalues['datastream'];
        $id2mdvalue[$id][$mdkey] = array();
        if (isset($obj[$dsid])) {
          $xpaths = $mdvalues['xpath'];
          $remove = array();

          $content = $obj[$dsid]->content;
          $domdoc = new DOMDocument();
          if ($domdoc->loadXML($content)) {
            $domxpath = new DOMXPath($domdoc);
            if (isset($mdvalues['namespace'])) {
              foreach ($mdvalues['namespace'] as $ns) {
                list($prefix, $uri) = explode(' ', $ns, 2);
                $domxpath->registerNamespace($prefix, $uri);
              }
            }
            $xpath = $mdvalues['xpath'];
            $domnodelist = $domxpath->query($xpath);
            if ($domnodelist && $domnodelist->length > 0) {
              foreach ($domnodelist as $domnode) {
                $text = $domnode->textContent;
                if (isset($text) && strlen($text) > 0) {
                  $id2mdvalue[$id][$mdkey][] = $text;
                }
              }
            }
          }
        }
      }
      cache_set($cachename, $id2mdvalue[$id], $cachebin);
    }
  }
  return $id2mdvalue[$id][$neededmdkey];
}
