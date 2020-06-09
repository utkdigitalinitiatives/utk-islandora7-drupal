# Islandora Binary Object Zip Importer

## Introduction

Zip file batch importer specifically tailored to the Binary Object SP's particular idiosyncrasies.

Other than that, works basically the same as the standard Zip Importer.

## Requirements

This module requires the following modules/libraries:

* [Islandora Batch](https://github.com/islandora/islandora_batch)
* [Islandora Zip Importer](https://github.com/islandora/islandora_importer) (submodule of that repository)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

No configuration options currently exist.

## Troubleshooting/Issues

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora google groups](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

## FAQ

Q. What happens if I upload a .xml file inside a .zip that isn't paired with any other files?

A. If the .xml corresponds to MODS, MADS, Dublin Core or Darwin Core, the file is skipped, as there is no way to tell currently whether the file is intended to be a stub record or a binary object. If it doesn't correspond to one of these known formats, it is uploaded as the OBJ datastream.

## Maintainers/Sponsors

Current maintainers:

* [discoverygarden](https://github.com/discoverygarden)

This project has been sponsored by:

* [University of Connecticut](http://lib.uconn.edu)

## Development

If you would like to contribute to this module, please check out [CONTRIBUTING.md](CONTRIBUTING.md). In addition, we have helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the [Islandora.ca](http://islandora.ca) site.

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
