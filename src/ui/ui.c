// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_loadingScreen
void ui_loadingScreen_screen_init(void);
lv_obj_t *ui_loadingScreen;
lv_obj_t *ui_Label1;
void ui_event_Panel3( lv_event_t * e);
lv_obj_t *ui_Panel3;
lv_obj_t *ui_Label8;


// SCREEN: ui_newOrExistingConnections
void ui_newOrExistingConnections_screen_init(void);
lv_obj_t *ui_newOrExistingConnections;
lv_obj_t *ui_Label3;
lv_obj_t *ui_Label4;
lv_obj_t *ui_Panel1;
lv_obj_t *ui_newConnectionCB;
lv_obj_t *ui_existConnectionCB;
lv_obj_t *ui_NewExistingCancelBtn;
lv_obj_t *ui_ExistingCancelL;
void ui_event_NewExistingOkBtn( lv_event_t * e);
lv_obj_t *ui_NewExistingOkBtn;
lv_obj_t *ui_ExistingOkL;


// SCREEN: ui_chooseConnection
void ui_chooseConnection_screen_init(void);
lv_obj_t *ui_chooseConnection;
lv_obj_t *ui_ssidPanel;
lv_obj_t *ui_Label2;
lv_obj_t *ui_Label5;
lv_obj_t *ui_Label6;
void ui_event_chooseConnectionOKBtn_StandardButton( lv_event_t * e);
lv_obj_t *ui_chooseConnectionOKBtn;
void ui_event_StandardButton3_StandardButton( lv_event_t * e);
lv_obj_t *ui_StandardButton3;
lv_obj_t *ui_StandardButton4;


// SCREEN: ui_passphrase
void ui_passphrase_screen_init(void);
lv_obj_t *ui_passphrase;
lv_obj_t *ui_Label10;
lv_obj_t *ui_passphraseText;
lv_obj_t *ui_Panel2;
lv_obj_t *ui_Keyboard1;
void ui_event_passphraseOKBtn_StandardButton( lv_event_t * e);
lv_obj_t *ui_passphraseOKBtn;
void ui_event_StandardButton1_StandardButton( lv_event_t * e);
lv_obj_t *ui_StandardButton1;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Panel3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_newOrExistingConnections, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_newOrExistingConnections_screen_init);
}
}
void ui_event_NewExistingOkBtn( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_chooseConnection, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_chooseConnection_screen_init);
      InitializeChooseConnectionPage( e );
}
}
void ui_event_chooseConnectionOKBtn_StandardButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_passphrase, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_passphrase_screen_init);
      InitializePassphrasePage( e );
}
}
void ui_event_StandardButton3_StandardButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_newOrExistingConnections, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_newOrExistingConnections_screen_init);
}
}
void ui_event_passphraseOKBtn_StandardButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      passphraseOkCallback( e );
}
}
void ui_event_StandardButton1_StandardButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_chooseConnection, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_chooseConnection_screen_init);
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_loadingScreen_screen_init();
ui_newOrExistingConnections_screen_init();
ui_chooseConnection_screen_init();
ui_passphrase_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_loadingScreen);
}