#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "../types.h"


Player initPlayer(); // Create the player sprite and initial positions
void updatePlayer(Player *player); // Move the player sprite and update animation
void drawPlayer(Player *player, float rotation);

#endif
