#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <WiFi.h>               // In-built
#include <HTTPClient.h>         // In-built
#include <ArduinoJson.h>        // https://github.com/bblanchon/ArduinoJson (v6.17.3)

#include "src/network.h"
#include "credentials.h"
#include "prefs.h"
#include "weather.h"
#include "utilities.h"
#include "src/ui/ui.h"
#include "listboxView.h"

//################ PROGRAM VARIABLES and OBJECTS ##########################################

#define I2C_SDA 16
#define I2C_SCL 17

TwoWire tcWire = TwoWire(0);
Adafruit_FT6206 ctp = Adafruit_FT6206();
long StartTime = 0;
Network network;

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 as the examples and demos are now part of the main LVGL library. */

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
    // Wait for a touch
    if (!ctp.touched())
    {
        data->state = LV_INDEV_STATE_REL;
        return;
    }
    // Retrieve a point  
    TS_Point p = ctp.getPoint();

    data->state = LV_INDEV_STATE_PR;

    // Serial.print("X = "); Serial.print(p.x);
    // Serial.print("\tY = "); Serial.print(p.y);
    // Serial.print(" ---- >");

    // flip it around to match the screen.
    data->point.x = map(p.y, 0, 480, 480, 0);
    data->point.y = p.x;

    // Print out raw data from screen touch controller
    // Serial.print("X = "); Serial.print(data->point.x);
    // Serial.print("\tY = "); Serial.print(data->point.y);
    // Serial.print("\n");

}

void initialiseDisplay()
{
  lv_init();

  tft.begin();          /* TFT init */
  tft.setRotation( 3 ); /* Landscape orientation, flipped */

  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );

  // /* Create simple label */
  // lv_obj_t *label = lv_label_create( lv_scr_act() );
  // lv_label_set_text( label, "Hello Ardino and LVGL!");
  // lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
}

void initialiseTouch()
{
  tcWire.begin(I2C_SDA, I2C_SCL, 100000);

  if (! ctp.begin(40, &tcWire)) {  // pass in 'sensitivity' coefficient and I2C bus
//      Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1) delay(10);
  }
}

void InitialiseSystem()
{
  StartTime = millis();

  Serial.begin(115200);
  while (!Serial);
  Serial.println(String(__FILE__) + "\nStarting...");

  // initializeNetworkPreferences(); // Initialize storage so we can get the ssid and pwd.
  // initializeWeatherPreferences(); // Initialize storage so we can get the lat/long.
  initialiseDisplay();
  initialiseTouch();

  auto status = network.initialize();
  Serial.print("\nNetwork status=" + static_cast<int>(status));
  Serial.println(static_cast<int>(status));
}

void setup() {
  // put your setup code here, to run once:
  InitialiseSystem();
  ui_init();

  //  Create List control and add to panel
  // lv_obj_t *list_ctrl = lv_list_create(ui_ssidList);
  // // lv_obj_set_(list_ctrl, 160, 200);
  // lv_obj_align(list_ctrl, LV_ALIGN_CENTER, 0, 0);
  // lv_obj_set_size(list_ctrl, lv_pct(100), lv_pct(100));

  // /*Add buttons to the list*/
  // lv_obj_t * list_btn;

  // auto status = network.initialize();
  // Serial.print("\nNetwork status=");
  // Serial.println(static_cast<int>(status));
  // if (status == NetworkStatus::SSID_PWD_REQUIRED)
  // {
  //   auto ssidList = network.getSSIDList();
  //   for (auto const& ssid: ssidList)
  //   {
  //     list_btn = lv_list_add_btn(list_ctrl, LV_SYMBOL_FILE, ssid.c_str());
  //     lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_CLICKED, NULL);
  //     lv_obj_add_event_cb(list_btn, event_handler, LV_EVENT_PRESSED, NULL);
  //   }
  // }


//   if (StartWiFi() == WL_CONNECTED)
//   {
// //     byte Attempts = 1;
// //     bool RxWeather  = false;
// //     bool RxForecast = false;
//     WiFiClientSecure client;
//     obtainNOAAGridData(client);
     

// //     while ((RxWeather == false || RxForecast == false) && Attempts <= 2)  // Try up-to 2 time for Weather and Forecast data
// //     {
// //       if (RxWeather  == false)  
// //         RxWeather  = obtainWeatherData(client, "onecall");
// //       if (RxForecast == false)
// //         RxForecast = obtainWeatherData(client, "forecast");
// //       Attempts++;
// //     }

// //     Serial.println("Received all weather data...");
// //     if (RxWeather && RxForecast)
// //     { // Only if received both Weather or Forecast proceed
// //       StopWiFi();         // Reduces power consumption
// // //        epd_poweron();      // Switch on EPD display
// // //        epd_clear();        // Clear the screen
// // //        DisplayWeather();   // Display the weather data
// // //        edp_update();       // Update the display to show the information
// // //        epd_poweroff_all(); // Switch off all power to EPD
// //     }
//   }
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay( 5 );
}
