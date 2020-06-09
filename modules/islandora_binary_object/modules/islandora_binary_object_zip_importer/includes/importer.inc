<?php

/**
 * @file
 * Defines the binary object import classes.
 */

/**
 * Binary Zip Importer.
 */
class BinaryObjectZipBatchImporter extends ZipBatchImporter {

  protected $itemClass = 'BinaryObjectZipBatchImportObject';

  /**
   * Get the form for this importer.
   *
   * @see IslandoraBatchImporter::getForm()
   */
  public static function getForm(array &$form_state) {
    // Get the namespace for binary objects.
    $parent = islandora_object_load($form_state['storage']['parent_pid']);
    $ns_options = array(
      NULL => t('Default namespace'),
    );
    // By this point we should know that the collection has a policy with a
    // binary object content model.
    $policy = new CollectionPolicy($parent['COLLECTION_POLICY']->content);
    $models = $policy->getContentModels();
    $namespace = $models['islandora:binaryObjectCModel']['namespace'];
    if (!empty($namespace)) {
      module_load_include('inc', 'islandora', 'includes/utilities');
      $namespace = islandora_get_namespace($namespace);
      $ns_options[$namespace] = $namespace;
    }

    return array(
      'fs' => array(
        '#type' => 'fieldset',
        '#title' => t('Binary Object Zip Batch Importer'),
        '#description' => t('Select the file containing the assets and metadata to import. Assets and metadata will be matched together based on the portion of the filename without the extension, e.g., my_file.xml and my_file.pdf would be combined into a single object. Only one file should be paired with each .xml, if this is the case. This importer currently does not support importing stub objects with .xml records.'),
        'file' => array(
          '#type' => 'managed_file',
          '#title' => t('Zip file containing files to import'),
          '#upload_validators' => array(
            'file_validate_extensions' => array('zip'),
          ),
        ),
        'namespace' => array(
          '#type' => 'select',
          '#title' => t('Object Namespace'),
          '#description' => t('The namespace in which the imported objects will be created.'),
          '#options' => $ns_options,
        ),
        'submit' => array(
          '#type' => 'submit',
          '#value' => t('Import'),
        ),
      ),
    );
  }

  /**
   * Determine if we're ready to process the batch.
   *
   * @see IslandoraBatchImporter::readyForBatch()
   */
  public static function readyForBatch(array &$form_state) {
    if (empty($form_state['values']['file'])) {
      form_set_error('file', t('Need a Zip file!'));
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Get info for the source parameter for the itemClass factory.
   *
   * @see IslandoraBatchImporterInterface::getBatchInfo()
   */
  public static function getBatchInfo(array &$form_state) {
    $file = is_object($form_state['values']['file']) ? $form_state['values']['file'] : file_load($form_state['values']['file']);
    return array(
      'file' => $file,
      'pid_namespace' => $form_state['values']['namespace'],
      'object_info' => static::getIngestInfo($file),
      'processed_objects' => array(),
    );
  }

}

/**
 * Zip import binary object.
 */
class BinaryObjectZipBatchImportObject extends ZipBatchImportObject {

  /**
   * Get an item from the source.
   *
   * @see IslandoraImportObjectInterface::getOne()
   */
  public static function getOne(&$info) {
    $key = key($info['object_info']);
    // @TODO: Ignoring XML for now (is it an object's OBJ or a stub record's
    // XML? Should be left up to the user ultimately).
    if (count($info['object_info'][$key]) == 1 && isset($info['object_info'][$key]['xml'])) {
      unset($info['object_info'][$key]);
      return FALSE;
    }
    $record = array(
      'pid_namespace' => $info['pid_namespace'],
      'file' => $info['file'],
      'content_model' => array('islandora:binaryObjectCModel'),
    );
    $record['object_info'] = $info['processed_objects'][$key] = $info['object_info'][$key];
    unset($info['object_info'][$key]);
    return (empty($record) ? FALSE : new static($record));
  }

  /**
   * Determine the mimetype for the given file.
   *
   * Without a DS-COMPOSITE-MODEL that defines OBJs, we kind of have to make a
   * best-effort guess here, which is all we do. For now, XML files are always
   * appended as XML records, and won't be passed through this.
   *
   * @param string $name
   *   The filename to determine DSID/mimetype for.
   *
   * @return string
   *   The detected mimetype of the given filename.
   */
  protected function determineMimetype($name) {
    static $mime_detect = NULL;
    if (is_null($mime_detect)) {
      $mime_detect = new MimeDetect();
    }
    return $mime_detect->getMimetype($name);
  }

  /**
   * Get the datastream structure for an object.
   *
   * @see IslandoraImportObject::getDatastreams()
   */
  protected function getDatastreams(&$errors = NULL, &$files = NULL) {
    $to_return = array();
    $default_scheme = file_default_scheme() . "://";
    module_load_include('inc', 'islandora', 'includes/utilities');

    // Get DSID and mimetype.
    foreach ($this->source['object_info'] as $datastream => $name) {
      if ($datastream == 'xml') {
        $mimetype = 'application/xml';
        // Darwin Core.
        if ($this->isDWC($this->getXML())) {
          $dsid = 'DWC';
        }
        // MADS.
        elseif ($this->isMADS($this->getXML())) {
          $dsid = 'MADS';
        }
        // MODS.
        elseif ($this->isMODS($this->getXML())) {
          $dsid = 'MODS';
        }
        // DC.
        elseif ($this->isDC($this->getXML())) {
          $dsid = 'DC';
        }
        // In all other cases, upload as an OBJ.
        else {
          $dsid = 'OBJ';
        }
      }
      // Everything else is the primary datastream.
      else {
        $dsid = 'OBJ';
        $mimetype = $this->determineMimetype($name);
      }

      // Generate DSID info.
      $zip = new ZipArchive();
      $zip->open(drupal_realpath($this->source['file']->uri));
      if ($stream = $zip->getStream($name)) {
        $uri = file_unmanaged_save_data($stream, $default_scheme . basename($name));
        $file = islandora_temp_file_entry($uri, $mimetype);
        $files[] = $file;

        $to_return += array(
          $dsid => array(
            'dsid' => $dsid,
            'label' => "$dsid datastream",
            'mimetype' => $mimetype,
            'datastream_file' => file_create_url($file->uri),
            'filename' => $name,
            'control_group' => 'M',
            'file' => $file,
          ),
        );
      }
      $zip->close();
    }

    // Correct labels.
    foreach ($to_return as &$datastream) {
      $datastream['label'] = $this->getLabel($datastream['dsid'], $datastream);
    }

    // See if the user uploaded DC, if not create it now.
    if (!isset($to_return['DC'])) {
      $obtained_dc = $this->getDC();
      if ($obtained_dc) {
        $uri = file_unmanaged_save_data($obtained_dc, $default_scheme . basename($name));
        $dc_file = islandora_temp_file_entry($uri, 'application/xml');
        $files[] = $dc_file;
        $to_return['DC'] = array(
          'dsid' => 'DC',
          'label' => 'DC Record',
          'mimetype' => 'application/xml',
          'control_group' => 'X',
          'datastream_file' => file_create_url($dc_file->uri),
          'file' => $dc_file,
        );
      }
      else {
        $errors[] = array(
          t('Failed to produce DC record for @pid.'),
        );
      }
    }
    return $to_return;
  }

}
