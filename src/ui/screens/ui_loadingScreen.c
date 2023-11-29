// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_loadingScreen_screen_init(void)
{
ui_loadingScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_loadingScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label1 = lv_label_create(ui_loadingScreen);
lv_obj_set_width( ui_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label1,"Loading...");

ui_Panel3 = lv_obj_create(ui_loadingScreen);
lv_obj_set_width( ui_Panel3, 100);
lv_obj_set_height( ui_Panel3, 50);
lv_obj_set_x( ui_Panel3, 172 );
lv_obj_set_y( ui_Panel3, -123 );
lv_obj_set_align( ui_Panel3, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label8 = lv_label_create(ui_Panel3);
lv_obj_set_width( ui_Label8, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label8, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label8, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label8,"Network ->");

ui_Panel4 = lv_obj_create(ui_loadingScreen);
lv_obj_set_width( ui_Panel4, 100);
lv_obj_set_height( ui_Panel4, 50);
lv_obj_set_x( ui_Panel4, 174 );
lv_obj_set_y( ui_Panel4, -67 );
lv_obj_set_align( ui_Panel4, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label9 = lv_label_create(ui_Panel4);
lv_obj_set_width( ui_Label9, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label9, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label9, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label9,"Time ->");

lv_obj_add_event_cb(ui_Panel3, ui_event_Panel3, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Label9, ui_event_Label9, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Panel4, ui_event_Panel4, LV_EVENT_ALL, NULL);

}
