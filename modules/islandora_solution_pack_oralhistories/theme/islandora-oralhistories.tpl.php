<?php

/**
 * @file
 * This is the template file for the object page for oralhistories
 *
 * Available variables:
 * - $islandora_object: The Islandora object rendered in this template file
 * - $islandora_dublin_core: The DC datastream object
 * - $dc_array: The DC datastream object values as a sanitized array. This
 *   includes label, value and class name.
 * - $islandora_object_label: The sanitized object label.
 * - $parent_collections: An array containing parent collection(s) info.
 *   Includes collection object, label, url and rendered link.
 *
 * @see template_preprocess_islandora_oralhistories()
 * @see theme_islandora_oralhistories()
 */
?>
<?php
    print t('<hr /><p />');
    $obj_id = $object->id;
    $obj_id2 = str_replace(':','%3A',$obj_id);
    $DOLLAR  = '&#036;';
    $COLON = '&#058;';
    /* $link_prefix = 'https://digital.lib.utk.edu/collections/islandora/object/'.$obj_id2; */
    /* print t($DOLLAR.'link_prefix = '.$link_prefix.' --C-- <p /> '); */
    /* $PDFurl = $link_prefix.'/datastream/PDF/view'; */
    $PDFurl = request_uri().'/datastream/PDF/view';
    $PDFtarget = $PDFurl.' target="_blank" ';
    if (isset($object['PDF'])){
        print t('<a href='.$PDFtarget.' >View/Download PDF</a>  <p />');
        print t('<hr />');
  }
    $documenturl = request_uri().'/datastream/MAIN_DOCUMENT/download';
    $doctarget = $documenturl.' target="_blank" ';

    if (isset($object['MAIN_DOCUMENT'])){
           print t('<a href='.$doctarget.' >View/Download Word Document</a>  <p />');
        print t('<hr />');
    }
?>
<div class="islandora-oralhistories-object islandora" vocab="http://schema.org/" prefix="dcterms: http://purl.org/dc/terms/" typeof="VideoObject">
  <div class="islandora-oralhistories-content-wrapper  clearfix">
    <?php if ($islandora_content['viewer']): ?>
      <div class="islandora-oralhistories-content">
        <?php print $islandora_content['viewer']; ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="islandora-oralhistories-metadata">
    <?php print $description; ?>
    <?php if ($parent_collections): ?>
      <div>
        <h2><?php print t('In collections'); ?></h2>
        <ul>
          <?php foreach ($parent_collections as $collection): ?>
        <li><?php print l($collection->label, "islandora/object/{$collection->id}"); ?></li>
          <?php endforeach; ?>
        </ul>
      </div>
    <?php endif; ?>
    <?php print $metadata; ?>
  </div>
</div>
