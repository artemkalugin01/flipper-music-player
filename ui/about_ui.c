#include "gui/canvas.h"
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>


void draw_about_pane(Canvas *canvas, void *context) {
  furi_assert(context);

  canvas_clear(canvas);
  canvas_set_font(canvas, FontPrimary);

  canvas_draw_box(canvas, 0, 0, 64, 12);
  canvas_set_color(canvas, ColorWhite);
  canvas_draw_str(canvas, 2, 12, "About section");

  canvas_set_color(canvas, ColorXOR);
  canvas_draw_str(canvas, 2, 36, "Press back");

  // test

  canvas_draw_str(canvas, 2, 60, "XX");
  canvas_draw_str(canvas, 60, 2, "YY");
}
