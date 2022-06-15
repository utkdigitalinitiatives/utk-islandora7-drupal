<?php

/**
 * @file
 * This is the template file for the object page for basic image
 *
 * @TODO: add documentation about file and available variables
 */
?>

<div class="islandora-basic-image-object islandora" vocab="http://schema.org/" prefix="dcterms: http://purl.org/dc/terms/" typeof="ImageObject">
    <div class="islandora-basic-image-content-wrapper clearfix">
        <div class="IIIF" style="display: block;">
            <?php $transformed_pid = str_replace(":", "/", $islandora_object->id); ?>
            <?php $assemble_uri = 'http://' . getenv('HTTP_HOST') . '/assemble/manifest/' . $transformed_pid . '?update=1'; ?>
            <?php print '<a href="' . $assemble_uri . '" ><img style="max-width:2rem" src="https://iiif.io/assets/images/logos/logo-sm.png" alt="View IIIF Manifest" title="View IIIF Manifest" /></a>'; ?>
            <?php print '<a href="https://uv-v3.netlify.app/#?c=&m=&s=&cv=&manifest=' . $assemble_uri . '" ><img style="max-width:2rem" src="https://www.qdl.qa/sites/all/themes/QDLTheme/css/img/logo_uv.png" alt="Open in Universal Viewer" title="Open in Universal Viewer"/></a>'; ?>
            <?php print '<a href="https://projectmirador.org/embed/?iiif-content=' . $assemble_uri . '" ><img style="max-width:2rem" src="https://www.qdl.qa/sites/all/themes/QDLTheme/css/img/logo_mirador.png" alt="Open in Mirador" title="Open in Mirador"/></a>'; ?>
        </div>
        <?php if (isset($islandora_content)): ?>
            <div class="islandora-basic-image-content">
                <?php print $islandora_content; ?>
            </div>
        <?php endif; ?>
    </div>
    <div class="islandora-basic-image-metadata">
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
