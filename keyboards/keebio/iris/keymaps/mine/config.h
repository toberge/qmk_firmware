#pragma once

// wtf is this
#define EE_HANDS

// Enable lightling layers
#define RGBLIGHT_LAYERS

// Reduce delay on keys that do different things when held vs tapped
#define TAPPING_TERM 120

//
// Reduce firmware size
// See https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
//

// Disable debug stuff in rules.mk (frees 2000 bytes!)

// Disable things that conflict with -flo (about 3000 bytes freed)
// Remove the line in rules.mk if any of this is enabled
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
