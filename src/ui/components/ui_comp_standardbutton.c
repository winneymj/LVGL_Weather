// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"


// COMPONENT StandardButton

lv_obj_t *ui_StandardButton_create(lv_obj_t *comp_parent) {

lv_obj_t *cui_StandardButton;
cui_StandardButton = lv_btn_create(comp_parent);
lv_obj_set_width( cui_StandardButton, 100);
lv_obj_set_height( cui_StandardButton, 50);
lv_obj_set_x( cui_StandardButton, 58 );
lv_obj_set_y( cui_StandardButton, 123 );
lv_obj_set_align( cui_StandardButton, LV_ALIGN_CENTER );
lv_obj_add_flag( cui_StandardButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( cui_StandardButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(cui_StandardButton, 30, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(cui_StandardButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(cui_StandardButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(cui_StandardButton, lv_color_hex(0x3F66E7), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(cui_StandardButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(cui_StandardButton, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_color(cui_StandardButton, lv_color_hex(0x3F66E7), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(cui_StandardButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_t *cui_Label12;
cui_Label12 = lv_label_create(cui_StandardButton);
lv_obj_set_width( cui_Label12, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( cui_Label12, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( cui_Label12, LV_ALIGN_CENTER );
lv_label_set_text(cui_Label12,"OK");

lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_STANDARDBUTTON_NUM);
children[UI_COMP_STANDARDBUTTON_STANDARDBUTTON] = cui_StandardButton;
children[UI_COMP_STANDARDBUTTON_LABEL12] = cui_Label12;
lv_obj_add_event_cb(cui_StandardButton, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
lv_obj_add_event_cb(cui_StandardButton, del_component_child_event_cb, LV_EVENT_DELETE, children);
ui_comp_StandardButton_create_hook(cui_StandardButton);
return cui_StandardButton; 
}
