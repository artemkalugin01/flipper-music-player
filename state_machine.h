#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>

#include "structs.h"

int process_state(InputEvent event, AppState* state);
