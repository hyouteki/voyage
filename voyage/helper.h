#ifndef VOYAGE_HELPER_H_
#define VOYAGE_HELPER_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "elements.h"

#define Vector2Dummy ((Vector2){0, 0})
#define Button_EleInit(...) ((Element){.type=BUTTON, .button=Button_Init(Vector2Dummy, 0, __VA_ARGS__)})
#define ImageContainer_EleInit(...) ((Element){.type=IMAGE_CONTAINER,	\
											   .imageContainer=ImageContainer_Init(Vector2Dummy, \
																				   Vector2Dummy, __VA_ARGS__)})
#define Label_EleInit(...) ((Element){.type=LABEL, .label=Label_Init(Vector2Dummy, 0, __VA_ARGS__)})
#define Voyage_Error(message) ({printf("Error: %s\n", message); exit(1);})
#define Voyage_ArraySize(array) (sizeof(array)/sizeof(array[0]))
#define Voyage_ScreenDimen ((Vector2){.x=GetScreenWidth(), .y=GetScreenHeight()})
#define Voyage_Vector2Equal(vec1, vec2) ((int)vec1.x == (int)vec2.x && (int)vec1.y == (int)vec2.y)

typedef unsigned int u32;

void Voyage_Setup(u32, u32, u32, char *, u32);
int Voyage_CheckPointRecCollision(Vector2, Vector2, Vector2);
float voyage_MouseWheelMove();

void Voyage_Setup(u32 width, u32 height, u32 fps, char *name, u32 flags) {
	SetConfigFlags(flags);
	InitWindow(width, height, name);
	SetTargetFPS(fps);
}

int Voyage_CheckPointRecCollision(Vector2 pointPos, Vector2 recPos, Vector2 recSize) {
	return (int)recPos.x <= (int)pointPos.x && (int)pointPos.x <= (int)recPos.x+(int)recSize.x && \
		(int)recPos.y <= (int)pointPos.y && (int)pointPos.y <= (int)recPos.y+(int)recSize.y;
}

float Voyage_MouseWheelMove() {
	float x = GetMouseWheelMove();
	if (x != 0) x = x > 0? 1: -1;
	return x;
}

#endif // VOYAGE_HELPER_H_
