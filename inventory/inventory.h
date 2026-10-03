#ifndef INVENTORY_H
#define INVENTORY_H
#include <stdio.h>
#include "../types.h"

void drawInventoryScreen(playerInventory *inventory, Texture2D *inventoryTextures);
Texture2D *loadInventoryTextures(playerInventory *inventory);
void drawInventoryItems(playerInventory *inventory, Rectangle textBox);
void destroyInventory(playerInventory *inventory);
void destroyLoadedInventoryTextures(playerInventory *inventory, Texture2D *inventoryTextures);




#endif


