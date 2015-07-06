<?php
 /**
  * @file
  * Administration page for Baidu Share Button
  * -------------------------------------------------------
  *   form setting values : 
  *       prefix: "baidu_share_";  subfix: "settings";
  *       global, common, share, slide, image, selectShare
  * -------------------------------------------------------
  *   add a script for button list someday, 
  *       the list of available buttons;
  *       selected options with weight valut to sort;
  * -------------------------------------------------------
  */
 
  
function baidu_share_page_global_settings() {

   // 模块选项
  $available_compo = array(
    'share'=>'Share buttons', 
    'slide'=>'Slide buttons', 
    'image'=>'Image Share', 
    'selectShare'=>'Select Text Share',
  );

  // 回流统计选项 bdSign
  $available_signs = array(
    'on' => t('default'),
    'off' => t('off'),
    'normal' => t('normal'),
  );

  // 下拉浮层中分享按钮的列数 bdMini
  $available_minis = array(
    "1" => "1",
    "2" => "2",
    "3" => "3",
  );

  // 默认标签列
  $default_buttons = _get_default_baidu_share_buttons();

  // default values
  $default_global = array(
    'enabledComponents' => array(),
    'default_buttons' => $default_buttons,
  );

  $default_common = array(
    'bdSign' => 'on',
    'bdMini' => 2,
    'bdMiniList' => '',
  );


  $global_settings = variable_get('baidu_share_global_settings',$default_global);
  $common_settings = variable_get('baidu_share_common_settings', $default_common);

  // section for global settings
  $form['baidu_share_global_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Settings'),
    '#tree' => TRUE,
  );
  
  $form['baidu_share_global_settings']['enabledComponents'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Enable components',
    '#options' => $available_compo,
    '#default_value' => $global_settings['enabledComponents'],
  );

  $form['baidu_share_global_settings']['default_buttons'] = array(
    '#type' => 'textfield',
    '#title' => 'Default button list',
    '#default_value' => $global_settings['default_buttons'],
  );

  // section for common settings
  $form['baidu_share_common_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Common Settings'),
    '#tree' => TRUE,
  );
  
  $form['baidu_share_common_settings']['bdSign'] = array(
    '#type' => 'select',
    '#title' => t('Flow back statistics'),
    '#options' => $available_signs,
    '#default_value' => $common_settings['bdSign'],
  );
  
  $form['baidu_share_common_settings']['bdMini'] =  array(
    '#type' => 'select',
    '#title' => t('Flyout list columns'),
    '#options' => $available_minis,
    '#default_value' => $common_settings['bdMini'],
  );
  
  $form['baidu_share_common_settings']['bdMiniList'] =  array(
    '#type' => 'textarea',
    '#title' => t('Custom flyout list'),
    '#description' => t('sample:  @default_list , visit for <a href="http://share.baidu.com/code/advance/#toid">分享媒体id对应表</a> more info', array('@default_list'=>$default_buttons)),
    '#default_value' => $common_settings['bdMiniList'],
  );


  return system_settings_form($form);

}

function baidu_share_page_share_settings() {
  // available optoins
  // 图标样式选项 bdStyle
  $available_styles = array(
    '0' => t('normal'),
    '1' => t('simple style'),
    '2' => t('grayscale'),
  );
  
  // 图标大小选项 bdSize/viewSize
  $available_sizes = array(
    '16' => t('16*16'),
    '24' => t('24*24'),
    '32' => t('32*32'),
  );

   $default_share = array(
    'node_types' => array(),
    'list' => '',
    'bdStyle' => 0,
    'bdSize' => 16,
    'more' => 'on',
    'count' => 'on',
  );

  // 默认标签列
  $default_buttons = _get_default_baidu_share_buttons();

  $share_settings = variable_get('baidu_share_share_settings', $default_share);

  // section for share settings
  $form['baidu_share_share_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Share Button Settings'),
    '#tree' => TRUE,
  );

  $form['baidu_share_share_settings']['node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display button on these content types:'),
    '#options' => node_type_get_names(),
    '#default_value' => $share_settings['node_types'],
  );

  $form['baidu_share_share_settings']['list'] = array(
    '#type' => 'textfield',
    '#title' => t('Button list'),
    '#description' => t('sample:  @default_list , visit for <a href="http://share.baidu.com/code/advance/#toid">分享媒体id对应表</a> more info. Global default button list will be loaded if leave this blank', array('@default_list'=>$default_buttons)),
    '#default_value' => $share_settings['list'],
  );

  $form['baidu_share_share_settings']['bdStyle'] =  array(
    '#type' => 'select',
    '#title' => t('Style'),
    '#options' => $available_styles,
    '#default_value' => $share_settings['bdStyle'],
  );

  $form['baidu_share_share_settings']['bdSize'] = array(
    '#type' => 'select',
    '#title' => t('Size'),
    '#options' => $available_sizes,
    '#default_value' => $share_settings['bdSize'],
  );

  $form['baidu_share_share_settings']['more'] = array(
    '#type' => 'radios',
    '#title' => t('More-buttons toggle'),
    '#options' => array('on'=>t('on'),'off'=>t('off')),
    '#default_value' => $share_settings['more'],
  );

  $form['baidu_share_share_settings']['count'] = array(
    '#type' => 'radios',
    '#title' => t('Count toggle'),
    '#options' => array('on'=>t('on'), 'off'=>t('off')),
    '#default_value' => $share_settings['count'],
  );

  return system_settings_form($form);
}

