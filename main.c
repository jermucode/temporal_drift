#include <stdio.h>
#include "config/config.h"
#include "player/player.h"
#include "maps/maps.h"
#include <raylib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <dirent.h>
#include "collisions/collisions.h"
#include "dialogue/dialogue.h"
#include "inventory/inventory.h"
#include "types.h"

int main(void) 
{

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Temporal Drift");
	SetTargetFPS(60);
	/*
	*/	
	Player player = initPlayer();

	Camera2D camera = { 0 };

	camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
	float playerRotation = 0.0f;
	int collisionLooper;
	bool dialogueActive = false;
	bool wasDialogueActive = false;

	bool inventoryActive = false;
	bool wasInventoryActive = false;

	char *dialogueFile;



	//char *mapName = "home_map_with_assets.txt";
	char mapName[256];
	long mapNameLength = 0;
	/*
	 The following part ensures current map gets loaded from a file. for testing purposes, we just need this to always be demo map. When creating a save game system, read this file and keep it updated. We replace this with just writing demo_map.txt into mapName

	FILE *fp = fopen("src/state/currentmap.txt", "r");



	 * */
	/*
	if(fp == NULL)
	{
		printf("error finding current map file\n");
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_END);
	mapNameLength = ftell(fp);
	rewind(fp);
	if(mapNameLength < 4) {
		strcpy(mapName, "home_map_with_assets.txt.bak");
		mapName[strlen("home_map_with_assets.txt")+1] = '\0';
	}
	else{
		fgets(mapName, 256, fp);
		mapName[strcspn(mapName, "\n")] = '\0';
	}
	fclose(fp);
	*/


	/*
	 * HERE LET'S OPEN THE DIALOGUE FOLDER
	 */
	strcpy(mapName, "demo_map.txt");

	printf("currentmap is: %s\nit's strlen is: %zu\n", mapName, strlen(mapName));

	//char *dialogueFolder;
	//size_t dialogueFolderNameLength;


	// USE THIS FOR STRLEN OF THE NAME OF THE OBJECT ASSET TO GENERATE DIALOGUE





	mapFileContents *myMap = mapFile(mapName);
	mapAssets *myAssets = assetsToRender(myMap);


	DialogueParsed *dialogue;
	int curPage = 0;


	// Item tracker initialization; FOR A SAVED GAME THIS NEEDS TO BE SAVED IN A FILE

	mapItemPickedUpTracker *mapItems = malloc(1 * sizeof(mapItemPickedUpTracker));
	mapItems->mapItemsPickedUp = malloc(1* sizeof(char*));
	mapItems->numItems = 0; //In the beginning it's always zero, for a saved game we load it from a file

	//playerInventory *inventory = malloc(1 * sizeof(playerInventory));
	playerInventory *inventory = calloc(1, sizeof(playerInventory));
	inventory->itemsInInventory = 0;
	inventory->items = NULL;

	bool inventoryTexturesLoaded = false;
	bool wereInventoryTexturesLoaded = false;
	Texture2D *inventoryTextures;





	while(!WindowShouldClose())
	{

		wasDialogueActive = dialogueActive; //Check dialogue


		wasInventoryActive = inventoryActive; //Check if inventoryActive

		wereInventoryTexturesLoaded = inventoryTexturesLoaded; //check if inventorytextures were loaded

		




		if(!wasDialogueActive && !wasInventoryActive && !inventoryTexturesLoaded) 
		{
			updatePlayer(&player);


			for(collisionLooper = 0; collisionLooper < myMap->fileObjectCount; collisionLooper++) {


				if(CheckCollisionRecs(player.destRec, myAssets->objectAssets[collisionLooper]->collisionRec)){
					if(myAssets->objectAssets[collisionLooper]->collision == 1 && 
							strncmp(myAssets->objectAssets[collisionLooper]->collisiontype, "maptransition",13) == 0) {
						handleMapTransition(
								&player, 
								&myMap,
								&myAssets,
								collisionLooper,
								mapItems
								);
						/* Set the new mapname so we can fetch dialogue*/
						FILE *mapFile = fopen("src/state/currentmap.txt","r");
						fgets(mapName, 256, mapFile);
						printf("mapfile is: %s\n", mapName);
						mapName[strcspn(mapName, "\n")] = '\0';
						fclose(mapFile);



						break;
					}
					if(myAssets->objectAssets[collisionLooper]->collision == 1 &&
							strncmp(myAssets->objectAssets[collisionLooper]->collisiontype, "wall", 4) == 0) {
						handleCollisionStop(&player);
					}


				}

			}

			// Stop the character from moving over objects
			for(collisionLooper = 0; collisionLooper < myMap->fileAnimationCount; collisionLooper++) {
				if(CheckCollisionRecs(player.destRec, myAssets->animationAssets[collisionLooper]->collisionRec)) {
					if(myAssets->animationAssets[collisionLooper]->collision == 1 && 
							strncmp(myAssets->animationAssets[collisionLooper]->collisiontype, "wall", 4) == 0) {
						handleCollisionStop(&player);
					}

					if(myAssets->animationAssets[collisionLooper]->collision == 1 && 
							strncmp(myAssets->animationAssets[collisionLooper]->collisiontype, "wall and text", 13) == 0 && IsKeyPressed(KEY_SPACE)) {
						dialogueFile = readDialogueFile(mapName, myAssets->animationAssets[collisionLooper]->name);
						dialogue = curDialogue(dialogueFile);
						dialogueActive = true;
					}
				}



			}

			for(collisionLooper = 0; collisionLooper < myMap->fileObjectCount; collisionLooper++) {
				if(CheckCollisionRecs(player.destRec, 
							(Rectangle) {myAssets->objectAssets[collisionLooper]->collisionRec.x-16.0f, 
							myAssets->objectAssets[collisionLooper]->collisionRec.y-16.0f,
							myAssets->objectAssets[collisionLooper]->collisionRec.width+32.0f,
							myAssets->objectAssets[collisionLooper]->collisionRec.height+32.0f })
						&& strncmp(myAssets->objectAssets[collisionLooper]->collisiontype, "wall and remove", 15) == 0 &&
						IsKeyPressed(KEY_SPACE)) {
					printf("function should be handleCollisionremove\n");
					handleCollisionPickup(mapItems, &myAssets, collisionLooper);
				}
			}



			for(collisionLooper = 0; collisionLooper < myMap->fileObjectCount; collisionLooper++) {
				if(CheckCollisionRecs(player.destRec, 
							(Rectangle) {myAssets->objectAssets[collisionLooper]->collisionRec.x-16.0f, 
							myAssets->objectAssets[collisionLooper]->collisionRec.y-16.0f,
							myAssets->objectAssets[collisionLooper]->collisionRec.width+32.0f,
							myAssets->objectAssets[collisionLooper]->collisionRec.height+32.0f })
						&& strncmp(myAssets->objectAssets[collisionLooper]->collisiontype, "wall and pickup", 15) == 0 &&
						IsKeyPressed(KEY_SPACE)) {
					printf("function should be handleCollisionPickup\n");
					handleCollisionInventory(mapItems, &myAssets, collisionLooper, inventory);
				}
			}



			// Interact with an object using space, displays text
			for(collisionLooper = 0; collisionLooper < myMap->fileObjectCount; collisionLooper++) {
				if(CheckCollisionRecs(player.destRec, 
							(Rectangle) {myAssets->objectAssets[collisionLooper]->collisionRec.x-16.0f, 
							myAssets->objectAssets[collisionLooper]->collisionRec.y-16.0f,
							myAssets->objectAssets[collisionLooper]->collisionRec.width+32.0f,
							myAssets->objectAssets[collisionLooper]->collisionRec.height+32.0f })
						&& strncmp(myAssets->objectAssets[collisionLooper]->collisiontype, "wall and text", 13) == 0 && 
						IsKeyPressed(KEY_SPACE)) {

					dialogueFile = readDialogueFile(mapName, myAssets->objectAssets[collisionLooper]->name);
					dialogue = curDialogue(dialogueFile);
					dialogueActive = true;


				}
			}


		}
		camera.target = player.position;
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);
		drawMap(myAssets, myMap, mapItems);
		drawPlayer(&player, playerRotation);
		EndMode2D();
		if(wasDialogueActive)  {
			drawDialogueBox(dialogue->parsedDialogue[curPage]);
			if(IsKeyPressed(KEY_SPACE)) {
				curPage++;
			}

			if(curPage >= dialogue-> pageCount) 
			{
				printf("curpage is %d and pageCount is %d\n", curPage, dialogue->pageCount);
				printf("we made it to destroy dialogues\n");
				destroyDialogueStruct(dialogue);
				destroyDialogueFile(dialogueFile);
				curPage = 0;
				dialogueActive = false;
			}

		}

		if(IsKeyPressed(KEY_I)) {
			inventoryActive = true;
			if(!wereInventoryTexturesLoaded)
			{
				if(inventory->itemsInInventory > 0)
				{
					inventoryTexturesLoaded = true;
					inventoryTextures = loadInventoryTextures(inventory);
					printf("we loaded inventorytextures from main\n");
				}
			}

		}

		if(wasInventoryActive)
		{
			drawInventoryScreen(inventory, inventoryTextures);
		}

		if(wasInventoryActive && IsKeyPressed(KEY_I))
		{
			inventoryActive = false;
			if(inventory->itemsInInventory > 0)
			{
				//call unload inventoryTextures
				inventoryTexturesLoaded = false;
				destroyLoadedInventoryTextures(inventory, inventoryTextures);

			}


		}




		EndDrawing();
	}

	destroyItemArray(mapItems);

	if(inventory->itemsInInventory > 0 && inventoryTexturesLoaded)
	{
		destroyLoadedInventoryTextures(inventory, inventoryTextures);
	}
	destroyInventory(inventory);

	UnloadTexture(player.sprite);
	//UnloadTexture(testAnimation);
	destroyMapAssets(myAssets, myMap);
	destroyMapFile(myMap);


	CloseWindow();

	}

