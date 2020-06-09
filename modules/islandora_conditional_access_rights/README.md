# Islandora conditional access rights

## Introduction

Islandora conditional access rights lets you define the access and access rights of an object conditionally. IP range, user role or metadata (of the object or its parents) can affect the access rights of the object.
It also defines which datastreams are downloadable.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)

## Installation
 
Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

At `admin/islandora/tools/islandora_conditional_access_rights` the configuration location can be defined. This should be an absolute file path
or a URL to the configuration file. See 'ini file' for more information.

### ini file

The configuration file is a file in the PHP INI format, see `https://en.wikipedia.org/wiki/INI_file`
for more information about this format. PHP has some special features, such as support for multiple values for one key by using key[] or key[attr].
See the `example_ini_files` directory for examples.

The configuration file should have the following parts:

Below examples of the parts of the configuration file:

### Metadata values

This part of the configuration is meant to define the metadata values that are used in other parts of the configuration.
This part contains zero or more sections. Each section is named "metadata:key" where "key" is a chosen value.
A "metadata:" section can contain the following keys:

 * datastream: the id of the datastream where the metadata is extracted from (mandatory)
 * xpath: a xpath to extract the data from the datastream (mandatory)
 * namespace: the namespace definition, use like "mods http://www.loc.gov/mods/v3" (multiple values, optional)

### Access conditions

This part of the configuration is meant to define the conditions.
This part should contain 1 or more sections. Each section is named "condition:key" where "key" is a chosen value.

A "condition:" section can contain a combination of the following keys:
 * `user_role`: the name of the user role. If the user with this role is logged on, this condition is met. (multiple values, optional)
 * `ip_range`: if the users IP falls in this range, the condition is met. A range should be defined like 1.1.1.1-2.2.2.2, IPv4 and IPv6 are supported. (multiple values, optional)
 * `content_model`: if the objects content model is the same is this, then this condition is met. (multiple values, optional)
 * condition: use this to combine previously defined conditions, the "operator" key defines how these conditions should be combined. (multiple values, optional)
 * operator: if combined with key "condition" this can have the following value: "and" (all conditions should be met), "or" (any condition should be met) or "negate" (disproves the condition). (optional)
 * metadata: use together with comparator and value. This value should be defined as a "metadata:" section. (optional)
 * comparator: use together with metadata and value. Defines how the metadata compares to the value. Valid values include: "equals" (metadata value is exactly the same as value), "contains" (metadata value contains or is contained by value), "lowercaseLetterMatch" (only letters and numbers are used to compare and uppercase is seen as lowercase. For example "Test." is the same as "tE.st!" with this comparator), "afterDateISO8601" and "beforeDateISO8601" (compare dates in ISO8601 format. after is TRUE if metadata date is after the value date. before is TRUE if metadata date is chronologically before the value date. If one of the values is not a valid ISO8601 date, the condition will be FALSE. Value can be a ISO8601 date or "today" (date of current day) or "now" (date and time of current moment).). (optional)
 * value: use together with metadata and comparator. Should be a string value. (optional)

### Access restrictions

This part of the configuration is meant to define the access restrictions for the conditions that are met.
This part contains 1 or more sections. Each section is named "access:`condition_key`" where "`condition_key`" is defined in the "access conditions" part of the configuration.

A "access:" section can contain the following keys:
 * `deny_viewing`: TRUE or FALSE, defines is the whole object can be viewed
 * `deny_access_to_dsid`: a datastream ID of the datastream to deny view access to. Make sure a administrator always has access to datastreams. (multiple values, optional)
 * `allow_access_to_dsid`: a datastream ID of the datastream to allow view access to. (multiple values, optional)
 * `provide_download_of_dsid`: a datastream ID of the datastream that is allowed to be downloaded. Remember to give access to the datastream as well. (multiple values, optional)
 * `access_text`: the access text. (optional)
 * `access_usetext`: the access use text. (optional)
 * `access_link`: the absolute link to the access rights explanation page. (optional)
 * `access_image`: the absolute URL of an image. (optional)

The values of the "`*_to_dsid`" and "`provide_download_of_dsid`" keys should be valid DSID's, or ALL (for all datastreams) or NONE (for no datastream at all).

## Documentation

Because this module also provides a download button, the code below should be included in the template file.

### How to include download buttons

```php
// Render the detail tools block
  $block = module_invoke_all('detail_tools_block_view');

  $block['list']['#type'] = 'ul';
  $block['list']['#theme'] = 'item_list';

  if (isset($block['list']['#attributes']['class'])) {
    $block['list']['#attributes']['class'] = array_unique($block['list']['#attributes']['class']);
  }

  print render($block);

```

## drush commands

### check\_access\_rights\_settings

Check the access rights value of the children of a specific collection.

```
drush --user=admin check_access_rights_settings --collection=islandora:root --configuration=/path/to/a/ini/file
drush --user=admin check_access_rights_settings --collection=islandora:root --configuration=/url/to/a/ini/file
drush --user=admin cars --collection=islandora:root --configuration=/url/to/a/ini/file
```


## Maintainers/Sponsors

Current maintainers:

* [Lucas van Schaik](https://github.com/lucasvanschaik)

## Development

If you would like to contribute to this module, please contact the current maintainer.


## License

[GPLv3](LICENSE.txt)
Copyright 2017-2018 Leiden University Library

