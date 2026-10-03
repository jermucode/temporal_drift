#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <dirent.h>
#include <errno.h>
#include "maps.h"
#include "raylib.h"
#include <ctype.h>
#include "../player/player.h"


char **assetToStrings(mapFileContents *mapFile, int stringType, int stringTypeIndex) { //index means which [asset] we're returning as strings
	char **returnStrings;
	size_t lineLength = 0;
	int curLine = 0;
	int index = 0; //increment by 1 until you hit stringTypeIndex

	int i = 0;

	switch(stringType) {
		case TILE:
			returnStrings = calloc(TILEFIELDS, sizeof(char*));
			for(i = 0; i < mapFile->fileLineCount; i++)
			{
				if(strncmp(mapFile->fileContents[i], "[tile]", 6) == 0) 
				{
					index++;
					if(index == stringTypeIndex) {
						while(curLine < TILEFIELDS) {
							lineLength = strlen(mapFile->fileContents[i]);
							returnStrings[curLine] = calloc(lineLength + 1, sizeof(char));
							strncpy(returnStrings[curLine], mapFile->fileContents[i], lineLength);
							curLine++;
							i++;
						}
						break;
					}
				}

			}
			break;

		case OBJECT:
			returnStrings = calloc(OBJECTFIELDS, sizeof(char*));
			for(i = 0; i < mapFile->fileLineCount; i++) {
				if(strncmp(mapFile->fileContents[i], "[object]", 8) == 0) {
					index++;
					if(index == stringTypeIndex) {
						while(curLine < OBJECTFIELDS) {
							lineLength = strlen(mapFile->fileContents[i]);
							returnStrings[curLine] = calloc(lineLength + 1, sizeof(char));
							strncpy(returnStrings[curLine], mapFile->fileContents[i], lineLength);
							curLine++;
							i++;
						}
						break;
					}
				}
			}
			break;
		case CHARACTER:
			returnStrings = calloc(CHARACTERFIELDS, sizeof(char*));
			for(i = 0; i < mapFile->fileLineCount; i++) {
				if(strncmp(mapFile->fileContents[i], "[character]", 11) == 0) {
					index++;
					if(index == stringTypeIndex) {
						while(curLine < CHARACTERFIELDS) {
							lineLength = strlen(mapFile->fileContents[i]);
							returnStrings[curLine] = calloc(lineLength + 1, sizeof(char));
							strncpy(returnStrings[curLine], mapFile->fileContents[i], lineLength);
							curLine++;
							i++;
						}
						break;
					}
				}
			}
			break;
		case ANIMATIONFIELDCOUNT:
			returnStrings = calloc(ANIMATIONFIELDS, sizeof(char*));
			for(i = 0; i < mapFile->fileLineCount; i++) {
				if(strncmp(mapFile->fileContents[i], "[animation]", 11) == 0) {
					index++;
					if(index == stringTypeIndex) {
						while(curLine < ANIMATIONFIELDS) {
							lineLength = strlen(mapFile->fileContents[i]);
							returnStrings[curLine] = calloc(lineLength +1, sizeof(char));
							strncpy(returnStrings[curLine], mapFile->fileContents[i], lineLength);
							curLine++;
							i++;
						}
						break;
					}
				}
			}
			break;

	}

	char **returnFields;
	char **returnTileFieldsTest;
	returnTileFieldsTest = orderedStrings(returnStrings, stringType);
	returnFields = cleanStrings(returnTileFieldsTest, stringType);
	destroyStrings(returnTileFieldsTest, stringType);
	destroyStrings(returnStrings, stringType);

	//destroyStrings(returnStrings, stringType);

	return returnFields;
}


