Drupal.TBMegaMenu = Drupal.TBMegaMenu || {};

(function ($) {
  Drupal.behaviors.tbMegaMenuBackendAction = {
    attach: function(context) {
      $('select[name="bootstrap-megamenu-animation"]').change(function() {
        $('#bootstrap-megamenu-duration-wrapper').css({'display': ($(this).val() == 'none' ? 'none' : 'inline-block')});
        $('#bootstrap-megamenu-delay-wrapper').css({'display': ($(this).val() == 'none' ? 'none' : 'inline-block')});
      });
      $(".bootstrap-megamenu-column-inner .close").click(function() {
        $(this).parent().html("");
      });
      $("#bootstrap-megamenu-admin select").chosen({
        disable_search_threshold : 15,
        allow_single_deselect: true
      });
    }
  }
})(jQuery);

