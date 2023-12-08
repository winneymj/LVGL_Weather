// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "../network.h"
#include "../ntpTime.h"

extern Network network;
extern NtpTime ntpTime;

static lv_timer_t *timer;
static lv_obj_t *list_ctrl = NULL;

static lv_style_t popupBox_style;
static lv_obj_t *popupBox;
static lv_obj_t *popupBoxCloseBtn;

static void setStyle() {
  // lv_style_init(&border_style);
  // lv_style_set_border_width(&border_style, 2);
  // lv_style_set_border_color(&border_style, lv_color_black());

  lv_style_init(&popupBox_style);
  lv_style_set_radius(&popupBox_style, 10);
  lv_style_set_bg_opa(&popupBox_style, LV_OPA_COVER);
  lv_style_set_border_color(&popupBox_style, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_border_width(&popupBox_style, 5);
}

void passphrase_event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);

  if (code == LV_EVENT_VALUE_CHANGED)
  {
    Serial.println("LV_EVENT_VALUE_CHANGED every char in passphrase");
    // See if we have some text and only enable the OK button if we have something
    auto const& passhraseText = lv_textarea_get_text(obj);
    auto stdString = std::string(passhraseText);
    stdString.erase(stdString.find_last_not_of(' ')+1); //Trim suffix
    stdString.erase(0, stdString.find_first_not_of(' ')); //prefixing spaces

    auto len = stdString.length();
    Serial.print("passphrase len=");
    Serial.println(len);

    // Enable the OK button by clearing the state
    if (len >= 0)
    {
      lv_obj_clear_state( ui_passphraseOKBtn, LV_STATE_DISABLED );
      network.setPassword(stdString);
    }
  }
}

void list_event_handler(lv_event_t *e)
{
  Serial.println("list_event_handler: ENTER");
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);

  if (code == LV_EVENT_CLICKED)
  {
    Serial.println("list_event_handler: LV_EVENT_CLICKED");
    auto selectedItem = std::string(lv_list_get_btn_text(list_ctrl, obj));
    Serial.print("list_event_handler: selectedItem=");
    Serial.println(selectedItem.c_str());
    auto pos = selectedItem.find_first_of(" (");

    Serial.print("list_event_handler: pos=");
    Serial.println(pos);

    Serial.print("Clicked='");
    Serial.print(selectedItem.substr(0, pos).c_str());
    Serial.println("'");

    // Set button selected
    lv_obj_add_state(obj, LV_STATE_PRESSED);

    //Enable the OK button by clearing the state
    lv_obj_clear_state( ui_chooseConnectionOKBtn, LV_STATE_DISABLED );
    network.setSSID(selectedItem.substr(0, pos));
  }
  else if (code == LV_EVENT_PRESSED)
  {
    Serial.println("list_event_handler: LV_EVENT_PRESSED");
    for(int i = 0; i < lv_obj_get_child_cnt(list_ctrl); i++)
    {
      lv_obj_t * child = lv_obj_get_child(list_ctrl, i);
      if(child == obj)
        lv_obj_add_state(child, LV_STATE_PRESSED);
      else
        lv_obj_clear_state(child, LV_STATE_PRESSED);
    }
  }
}