char **orderedStrings(char **inputStrings, int stringType) {
	char **outputStrings;
	size_t lineLength;
	int i;
	switch(stringType) {
		case TILE:
			outputStrings = calloc(TILEFIELDS, sizeof(char*));
			if(outputStrings == NULL) {
				printf("Error in callocing outputstrings in newrenderstructs.c char **orderedstrings\nerror:%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}

			for(i = 0; i < TILEFIELDS; i++) {
				lineLength = strlen(inputStrings[i]);
				if(strncmp(inputStrings[i], "[tile]", 6) == 0) {
					outputStrings[0] = calloc(lineLength+1, sizeof(char));
					strncpy(outputStrings[0], inputStrings[i], lineLength);
				}
				else if(strncmp(inputStrings[i], "name:", 5) == 0) {
					outputStrings[1] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[1], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "tile:", 5) == 0 && strncmp(inputStrings[i], "[tile]:", 7) != 0) {
					outputStrings[2] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[2], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec1:", 11) == 0) {
					outputStrings[3] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[3], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec2:", 11) == 0) {
					outputStrings[4] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[4], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec3:", 11) == 0) {
					outputStrings[5] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[5], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec4:", 11) == 0) {
					outputStrings[6] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[6], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "tileSize:", 9) == 0 &&
						strncmp(inputStrings[i], "[tile]:", 9) != 0 &&
						strncmp(inputStrings[i], "tile:", 9) != 0) {
					outputStrings[7] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[7], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "map_width:", 10) == 0) {
					outputStrings[8] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[8], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "map_height:", 11) == 0) {
					outputStrings[9] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[9], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "origin1:", 8) == 0)  {
					outputStrings[10] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[10], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "origin2:", 8) == 0) {
					outputStrings[11] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[11], inputStrings[i]);

				}
				else if(strncmp(inputStrings[i], "scale:", 6) == 0) {
					outputStrings[12] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[12], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "rotation:", 9) == 0) {
					outputStrings[13] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[13], inputStrings[i]);
				}
			}
			break;

		case OBJECT: 
			outputStrings = calloc(OBJECTFIELDS, sizeof(char*));
			if(outputStrings == NULL) {
				printf("Error in callocing outputstrings in newrenderstructs.c char **orderedstrings\nerror:%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			for(i = 0; i < OBJECTFIELDS; i++) {
				lineLength = strlen(inputStrings[i]);
				if(strncmp(inputStrings[i], "[object]", 8) == 0) {
					outputStrings[0] = calloc(lineLength+1, sizeof(char));
					strncpy(outputStrings[0], inputStrings[i], lineLength);
				}
				else if(strncmp(inputStrings[i], "name:", 5) == 0) {
					outputStrings[1] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[1], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "tile:", 5) == 0 && strncmp(inputStrings[i], "[tile]:", 7) != 0) {
					outputStrings[2] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[2], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec1:", 11) == 0) {
					outputStrings[3] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[3], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec2:", 11) == 0) {
					outputStrings[4] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[4], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec3:", 11) == 0) {
					outputStrings[5] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[5], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "sourceRec4:", 11) == 0) {
					outputStrings[6] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[6], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec1:",9) == 0) {
					outputStrings[7] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[7], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec2:",9) == 0) {
					outputStrings[8] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[8], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec3:",9) == 0) {
					outputStrings[9] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[9], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec4:",9) == 0) {
					outputStrings[10] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[10], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "origin1:", 8) == 0) {
					outputStrings[11] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[11], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "origin2:", 8) == 0) {
					outputStrings[12] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[12], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "scale:",6) == 0) {
					outputStrings[13] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[13], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "rotation:", 9) == 0) {
					outputStrings[14] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[14], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collision:", 10) == 0) {
					outputStrings[15] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[15], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisiontype:", 14) == 0) {
					outputStrings[16] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[16], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "nextmap:", 8) == 0) {
					outputStrings[17] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[17], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "nextmapspawnx:", 14) == 0) {
					outputStrings[18] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[18], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "nextmapspawny", 14) == 0) {
					outputStrings[19] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[19], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "interacttext:", 13) == 0) {
					outputStrings[20] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[20], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "itemId:", 7) == 0) {
					outputStrings[21] = calloc(lineLength + 1, sizeof(char));
					strcpy(outputStrings[21], inputStrings[i]);
					printf("%s\n%s\n", outputStrings[21], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec1:", 14) == 0) {
					outputStrings[22] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[22], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec2:", 14) == 0) {
					outputStrings[23] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[23], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec3:", 14) == 0) {
					outputStrings[24] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[24], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec4:", 14) == 0) {
					outputStrings[25] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[25], inputStrings[i]);
				}

			}
			break;
		case ANIMATIONFIELDCOUNT: 
			outputStrings = calloc(ANIMATIONFIELDS, sizeof(char*));
			if(outputStrings == NULL) {
				printf("Error in callocing outputstrings in newrenderstructs.c char **orderedstrings\nerror:%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			for(i = 0; i < ANIMATIONFIELDS; i++) {
				lineLength = strlen(inputStrings[i]);
				if(strncmp(inputStrings[i], "[animation]", 11) == 0) {
					outputStrings[0] = calloc(lineLength+1, sizeof(char));
					strncpy(outputStrings[0], inputStrings[i], lineLength);
				}
				else if(strncmp(inputStrings[i], "name:", 5) == 0) {
					outputStrings[1] = calloc(lineLength+1, sizeof(char));
					strncpy(outputStrings[1], inputStrings[i], lineLength);
				}
				else if(strncmp(inputStrings[i], "tile:", 5) == 0 && strncmp(inputStrings[i], "[tile]:", 7) != 0) {
					outputStrings[2] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[2], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "numFramesPerRow:", 16) == 0) {
					outputStrings[3] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[3], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "frameWidth:", 11) == 0) {
					outputStrings[4] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[4], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "frameHeight:", 12) == 0) {
					outputStrings[5] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[5], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "first:", 6) == 0) {
					outputStrings[6] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[6], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "last:", 5) == 0) {
					outputStrings[7] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[7], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "cur:", 4) == 0) {
					outputStrings[8] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[8], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "speed:", 6) == 0) {
					outputStrings[9] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[9], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "duration_left:", 14) == 0) {
					outputStrings[10] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[10], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec1:",9) == 0) {
					outputStrings[11] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[11], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec2:",9) == 0) {
					outputStrings[12] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[12], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec3:",9) == 0) {
					outputStrings[13] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[13], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "destRec4:",9) == 0) {
					outputStrings[14] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[14], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "origin1:", 8) == 0) {
					outputStrings[15] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[15], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "origin2:", 8) == 0) {
					outputStrings[16] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[16], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "scale:", 6) == 0) {
					outputStrings[17] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[17], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "rotation:", 9) == 0) {
					outputStrings[18] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[18], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collision:", 10) == 0) {
					outputStrings[19] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[19], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisiontype:", 14) == 0) {
					outputStrings[20] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[20], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "nextmap:", 8) == 0) {
					outputStrings[21] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[21], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "nextmapspawnx:", 14) == 0) {
					outputStrings[22] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[22], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "nextmapspawny:", 14) == 0) {
					outputStrings[23] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[23], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "interacttext:", 13) == 0) {
					outputStrings[24] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[24], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec1:", 14) == 0) {
					outputStrings[25] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[25], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec2:", 14) == 0) {
					outputStrings[26] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[26], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec3:", 14) == 0) {
					outputStrings[27] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[27], inputStrings[i]);
				}
				else if(strncmp(inputStrings[i], "collisionRec4:", 14) == 0) {
					outputStrings[28] = calloc(lineLength+1, sizeof(char));
					strcpy(outputStrings[28], inputStrings[i]);
				}


			}
			break;

	}



	return(outputStrings);
}






