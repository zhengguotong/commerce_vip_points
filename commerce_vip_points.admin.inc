<?php

/**
 * commerce vip point settings page callback
 *
 * @return array
 */
function commerce_vip_points_setting_page(){
    $form = array();

    $form['commerce_vip_points_setting'] = array(
        '#type' => 'fieldset',
    );

    $form ['commerce_vip_points_setting']['commerce_vip_points_3_percent'] = array(
        '#type' => 'textfield',
        '#title' => t('3%'),
        '#default_value' => empty($percent3 = variable_get('commerce_vip_points_3_percent'))? '200' : $percent3,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );

    $form ['commerce_vip_points_setting']['commerce_vip_points_6_percent'] = array(
        '#type' => 'textfield',
        '#title' => t('6%'),
        '#default_value' => empty($percent6 = variable_get('commerce_vip_points_6_percent'))? '800': $percent6,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );

    $form ['commerce_vip_points_setting']['commerce_vip_points_9_percent'] = array(
        '#type' => 'textfield',
        '#title' => t('9%'),
        '#default_value' => empty($percent9 = variable_get('commerce_vip_points_9_percent'))? '2000': $percent9,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );

    $form ['commerce_vip_points_setting']['commerce_vip_points_12_percent'] = array(
        '#type' => 'textfield',
        '#title' => t('12%'),
        '#default_value' => empty($percent12 = variable_get('commerce_vip_points_12_percent'))? '4000': $percent12,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );


    $form ['commerce_vip_points_setting']['commerce_vip_points_15_percent'] = array(
        '#type' => 'textfield',
        '#title' => t('15%'),
        '#default_value' => empty($percent15 = variable_get('commerce_vip_points_15_percent'))? '6500': $percent15,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );

    $form ['commerce_vip_points_setting']['commerce_vip_points_18_percent'] = array(
        '#type' => 'textfield',
        '#title' => t('18%'),
        '#default_value' => empty($percent18 = variable_get('commerce_vip_points_18_percent'))? '10000': $percent18,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );

    $form ['commerce_vip_points_setting']['commerce_vip_points_21_percent'] = array(
        '#type' => 'textfield',
        '#title' => t('21%'),
        '#default_value' =>empty($percent21 = variable_get('commerce_vip_points_21_percent'))? '15000': $percent21,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );

    $form['commerce_vip_points_extral_cashback_setting'] = array(
        '#type' => 'fieldset',
    );

    $form ['commerce_vip_points_extral_cashback_setting']['commerce_vip_points_extral_cashback'] = array(
        '#type' => 'textfield',
        '#title' => t('额外奖金'),
        '#default_value' =>empty($extral_cashback = variable_get('commerce_vip_points_extral_cashback'))? '500': $extral_cashback,
        '#size' => 20,
        '#maxlength' => 128,
        '#element_validate'  => array('element_validate_integer_positive'),
        '#required' => TRUE,
    );

    $form['itciti_order_split']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('保存'),
        '#submit' => array(
            'commerce_vip_points_setting_form_submit'
        )
    );

    return $form;
}

function commerce_vip_points_setting_form_submit($form, &$form_state){
    variable_set('commerce_vip_points_3_percent', $form_state['values']['commerce_vip_points_3_percent']);
    variable_set('commerce_vip_points_6_percent', $form_state['values']['commerce_vip_points_6_percent']);
    variable_set('commerce_vip_points_9_percent', $form_state['values']['commerce_vip_points_9_percent']);
    variable_set('commerce_vip_points_12_percent', $form_state['values']['commerce_vip_points_12_percent']);
    variable_set('commerce_vip_points_15_percent', $form_state['values']['commerce_vip_points_15_percent']);
    variable_set('commerce_vip_points_18_percent', $form_state['values']['commerce_vip_points_18_percent']);
    variable_set('commerce_vip_points_21_percent', $form_state['values']['commerce_vip_points_21_percent']);
    variable_set('commerce_vip_points_21_percent', $form_state['values']['commerce_vip_points_21_percent']);
    variable_set('commerce_vip_points_extral_cashback', $form_state['values']['commerce_vip_points_extral_cashback']);
    drupal_set_message(t('保存成功'));
}
