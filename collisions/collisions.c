#include <stdio.h>
#include <stdlib.h>
#include "collisions.h"
#include "../maps/maps.h"
#include "raylib.h"
#include "../config/config.h"
#include <dirent.h>

void handleMapTransition(Player *player, 
		mapFileContents **myMap, 
		mapAssets **myAssets,
		int loopIndex, 
		mapItemPickedUpTracker *mapItems) {
	size_t newMapLength = strlen((*myAssets)->objectAssets[loopIndex]->nextmap);
	char newMapName[MAXMAPNAMELENGTH];
	int nextMapSpawnX = (*myAssets)->objectAssets[loopIndex]->nextmapspawnx;
	int nextMapSpawnY = (*myAssets)->objectAssets[loopIndex]->nextmapspawny;
	strncpy(newMapName, (*myAssets)->objectAssets[loopIndex]->nextmap, newMapLength);
	newMapName[newMapLength] = '\0';
	FILE *fp = fopen("src/state/currentmap.txt", "w");
	fputs(newMapName, fp);
	fclose(fp);
	destroyMapAssets(*myAssets, *myMap);
	destroyMapFile(*myMap);
	*myMap = mapFile(newMapName);
	*myAssets = assetsToRender(*myMap);
	drawMap(*myAssets, *myMap, mapItems);
	player->position.x = nextMapSpawnX;
	player->position.y = nextMapSpawnY;


}


void handleCollisionStop(Player *player) {

	if(player->direction == FACING_RIGHT) {
		player->position.x -= 2.1f;
	}
	if(player->direction == FACING_LEFT) {
		player->position.x += 2.1f;
	}
	if(player->direction == FACING_BACKWARD) {
		player->position.y += 2.1f;
	}
	if(player->direction == FACING_FORWARD) {
		player->position.y -= 2.1f;
	}

}


/*
 * THE NAMING BELOW IS CONFUSING; KEEP THAT IN MIND. ITEMNAMELENGTH is the length of the itemID, not its name
 *
 * */


void handleCollisionPickup(mapItemPickedUpTracker *mapItems, mapAssets **myAssets, int loopIndex) // Add picked up items to mapItemTracker
{

	int item; //item looper to check if allocs are necessary
	int i = mapItems->numItems;

	bool itemAccountedFor = false;
	for(item = 0; i < mapItems->numItems; i++)
	{
		printf("in forloopitemaccount\n");
		if(strcmp(mapItems->mapItemsPickedUp[item], (*myAssets)->objectAssets[loopIndex]->itemId) == 0)
		{
			printf("itemaccountedfor\n");
			itemAccountedFor = true;
		}

	}
	if(!itemAccountedFor)
	{
		mapItems->mapItemsPickedUp = realloc(mapItems->mapItemsPickedUp, (i+1) * sizeof(char*));
		size_t itemNameLength = strlen((*myAssets)->objectAssets[loopIndex]->itemId);
		printf("ItemID is: %s\n", (*myAssets)->objectAssets[loopIndex]->itemId);
		mapItems->mapItemsPickedUp[i] = malloc((itemNameLength + 1) * sizeof(char));
		strncpy(mapItems->mapItemsPickedUp[i], (*myAssets)->objectAssets[loopIndex]->itemId, itemNameLength);
		mapItems->mapItemsPickedUp[i][itemNameLength] = '\0';
		mapItems->numItems++;
	}
	itemAccountedFor = false;


}


