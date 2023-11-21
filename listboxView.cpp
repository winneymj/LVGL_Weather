#include "listboxView.h"
#include "src/ui/ui.h"

ListBoxView::ListBoxView(lv_obj_t *listbox, Elements const& ssidArray)
{
  // Loop the array and create buttons and text
  for (auto ssid: ssidArray)
  {
    auto row = create_row();
  }
}

lv_obj_t *ListBoxView::create_row()
{
  // auto ui_row1 = lv_btn_create(ui_SSIDList);
  // lv_obj_set_width( ui_row1, lv_pct(100));
  // lv_obj_set_height( ui_row1, LV_SIZE_CONTENT);   /// 50
  // lv_obj_set_align( ui_row1, LV_ALIGN_CENTER );
  // lv_obj_add_flag( ui_row1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
  // lv_obj_clear_flag( ui_row1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
  // lv_obj_set_style_bg_color(ui_row1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
  // lv_obj_set_style_bg_opa(ui_row1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
  // lv_obj_set_style_text_color(ui_row1, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT );
  // lv_obj_set_style_text_opa(ui_row1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

  // auto ui_Label3 = lv_label_create(ui_row1);
  // lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
  // lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
  // lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );

  // return ui_row1;
}