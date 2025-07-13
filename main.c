#include <furi.h>
#include <storage/storage.h>
#include <gui/gui.h>
#include <input/input.h>
#include <string.h>

#include "ui/about_ui.h"
#include "ui/settings_ui.h"
#include "ui/main_ui.h"
#include "structs.h"
#include "state_machine.h"

#define TAG "MusicPlayer"

static void app_draw_callback(Canvas* canvas, void* context) {
    furi_assert(context);
    AppState* state = context;

    // Decide which helper to call based on the current view
    switch(state->current_view) {
    case AppViewMainMenu:
        draw_main_pane(canvas, state);
        break;
    case AppViewAbout:
        draw_about_pane(canvas, state);
        break;
    // TODO different state
    case AppViewBrowse:
        draw_settings_pane(canvas, state);
        break;
    default:
        // Should not be in default. Return non zero code but can't.
        // Drawing main pane
        // TODO logging?
        draw_settings_pane(canvas, state);
        break;
    }
}

static void app_input_callback(InputEvent* event, void* context) {
    furi_assert(context);
    AppState* state = context;

    furi_message_queue_put(state->event_queue, event, FuriWaitForever);
}


int32_t hello_gui_main(void* p) {
    UNUSED(p);
    FURI_LOG_I(TAG, "Info print:");

    // --- Allocation ---
    // Allocate our app state struct
    AppState* state = malloc(sizeof(AppState));
    // Initialize the state
    state->selected_index = 0;
    state->current_view = AppViewMainMenu;
    state->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    // Allocate the browse pane state
    BrowsePaneState* browse_pane_state = malloc(sizeof(BrowsePaneState));
    browse_pane_state->selected_index = 0;
    browse_pane_state->file_names = NULL;
    browse_pane_state->file_count = 0;

    // The viewport is our application's window on the screen.
    ViewPort* view_port = view_port_alloc();

    // Pass the *state* as the context to both callbacks
    view_port_draw_callback_set(view_port, app_draw_callback, state);
    view_port_input_callback_set(view_port, app_input_callback, state);
    view_port_set_orientation(view_port, ViewPortOrientationVertical);
    // Get the gui service and add our viewport to it to make it visible.
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    // --- Phase 3: The Main Loop ---
    bool running = true;
    while(running) {
        InputEvent event;
        // Get events from the queue
        if(furi_message_queue_get(state->event_queue, &event, FuriWaitForever) == FuriStatusOk) {
            // Process the event and update the state
            int state_update = process_state(event, state);
            if(state_update != 0) {
                running = false;
            }
        }
        // call redraw after state change
        view_port_update(view_port);
    }

    // --- Phase 4: Cleanup ---
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_message_queue_free(state->event_queue);
    free(state);
    free(browse_pane_state);
    furi_record_close(RECORD_GUI);

    return 0;
}
