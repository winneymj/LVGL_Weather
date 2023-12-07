SET(SOURCES components/ui_comp_standardbutton.c
    components/ui_comp.c
    screens/ui_loadingScreen.c
    screens/ui_newOrExistingConnections.c
    screens/ui_chooseConnection.c
    screens/ui_passphrase.c
    screens/ui_setTimeScreen.c
    screens/ui_TimeScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c)

add_library(ui ${SOURCES})
