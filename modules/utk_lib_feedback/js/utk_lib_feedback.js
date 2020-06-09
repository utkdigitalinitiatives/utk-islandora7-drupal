(function ($, Drupal) {

  Drupal.behaviors.utk_lib_feedback = {
    attach: function () {
      $('#utk-lib-feedback-trigger').click(function(e) {
        $('body').toggleClass("utk-feedback-modal");
        $('#utk-script-append').append('<script src="//www.questionpro.com/javascript/embedsurvey.js?version=1"></script>');
      });

      $('#utk-lib-feedback-close').click(function(e) {
        $('body').toggleClass("utk-feedback-modal");
      });
    }
  };

})(jQuery, Drupal);
