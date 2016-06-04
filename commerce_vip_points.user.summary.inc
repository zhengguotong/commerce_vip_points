<?php
/**
 * 
 * User: zhengguotong
 * Date: 2/06/16
 * Time: 9:30 PM
 */

function commerce_vip_points_user_summary_page($form, &$form_state){
    global $user;
    $form = array();

    // Check if there is sorting request
    if(isset($_GET['sort']) && isset($_GET['order'])){
        // Sort it Ascending or Descending?
        if($_GET['sort'] == 'asc')
            $sort = 'ASC';
        else
            $sort = 'DESC';
        // Which column will be sorted
        switch($_GET['order']){
            case '返现月份':
                $order = 'field_cashback_date_value';
                break;
            case '返现奖金':
                $order = 'field_total_cashback_value';
                break;
            case '额外奖金':
                $order = 'field_extral_cashback_value';
                break;
            default:
                $order = 'field_cashback_date_value';
        }
    }
    else {
        // Default sort
        $sort = 'DESC';
        $order = 'field_cashback_date_value';
    }

    $header = array(
        array('data' => t('返现月份'),'field' => 'field_data_field_cashback_date'),
        array('data' => t('个人积分')),
        array('data' => t('团队积分')),
        array('data' => t('返现奖金'),'field' => 'field_total_cashback_value'),
        array('data' => t('额外奖金'),'field' => 'field_extral_cashback_value'),
        array('data' => t('总奖金')),
    );

    $query = db_select('field_data_field_cashback_points' , 'fdfcp');
            $query->Join('field_collection_item' , 'fci','fdfcp.field_cashback_points_value = fci.item_id');
            $query->Join('field_data_field_total_cashback' , 'fdftc','fdftc.entity_id = fci.item_id');
            $query->Join('field_data_field_extral_cashback' , 'fdfec','fdfec.entity_id = fci.item_id');
            $query->Join('field_data_field_cashback_date' , 'fdfcd','fdfcd.entity_id = fci.item_id');

     $query->fields('fdftc', array('field_total_cashback_value'))
          ->fields('fdfec', array('field_extral_cashback_value'))
          ->fields('fdfcd', array('field_cashback_date_value'))
          ->condition('fdfcp.entity_id', $user->uid,'=');

      $result= $query->orderBy($order, $sort)
              ->extend('TableSort')->extend('PagerDefault')->limit(20)
              ->execute();

    $rows = array();

    foreach ($result as $u) {
        $date = new DateTime($u->field_cashback_date_value);
        $cashback_date = $date->format('Y-m');
        $points =_commerce_vip_points_get_user_points($user->uid, $cashback_date);


        // Fill the table rows
        $rows[] = array(
            $cashback_date,
            !empty($points['personal']) ? $points['personal'] : 0,
            !empty ($points['team']) ? $points['team'] : 0,
            number_format($u->field_total_cashback_value,2),
            number_format($u->field_extral_cashback_value,2),
            number_format( $u->field_total_cashback_value + $u->field_extral_cashback_value,2),
        );
    }

    $form['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#empty' => t('没有相应月份的会员积分统计数据!')
    );

    $form['pager'] = array('#markup' => theme('pager'));

    return $form;
}
