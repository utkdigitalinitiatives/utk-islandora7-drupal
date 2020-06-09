/**
 * @file
 * js/conditional_access_rights.js
 *
 *
 *  Copyright 2017 Leiden University Library
 *
 *  This file is part of islandora_condtional_access_rights.
 *
 *  islandora_condtional_access_rights is free software: you can redistribute it and/or modify
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

(function ($) {
  var tnurl = '';
  Drupal.behaviors.conditional_access_rights = {
    attach: function(context, settings) {
      tnurl = settings.conditional_access_rights.tn_access_restricted;
    }
  }
  var replaceInaccessibleThumbnail = function() {
    var _replaceInaccessibleThumbnail = function(img) {
      if (tnurl === '') {
        setTimeout(function() { _replaceInaccessibleThumbnail(img) }, 100);
        return;
      }
      var parts = img.src.split("?", 2);
      var isThumb = (parts[0].endsWith('datastream/TN/view') || parts[0].endsWith('islandora/images/folder.png'));
      isThumb = isThumb || (parts[0].indexOf('islandora_imagecache') !== -1);
      if (isThumb) {
        var newsrc = tnurl;
        if (parts.length == 2) {
          newsrc += '?' + parts[1];
        }
        
        $(img)
          .unbind("error")
          .attr("src", newsrc)
          .parent().find(":hidden").show();
      }
    };
    _replaceInaccessibleThumbnail(this);
  };
  $(document).ready(function() {
    $('.islandora-solr-search-result IMG').on("error", replaceInaccessibleThumbnail);
    $('.islandora-solr-grid .solr-grid-thumb IMG').on("error", replaceInaccessibleThumbnail);
    $('.islandora-object-thumb IMG').on("error", replaceInaccessibleThumbnail);
    $('.islandora-compound-thumbs .dc-grid-item IMG').on("error", replaceInaccessibleThumbnail);
  });
})(jQuery);