char **cleanStrings(char **strings, int type) {
	int count, i;
	size_t lineLength;
	if(type == TILE) count = TILEFIELDS;
	if(type == OBJECT) count = OBJECTFIELDS;
	if(type == CHARACTER) count = CHARACTERFIELDS;
	if(type == ANIMATIONFIELDCOUNT) count = ANIMATIONFIELDS;
	char **cleanStrings = calloc(count, sizeof(char*));
	char *line;
	for(i = 0; i < count; i++) {
		if(strings[i] == NULL) {
			cleanStrings[i] = calloc(1, sizeof(char));
			cleanStrings[i][0] = '\0';
			continue;
		}
		line = strings[i];
		if(strncmp(strings[i], "[tile]", 6) == 0 || 
				strncmp(strings[i], "[object]", 8) == 0 || 
				strncmp(strings[i], "[character]", 11) == 0 || 
				strncmp(strings[i], "[animation]", 11) == 0 ) {
			lineLength = strlen(line) + 1;
			cleanStrings[i] = calloc(lineLength, sizeof(char));
			strncpy(cleanStrings[i], line, lineLength);
		} else {
			while(*line != ':' && *line != '\0') {
				line++;
			}
			if(*line == ':') {
				line++;
				while(*line && !isalnum(*line)) {
					line++;
				}
			}
			lineLength = strlen(line) + 1;
			cleanStrings[i] = calloc(lineLength, sizeof(char));
			strncpy(cleanStrings[i], line, lineLength);
		}
	}
	return cleanStrings;
}


