<div <?php print $attributes;?> class="<?php print $classes;?> navbar">
  <?php if($section == 'frontend') :?>
    <button data-target=".navbar-collapse" data-toggle="collapse" class="btn navbar-btn bootstrap-megamenu-button" type="button">
      <i class="fa fa-reorder"></i>
    </button>
    <div class="navbar-collapse <?php print $block_config['always-show-submenu'] ? ' always-show' : '';?>">
  <?php endif;?>
  <?php print $content;?>
  <?php if($section == 'frontend') :?>
    </div>
  <?php endif;?>
</div>
