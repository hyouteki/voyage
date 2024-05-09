#ifndef VOYAGE_BUTTON_H_
#define VOYAGE_BUTTON_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "colors.h"

#define Button_Font GetFontDefault()
#define Button_FontSize 24
#define Button_TextSpacing 3
#define Button_HOffset 10
#define Button_VOffset 10

typedef struct ButtonOptions {
	int centerText;
	Color bgColor;
	Color fgColor;
	Color border;
} ButtonOptions;

typedef struct Button {
	Vector2 pos;
	int width;
	char *text;
	ButtonOptions options;
	int (*onClick)();
} Button;

#define ButtonDefaultOptions ((ButtonOptions) \
		{.centerText=1, .bgColor=Voyage_LightGrey, .fgColor=Voyage_DarkGrey, \
		 .border=Voyage_DarkGrey})

// TODO: omiting onClick action for now  
Button Button_Init(Vector2, int, char *);
void Button_SetOptions(Button *, ButtonOptions);
void Button_Resize(Button *, int);
Vector2 Button_Size(Button);
void Button_Draw(Button);

Button Button_Init(Vector2 pos, int width, char *text) {
	return (Button){.pos = pos, .width=width, .text=text,
					.options=ButtonDefaultOptions};
}

void Button_SetOptions(Button *button, ButtonOptions options) {
	button->options = options;
}

void Button_Resize(Button *button, int width) {
	button->width = width;
}

Vector2 Button_Size(Button button) {
	Vector2 textSize = MeasureTextEx(Button_Font, button.text,
									 Button_FontSize, Button_TextSpacing);
	return (Vector2){button.width, textSize.y+2*Button_VOffset};
}

void Button_Draw(Button button) {
	Vector2 textSize = MeasureTextEx(Button_Font, button.text,
									 Button_FontSize, Button_TextSpacing);
	Vector2 textPos = (Vector2){button.pos.x+Button_HOffset,
								button.pos.y+Button_VOffset};
	if (button.options.centerText) {
		textPos.x = button.pos.x+(button.width-textSize.x)/2;
	}
	Rectangle container = (Rectangle){button.pos.x, button.pos.y,
									  button.width, textSize.y+2*Button_VOffset};
	DrawRectangleRec(container, button.options.bgColor);
	DrawRectangleLinesEx(container, 5, button.options.border); 
	DrawTextEx(Button_Font, button.text, textPos, Button_FontSize,
			   Button_TextSpacing, button.options.fgColor);
}

#endif // VOYAGE_BUTTON_H_