mapAssets *assetsToRender(mapFileContents *mapFile) {

	mapAssets *returnAssets = calloc(1, sizeof(mapAssets));
	int i;
	int countTiles = mapFile->fileTileCount;
	int countObjects = mapFile->fileObjectCount;
	int countCharacters = mapFile->fileCharacterCount;
	int countAnimations = mapFile->fileAnimationCount;
	char **strings;
	if(countTiles == 1) {
		returnAssets->mapTiles = calloc(1, sizeof(tileAsset*));
		strings = assetToStrings(mapFile, TILE, 1);
		returnAssets->mapTiles[0] = stringsToTile(strings);
		destroyStrings(strings, TILE);
	}
	if(countTiles > 1) {
		returnAssets->mapTiles = calloc(countTiles, sizeof(tileAsset*));
		for(i = 0; i < countTiles; i++) {
			strings = assetToStrings(mapFile, TILE, i+1);
			//returnAssets->mapTiles[i] = calloc(1, sizeof(tileAsset));
			returnAssets->mapTiles[i] = stringsToTile(strings);
			destroyStrings(strings, TILE);
		}
	}
	if(countObjects == 1) {
		returnAssets->objectAssets = calloc(1, sizeof(objectAsset*));
		strings = assetToStrings(mapFile, OBJECT, 1);
		returnAssets->objectAssets[0] = stringsToObject(strings);
		destroyStrings(strings, OBJECT);
	}
	if(countObjects > 1) {
		returnAssets->objectAssets = calloc(countObjects, sizeof(objectAsset*));
		for(i = 0;  i < countObjects; i++) {
			strings = assetToStrings(mapFile, OBJECT, i+1);
			//returnAssets->objectAssets[i] = calloc(1, sizeof(objectAsset));
			returnAssets->objectAssets[i] = stringsToObject(strings);
			destroyStrings(strings, OBJECT);
		}
	}

	if(countCharacters == 1) {
		returnAssets->characterAssets = calloc(1, sizeof(characterAsset*));
		strings = assetToStrings(mapFile, CHARACTER, 1);
		returnAssets->characterAssets[0] = stringsToCharacter(strings);
		destroyStrings(strings, CHARACTER);
	}

	if(countCharacters > 1) {
		returnAssets->characterAssets = calloc(countCharacters, sizeof(characterAsset*));
		for(i = 0; i < countCharacters; i++) {
			strings = assetToStrings(mapFile, CHARACTER, i+1);
			returnAssets->characterAssets[i] = stringsToCharacter(strings);
			destroyStrings(strings, CHARACTER);

		}

	}
	if(countAnimations == 1)  {
		returnAssets->animationAssets = calloc(1, sizeof(Animation*));
		strings = assetToStrings(mapFile, ANIMATIONFIELDCOUNT, 1);
		returnAssets->animationAssets[0] = stringsToAnimation(strings);
		destroyStrings(strings, ANIMATIONFIELDCOUNT);
	}
	if(countAnimations > 1) {
		returnAssets->animationAssets = calloc(countAnimations, sizeof(Animation *));
		for(i = 0; i < countAnimations; i++) {
			strings = assetToStrings(mapFile, ANIMATIONFIELDCOUNT, i+1);
			returnAssets->animationAssets[i] = stringsToAnimation(strings);
			destroyStrings(strings, ANIMATIONFIELDCOUNT);
		}
	}




	return(returnAssets);
}

