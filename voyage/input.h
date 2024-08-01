#ifndef VOYAGE_INPUT_H_
#define VOYAGE_INPUT_H_

#include "colors.h"
#include "helper.h"
#include "../cxmlp/node.h"

typedef struct InputOptions {
	Color bgColor;
	Color fgColor;
	Color border;
	Color accent;
	Font font;
	u32 fontSize;
	u32 maxChars;
	u32 textSpacing;
	u32 hOffset;
	u32 vOffset;
	u32 borderWidth;
} InputOptions;

typedef struct Input {
	Vector2 pos;
	u32 width;
	char *text;
	char *id;
	u32 cursorIndex;
	enum Input_State {
		Input_State_Active,
		Input_State_Inactive
	} state;
	InputOptions options;
	void (*onEnter)(struct Input);
} Input;

extern FontW defaultFont;

#define InputDefaultOptions ((InputOptions)								\
							 {.bgColor=Voyage_Black,  .fgColor=Voyage_White, \
							  .border=Voyage_LightGrey, .accent=Voyage_White, \
							  .font=defaultFont.font, .fontSize=defaultFont.fontSize, \
							  .textSpacing=defaultFont.textSpacing, .maxChars=50, \
							  .hOffset=10, .vOffset=10, .borderWidth=2})

void InputDefaultOnEnter(Input input) {
	printf("Log: Input(%s) entered\n", input.text);
}

char cursorChar = '|';

Input Input_Init(Vector2, u32, char *, void (*)(Input));
Input Input_InitAtr(XmlNode *);
void Input_SetOptions(Input *, InputOptions);
void Input_Resize(Input *, u32);
void Input_ResizeReposition(Input *, Vector2, u32);
Vector2 Input_Size(Input);
void Input_Draw(Input);

Input Input_Init(Vector2 pos, u32 width, char *initialText, void (*onEnter)(Input)) {
	char *text = (char *)malloc(sizeof(char)*(InputDefaultOptions.maxChars+1));
	*text = 0;
	u32 hintLen = Voyage_Min(InputDefaultOptions.maxChars, (u32)strlen(initialText));
	if (hintLen) memcpy(text, initialText, hintLen);
	text[hintLen] = cursorChar;
	text[hintLen+1] = 0;
	return (Input){.pos = pos, .width=width, .text=text, .options=InputDefaultOptions,
				   .onEnter = onEnter? onEnter: &InputDefaultOnEnter, .cursorIndex=0,
				   .state = Input_State_Inactive};
}

Input Input_InitAtr(XmlNode *root) {
	if (strcmp(root->name, "input") != 0) {
		Voyage_Xml_ErrorFmt("expected node <input>; but got '<%s>'", root->name);
	}
	Input input = (Input){.pos = Vector2Dummy, .width=0, .options=InputDefaultOptions,
						  .onEnter=&InputDefaultOnEnter, .cursorIndex=0, .state=Input_State_Inactive};
	Steel_Node *itr = Steel_LL_Head(root->attributes);
	char *fontPath = NULL;
	while (itr) {
		Attribute *attribute = (Attribute *)itr->data;
		if (strcmp(attribute->name, "background") == 0) {
			input.options.bgColor = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "foreground") == 0) {
			input.options.fgColor = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "border") == 0) {
			input.options.border = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "accent") == 0) {
			input.options.accent = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "font") == 0) {
			fontPath = strdup(attribute->value);
		}
		if (strcmp(attribute->name, "font-size") == 0) {
			input.options.fontSize = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "max-characters") == 0) {
			input.options.maxChars = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "id") == 0) {
			input.id = strdup(attribute->value);
		}
		if (strcmp(attribute->name, "text-spacing") == 0) {
			input.options.textSpacing = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "horizontal-offset") == 0) {
			input.options.hOffset = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "vertical-offset") == 0) {
			input.options.vOffset = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "border-width") == 0) {
			input.options.borderWidth = atoi(attribute->value);
		}
		Steel_Node_Next(itr);
	}
	if (fontPath) {
		input.options.font = LoadFontEx(fontPath, input.options.fontSize, NULL, 0);
	}
	input.text = (char *)malloc(sizeof(char)*(input.options.maxChars+1));
	input.text[0] = cursorChar;
	input.text[1] = 0;
	return input;
} 

void Input_SetOptions(Input *input, InputOptions options) {
	input->options = options;
}

void Input_Resize(Input *input, u32 width) {
	input->width = width;
}

void Input_ResizeReposition(Input *input, Vector2 pos, u32 width) {
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
			input->text[input->cursorIndex] = cursorChar;
			input->text[input->cursorIndex+1] = 0;
		}
		while (key > 0) {
			if (key >= 32 && key <= 125 && input->cursorIndex < input->options.maxChars) {
				input->text[input->cursorIndex++] = key;
				if (input->cursorIndex < input->options.maxChars) {
					input->text[input->cursorIndex] = cursorChar;
					input->text[input->cursorIndex+1] = 0;
				} else input->text[input->cursorIndex] = 0;
			}
			key = GetCharPressed();
		}
		if (IsKeyPressed(KEY_BACKSPACE) && input->cursorIndex > 0) {
			input->text[input->cursorIndex] = 0;
			input->text[--input->cursorIndex] = cursorChar;
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
