#ifndef VOYAGE_BUTTON_H_
#define VOYAGE_BUTTON_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"

typedef struct ButtonOptions {
	int centerText;
} ButtonOptions;

typedef struct Button {
	Vector2 pos;
	int width;
	Color color;
	char *text;
	ButtonOptions buttonOptions;
	int (*onClick)();
} Button;

// TODO: omiting onClick action for now  
Button Button_Init(Vector2, int, Color, char *, ButtonOptions);
void Button_Draw(Button);

Button Button_Init(Vector2 pos, int width, Color color,
				   char *text, ButtonOptions buttonOptions) {
	return (Button){.pos = pos, .width=width, .color=color,
					.text=text, .buttonOptions=buttonOptions};
}

void Button_Draw(Button button) {
	const Font font = GetFontDefault();
	const int fontSize = 24, spacing = 3;
	const int hOffset = 10, vOffset = 10;
	Vector2 textSize = MeasureTextEx(font, button.text, fontSize, spacing);
	Vector2 textPos = (Vector2){button.pos.x+hOffset,
								button.pos.y+vOffset};
	if (button.buttonOptions.centerText) {
		textPos.x = button.pos.x+(button.width-textSize.x)/2;
	}
	Vector2 containerSize = (Vector2){button.width, textSize.y+2*vOffset};
	DrawRectangleV(button.pos, containerSize, button.color);
	DrawTextEx(font, button.text, textPos, fontSize, spacing, WHITE);
}

#endif // VOYAGE_BUTTON_H_
