#ifndef DIALOGUE_H
#define DIALOGUE_H
#include <stdio.h>
#include "../types.h"



char *getFileText(const char *fileName);
dialogueBox *initDialogueBox(const char *fileName);
void destroyDialogueFile(char *dialogueFile);
void drawDialogueBox(char *dialogueFile);
void updateDialogueBox( dialogueBox *dialogue, float delta);
char *getDialogueFolder(char *mapName);
char *readDialogueFile(char *mapName, char *objectName);
char **parseDialogueFile(char *dialogue);
void destroyDialogueStruct(DialogueParsed *dialogueStruct);
DialogueParsed *curDialogue(char *dialogueFile);


#endif