function baidu_share_page_slide_settings() {
  //available options
  // 浮窗位置选项 bdPos
  $available_position = array(
    'left' => t('left'),
    'right' => t('right'),
  );

  // 浮窗标签颜色选项 bdImg 
  $available_color = array(
    '0' => t('orange'),
    '1' => t('green'),
    '2' => t('ligth blue'),
    '3' => t('gray'),
    '4' => t('pink'),
    '5' => t('black'),
    '6' => t('blue'),
    '7' => t('magenta'),
    '8' => t('blue gray'),
  );

  $default_slide = array(
    'node_types' => array(),
    'bdImg' => '0',
    'bdPos' => 'right',
    'bdTop' => '100',
  );

  // 默认标签列
  $default_buttons = "['qzone','tsina','huaban','tqq','renren']";

  $slide_settings = variable_get('baidu_share_slide_settings', $default_slide);

  // section for slide settings
  $form['baidu_share_slide_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slide Button Settings'),
    '#tree' => TRUE,
  );

  $form['baidu_share_slide_settings']['node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display button on these content types:'),
    '#options' => node_type_get_names(),
    '#default_value' => $slide_settings['node_types'],
  );

  $form['baidu_share_slide_settings']['bdImg'] = array(
    '#type' => 'select',
    '#title' => t('Tag color'),
    '#options' => $available_color,
    '#default_value' => $slide_settings['bdImg'],
  );

  $form['baidu_share_slide_settings']['bdPos'] = array(
    '#type' => 'select',
    '#title' => t('Position'),
    '#options' => $available_position,
    '#default_value' => $slide_settings['bdPos'],
  );

  $form['baidu_share_slide_settings']['bdTop'] = array(
    '#type' => 'textfield',
    '#title' => t('Pixel value to window top'),
    '#default_value' => $slide_settings['bdTop'],
  );

  return system_settings_form($form);
}

function baidu_share_page_image_settings() {
  // availabel options
  // 图标大小选项 bdSize/viewSize
  $available_sizes = array(
    '16' => t('16*16'),
    '24' => t('24*24'),
    '32' => t('32*32'),
  );

  // 图片分享类型
   $available_viewType = array(
    'list' => t('list'),
    'collection' => t('collection'),
  );

  // 图片分享位置
  $available_viewPos = array(
    'top' => t('top'),
    'bottom' => t('bottom'),
  );

  // 图片分享背景色
  $available_viewColor = array(
    'black' => t('black'),
    'white' => t('white'),
  );

  // 默认标签列
  $default_buttons = "['qzone','tsina','huaban','tqq','renren']";


  $default_image = array(
    'node_types' => array(),
    'viewType' => 'list',
    'viewPos' => 'top',
    'viewColor' => 'black',
    'viewSize' => '16',
    'viewList' => "",
  );

  $image_settings = variable_get('baidu_share_image_settings', $default_image);

  // section for image settings 
  $form['baidu_share_image_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image Share Settings'),
    '#tree' => TRUE,
  );

  $form['baidu_share_image_settings']['node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display button on these content types:'),
    '#options' => node_type_get_names(),
    '#default_value' => $image_settings['node_types'],
  );

  $form['baidu_share_image_settings']['viewType'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => $available_viewType,
    '#default_value' => $image_settings['viewType'],
  );

  $form['baidu_share_image_settings']['viewPos'] = array(
    '#type' => 'select',
    '#title' => t('Position'),
    '#options' => $available_viewPos,
    '#default_value' => $image_settings['viewPos'],
  );

  $form['baidu_share_image_settings']['viewColor'] = array(
    '#type' => 'select',
    '#title' => t('Color'),
    '#options' => $available_viewColor,
    '#default_value' => $image_settings['viewColor'],
  );

  $form['baidu_share_image_settings']['viewSize'] = array(
    '#type' => 'select',
    '#title' => t('Size'),
    '#options' => $available_sizes,
    '#default_value' => $image_settings['viewSize'],
  );

  $form['baidu_share_image_settings']['viewList'] = array(
    '#type' => 'textfield',
    '#title' => t('Button list'),
    '#description' => t('sample:  @default_list , visit for <a href="http://share.baidu.com/code/advance/#toid">分享媒体id对应表</a> more info. Global default button list will be loaded if leave this blank', array('@default_list'=>$default_buttons)),
    '#default_value' => $image_settings['viewList'],
  );

  return system_settings_form($form);
}

function baidu_share_page_select_settings() {
 
 
  $default_select = array(
    'node_types' => array(),
    'bdSelectMiniList' => "",
    'bdContainerClass' => '',
  );

  // 默认标签列
  $default_buttons = "['qzone','tsina','huaban','tqq','renren']";
  
  $select_settings = variable_get('baidu_share_selectShare_settings', $default_select);
  
  // section for selectShare settings
  $form['baidu_share_selectShare_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select Text Share'),
    '#tree' => TRUE,
  );

  $form['baidu_share_selectShare_settings']['node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display button on these content types:'),
    '#options' => node_type_get_names(),
    '#default_value' => $select_settings['node_types'],
  );

  $form['baidu_share_selectShare_settings']['bdSelectMiniList'] = array(
    '#type' => 'textfield',
    '#title' => t('Button list'),
    '#default_value' => $select_settings['bdSelectMiniList'],
    '#description' => t('sample:  @default_list , visit for <a href="http://share.baidu.com/code/advance/#toid">分享媒体id对应表</a> more info. Global default button list will be loaded if leave this blank', array('@default_list'=>$default_buttons)),
  );

  $form['baidu_share_selectShare_settings']['bdContainerClass'] = array(
    '#type' => 'textfield',
    '#title' => t('Container class '),
    '#default_value' => $select_settings['bdContainerClass'],
  );
  
  return system_settings_form($form);
}