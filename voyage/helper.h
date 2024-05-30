#ifndef VOYAGE_HELPER_H_
#define VOYAGE_HELPER_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "elements.h"

#define Vector2Dummy ((Vector2){0, 0})
#define Button_EleInit(...) ((Element){.type=BUTTON, .button=Button_Init(Vector2Dummy, 0, __VA_ARGS__)})
#define ImageContainer_EleInit(...) ((Element){.type=IMAGE_CONTAINER,	\
											   .imageContainer=ImageContainer_Init(__VA_ARGS__)})
#define Label_EleInit(...) ((Element){.type=LABEL, .label=Label_Init(Vector2Dummy, 0, __VA_ARGS__)})
#define Voyage_Error(message) ({printf("Error: %s\n", message); exit(1);})
#define Voyage_ArraySize(array) (sizeof(array)/sizeof(array[0]))
#define Voyage_ScreenDimen ((Vector2){.x=GetScreenWidth(), .y=GetScreenHeight()})

typedef unsigned int u32;

void Voyage_Setup(u32, u32, u32, char *, u32);

void Voyage_Setup(u32 width, u32 height, u32 fps, char *name, u32 flags) {
	SetConfigFlags(flags);
	InitWindow(width, height, name);
	SetTargetFPS(fps);
}

#endif // VOYAGE_HELPER_H_
