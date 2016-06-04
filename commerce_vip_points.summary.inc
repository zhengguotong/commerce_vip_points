<?php
/**
 * 
 * User: zhengguotong
 * Date: 2/06/16
 * Time: 9:30 PM
 */

function commerce_vip_points_summary_page($form, &$form_state){
    $form = array();
    $default = true;

    $form['header'] = array(
        '#markup' => '<p>会员奖金系统会在每天凌晨2点更新，如果你要最新的会员奖金数据你可以你可以点击<a  href="/admin/userpoints/update-user-cashback">手动更新会员奖金</a> 进行手动更新。</p>',
    );

    //Filter
    $form['filter'] = array(
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => false,
        '#title' => t('选择会员积分统计月份')
    );

    $form['filter']['filter_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('月份'),
         '#date_format' => 'Y-m',
        '#default_value' => date('Y-m'),
    );

    $form['filter']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Filter'),
    );

    // Check if there is sorting request
    if(isset($_GET['sort']) && isset($_GET['order'])){
        // Sort it Ascending or Descending?
        if($_GET['sort'] == 'asc')
            $sort = 'ASC';
        else
            $sort = 'DESC';
        // Which column will be sorted
        switch($_GET['order']){
            case '用户':
                $order = 'name';
                break;
            case '返现奖金':
                $order = 'field_total_cashback_value';
                break;
            case '额外奖金':
                $order = 'field_extral_cashback_value';
                break;
            default:
                $order = 'uid';
        }
    }
    else {
        // Default sort
        $sort = 'ASC';
        $order = ' uid';
    }

    $header = array(
        array('data' => t('用户'),'field' => 'name'),
        array('data' => t('个人积分')),
        array('data' => t('团队积分')),
        array('data' => t('返现奖金'),'field' => 'field_total_cashback_value'),
        array('data' => t('额外奖金'),'field' => 'field_extral_cashback_value'),
        array('data' => t('总奖金')),
    );

    $query = db_select('users_roles', 'ur');
            $query ->join('users','u','u.uid = ur.uid');
            $query->join('role','r', 'r.rid = ur.rid');
            $query->leftJoin('field_data_field_cashback_points' , 'fdfcp','fdfcp.entity_id = u.uid');
            $query->Join('field_collection_item' , 'fci','fdfcp.field_cashback_points_value = fci.item_id');
            $query->Join('field_data_field_total_cashback' , 'fdftc','fdftc.entity_id = fci.item_id');
            $query->Join('field_data_field_extral_cashback' , 'fdfec','fdfec.entity_id = fci.item_id');
            $query->Join('field_data_field_cashback_date' , 'fdfcd','fdfcd.entity_id = fci.item_id');

     $query->fields('u', array('name','uid'))
          ->fields('fdftc', array('field_total_cashback_value'))
          ->fields('fdfec', array('field_extral_cashback_value'))
          ->condition('r.name', '会员','=');

      if(isset($form_state['filters']['date'])){
          $default = false;
          $query->condition('fdfcd.field_cashback_date_value', $form_state['filters']['date'] . '-01 00:00:00','=');
      }else{
          $query->condition('fdfcd.field_cashback_date_value', date('Y-m-01'),'=');
      }

      $result= $query->orderBy($order, $sort)
              ->extend('TableSort')->extend('PagerDefault')->limit(20)
              ->execute();

    $rows = array();

    foreach ($result as $u) {
        if($default){
            $points =_commerce_vip_points_get_user_points($u->uid,date('Y-m'));
        }else{
           $points =  _commerce_vip_points_get_user_points($u->uid,$form_state['filters']['date']);
        }

        // Fill the table rows
        $rows[] = array(
            l($u->name, 'user/'. $u->uid),
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

function commerce_vip_points_summary_page_submit($form, &$form_state) {
    $form_state['filters']['date'] = $form_state['values']['filter_date'];
    $form_state['rebuild'] = TRUE;
}