static void btn_event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *btn = lv_event_get_target(e);

  if (code == LV_EVENT_CLICKED) {
    // if (btn == settingBtn) {
    //   lv_obj_clear_flag(settings, LV_OBJ_FLAG_HIDDEN);
    // } else if (btn == settingCloseBtn) {
    //   lv_obj_add_flag(settings, LV_OBJ_FLAG_HIDDEN);
    // } else if (btn == mboxConnectBtn) {
    //   ssidPW = String(lv_textarea_get_text(mboxPassword));

    //   beginWIFITask();
    //   //networkConnector();
    //   lv_obj_move_background(mboxConnect);
    //   popupMsgBox("Connecting!", "Attempting to connect to the selected network.");
    // } else if (btn == mboxCloseBtn) {
    //   lv_obj_move_background(mboxConnect);
    // } else if (btn == popupBoxCloseBtn) {
    //   lv_obj_move_background(popupBox);
    // }

  } else if (code == LV_EVENT_VALUE_CHANGED) {
    // if (btn == settingWiFiSwitch) {

    //   if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {

    //     if (ntScanTaskHandler == NULL) {
    //       networkStatus = NETWORK_SEARCHING;
    //       networkScanner();
    //       timer = lv_timer_create(timerForNetwork, 1000, wfList);
    //       lv_list_add_text(wfList, "WiFi: Looking for Networks...");
    //     }

    //   } else {

    //     if (ntScanTaskHandler != NULL) {
    //       networkStatus = NONE;
    //       vTaskDelete(ntScanTaskHandler);
    //       ntScanTaskHandler = NULL;
    //       lv_timer_del(timer);
    //       lv_obj_clean(wfList);
    //     }

    //     if (WiFi.status() == WL_CONNECTED) {
    //       WiFi.disconnect(true);
    //       lv_label_set_text(timeLabel, "WiFi Not Connected!    " LV_SYMBOL_CLOSE);
    //     }
    //   }
    // }
  }
}

