#include "raylib.h"
#include "dialogue.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../../src/config/config.h"
#include <dirent.h>
#include <math.h>




void drawDialogueBox(char *dialogueText) //This should probably change so it takes as argument the dialogue struct
{


	Rectangle textBox;
	textBox = (Rectangle) { SCREEN_WIDTH/2.0f - 600.0f,
		SCREEN_HEIGHT/2.0f+100,
		1200.0f,
		SCREEN_HEIGHT/2.0-150.0f
	};

	DrawRectangleRec(textBox, BLACK);
	DrawRectangleLinesEx(textBox, 6.0f, WHITE);
	DrawText(dialogueText, textBox.x+25.0f,textBox.y+50,40,WHITE);

}


DialogueParsed *curDialogue (char *dialogueFile) //Returns a pointer to struct to a dialogue
{
	DialogueParsed *returnStruct = malloc(1 * sizeof(DialogueParsed));
	char *dialoguePtr = dialogueFile;
	int newLineCounter = 0;
	//int charCounter = 0;
	//size_t dialogueLength;
	int pageCount;
	while(*dialoguePtr){

		if(*dialoguePtr == '\n') {
			newLineCounter++;
		}
		dialoguePtr++;
		//charCounter++;
	}
	pageCount = (int) ceil((newLineCounter / 9.0));


	char *pageStart;
	int length;
	if(pageCount == 1)
	{
		length = strlen(dialogueFile);
		printf("length of dialoguefile is: %d\n", length);
		//returnArray = malloc(2 * sizeof(char*));
		returnStruct->parsedDialogue = malloc(2 * sizeof(char*));
		returnStruct->parsedDialogue[0] = malloc((length+1) * sizeof(char));
		memcpy(returnStruct->parsedDialogue[0], dialogueFile, length);
		returnStruct->parsedDialogue[0][length] = '\0';
		returnStruct->parsedDialogue[1] = NULL;

	}
	else { //INSTEAD OF WHATS BELOW JUST CREATE AN ANCHOR SYSTEM TO END OF STRING AND CHANGE TO MEMCPY
		dialoguePtr = dialogueFile;
		int i;
		returnStruct->parsedDialogue = malloc((pageCount + 1) * sizeof(char*));

		for(i = 0; i < pageCount; i++) {
			pageStart = dialoguePtr;
			newLineCounter = 0;
			while(*dialoguePtr) {
				if(*dialoguePtr == '\n') {
					newLineCounter++;
					if(newLineCounter == 9)
					{
						length = dialoguePtr - pageStart;
						printf("This is i in dialogue else statement: %d\n", i);
						returnStruct->parsedDialogue[i] = malloc((length+1) * sizeof(char));
						memcpy(returnStruct->parsedDialogue[i], pageStart, length);
						returnStruct->parsedDialogue[i][length] = '\0';
						newLineCounter = 0;
						dialoguePtr++;
						break;

					}
				}
				if(*dialoguePtr == '\0') {
					length = dialoguePtr - pageStart;
					returnStruct->parsedDialogue[i] = malloc((length+1) * sizeof(char));
					memcpy(returnStruct->parsedDialogue[i], pageStart, length);
					returnStruct->parsedDialogue[i][length] = '\0';
					break;
				}
				dialoguePtr++;
			}
		}

		length = dialoguePtr - pageStart;
		if(length > 0 && newLineCounter % 9 != 0)
		{
			returnStruct->parsedDialogue[pageCount-1] = malloc((length+1) * sizeof(char));
			memcpy(returnStruct->parsedDialogue[pageCount-1], pageStart, length);
			returnStruct->parsedDialogue[pageCount-1][length] = '\0';
		}
		returnStruct->parsedDialogue[pageCount] = NULL;
	}


	returnStruct->pageCount = pageCount;


	return returnStruct;

}

void destroyDialogueStruct(DialogueParsed *dialogueStruct)
{
	int i = 0;
	if(dialogueStruct->pageCount == 1)
	{
		free(dialogueStruct->parsedDialogue[0]);
		free(dialogueStruct->parsedDialogue);
	}
	else
	{
		while(dialogueStruct->parsedDialogue[i] != NULL)
		{
			free(dialogueStruct->parsedDialogue[i]);
			i++;

		}
		free(dialogueStruct->parsedDialogue);
	}
	free(dialogueStruct);
}


void destroyDialogueFile(char *dialogueFile) {
	free(dialogueFile);
}



char *readDialogueFile(char *mapName, char *objectName) {
	char dialogueFolder[512];
	char dialogueFile[1024];
	snprintf(dialogueFolder, sizeof(dialogueFolder), "src/dialogue/%s", mapName);
	dialogueFolder[strcspn(dialogueFolder, ".")] = '\0'; //REMEMBER HERE THAT IF PERIOD EXISTS ANYWHERE ELSE IT WILL BREAK
	snprintf(dialogueFile, sizeof(dialogueFile), "%s/%s.txt", dialogueFolder, objectName);

	FILE *fp = fopen(dialogueFile, "r");
	if(fp == NULL) 
	{
		printf("dialoguefile not found, exiting\n");
		exit(EXIT_FAILURE);
	}
	int c;
	long long int textLength = 0;

	fseek(fp, 0, SEEK_END);
	textLength = ftell(fp);
	rewind(fp);

	char *returnString = calloc(textLength+1, sizeof(char));
	int i = 0;
	while((c = fgetc(fp)) != EOF) {
		returnString[i] = c;
		i++;
	}
	returnString[i] = '\0';

	fclose(fp);
	return(returnString);
}



