#include "gui/canvas.h"
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>

void draw_settings_pane(Canvas* canvas, void* context) {
    furi_assert(context);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_str(canvas, 2, 12, "File 1");
    canvas_draw_str(canvas, 2, 24, "File 2");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 36, "File 3");

    // test

    canvas_draw_str(canvas, 2, 60, "XX");
}
