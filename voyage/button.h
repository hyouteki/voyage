#ifndef VOYAGE_BUTTON_H_
#define VOYAGE_BUTTON_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"

#define Button_Font GetFontDefault()
#define Button_FontSize 24
#define Button_TextSpacing 3
#define Button_HOffset 10
#define Button_VOffset 10

typedef struct ButtonOptions {
	int centerText;
	Color bgColor;
	Color fgColor;
} ButtonOptions;

typedef struct Button {
	Vector2 pos;
	int width;
	char *text;
	ButtonOptions buttonOptions;
	int (*onClick)();
} Button;

// TODO: omiting onClick action for now  
Button Button_Init(Vector2, int, char *, ButtonOptions);
void Button_Resize(Button *, int);
Vector2 Button_Size(Button);
void Button_Draw(Button);

Button Button_Init(Vector2 pos, int width, char *text,
				   ButtonOptions buttonOptions) {
	return (Button){.pos = pos, .width=width, .text=text,
					.buttonOptions=buttonOptions};
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
	if (button.buttonOptions.centerText) {
		textPos.x = button.pos.x+(button.width-textSize.x)/2;
	}
	Vector2 containerSize = (Vector2){button.width,
									  textSize.y+2*Button_VOffset};
	DrawRectangleV(button.pos, containerSize, button.buttonOptions.bgColor);
	DrawTextEx(Button_Font, button.text, textPos, Button_FontSize,
			   Button_TextSpacing, button.buttonOptions.fgColor);
}

#endif // VOYAGE_BUTTON_H_
