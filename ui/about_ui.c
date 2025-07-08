#include "gui/canvas.h"
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>


void draw_about_pane(Canvas* canvas, void* context) {
  furi_assert(context);

  canvas_clear(canvas);
  canvas_set_color(canvas, ColorBlack);

  // To center text, we calculate the starting X position for each string.
  // X = (Screen Width - String Width) / 2
  const uint8_t screen_width = 64;
  uint8_t str_width;
  uint8_t x;

  // Use FontPrimary for a bold effect to contrast with the smaller font.
  canvas_set_font(canvas, FontPrimary);
  const char* text_music = "Music";
  str_width = canvas_string_width(canvas, text_music);
  x = (screen_width - str_width) / 2;
  canvas_draw_str(canvas, x, 12, text_music);

  // Use a smaller font for "aah" to create the desired contrast.
  canvas_set_font(canvas, FontKeyboard);
  const char* text_aah = "aah";
  str_width = canvas_string_width(canvas, text_aah);
  x = (screen_width - str_width) / 2;
  canvas_draw_str(canvas, x, 26, text_aah);

  // Revert to FontPrimary for the rest of the text.
  canvas_set_font(canvas, FontPrimary);
  const char* text_player = "Player";
  str_width = canvas_string_width(canvas, text_player);
  x = (screen_width - str_width) / 2;
  canvas_draw_str(canvas, x, 38, text_player);

  const char* text_for_8bit = "For 8-bit";
  str_width = canvas_string_width(canvas, text_for_8bit);
  x = (screen_width - str_width) / 2;
  canvas_draw_str(canvas, x, 52, text_for_8bit);

  const char* text_music_lower = "music";
  str_width = canvas_string_width(canvas, text_music_lower);
  x = (screen_width - str_width) / 2;
  canvas_draw_str(canvas, x, 62, text_music_lower);
}
