#include "raylib.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../../src/config/config.h"
#include <dirent.h>
#include <math.h>
#include "inventory.h"

Texture2D *loadInventoryTextures(playerInventory *inventory)
{
	Texture2D *inventoryTextures = calloc(inventory->itemsInInventory, sizeof(Texture2D));
	int i;

	if(inventory->itemsInInventory > 0)
	{
		for(i = 0; i < inventory->itemsInInventory; i++) 
		{
			printf("loaded textures because inventorytexturesloaded was false\n");
			inventoryTextures[i] = LoadTexture(inventory->items[i]->itemTexturePath);
		}
	}
	else 
	{
		inventoryTextures[0] = LoadTexture(inventory->items[0]->itemTexturePath);
	}

	return inventoryTextures;
}


void destroyLoadedInventoryTextures(playerInventory *inventory, Texture2D *inventoryTextures)
{
	int i;
	if(inventory->itemsInInventory == 1)
	{
		UnloadTexture(inventoryTextures[0]);

	}
	else 
	{
		for(i = 1; i < inventory->itemsInInventory; i++)
		{
			UnloadTexture(inventoryTextures[i]);
		}

	}
	free(inventoryTextures);
}






void drawInventoryScreen(playerInventory *inventory, Texture2D *inventoryTextures)
{



	Rectangle textBox;
	textBox = (Rectangle) { 
		SCREEN_WIDTH/2.0f - 600.0f,
		SCREEN_HEIGHT/7.5+1.0f,
		1200.0f,
		SCREEN_HEIGHT-200.0f
	};

	if(inventory->itemsInInventory == 0)
	{

		DrawRectangleRec(textBox, BLACK);
		DrawRectangleLinesEx(textBox, 6.0f, WHITE);
		DrawText("inventory", textBox.x+25.0f, textBox.y+50, 40, WHITE);
	}

	int i;

	if(inventory->itemsInInventory > 0)
	{
		DrawRectangleRec(textBox, BLACK);
		DrawRectangleLinesEx(textBox, 6.0f, WHITE);
		DrawText("inventory", textBox.x+25.0f, textBox.y+50, 40, WHITE);
		for(i = 0; i < inventory->itemsInInventory; i++)
		{
			if(i < 5)
			{
			DrawTexturePro(inventoryTextures[i], 
					*inventory->items[i]->sourceRec, 
					(Rectangle) {
					textBox.x + 80.0f, 
					textBox.y + 100.0f + (i*180.0f),
					150,
					150
					},
					(Vector2) {0.0,0.0},
					0.0,
					WHITE);
			}

		}
	}



}



//also make a separate destroy inventorytextures function

void destroyInventory(playerInventory *inventory)
{
	int i = 0;
	if(inventory->itemsInInventory > 0)
	{
		for(i = 0; i < inventory->itemsInInventory; i++) {
			free(inventory->items[i]->itemName);
			free(inventory->items[i]->itemId);
			free(inventory->items[i]->itemTexturePath);
			free(inventory->items[i]->sourceRec);
			free(inventory->items[i]);

		}
		free(inventory->items);

	}
	free(inventory);
}


