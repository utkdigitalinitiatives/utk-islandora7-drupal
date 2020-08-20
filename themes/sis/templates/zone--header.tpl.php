<?php
$block = module_invoke('utk_lib_digital_custom', 'block_view', 'utk_lib_digital_custom_header');
if (array_key_exists('content', $block)) :
    print $block['content'];
endif;
?>
