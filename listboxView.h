#ifndef LISTBOX_H_
#define LISTBOX_H_

#include <Array.h>
#include <lvgl.h>

#define ELEMENT_COUNT_MAX 20
typedef Array<int,ELEMENT_COUNT_MAX> Elements;

class ListBoxView {
public:
  ListBoxView(lv_obj_t *listbox, Elements const& ssidArray);

private:
  lv_obj_t *create_row();

};

#endif /* ifndef LISTBOX_H_ */