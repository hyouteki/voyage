#ifndef VOYAGE_BUTTON_H_
#define VOYAGE_BUTTON_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "colors.h"

typedef struct ButtonOptions {
	int centerText;
	Color bgColor;
	Color fgColor;
	Color border;
	Font font;
	int fontSize;
	int textSpacing;
	int hOffset;
	int vOffset;
} ButtonOptions;

typedef struct Button {
	Vector2 pos;
	int width;
	char *text;
	ButtonOptions options;
	void (*onClick)();
} Button;
 
#define ButtonDefaultOptions ((ButtonOptions)							\
							  {.centerText=1, .bgColor=Voyage_LightGrey, \
							   .fgColor=Voyage_White, .border=Voyage_DarkGrey, \
							   .font=GetFontDefault(), .fontSize=24, .textSpacing=3, \
							   .hOffset=10, .vOffset=10})
#define ButtonDefaultOnClick() (printf("Log: Button(%s) clicked\n", button.text))

Button Button_Init(Vector2, int, char *, void (*onClick)());
void Button_SetOptions(Button *, ButtonOptions);
void Button_Resize(Button *, int);
void Button_ResizeReposition(Button *, Vector2, int);
Vector2 Button_Size(Button);
void Button_Draw(Button);

Button Button_Init(Vector2 pos, int width, char *text, void (*onClick)()) {
	return (Button){.pos = pos, .width=width, .text=text,
					.options=ButtonDefaultOptions, .onClick = onClick};
}

void Button_SetOptions(Button *button, ButtonOptions options) {
	button->options = options;
}

void Button_Resize(Button *button, int width) {
	button->width = width;
}

void Button_ResizeReposition(Button *button, Vector2 pos, int width) {
	button->pos = pos;
	button->width = width;
}

Vector2 Button_Size(Button button) {
	Vector2 textSize = MeasureTextEx(button.options.font, button.text,
									 button.options.fontSize, button.options.textSpacing);
	return (Vector2){button.width, textSize.y+2*button.options.vOffset};
}

void Button_Draw(Button button) {
	Vector2 textSize = MeasureTextEx(button.options.font, button.text,
									 button.options.fontSize, button.options.textSpacing);
	Vector2 textPos = (Vector2){button.pos.x+button.options.hOffset,
								button.pos.y+button.options.vOffset};
	if (button.options.centerText) {
		textPos.x = button.pos.x+(button.width-textSize.x)/2;
	}
	Rectangle container = (Rectangle){button.pos.x, button.pos.y,
									  button.width, textSize.y+2*button.options.vOffset};
	Vector2 mousePoint = GetMousePosition();
	int state = 0, action = 0;
	if (CheckCollisionPointRec(mousePoint, container)) {
		state = (IsMouseButtonDown(MOUSE_BUTTON_LEFT))? 2: 1; // PRESSED: HOVER
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) action = 1; // CLICK
	}
	else state = 0; // NORMAL
	Color bgColor = button.options.bgColor, fgColor = button.options.fgColor;
	Color border = button.options.border;
	if (state) {
		bgColor = button.options.fgColor;
		fgColor = button.options.bgColor;
		border = button.options.bgColor;
	}
	DrawRectangleRec(container, bgColor);
	DrawRectangleLinesEx(container, 2, border); 
	DrawTextEx(button.options.font, button.text, textPos, button.options.fontSize,
			   button.options.textSpacing, fgColor);
	if (action) {
		if (!button.onClick) ButtonDefaultOnClick();
		else button.onClick();
	}
}

#endif // VOYAGE_BUTTON_H_
