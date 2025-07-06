#include "core/core_defines.h"
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>

// static const char *BROWSE = "Browse";
// static const int BROWSE_IDX = 0;


// static const char *SHUFFLE = "Shuffle";
// static const int SHUFFLE_IDX = 1;

// static const char *ABOUT = "About";
// static const int ABOUT_IDX = 2;


static const char *menu_items[] = {
    "Browse",
    "Shuffle",
    "About",
};
static const int menu_items_count = sizeof(menu_items) / sizeof(char *);

typedef struct {
  FuriMessageQueue *event_queue;
  int selected_index;
  int selected_pane;
} AppState;

static void app_draw_callback(Canvas *canvas, void *context) {
  furi_assert(context);
  AppState *state = context;

  canvas_clear(canvas);
  canvas_set_font(canvas, FontPrimary);

  for (int i = 0; i < menu_items_count; i++) {
    // Highlight the selected item
    if (i == state->selected_index) {
      canvas_draw_box(canvas, 0, i * 12, 128, 12);
      canvas_set_color(canvas, ColorWhite);
      canvas_draw_str(canvas, 2, (i * 12) + 10, menu_items[i]);
      canvas_set_color(canvas, ColorBlack);
    } else {
      canvas_draw_str(canvas, 2, (i * 12) + 10, menu_items[i]);
    }
  }
}

static void app_input_callback(InputEvent *event, void *context) {
  furi_assert(context);
  AppState *state = context;

  furi_message_queue_put(state->event_queue, event, FuriWaitForever);
}

int32_t hello_gui_main(void *p) {
  UNUSED(p);

  // --- Allocation ---
  // Allocate our state struct
  AppState *state = malloc(sizeof(AppState));
  // Initialize the state
  state->selected_index = 0;
  state->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

  // The viewport is our application's window on the screen.
  ViewPort *view_port = view_port_alloc();


  // Pass the *state* as the context to both callbacks
  view_port_draw_callback_set(view_port, app_draw_callback, state);
  view_port_input_callback_set(view_port, app_input_callback, state);
  view_port_set_orientation(view_port, ViewPortOrientationVertical);
  // Get the gui service and add our viewport to it to make it visible.
  Gui *gui = furi_record_open(RECORD_GUI);
  gui_add_view_port(gui, view_port, GuiLayerFullscreen);

  // --- Phase 3: The Main Loop ---
  bool running = true;
  while (running) {
    InputEvent event;
    // Get events from the queue
    if (furi_message_queue_get(state->event_queue, &event, FuriWaitForever) ==
        FuriStatusOk) {
      // Process input events
      if (event.type == InputTypeShort || event.type == InputTypeRepeat) {
        if (event.key == InputKeyUp) {
          // Decrement index
          state->selected_index = (state->selected_index == 0)
                                      ? menu_items_count - 1
                                      : state->selected_index - 1;
        } else if (event.key == InputKeyDown) {
          // Increment index
          state->selected_index =
              (state->selected_index + 1) % menu_items_count;
        } else if (event.key == InputKeyBack) {
          // Stop application
          running = false;
        }
      }
    }
    //  After changing state, tell the viewport to redraw
    view_port_update(view_port);
  }

  // --- Phase 4: Cleanup ---
  gui_remove_view_port(gui, view_port);
  view_port_free(view_port);
  furi_message_queue_free(state->event_queue);
  free(state);
  furi_record_close(RECORD_GUI);

  return 0;
}
