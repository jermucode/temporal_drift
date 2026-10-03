#ifndef COLLISIONS_H
#define COLLISIONS_H


#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <dirent.h>
#include <sys/stat.h>
#include "../types.h"

void handleMapTransition(Player *player,
mapFileContents **mymap,
mapAssets **myMap,
int loopIndex, 
mapItemPickedUpTracker *mapItems);
void handleCollisionStop(Player *player);
void handleCollisionText(char mapName[], objectAsset *object);
void handleCollisionPickup(mapItemPickedUpTracker *mapItems, mapAssets **myAssets, int loopIndex); // Add picked up items to mapItemTracker
void handleCollisionInventory(mapItemPickedUpTracker *mapItems, mapAssets **myAssets, int loopIndex, playerInventory *inventory);										
void destroyItemArray(mapItemPickedUpTracker *mapItems);



#endif
