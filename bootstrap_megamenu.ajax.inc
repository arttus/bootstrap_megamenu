<?php

function bootstrap_megamenu_request() {
  $action = isset($_POST['action']) ? $_POST['action'] : NULL;
  switch($action) {
    case 'load':
      $block = bootstrap_megamenu_render_block($_POST['menu_name']);
      print($block['content']['#markup']);
      break;
    case 'save':
      global $language;
      $menu_config = isset($_POST['menu_config']) ? $_POST['menu_config'] : NULL;
      $block_config = isset($_POST['block_config']) ? $_POST['block_config'] : NULL;
      $menu_name = isset($_POST['menu_name']) ? $_POST['menu_name'] : NULL;
      if($menu_config && $menu_name) {
        $bootstrap_megamenu = db_select('bootstrap_megamenus', 't')->fields('t')->condition('menu_name', $menu_name)->condition('language', $language->language)->execute()->fetchObject();
        if($bootstrap_megamenu) {
          db_update('bootstrap_megamenus')->fields(array('menu_config' => $menu_config, 'block_config' => $block_config, 'language' => $language->language))->condition('menu_name', $menu_name)->condition('language', $language->language)->execute();
        }
        else {
          db_insert('bootstrap_megamenus')->fields(array('menu_name' => $menu_name, 'block_config' => $block_config, 'menu_config' => $menu_config, 'language' => $language->language))->execute();
        }
      }
      break;
    case 'load_block':
      $block_key = isset($_POST['block_key']) ? $_POST['block_key'] : NULL;
      $id = isset($_POST['id']) ? $_POST['id'] : NULL;
      $showblocktitle = isset($_POST['showblocktitle']) ? $_POST['showblocktitle'] : NULL;
      if($block_key) {
        $content = json_encode(array('content' => theme('bootstrap_megamenu_block', array('block_key' => $block_key, 'section' => 'backend', 'showblocktitle' => $showblocktitle)), 'id' => $id));
        print($content);
      }
      break;
  }
  exit;
}
