<?php

define('FONT_AWESOME_47', 'https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.4.7/css/font-awesome.min.css');
define('JS_CHOSEN_162', 'https://cdnjs.cloudflare.com/ajax/libs/chosen/1.6.2/chosen.jquery.min.js');
define('CSS_CHOSEN_162', 'https://cdnjs.cloudflare.com/ajax/libs/chosen/1.6.2/chosen.min.css');

include_once drupal_get_path('module', 'bootstrap_megamenu') . '/bootstrap_megamenu.functions.inc';

function bootstrap_megamenu_admin_settings($form) {
  $menus = bootstrap_megamenu_get_megamenus();
  foreach ($menus as $menu) {
    $form[$menu->menu_name]['#bootstrap_megamenu'] = $menu;
    $form[$menu->menu_name]['menu_name'] = array('#markup' => $menu->menu_name);
    $form[$menu->menu_name]['title'] = array('#markup' => $menu->title);
    $form[$menu->menu_name]['config_megamenu'] = array('#type' => 'link', '#title' => t('Config'), '#href' => "admin/structure/bootstrap-megamenu/$menu->menu_name");
    $form[$menu->menu_name]['config_links'] = array('#type' => 'link', '#title' => t('Edit links'), '#href' => "admin/structure/menu/manage/$menu->menu_name");
  }
  return $form;
}

function theme_bootstrap_megamenu_admin_settings($variables) {
  $form = $variables['form'];
  $rows = array();
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['#bootstrap_megamenu'])) {
      $menu = &$form[$key];
      $menu['enabled']['#parents'] = array($key, 'enabled');
      $menu['enabled']['#name'] = $key . "[enabled]";
      $row = array();
      $row[] = drupal_render($menu['menu_name']);
      $row[] = drupal_render($menu['title']);
      $row[] = drupal_render($menu['config_megamenu']);
      $row[] = drupal_render($menu['config_links']);
      $rows[] = $row;
    }
  }
  $header = array(t('Menu Name'), t('Menu Title'));
  $header[] = array('data' => t('Operations'), 'colcol-md-' => 2);
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No MegaMenu block available. <a href="@link">Add MegaMenu Block</a>.', array('@link' => url('admin/config/user-interface/bootstrap_megamenu/add'))), 'attributes' => array('id' => 'bootstrap_megamenu'))) . drupal_render_children($form);
}

function bootstrap_megamenu_configure_form($form, &$form_state, $menu_names = array()) {
  $lib_fontawesome = bootstrap_megamenu_check_library('fontawesome', 'fontawesome');
  if(module_exists('fontawesome') && $lib_fontawesome) {
    bootstrap_megamenu_add_css($lib_fontawesome['css']);
  }
  else {
    drupal_add_css(FONT_AWESOME_47, array(
      'type' => 'external'
    ));
  }

  $lib_chosen = bootstrap_megamenu_check_library('chosen', 'chosen');
  $lib_chosen_existed = module_exists('chosen') && $lib_chosen;
  if($lib_chosen_existed && !empty($lib_chosen['css'])) {
    bootstrap_megamenu_add_css($lib_chosen['css']);
  }
  else {
    // bootstrap_megamenu_add_css(drupal_get_path('module', 'bootstrap_megamenu') . '/css/chosen/chosen.min.css');
    // drupal_add_js(drupal_get_path('module', 'bootstrap_megamenu') . '/js/chosen/chosen.jquery.min.js');
    drupal_add_js(JS_CHOSEN_162, array(
      'type' => 'external'
    ));
    drupal_add_css(CSS_CHOSEN_162, array(
      'type' => 'external'
    ));
  }
  bootstrap_megamenu_add_css(drupal_get_path('module', 'bootstrap_megamenu') . '/css/bootstrap.css');
  bootstrap_megamenu_add_css(drupal_get_path('module', 'bootstrap_megamenu') . '/css/base.css');
  bootstrap_megamenu_add_css(drupal_get_path('module', 'bootstrap_megamenu') . '/css/admin.css');
  bootstrap_megamenu_add_css(drupal_get_path('module', 'bootstrap_megamenu') . '/css/backend.css');
  if($lib_chosen_existed && !empty($lib_chosen['js'])) {
    drupal_add_js($lib_chosen['js']);
  }

  drupal_add_js('
    (function ($) {
      Drupal.TBMegaMenu = Drupal.TBMegaMenu || {};
      Drupal.TBMegaMenu.ajax_link = "' . (variable_get('clean_url', 0) ? '' : '?q=') . '";
    })(jQuery);
  ', 'inline');

  drupal_add_js(drupal_get_path('module', 'bootstrap_megamenu') . '/js/bootstrap-megamenu-backend.js');
  drupal_add_js(drupal_get_path('module', 'bootstrap_megamenu') . '/js/bootstrap-megamenu-object.js');
  if(!empty($menu_names)) {
    $form['bootstrap_megamenu'] = array(
      '#markup' => theme('bootstrap_megamenu_backend', array(
        'menu_name' => $menu_names[0],
      )),
    );
  }
  return $form;
}
