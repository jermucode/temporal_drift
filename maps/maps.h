#ifndef MAPS
#define MAPS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <dirent.h>
#include <errno.h>
#include "../types.h"

char **assetToStrings(mapFileContents *mapFile, int stringType, int stringTypeIndex);

char **cleanStrings(char **strings, int type);

mapAssets *assetsToRender(mapFileContents *mapFile);

void destroyMapAssets(mapAssets *assets, mapFileContents *mapFile);

mapFileContents *mapFile(char *mapName);

void destroyMapFile(mapFileContents *mapConts);

void destroyStrings(char **strings, int type);

tileAsset *stringsToTile(char **strings);

objectAsset *stringsToObject(char **strings);

characterAsset *stringsToCharacter(char **strings);

void destroyTileAsset(tileAsset *asset);

void destroyObjectAsset(objectAsset *asset);

void destroyCharacterAsset(characterAsset *asset);

void drawTile(tileAsset *asset);

void drawObject(objectAsset *asset);

void drawCharacter(characterAsset *asset);

void drawMap(mapAssets *assets, mapFileContents *mapName, mapItemPickedUpTracker *pickedUpItems);


char *mapName(void);


Animation *stringsToAnimation(char **strings);

char **orderedStrings(char **inputStrings, int stringType);


extern void (*drawMapPtr)(mapAssets *assets, mapFileContents *mapName);
extern void (*mapNameLength)(char *mapName);
extern void (*destroyMapAssetsPtr)(mapAssets *assets, mapFileContents *mapName);
extern mapAssets *(*assetsToRenderPtr)(mapFileContents *mapName);







#endif