void handleCollisionInventory(mapItemPickedUpTracker *mapItems, mapAssets **myAssets, int loopIndex, playerInventory *inventory)
{
	size_t itemPathLength;
	int itemCharacterCount;
	// Deal with removing item from the gameworld
	int i = mapItems->numItems;
	mapItems->mapItemsPickedUp = realloc(mapItems->mapItemsPickedUp, (i+1) * sizeof(char*));
	size_t itemNameLength = strlen((*myAssets)->objectAssets[loopIndex]->itemId);
	printf("ItemID is: %s\n", (*myAssets)->objectAssets[loopIndex]->itemId);
	mapItems->mapItemsPickedUp[i] = malloc((itemNameLength + 1) * sizeof(char));
	strncpy(mapItems->mapItemsPickedUp[i], (*myAssets)->objectAssets[loopIndex]->itemId, itemNameLength);
	mapItems->mapItemsPickedUp[i][itemNameLength] = '\0';
	mapItems->numItems++;

	/* CHECK IF ITEM ALREADY IN INVENTORY */

	bool itemPickedUp = false;
	int inventoryLooper;
	for(inventoryLooper = 0; inventoryLooper < inventory->itemsInInventory; i++)
	{
		if(strcmp((*myAssets)->objectAssets[loopIndex]->itemId, inventory->items[inventoryLooper]->itemId) == 0)
		{
			printf("check if item pickedup strcmp\n");
			itemPickedUp = true;
			break;
		}



	}





	if(!itemPickedUp)
	{

		if(inventory->itemsInInventory == 0)
		{
			printf("we are in itemsininventory = 0");
			inventory->items = malloc(1 * sizeof(inventoryItem*));
			inventory->items[0] = malloc(1 * sizeof(inventoryItem));
			inventory->items[0]->itemId = malloc((itemNameLength + 1) * sizeof(char));
			strncpy(inventory->items[0]->itemId, (*myAssets)->objectAssets[loopIndex]->itemId, itemNameLength);
			inventory->items[0]->itemId[itemNameLength] = '\0';


			//itemCharacterCount refers to the length of the item name
			itemCharacterCount = strlen((*myAssets)->objectAssets[loopIndex]->name);

			inventory->items[0]->itemName = malloc((itemCharacterCount + 1) * sizeof(char));
			strncpy(inventory->items[0]->itemName, (*myAssets)->objectAssets[loopIndex]->name, itemCharacterCount);
			inventory->items[0]->itemName[itemCharacterCount] = '\0';

			itemPathLength = strlen((*myAssets)->objectAssets[loopIndex]->texturePath);

			inventory->items[0]->itemTexturePath = malloc((itemPathLength + 1) * sizeof(char));
			strncpy(inventory->items[0]->itemTexturePath, (*myAssets)->objectAssets[loopIndex]->texturePath, itemPathLength);
			inventory->items[0]->itemTexturePath[itemPathLength] = '\0';

			inventory->items[0]->sourceRec = malloc(1 * sizeof(Rectangle));
			*inventory->items[0]->sourceRec = (*myAssets)->objectAssets[loopIndex]->sourceRec;


			inventory->itemsInInventory = 1;
		}
		else if(inventory->itemsInInventory > 0)
		{
			int j = inventory->itemsInInventory;
			inventory->items = realloc(inventory->items, (j+1) * sizeof(inventoryItem*));
			inventory->items[j] = malloc(1 * sizeof(inventoryItem));

			inventory->items[j]->itemId = malloc((itemNameLength + 1) * sizeof(char));
			strncpy(inventory->items[j]->itemId, (*myAssets)->objectAssets[loopIndex]->itemId, itemNameLength);
			inventory->items[j]->itemId[itemNameLength] = '\0';


			//itemCharacterCount refers to the length of the item name
			itemCharacterCount = strlen((*myAssets)->objectAssets[loopIndex]->name);

			inventory->items[j]->itemName = malloc((itemCharacterCount + 1) * sizeof(char));
			strncpy(inventory->items[j]->itemName, (*myAssets)->objectAssets[loopIndex]->name, itemCharacterCount);
			inventory->items[j]->itemName[itemCharacterCount] = '\0';

			itemPathLength = strlen((*myAssets)->objectAssets[loopIndex]->texturePath);
			inventory->items[j]->itemTexturePath = malloc((itemPathLength + 1) * sizeof(char));
			strncpy(inventory->items[j]->itemTexturePath, (*myAssets)->objectAssets[loopIndex]->texturePath, itemPathLength);
			inventory->items[j]->itemTexturePath[itemPathLength] = '\0';


			inventory->items[j]->sourceRec = malloc(1 * sizeof(Rectangle));
			*inventory->items[j]->sourceRec = (*myAssets)->objectAssets[loopIndex]->sourceRec;
			inventory->itemsInInventory++;


		}
	}

	itemPickedUp = false;


}





void destroyItemArray(mapItemPickedUpTracker *mapItems) //destroy mapItems picked up tracker, use at the end of the program
{
	int i = 0;
	if(mapItems->numItems > 0) {
		for(i = 0; i < mapItems->numItems; i++)
		{
			free(mapItems->mapItemsPickedUp[i]);
		}
	}
	free(mapItems->mapItemsPickedUp);
	free(mapItems);

}

