<?php
/**
 * @file
 * Template file to style output.
 * add code for link to View/Download PDF per DIT-370
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



<?php if(isset($viewer)): ?>
  <div id="book-viewer">
      <?php $transformed_pid = str_replace(":", "/", $object->id); ?>
      <?php $assemble_uri = 'http://' . getenv('HTTP_HOST') . '/assemble/manifest/' . $transformed_pid ; ?>
      <?php print '<a href="' . $assemble_uri . '" ><img style="max-width:2rem" src="https://iiif.io/assets/images/logos/logo-sm.png" alt="View IIIF Manifest" title="View IIIF Manifest" /></a>'; ?>
      <?php print '<a href="https://uv-v3.netlify.app/#?c=&m=&s=&cv=&manifest=' . $assemble_uri . '" ><img style="max-width:2rem" src="https://www.qdl.qa/sites/all/themes/QDLTheme/css/img/logo_uv.png" alt="Open in Universal Viewer" title="Open in Universal Viewer"/></a>'; ?>
      <?php print '<a href="https://projectmirador.org/embed/?iiif-content=' . $assemble_uri . '" ><img style="max-width:2rem" src="https://www.qdl.qa/sites/all/themes/QDLTheme/css/img/logo_mirador.png" alt="Open in Mirador" title="Open in Mirador"/></a>'; ?>
    <?php print $viewer; ?>
  </div>
<?php endif; ?>

<?php if($display_metadata === 1): ?>
  <div class="islandora-book-metadata">
    <?php print $description; ?>
    <?php if($parent_collections): ?>
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
<?php endif; ?>
