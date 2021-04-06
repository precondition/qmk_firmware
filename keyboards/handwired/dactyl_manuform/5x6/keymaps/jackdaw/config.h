#pragma once

#define USE_SERIAL
#define MASTER_LEFT

// Default tapping term is 200
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT
 
// This prevents accidental repeats of the tap-hold keys when typing quickly.
#define TAPPING_FORCE_HOLD
 
// This prevents short hold periods to be interpreted as individual taps when typing quickly.
#define PERMISSIVE_HOLD

// Limits the max. amount of layers to 8 to save firmware memory.
#define LAYER_STATE_8BIT
