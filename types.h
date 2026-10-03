#ifndef TYPES_H
#define TYPES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// Animation types

/*typedef struct Animation {
	Texture2D tile;
	int numFramesPerRow;
	float frameWidth;
	float frameHeight;
	int first; //first frame
	int last; //last frame
	int cur; //current frame
	float speed; //animation speed
	float duration_left; //time until next frame
} Animation;

*/




// Dialogue types
typedef enum {
	OBJECTDIALOGUE
} dialogueType;

typedef struct {
	char *text;
	char **textLines;
	char *textOfLine;
	bool dialogueIsActive;
	int currentCharIndex;
	size_t numLines;
	size_t linesToUse;
	int currentLine;
	float dialogueWidth;
	float dialogueHeight;
	int boxX;
	int boxY;
	int padding;
	float fontSize;
	float spacing;
	float timer;
} dialogueBox;



typedef struct DialogueParsed {
	int pageCount;
	char **parsedDialogue;

} DialogueParsed;


// Newrenderstructs types:

#define TILEFIELDS 14
#define OBJECTFIELDS 26 //26 now since we added collisionrecs to objects
#define CHARACTERFIELDS 17
#define ANIMATIONFIELDS 29


typedef struct {
	Texture2D tile;
	Rectangle sourceRec;
	int tileSize; // Native tile size in spritesheet (e.g., 16 pixels)
	int map_width; // Number of tiles in x
int map_height; // Number of tiles in y
	Vector2 origin;
	float scale; // Scale factor for rendering (e.g., 2.0 for 32x32 tiles)
	int rotation;
} tileAsset;

typedef struct {
	char name[256];
	Texture2D tile;
	Rectangle sourceRec;
	Rectangle destRec;
	Vector2 origin;
	float scale; // Scale factor for rendering (e.g., 2.0 for 32x32 tiles)
	int rotation;
	int collision;
	char *collisiontype;
	char *nextmap;
	float nextmapspawnx;
	float nextmapspawny;
	char *interacttext;
	char *itemId;
	char *texturePath; // Gets created from tile in stringsToObject
	Rectangle collisionRec;
} objectAsset;

typedef struct {
	Texture2D tile;
	Rectangle sourceRec;
	Rectangle destRec;
	Vector2 origin;
	float scale; // Scale factor for rendering (e.g., 2.0 for 32x32 tiles)
	int rotation;
	int collision;
	char *collisionType;
} characterAsset;

typedef struct Animation {
	char name[256];
	Texture2D tile;
	int numFramesPerRow;
	float frameWidth;
	float frameHeight;
	int first; //first frame
	int last; //last frame
	int cur; //current frame
	float speed; //animation speed
	float duration_left; //time until next frame
	Rectangle destRec;
	Vector2 origin;
	float scale;
	int rotation;
	int collision;
	char *collisiontype;
	char *nextmap;
	float nextmapspawnx;
	float nextmapspawny;
	char *interacttext;
	Rectangle collisionRec;
	
} Animation;

typedef struct {
	char **fileContents;
	int fileLineCount;
	int fileTileCount;
	int fileObjectCount;
	int fileCharacterCount;
	int countSpawnPoints;
	Vector2 *spawnPoints;
	int fileAnimationCount;
} mapFileContents;

typedef struct {
	tileAsset **mapTiles;
	objectAsset **objectAssets;
	characterAsset **characterAssets;
	Animation **animationAssets;
} mapAssets;

typedef struct {
	char **tileAssetStrings;
	char **objectAssetStrings;
	char **characterAssetStrings;
	char **animationAssetStrings;

} mapAssetsFromStrings;

enum stringType {
	TILE, 
	OBJECT, 
	CHARACTER,
	ANIMATIONFIELDCOUNT
	
};


/*
typedef struct mapItemTracker 
{
	char mapName[256];
	objectAsset **objects;
	}
mapItemTracker;
*/

// Array to hold picked up items
//
//
//

#define MAX_INVENTORY 100



typedef struct inventoryItem {
	char *itemId;
	char *itemName;
	char *itemTexturePath;
	Rectangle *sourceRec;

} inventoryItem;

typedef struct playerInventory {
	int itemsInInventory;
	inventoryItem** items;
} playerInventory;

typedef struct mapItemPickedUpTracker {
	char **mapItemsPickedUp;
	int numItems;
} mapItemPickedUpTracker;

// Player
typedef enum {
    FACING_FORWARD,  // Row 1, y=0
    FACING_LEFT,     // Row 2, y=32
    FACING_RIGHT,    // Row 3, y=64
    FACING_BACKWARD  // Row 4, y=96
} FacingDirection;

typedef struct {
    Texture2D sprite;
    float frameWidth;
    float frameHeight;
    Rectangle sourceRec;
    Rectangle destRec;
    Vector2 origin;
    Vector2 position;
    float speed;
    FacingDirection direction; // Current facing direction
    int currentFrame;         // 0=walk1, 1=stand, 2=walk2
    float animationTimer;     // Timer for frame switching
} Player;

#endif