void destroyTileAsset(tileAsset *asset) {
	UnloadTexture(asset->tile);
	free(asset);
}

void destroyObjectAsset(objectAsset *asset) {
	UnloadTexture(asset->tile);
	if(asset->collisiontype != NULL) {
		free(asset->collisiontype);
	}
	if(asset->nextmap != NULL) {
		free(asset->nextmap);
	}
	if(asset->itemId != NULL) {
		free(asset->itemId);
	}
	if(asset->texturePath != NULL) {
		free(asset->texturePath);
	}
	free(asset);
}

void destroyCharacterAsset(characterAsset *asset) {
	UnloadTexture(asset->tile);
	free(asset);
}

void destroyAnimationAsset(Animation *asset) {
	UnloadTexture(asset->tile);
	if(asset->collisiontype != NULL)
		free(asset->collisiontype);
	if(asset->nextmap != NULL)
		free(asset->nextmap);
	if(asset->interacttext != NULL)
		free(asset->interacttext);
	free(asset);
}




void destroyMapAssets(mapAssets *assets, mapFileContents *mapFile) {

	int i;
	if(assets->mapTiles) {
		for(i = 0; i < mapFile->fileTileCount; i++) {
			if(assets->mapTiles[i]) {
				destroyTileAsset(assets->mapTiles[i]);
			}
		}

		free(assets->mapTiles);
	}

	if(assets->objectAssets) {
		for(i = 0; i < mapFile->fileObjectCount; i++) {
			if(assets->objectAssets[i]) {
				destroyObjectAsset(assets->objectAssets[i]);
			}
		}
		free(assets->objectAssets);
	}

	if(assets->characterAssets) {
		for(i = 0; i < mapFile->fileCharacterCount; i++) {
			if(assets->characterAssets[i]) {
				destroyCharacterAsset(assets->characterAssets[i]);
			}
		}
		free(assets->characterAssets);
	}
	if(assets->animationAssets) {
		for(i = 0; i < mapFile->fileAnimationCount; i++) {
			if(assets->animationAssets[i]) {
				destroyAnimationAsset(assets->animationAssets[i]);
			}
		}
		free(assets->animationAssets);

	}
	free(assets);

}



