// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_chooseConnection_screen_init(void)
{
ui_chooseConnection = lv_obj_create(NULL);
lv_obj_clear_flag( ui_chooseConnection, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_ssidPanel = lv_obj_create(ui_chooseConnection);
lv_obj_set_width( ui_ssidPanel, 432);
lv_obj_set_height( ui_ssidPanel, 180);
lv_obj_set_x( ui_ssidPanel, 0 );
lv_obj_set_y( ui_ssidPanel, -3 );
lv_obj_set_align( ui_ssidPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_ssidPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label2 = lv_label_create(ui_chooseConnection);
lv_obj_set_width( ui_Label2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label2, -200 );
lv_obj_set_y( ui_Label2, -117 );
lv_obj_set_align( ui_Label2, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label2,"MAC:");
lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0x3F66E7), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label5 = lv_label_create(ui_chooseConnection);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label5, -109 );
lv_obj_set_y( ui_Label5, -143 );
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,"Choose a wireless connection");
lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0x3F66E7), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_Label5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label6 = lv_label_create(ui_chooseConnection);
lv_obj_set_width( ui_Label6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label6, -116 );
lv_obj_set_y( ui_Label6, -117 );
lv_obj_set_align( ui_Label6, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label6,"00:00:00:00:00:00");
lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0x3F66E7), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_Label6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_chooseConnectionOKBtn = ui_StandardButton_create(ui_chooseConnection);
lv_obj_set_x( ui_chooseConnectionOKBtn, 169 );
lv_obj_set_y( ui_chooseConnectionOKBtn, 123 );
lv_obj_add_state( ui_chooseConnectionOKBtn, LV_STATE_DISABLED );     /// States

ui_StandardButton3 = ui_StandardButton_create(ui_chooseConnection);
lv_obj_set_x( ui_StandardButton3, 58 );
lv_obj_set_y( ui_StandardButton3, 123 );

lv_label_set_text(ui_comp_get_child(ui_StandardButton3, UI_COMP_STANDARDBUTTON_LABEL12),"BACK");

ui_StandardButton4 = ui_StandardButton_create(ui_chooseConnection);
lv_obj_set_x( ui_StandardButton4, -81 );
lv_obj_set_y( ui_StandardButton4, 123 );

lv_label_set_text(ui_comp_get_child(ui_StandardButton4, UI_COMP_STANDARDBUTTON_LABEL12),"REFRESH");

lv_obj_add_event_cb(ui_chooseConnectionOKBtn, ui_event_chooseConnectionOKBtn_StandardButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_StandardButton3, ui_event_StandardButton3_StandardButton, LV_EVENT_ALL, NULL);

}
