#ifndef VOYAGE_HELPER_H_
#define VOYAGE_HELPER_H_

#include <stdio.h>
#include <string.h>

#define Vector2Dummy ((Vector2){0, 0})
#define Button_EleInit(...) ((Element){.type=Element_Button, .button=Button_Init(Vector2Dummy, 0, __VA_ARGS__)})
#define ImageContainer_EleInit(...) ((Element){.type=Element_ImageContainer, \
											   .imageContainer=ImageContainer_Init(Vector2Dummy, \
																				   Vector2Dummy, __VA_ARGS__)})
#define Label_EleInit(...) ((Element){.type=Element_Label, .label=Label_Init(Vector2Dummy, 0, __VA_ARGS__)})
#define Quote_EleInit(...) ((Element){.type=Element_Quote, .quote=Quote_Init(Vector2Dummy, 0, __VA_ARGS__)})
#define Space_EleInit(height) ((Element){.type=Element_Space, .space=Space_Init(Vector2Dummy, 0, height)})
#define Input_EleInit(...) ((Element){.type=Element_Input, .input=Input_Init(Vector2Dummy, 0, __VA_ARGS__)})

#define Voyage_Error(message) ({printf("Error: %s\n", message); exit(1);})
#define Voyage_ArraySize(array) (sizeof(array)/sizeof(array[0]))
#define Voyage_ScreenDimen ((Vector2){.x=GetScreenWidth(), .y=GetScreenHeight()})
#define Voyage_Vector2Equal(vec1, vec2) ((int)vec1.x == (int)vec2.x && (int)vec1.y == (int)vec2.y)
#define Voyage_MaxInt(n1, n2) (n1 > n2? n1: n2)
#define Voyage_Min(n1, n2) (n1 < n2? n1: n2)
#define Voyage_FontSize(options) (MeasureTextEx(options.font, "v", options.fontSize, options.textSpacing))

typedef unsigned int u32;

typedef struct FontW {
	char *fontPath;
    Font font;
    int fontSize;
    int textSpacing;
} FontW;

FontW defaultFont;

void Voyage_Setup(u32, u32, u32, char *, u32);
int Voyage_CheckPointRecCollision(Vector2, Vector2, Vector2);
float Voyage_MouseWheelMove();
void Voyage_InitDefaultFont();
Font Voyage_ChangeFontSize(FontW, u32);

void Voyage_Setup(u32 width, u32 height, u32 fps, char *name, u32 flags) {
	SetConfigFlags(flags);
	InitWindow(width, height, name);
	SetTargetFPS(fps);
	/* Voyage_InitDefaultFont("PlayFair.ttf", 32, 1); */
	Voyage_InitDefaultFont("./resources/FiraSans.ttf", 32, 0);
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

void Voyage_InitDefaultFont(char *fontPath, u32 fontSize, u32 textSpacing) {
	defaultFont.fontPath = strdup(fontPath);
    defaultFont.font = LoadFontEx(fontPath, fontSize, NULL, 0);
    defaultFont.fontSize = fontSize;
    defaultFont.textSpacing = textSpacing;
}

Font Voyage_ChangeFontSize(FontW fontW, u32 fontSize) {
    return LoadFontEx(fontW.fontPath, fontSize, NULL, 0);
}

#endif // VOYAGE_HELPER_H_
