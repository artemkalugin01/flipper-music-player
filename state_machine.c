#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>

#include "furi_hal_resources.h"
#include "structs.h"

static void process_main_menu_navigation(AppState* state, InputKey key) {
    if(key == InputKeyUp) {
        // Decrement index
        state->selected_index = (state->selected_index == 0) ? menu_items_count - 1 :
                                                               state->selected_index - 1;
    } else if(key == InputKeyDown) {
        // Increment index
        state->selected_index = (state->selected_index + 1) % menu_items_count;
    }
}

int process_state(InputEvent event, AppState* state) {
    // State machine processor
    // Switch case firstly by application pane
    // Then by user input

    // 1. Enumeration values 'AppViewAbout', 'AppViewBrowse', and 'AppViewShuffle' not handled in switch [-Wswitch]
    switch(state->current_view) {
    case AppViewMainMenu:
        if(event.type == InputTypeShort || event.type == InputTypeRepeat) {
            if(event.key == InputKeyBack) {
                // Stop application
                return -1;
            }
            if(event.key == InputKeyUp || event.key == InputKeyDown) {
                process_main_menu_navigation(state, event.key);
                break;
            }

            switch(state->selected_index) {
            case 0:
                state->current_view = AppViewBrowse;
                break;
            case 1:
                state->current_view = AppViewShuffle;
                break;
            case 2:
                state->current_view = AppViewAbout;
                break;
            default:
                break;
            }
        }
        break;
    case AppViewAbout:
        // back to main menu case
        if((event.type == InputTypeShort || event.type == InputTypeRepeat) &&
           event.key == InputKeyBack) {
            state->current_view = AppViewMainMenu;
            break;
        }

        // S
        break;
    case AppViewBrowse:
        // back to main menu case
        if((event.type == InputTypeShort || event.type == InputTypeRepeat) &&
           event.key == InputKeyBack) {
            state->current_view = AppViewMainMenu;
            break;
        }
        break;
    case AppViewShuffle:
        // back to main menu case
        if((event.type == InputTypeShort || event.type == InputTypeRepeat) &&
           event.key == InputKeyBack) {
            state->current_view = AppViewMainMenu;
            break;
        }
        break;
    default:
        // Should not be in default
        // Return to main menu
        // Also should log err

        state->current_view = AppViewMainMenu;
        break;
    }

    return 0;
}
