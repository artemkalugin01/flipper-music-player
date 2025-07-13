#pragma once

#include <furi.h> // Assuming FuriMessageQueue is defined in furi.h

// Enum for application views - TYPE DEFINITION
typedef enum {
    AppViewMainMenu,
    AppViewAbout,
    AppViewBrowse,
    AppViewShuffle
} AppView;

// Structure for application state - TYPE DEFINITION
typedef struct {
  FuriMessageQueue *event_queue;
  int selected_index;
  AppView current_view;
} AppState;

// State of "Browse" pane of app
typedef struct {
    int selected_index;
    // List of file names
    char **file_names;
    int file_count;
} BrowsePaneState;


// Menu items as a public constant array of strings - DECLARATION
// Use 'extern' to declare that this constant is defined in an *another* .c file.
extern const char *menu_items[];
extern const int menu_items_count;
