Drupal.BSMegaMenu = Drupal.BSMegaMenu || {};

(function ($) {
  Drupal.BSMegaMenu.oldWindowWidth = 0;
  Drupal.BSMegaMenu.displayedMenuMobile = false;
  Drupal.BSMegaMenu.supportedScreens = [980];
  Drupal.BSMegaMenu.menuResponsive = function () {
    var windowWidth = window.innerWidth ? window.innerWidth : $(window).width();
    var navCollapse = $('.bootstrap-megamenu').children('.navbar-collapse');
    if (windowWidth < Drupal.BSMegaMenu.supportedScreens[0]) {
      navCollapse.addClass('collapse');
      if (Drupal.BSMegaMenu.displayedMenuMobile) {
        navCollapse.css({height: 'auto', overflow: 'visible'});
      } else {
        navCollapse.css({height: 0, overflow: 'hidden'});
      }
    } else {
      // If width of window is greater than 980 (supported screen).
      navCollapse.removeClass('collapse');
      if (navCollapse.height() <= 0) {
        navCollapse.css({height: 'auto', overflow: 'visible'});
      }
    }
  };

  Drupal.behaviors.bsMegaMenuAction = {
    attach: function(context) {
      $('.bootstrap-megamenu-button', context).once('menuIstance', function () {
        var This = this;
        $(This).click(function() {
          if(parseInt($(this).parent().children('.navbar-collapse').height())) {
            $(this).parent().children('.navbar-collapse').css({height: 0, overflow: 'hidden'});
            Drupal.BSMegaMenu.displayedMenuMobile = false;
          }
          else {
            $(this).parent().children('.navbar-collapse').css({height: 'auto', overflow: 'visible'});
            Drupal.BSMegaMenu.displayedMenuMobile = true;
          }
        });
      });
      
      
      var isTouch = 'ontouchstart' in window && !(/hp-tablet/gi).test(navigator.appVersion);
      if(!isTouch){
        $(document).ready(function($){
          var mm_duration = 0;
          $('.bootstrap-megamenu').each (function(){
            if ($(this).data('duration')) {
              mm_duration = $(this).data('duration');
            }
          });
          var mm_timeout = mm_duration ? 100 + mm_duration : 500;
          $('.nav > li, li.mega').hover(function(event) {
            var $this = $(this);
            if ($this.hasClass ('mega')) {
              $this.addClass ('animating');
              clearTimeout ($this.data('animatingTimeout'));
              $this.data('animatingTimeout', setTimeout(function(){$this.removeClass ('animating')}, mm_timeout));
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', setTimeout(function(){$this.addClass ('open')}, 100));  
            } else {
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', 
              setTimeout(function(){$this.addClass ('open')}, 100));
            }
          },
          function(event) {
            var $this = $(this);
            if ($this.hasClass ('mega')) {
              $this.addClass ('animating');
              clearTimeout ($this.data('animatingTimeout'));
              $this.data('animatingTimeout', 
              setTimeout(function(){$this.removeClass ('animating')}, mm_timeout));
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', setTimeout(function(){$this.removeClass ('open')}, 100));
            } else {
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', 
              setTimeout(function(){$this.removeClass ('open')}, 100));
            }
          });
        });
      }

      $(".bootstrap-megamenu-submenu.full-width-menu").each(function(){
        $(this).css("min-width", ($(this).parents(".bootstrap-megamenu-nav.level-0").width())+"px");
      });     
      $(window).resize(function() {
         $(".bootstrap-megamenu-submenu.full-width-menu").each(function(){
        $(this).css("min-width", ($(this).parents(".bootstrap-megamenu-nav.level-0").width())+"px");
      });
        var windowWidth = window.innerWidth ? window.innerWidth : $(window).width();
        if (windowWidth != Drupal.BSMegaMenu.oldWindowWidth) {
          Drupal.BSMegaMenu.oldWindowWidth = windowWidth;
          Drupal.BSMegaMenu.menuResponsive();
        }
      });
    },
  }
})(jQuery);