void popupMsgBox(String title, String msg)
{
  if (popupBox != NULL)
  {
    lv_obj_del(popupBox);
  }

  popupBox = lv_obj_create(lv_scr_act());
  lv_obj_add_style(popupBox, &popupBox_style, 0);
  lv_obj_set_size(popupBox, 480 * 2 / 3, 320 / 2);
  lv_obj_center(popupBox);

  lv_obj_t *popupTitle = lv_label_create(popupBox);
  lv_label_set_text(popupTitle, title.c_str());
  lv_obj_set_width(popupTitle, 480 * 2 / 3 - 50);
  lv_obj_align(popupTitle, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_t *popupMSG = lv_label_create(popupBox);
  lv_obj_set_width(popupMSG, 480 * 2 / 3 - 50);
  lv_label_set_text(popupMSG, msg.c_str());
  lv_obj_align(popupMSG, LV_ALIGN_TOP_LEFT, 0, 40);

  popupBoxCloseBtn = lv_btn_create(popupBox);
  lv_obj_add_event_cb(popupBoxCloseBtn, btn_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_align(popupBoxCloseBtn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_t *btnLabel = lv_label_create(popupBoxCloseBtn);
  lv_label_set_text(btnLabel, "Okay");
  lv_obj_center(btnLabel);
}

void showingFoundWiFiList()
{
  Serial.println("showingFoundWiFiList(): ENTER");
  Serial.print("network.foundWifiList=");
  Serial.println(network.foundWifiList.size());

  if (network.foundWifiList.size() == 0)
    return;

  if (list_ctrl != NULL)
    lv_obj_clean(list_ctrl);

  int loop = 0;
  for (std::vector<String>::iterator item = network.foundWifiList.begin(); item != network.foundWifiList.end(); ++item)
  {
    Serial.println((*item).c_str());
    auto list_btn = lv_list_add_btn(list_ctrl, LV_SYMBOL_FILE, (*item).c_str());
    lv_obj_add_event_cb(list_btn, list_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(list_btn, list_event_handler, LV_EVENT_PRESSED, NULL);
    delay(1);

    loop++;
  }

  // foundNetworks = network.foundWifiList.size();
  Serial.println("showingFoundWiFiList(): EXIT");
}

void timerForNetwork(lv_timer_t *timer)
{
  LV_UNUSED(timer);

  switch (network.networkStatus)
  {
    case NETWORK_SEARCHING:
      Serial.println("Network::timerForNetwork:NETWORK_SEARCHING");
      break;

    case NETWORK_SEARCHING_DONE:
      Serial.println("Network::timerForNetwork:NETWORK_SEARCHING_DONE");
      showingFoundWiFiList();
      network.stopNetworkScanner();
      lv_timer_del(timer);
      break;

    case NETWORK_CONNECTING:
      Serial.println("Network::timerForNetwork:NETWORK_CONNECTING");
      break;

    case NETWORK_CONNECTED:
      Serial.println("Network::timerForNetwork:NETWORK_CONNECTED");
      network.stopWifiConnection();
      lv_timer_del(timer);
      // popupMsgBox("WiFi Connected!", "Now you'll get the current time soon.");
      break;

    case NETWORK_CONNECTION_FAILED:
      Serial.println("Network::timerForNetwork:NETWORK_CONNECTION_FAILED");
      network.stopWifiConnection();
      lv_timer_del(timer);
      // network.stopWifiConnection();
      // lv_timer_del(timer);
      // popupMsgBox("WiFi Connected!", "Now you'll get the current time soon.");
      break;

    // case NETWORK_CONNECTED_POPUP:
    //   popupMsgBox("WiFi Connected!", "Now you'll get the current time soon.");
    //   networkStatus = NETWORK_CONNECTED;
    //   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    //   break;

    // case NETWORK_CONNECTED:

    //   showingFoundWiFiList();
    //   updateLocalTime();
    //   break;

    // case NETWORK_CONNECT_FAILED:
    //   networkStatus = NETWORK_SEARCHING;
    //   popupMsgBox("Oops!", "Please check your wifi password and try again.");
    //   break;

    default:
      break;
  }
}

void passphraseOkCallback(lv_event_t * e)
{
  network.startWifiConnection();
  timer = lv_timer_create(timerForNetwork, 1000, list_ctrl);
}

void InitializeChooseConnectionPage(lv_event_t * e)
{
  list_ctrl = lv_list_create(ui_ssidPanel);
  lv_obj_align(list_ctrl, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_size(list_ctrl, lv_pct(100), lv_pct(100));
  lv_list_add_text(list_ctrl, "WiFi: Looking for Networks...");

  network.startNetworkScanner();
  timer = lv_timer_create(timerForNetwork, 1000, list_ctrl);
}

void InitializePassphrasePage(lv_event_t * e)
{
  // add event to the passphrase input field
  lv_obj_add_event_cb(ui_passphraseText, passphrase_event_handler, LV_EVENT_VALUE_CHANGED, ui_Keyboard1);
}

void saveTimeDateSettings(lv_event_t * e)
{
  Serial.println("saveTimeDateSettings:ENTER");

  // Save the set time from internet checkbox and the timezone
  const bool internetCheckedState = lv_obj_get_state(ui_internetTime) & LV_STATE_CHECKED ? true : false;
  const bool twentyFourHourMode = lv_obj_get_state(ui_twentyFourHrMode) & LV_STATE_CHECKED ? true : false;
  const int timezonePos = lv_dropdown_get_selected(ui_Dropdown1);
  ntpTime.setInternetTimeEnabled(internetCheckedState);
  ntpTime.setTimeZonePos(timezonePos);
  ntpTime.set24HourMode(twentyFourHourMode);
  ntpTime.getTime();
}

void initializeTimeScreen(lv_event_t * e)
{
  auto timezonePos = ntpTime.getTimeZonePos();
  lv_dropdown_set_selected(ui_Dropdown1, timezonePos);
  auto twentyFourMode = ntpTime.get24HourMode();
  if (twentyFourMode)
    lv_obj_add_state(ui_twentyFourHrMode, LV_STATE_CHECKED);
  else
    lv_obj_clear_state(ui_twentyFourHrMode, LV_STATE_CHECKED);
}

void TimeScreenOnLoad(lv_event_t * e)
{
  auto twentyFourMode = ntpTime.get24HourMode();
  auto hour = ntpTime.getHour(twentyFourMode);
  auto minutes = ntpTime.getMinutes();
  // Add a custom font for the time to the display
  lv_obj_set_style_text_font(ui_TimeScreenTimeLabel, &arial_160, 0);
  lv_label_set_text_fmt(ui_TimeScreenTimeLabel, "%d:%d", hour, minutes);
}
