#include "raylib.h"
#include "player.h"
#include <stdio.h>


Player initPlayer() {
	Player player;
	player.sprite = LoadTexture("assets/RCCgangCHARspritesV2/chromedandies/png/vince.png");
	//player.sprite = LoadTexture("assets/PVGames_SciFi/SciFi/Preset Characters/$Captain_Male.png");
	player.position = (Vector2){ 300.0f, 400.0f };
	player.speed = 2.0f;
	player.frameWidth = 32.0f;
	player.frameHeight = 32.0f;
	player.sourceRec = (Rectangle){ 
		32.0f, 0.0f, player.frameWidth, player.frameHeight };
	player.destRec = (Rectangle) {
		player.position.x, player.position.y, player.frameWidth*2.0f, player.frameHeight*2.0f };
	player.origin = (Vector2) { player.frameWidth/2.0f, player.frameHeight/2.0f };
	player.direction = FACING_FORWARD;
	player.currentFrame = 1;
	player.animationTimer = 0.0f;
	return player;

}

void updatePlayer(Player *player){
	bool isMoving = false;
	FacingDirection newDirection = player->direction;


	if (IsKeyDown(KEY_RIGHT))
	{
		player->position.x += player->speed;
		newDirection = FACING_RIGHT;
		isMoving = true;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		player->position.x -= player->speed;
		newDirection = FACING_LEFT;
		isMoving = true;
	}
	else if (IsKeyDown(KEY_DOWN)) // Forward is down; Y is drawn down
	{
		player->position.y += player->speed;
		newDirection = FACING_FORWARD;
		isMoving = true;
	}
	else if (IsKeyDown(KEY_UP))
	{
		player->position.y -= player->speed;
		newDirection = FACING_BACKWARD;
		isMoving = true;
	}


	if (isMoving) {
		//printf("direction: %d\n", newDirection);
		player->direction = newDirection;
		player->animationTimer += GetFrameTime();
		if (player->animationTimer >= 0.2f) {
			player->currentFrame = (player->currentFrame == 0) ? 2 : 0; // Toggle walk1 (0) and walk2 (2)
			player->animationTimer -= 0.25f; // Subtract cycle time
			//printf("Moving: Direction=%d, Frame=%d, Timer=%f\n", player->direction, player->currentFrame, player->animationTimer);
		}
	} else {
		if (player->currentFrame != 1) {
			player->currentFrame = 1; // Set to stand only if not already
			player->animationTimer = 0.0f;
			//printf("Idle: Direction=%d, Frame=%d, Timer=%f\n", player->direction, player->currentFrame, player->animationTimer);
		}
	}



	float y = 0.0f;
	switch(player->direction)
	{
		case FACING_FORWARD: y = 0.0f; break;
		case FACING_LEFT: y = 32.0f; break;
		case FACING_RIGHT: y = 64.0f; break;
		case FACING_BACKWARD: y = 96.0f; break;


	}

	player->sourceRec.x = player->currentFrame * player->frameWidth;
	player->sourceRec.y = y;

	player->destRec.x = player->position.x;
	player->destRec.y = player->position.y;


}

void drawPlayer(Player *player, float rotation)
{
	DrawTexturePro(player->sprite,
			player->sourceRec,
			player->destRec,
			player->origin,
			rotation,
			WHITE);
}

