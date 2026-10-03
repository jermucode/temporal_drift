#include <raylib.h>
#include "animations.h"


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



Animation *textToStruct(mapFileContents *mapName) {





}


