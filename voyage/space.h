#ifndef VOYAGE_SPACE_H_
#define VOYAGE_SPACE_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "colors.h"
#include "helper.h"

typedef struct SpaceOptions {
	Color bgColor;
	u32 hOffset;
	u32 transparent;
} SpaceOptions;

typedef struct Space {
	Vector2 pos;
	u32 width;
	u32 height;
	SpaceOptions options;
} Space;

#define SpaceDefaultOptions ((SpaceOptions){.bgColor=Voyage_LightGrey, .hOffset=10, .transparent=1})

Space Space_Init(Vector2, u32, u32);
void Space_SetOptions(Space *, SpaceOptions);
void Space_Resize(Space *, u32);
void Space_Reposition(Space *, Vector2);
void Space_ResizeReposition(Space *, Vector2, u32);
Vector2 Space_Size(Space);
void Space_Draw(Space);

Space Space_Init(Vector2 pos, u32 width, u32 height) {
	return (Space){.pos=pos, .width=width, .height=height, .options=SpaceDefaultOptions};
}

void Space_SetOptions(Space *space, SpaceOptions options) {
	space->options = options;
}

void Space_Resize(Space *space, u32 width) {
	space->width = width;
}

void Space_Reposition(Space *space, Vector2 pos) {
	space->pos = pos;
}

void Space_ResizeReposition(Space *space, Vector2 pos, u32 width) {
	space->pos = pos;
	space->width = width;
}

Vector2 Space_Size(Space space) {
	return (Vector2){.x=space.width, .y=space.height};
}

void Space_Draw(Space space) {
	if (space.options.transparent) return;
	DrawRectangleRec((Rectangle){.x=space.pos.x+space.options.hOffset, .y=space.pos.y,
								 .width=space.width-2*space.options.hOffset, .height=space.height},
		space.options.bgColor);
}

#endif // VOYAGE_SPACE_H_
