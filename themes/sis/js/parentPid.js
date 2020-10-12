(function ($, Drupal) {

    Drupal.behaviors.parentPid = {
        attach: function () {

            $(document).ready(function () {

                var source = "#utk-parent-pid";

                if ($(source).length) {
                    var parentPid = $(source).attr("data-pid");
                    var target = "option[value='"+ parentPid + "']";
                    $(target).prependTo("#edit-collection-select");
                    $(target).attr("selected", "selected");
                }

            });

        }
    };

})(jQuery, Drupal);
