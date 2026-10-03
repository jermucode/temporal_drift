#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "raylib.h"
#include <stdio.h>
#include "../types.h"


void animationUpdate(Animation *self);

Rectangle animationFrame(Animation *self, int numFramesPerRow, float frameWidth, float frameHeight);

Animation *textToStruct(mapFileContents *mapName);

#endif