mapFileContents *mapFile(char *mapName) {

	mapFileContents *returnStruct = malloc(1 * sizeof(mapFileContents));
	if(returnStruct == NULL) {
		printf("Failed to malloc returnStruct for mapFileContents\n%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	char filePath[256];
	snprintf(filePath,sizeof(filePath),"src/maps/%s", mapName);
	//strncpy(filePath, "src/maps/home_map_with_assets.txt", (int) strlen("src/maps/home_map_with_assets.txt")+1); //for testing, remove src/maps/... and just use filename
	//strncpy(filePath,"src/maps/%s",(int) sizeof(filePath));
	FILE *fp = fopen(filePath, "r");
	if(fp == NULL) {
		printf("failed to open mapfile: %s: IN FILEPATH: %s\n", mapName, filePath);
		free(returnStruct);
		exit(EXIT_FAILURE);
	}
	int c;
	char line[600];
	int lineCount = 0;
	int i;
	size_t lineLength = 0;

	while((c = fgetc(fp))!=EOF) {
		if(c == '\n') 
			lineCount++;
	}
	char **returnFile = calloc(lineCount, sizeof(char*));
	if(returnFile == NULL) {
		printf("Failed to malloc map file in function char **fileContents\n%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	rewind(fp);
	int tileCount = 0;
	int objectCount = 0;
	int characterCount = 0;
	int animationCount = 0;

	for(i = 0; i < lineCount; i++) {
		fgets(line, 600, fp);
		lineLength = strlen(line);
		returnFile[i] = calloc(lineLength+1, sizeof(char));
		strncpy(returnFile[i], line, lineLength-1);
		returnFile[i][lineLength - 1] = '\0';
		if(strncmp(returnFile[i], "[tile]", lineLength) == 0) {
			// PRINT LINE HERE FOR TESTING printf("%s\n", line);
			tileCount++;
		}
		else if(strncmp(returnFile[i], "[object]", 8) == 0) 
			objectCount++;
		else if(strncmp(returnFile[i], "[character]", 11) == 0)
			characterCount++;
		else if(strncmp(returnFile[i], "[animation]", 11) == 0)
			animationCount++;

	}



	fclose(fp);


	returnStruct->fileContents = returnFile;
	returnStruct->fileLineCount = lineCount;
	returnStruct->fileTileCount = tileCount;
	returnStruct->fileObjectCount = objectCount;
	returnStruct->fileCharacterCount = characterCount;
	returnStruct->fileAnimationCount = animationCount;

	return returnStruct;

}

void destroyMapFile(mapFileContents *mapConts) {
	int i;
	for(i = 0; i < mapConts->fileLineCount; i++) {
		free(mapConts->fileContents[i]);
	}
	free(mapConts->fileContents);
	free(mapConts);

}

void destroyStrings(char **strings, int type) {
	int count;
	if(type == TILE) {
		count = TILEFIELDS;
	}
	if(type == OBJECT) {
		count = OBJECTFIELDS;
	}
	if(type == CHARACTER) {
		count = CHARACTERFIELDS;
	}
	if(type == ANIMATIONFIELDCOUNT) {
		count = ANIMATIONFIELDS;
	}
	for(int i = 0; i < count; i++) {
		free(strings[i]);
	}
	free(strings);
}

tileAsset *stringsToTile(char **strings) {
	tileAsset *returnTile = calloc(1, sizeof(tileAsset));
	returnTile->tile = LoadTexture(strings[2]);

	returnTile->sourceRec = 
		(Rectangle) { atof(strings[3]), 
			atof(strings[4]), 
			atof(strings[5]),
			atof(strings[6]) };
	returnTile->tileSize = atoi(strings[7]);
	returnTile->map_width = atoi(strings[8]);
	returnTile->map_height = atoi(strings[9]);
	returnTile->origin = 
		(Vector2) { atof(strings[10]), atof(strings[11]) };
	returnTile->scale = atof(strings[12]);
	returnTile->rotation = atoi(strings[13]);

	return returnTile;

}



objectAsset *stringsToObject(char **strings) {
	objectAsset *returnObject = calloc(1, sizeof(objectAsset));
	strcpy(returnObject->name, strings[1]); 
	returnObject->tile = LoadTexture(strings[2]);

	returnObject->sourceRec = 
		(Rectangle) { atof(strings[3]), 
			atof(strings[4]), 
			atof(strings[5]),
			atof(strings[6]) };
	returnObject->destRec = 
		(Rectangle) { atof(strings[7]), 
			atof(strings[8]), 
			atof(strings[9]),
			atof(strings[10]) };
	returnObject->origin = (Vector2) {atof(strings[11]), atof(strings[12]) };
	returnObject->scale = atof(strings[13]);
	returnObject->rotation = atoi(strings[14]);
	returnObject->collision = atoi(strings[15]);
	returnObject->collisiontype = calloc(strlen(strings[16])+1, sizeof(char));
	strncpy(returnObject->collisiontype, strings[16], strlen(strings[16]));
	returnObject->nextmap = calloc(strlen(strings[17])+1, sizeof(char));
	strncpy(returnObject->nextmap, strings[17], strlen(strings[17]));
	returnObject->nextmapspawnx = atof(strings[18]);
	returnObject->nextmapspawny = atof(strings[19]);
	//returnObject->interacttext = atof(string[20]); We don't need this since this gets done in dialogue
	returnObject->itemId = calloc(strlen(strings[21]) + 1, sizeof(char));
	printf("In stringstoobject: strings[21]: %s\n", strings[21]);
	strcpy(returnObject->itemId, strings[21]);
	returnObject->itemId[strlen(strings[21])] = '\0';
	printf("returnobject->itemId in stringstoobject: %s\n", returnObject->itemId);
	returnObject->texturePath = calloc(strlen(strings[2]) + 1, sizeof(char));
	//strncpy(returnObject->texturePath, strings[2], strlen(strings[2]));
	strcpy(returnObject->texturePath, strings[2]);
	returnObject->texturePath[strlen(returnObject->texturePath)] = '\0';
	returnObject->collisionRec = 
		(Rectangle) { atof(strings[22]),
			atof(strings[23]),
			atof(strings[24]),
			atof(strings[25]) };





	return returnObject;

}

characterAsset *stringsToCharacter(char **strings) {
	characterAsset *returnCharacter = calloc(1, sizeof(characterAsset));
	returnCharacter->tile = LoadTexture(strings[2]);

	returnCharacter->sourceRec = 
		(Rectangle) { atof(strings[3]), 
			atof(strings[4]), 
			atof(strings[5]),
			atof(strings[6]) };
	returnCharacter->destRec = 
		(Rectangle) { atof(strings[7]), 
			atof(strings[8]), 
			atof(strings[9]),
			atof(strings[10]) };
	returnCharacter->origin = (Vector2) {atof(strings[11]), atof(strings[12]) };
	returnCharacter->scale = atof(strings[13]);
	returnCharacter->rotation = atoi(strings[14]);


	return returnCharacter;

}

Animation *stringsToAnimation(char **strings) {
	Animation *returnAnimation = calloc(1, sizeof(Animation));
	returnAnimation->tile = LoadTexture(strings[2]);
	returnAnimation->numFramesPerRow = atoi(strings[3]);
	returnAnimation->frameWidth = atof(strings[4]);
	returnAnimation->frameHeight = atof(strings[5]);
	returnAnimation->first = atoi(strings[6]);
	returnAnimation->last = atoi(strings[7]);
	returnAnimation->cur = atoi(strings[8]);
	returnAnimation->speed = atof(strings[9]);
	returnAnimation->duration_left = atof(strings[10]);
	returnAnimation->destRec = 
		(Rectangle) {atof(strings[11]),
			atof(strings[12]),
			atof(strings[13]),
			atof(strings[14]) };
	returnAnimation->origin = (Vector2) {atof(strings[15]), atof(strings[16]) };
	returnAnimation->scale = atof(strings[17]);
	returnAnimation->rotation = atoi(strings[18]);
	returnAnimation->collision = atoi(strings[19]);
	returnAnimation->collisiontype = calloc(strlen(strings[20])+1, sizeof(char));
	strncpy(returnAnimation->collisiontype, strings[20], strlen(strings[20]));
	returnAnimation->nextmap = calloc(strlen(strings[21])+1, sizeof(char));
	strncpy(returnAnimation->nextmap, strings[21], strlen(strings[21]));
	returnAnimation->nextmapspawnx = atof(strings[22]);
	returnAnimation->nextmapspawny = atof(strings[23]);
	returnAnimation->interacttext = calloc(strlen(strings[24])+1, sizeof(char));
	strncpy(returnAnimation->interacttext, strings[24], strlen(strings[24]));
	returnAnimation->collisionRec = 
		(Rectangle) {atof(strings[25]), 
			atof(strings[26]),
			atof(strings[27]),
			atof(strings[28])
		};



	return returnAnimation;
}


void drawTile(tileAsset *asset) {
	int tilesWide = (int)(asset->sourceRec.width / asset->tileSize);
	int tilesHigh = (int)(asset->sourceRec.height / asset->tileSize);

	int y, x, tileX, tileY;
	for(y = 0; y < asset->map_height; y++) {
		for(x = 0; x < asset->map_width; x++) {
			tileX = x % tilesWide;
			tileY = y % tilesHigh;
			Rectangle tileRec = {
				asset->sourceRec.x + tileX * asset->tileSize, 
				asset->sourceRec.y + tileY * asset->tileSize,
				asset->tileSize, 
				asset->tileSize 
			};

			Rectangle destRec = {
				asset->origin.x + x * asset->tileSize * asset->scale, 
				asset->origin.y + y * asset->tileSize * asset->scale, 
				asset->tileSize * asset->scale, 
				asset->tileSize * asset->scale 
			};
			DrawTexturePro(asset->tile, tileRec, destRec, (Vector2) { 0, 0}, asset->rotation, WHITE);
		}
	}
}

void drawObject(objectAsset *asset) {

	DrawTexturePro(asset->tile, 
			asset->sourceRec,
			asset->destRec,
			asset->origin, 
			asset->rotation,
			WHITE);
}

void drawCharacter(characterAsset *asset) {

	DrawTexturePro(asset->tile, 
			asset->sourceRec,
			asset->destRec,
			asset->origin, 
			asset->rotation,
			WHITE);
}


Rectangle animationFrame(Animation *self, int numFramesPerRow, float frameWidth, float frameHeight) {
	int x = (self->cur % numFramesPerRow) * frameWidth;
	int y = (self->cur / numFramesPerRow) * frameHeight;
	return (Rectangle) {
		.x = (float)x,
		.y = (float)y,
		.width = frameWidth,
		.height = frameHeight
	};
}

void animationUpdate(Animation *self) {

	float dt = GetFrameTime();
	self->duration_left -= dt;

	if(self->duration_left <= 0.0) {
		self->duration_left = self->speed;
		self->cur++;
		if(self->cur > self->last) {
			self->cur = self->first;
		}

	}

}

void drawAnimation(Animation *asset) {
	animationUpdate(asset);
	Rectangle animFrame;
	animFrame = animationFrame(asset, asset->numFramesPerRow, asset->frameWidth, asset->frameHeight);
	DrawTexturePro(asset->tile, 
			animFrame,
			asset->destRec, 
			asset->origin, 
			asset->rotation, 
			WHITE);

}






void drawMap(mapAssets *assets, mapFileContents *mapName, mapItemPickedUpTracker *pickedUpItems) { //we'll add the mapItemtracker check in here
	int i, j;
	if(mapName->fileTileCount > 1) {
		for(i = 0; i < mapName->fileTileCount; i++) {
			drawTile(assets->mapTiles[i]);
		}
	}
	if(mapName->fileTileCount == 1) {
		drawTile(assets->mapTiles[0]);
	}

	if(mapName->fileObjectCount > 1) {
		for(i = 0; i < mapName->fileObjectCount; i++) {
			for(j = 0; j < pickedUpItems->numItems; j++) {
				if(strcmp(pickedUpItems->mapItemsPickedUp[j], assets->objectAssets[i]->itemId) == 0 && pickedUpItems->numItems > 0)
				{
					assets->objectAssets[i]->collision = 0;
					break;
				}
			}
			if(j == pickedUpItems->numItems)
				drawObject(assets->objectAssets[i]);
		}
	}
	if(mapName->fileObjectCount == 1) {
		for(j = 0; j < pickedUpItems->numItems; j++) {
			if(strcmp(pickedUpItems->mapItemsPickedUp[j], assets->objectAssets[0]->itemId) == 0
					&& pickedUpItems->numItems > 0)
			{
				assets->objectAssets[0]->collision = 0;
				break;
			}
			else if(j == pickedUpItems->numItems)
			{
				drawObject(assets->objectAssets[0]);
			}
		}
	}
	if(mapName->fileCharacterCount > 1) {
		for(i = 0; i < mapName->fileCharacterCount; i++) {
			drawCharacter(assets->characterAssets[i]);
		}
	}
	if(mapName->fileCharacterCount == 1) {
		drawCharacter(assets->characterAssets[0]);
	}
	if(mapName->fileAnimationCount > 1) {
		for(i = 0; i < mapName->fileAnimationCount; i++) {
			drawAnimation(assets->animationAssets[i]);
		}
	}
	if(mapName->fileAnimationCount == 1) {
		drawAnimation(assets->animationAssets[0]);
	}



}



void(*destroyMapAssetsPtr)(mapAssets *assets, mapFileContents *mapName)=&destroyMapAssets;
void(*destroyMapFilePtr)(mapFileContents *mapName) = &destroyMapFile;
mapAssets *(*assetsToRenderPtr)(mapFileContents *mapName) = &assetsToRender;







