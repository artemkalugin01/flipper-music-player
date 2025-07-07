
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include "gui/canvas.h"
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include "structs.h"

void draw_main_pane(Canvas *canvas, void *context) {
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
