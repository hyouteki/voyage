#ifndef VOYAGE_INPUT_H_
#define VOYAGE_INPUT_H_

#include "colors.h"
#include "helper.h"

typedef struct InputOptions {
	Color bgColor;
	Color fgColor;
	Color border;
	Color accent;
	Font font;
	int fontSize;
	int maxChars;
	int textSpacing;
	int hOffset;
	int vOffset;
	int borderWidth;
} InputOptions;

typedef struct Input {
	Vector2 pos;
	int width;
	char *text;
	int cursorIndex;
	enum Input_State {
		Input_State_Active,
		Input_State_Inactive
	} state;
	InputOptions options;
	void (*onEnter)(struct Input);
} Input;
 
#define InputDefaultOptions ((InputOptions)								\
							 {.bgColor=Voyage_Black,  .fgColor=Voyage_White, \
							  .border=Voyage_LightGrey, .accent=Voyage_White, \
							  .font=GetFontDefault(), .fontSize=24, .maxChars=50, \
							  .textSpacing=3, .hOffset=10, .vOffset=10, .borderWidth=2})

void InputDefaultOnEnter(Input input) {
	printf("Log: Input(%s) entered\n", input.text);
}

Input Input_Init(Vector2, int, char *, void (*)(Input));
void Input_SetOptions(Input *, InputOptions);
void Input_Resize(Input *, int);
void Input_ResizeReposition(Input *, Vector2, int);
Vector2 Input_Size(Input);
void Input_Draw(Input);

Input Input_Init(Vector2 pos, int width, char *initialText, void (*onEnter)(Input)) {
	char *text = (char *)malloc(sizeof(char)*(InputDefaultOptions.maxChars+1));
	memcpy(text, initialText, InputDefaultOptions.maxChars);
	text[strlen(text)] = '_';
	text[InputDefaultOptions.maxChars] = 0;
	return (Input){.pos = pos, .width=width, .text=text, .options=InputDefaultOptions,
				   .onEnter = onEnter? onEnter: &InputDefaultOnEnter, .cursorIndex=0,
				   .state = Input_State_Inactive};
}

void Input_SetOptions(Input *input, InputOptions options) {
	input->options = options;
}

void Input_Resize(Input *input, int width) {
	input->width = width;
}

void Input_ResizeReposition(Input *input, Vector2 pos, int width) {
	input->pos = pos;
	input->width = width;
}

Vector2 Input_Size(Input input) {
	return (Vector2){input.width, Voyage_FontSize(input.options).y+2*input.options.vOffset};
}

void Input_TypeEventListener(Input *input) {
	Rectangle container = (Rectangle){.x=input->pos.x, .y=input->pos.y, .width=input->width,
									  .height=Voyage_FontSize(input->options).y+2*input->options.vOffset};
	input->state = Input_State_Inactive;
	if (CheckCollisionPointRec(GetMousePosition(), container)) {
		input->state = Input_State_Active;
		int key = GetCharPressed();
		if (GetKeyPressed() == 257) {
			input->text[input->cursorIndex] = 0;
			input->onEnter(*input);
			input->cursorIndex = 0;
			input->text[input->cursorIndex] = '_';
			input->text[input->cursorIndex+1] = 0;
		}
		while (key > 0) {
			if (key >= 32 && key <= 125 && input->cursorIndex < input->options.maxChars) {
				input->text[input->cursorIndex++] = key;
				if (input->cursorIndex < input->options.maxChars) {
					input->text[input->cursorIndex] = '_';
					input->text[input->cursorIndex+1] = 0;
				} else input->text[input->cursorIndex] = 0;
			}
			key = GetCharPressed();
		}
		if (IsKeyPressed(KEY_BACKSPACE) && input->cursorIndex > 0) {
			input->text[input->cursorIndex] = 0;
			input->text[--input->cursorIndex] = '_';
		}
	}
}

void Input_Draw(Input input) {
	Vector2 textPos = (Vector2){input.pos.x+input.options.hOffset,
								input.pos.y+input.options.vOffset};
	Rectangle container = (Rectangle){.x=input.pos.x, .y=input.pos.y, .width=input.width,
									  .height=Voyage_FontSize(input.options).y+2*input.options.vOffset};

	SetMouseCursor(input.state == Input_State_Active? MOUSE_CURSOR_IBEAM: MOUSE_CURSOR_DEFAULT);
	Color border = input.state == Input_State_Active? input.options.accent: input.options.border;
	
	DrawRectangleRec(container, input.options.bgColor);
	DrawRectangleLinesEx(container, input.options.borderWidth, border);
	DrawTextEx(input.options.font, input.text, textPos, input.options.fontSize,
			   input.options.textSpacing, input.options.fgColor);
}

#endif // VOYAGE_INPUT_H_
