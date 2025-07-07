#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>

#include "structs.h"

int process_state(InputEvent event, AppState *state) {
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
        }
        if (event.key == InputKeyBack) {
          // Stop application
          return -1;
        }
      }

      return 0;
}
