<?php

/**
 * @file
 * This is the template file for the object page for audio file.
 *
 * @TODO: add documentation about file and available variables
 */
?>

<div class="islandora-audio-object islandora" vocab="http://schema.org/" prefix="dcterms: http://purl.org/dc/terms/" typeof="AudioObject">
  <div class="islandora-audio-content-wrapper clearfix">
    <?php if (isset($islandora_content)): ?>
      <div class="islandora-audio-content">
        <?php if (isset($object['PROXY_MP3']) && !islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $object['PROXY_MP3'])): ?><p>This audio file is restricted to campus only.</p><?php endif; ?>
        <?php print $islandora_content; ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="islandora-audio-metadata">
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
