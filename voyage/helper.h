#ifndef VOYAGE_HELPER_H_
#define VOYAGE_HELPER_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "elements.h"

#define Vector2Dummy ((Vector2){0, 0})
#define Button_EleInit(...) ((Element){.type=BUTTON, .button=Button_Init(__VA_ARGS__)})
#define ImageContainer_EleInit(...) ((Element){.type=IMAGE_CONTAINER,	\
											   .imageContainer=ImageContainer_Init(__VA_ARGS__)})
#define Label_EleInit(...) ((Element){.type=LABEL, .label=Label_Init(__VA_ARGS__)})
#define Voyage_Error(message) ({printf("Error: %s\n", message); exit(1);})
#define Voyage_ArraySize(array) (sizeof(array)/sizeof(array[0]))

typedef unsigned int u32;

#endif // VOYAGE_HELPER_H_
