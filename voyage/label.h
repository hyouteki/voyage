#ifndef VOYAGE_LABEL_H_
#define VOYAGE_LABEL_H_

#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "helper.h"
#include "../cxmlp/node.h"

typedef struct LabelOptions {
    Color bgColor;
    Color fgColor;
    Font font;
    int fontSize;
    int textSpacing;
	int textSpacingV;
    int hOffset;
    int vOffset;
} LabelOptions;

typedef struct VecStr {
	char *str;
	struct VecStr *next;
} VecStr;

typedef struct Label {
    Vector2 pos;
	int width;
	char *text;
	VecStr *vecstr;
    LabelOptions options;
} Label;

extern FontW defaultFont;

#define LabelDefaultOptions ((LabelOptions){.bgColor=Voyage_LightGrey, .fgColor=Voyage_White, \
											.font=defaultFont.font, .fontSize=defaultFont.fontSize, \
											.textSpacing=defaultFont.textSpacing, \
											.textSpacingV=5, .hOffset=10, .vOffset=10})

static void VecStr_Add(VecStr **, char *);
static void VecStr_Free(VecStr *);
static void Label_WrapText(const char *, LabelOptions, int, VecStr **);

Label Label_Init(Vector2, int, char *);
Label Label_InitAtr(XmlNode *);
Label Label_InitC(Vector2, int, char *, LabelOptions);
void Label_ResizeReposition(Label *, Vector2, int);
Vector2 Label_Size(Label);
void Label_SetOptions(Label *, LabelOptions);
void Label_Draw(Label);

static void VecStr_Add(VecStr **vecstr, char *str) {
	VecStr *node = (VecStr *)malloc(sizeof(VecStr));
	if (!node) Voyage_Error("unable to allocate memory for node");
	node->str = strdup(str);
	if (!node->str) Voyage_Error("unable to allocate memory for node->str");
	node->next = NULL;
	VecStr *itr = *vecstr;
	if (!itr) {
		*vecstr = node;
		return;
	}
	while (itr->next != NULL) itr = itr->next;
	itr->next = node;
}

static void VecStr_Free(VecStr *vecstr) {
    while (vecstr) {
        VecStr *next = vecstr->next;
        free(vecstr->str);
        free(vecstr);
        vecstr = next;
    }
}

Label Label_Init(Vector2 pos, int width, char *text) {
	VecStr *vecstr = NULL;
	Label_WrapText(text, LabelDefaultOptions, width, &vecstr);
    return (Label){.pos = pos, .width=width, .text=text,
				   .vecstr = vecstr, .options = LabelDefaultOptions};
}

Label Label_InitAtr(XmlNode *root) {
	if (strcmp(root->name, "label") != 0) {
		Voyage_Xml_ErrorFmt("expected node <label>; but got '<%s>'", root->name);
	}
	VecStr *vecstr = NULL;
	Label label = (Label){.pos = Vector2Dummy, .width=0, .options=LabelDefaultOptions, .text=""};
	Steel_Node *itr = Steel_LL_Head(root->attributes);
	char *fontPath = NULL;
	while (itr) {
		Attribute *attribute = (Attribute *)itr->data;
		if (strcmp(attribute->name, "background") == 0) {
			label.options.bgColor = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "foreground") == 0) {
			label.options.fgColor = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "font") == 0) {
			fontPath = strdup(attribute->value);
		}
		if (strcmp(attribute->name, "font-size") == 0) {
			label.options.fontSize = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "text-spacing") == 0) {
			label.options.textSpacing = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "vertical-text-spacing") == 0) {
			label.options.textSpacingV = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "horizontal-offset") == 0) {
			label.options.hOffset = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "vertical-offset") == 0) {
			label.options.vOffset = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "text") == 0) {
			label.text = strdup(attribute->value);
		}
		Steel_Node_Next(itr);
	}
	if (fontPath) {
		label.options.font = LoadFontEx(fontPath, label.options.fontSize, NULL, 0);
	}
	Label_WrapText(label.text, label.options, 0, &vecstr);
	return label;
} 

Label Label_InitC(Vector2 pos, int width, char *text, LabelOptions options) {
	VecStr *vecstr = NULL;
	Label_WrapText(text, LabelDefaultOptions, width, &vecstr);
    return (Label){.pos = pos, .width=width, .text=text, .vecstr = vecstr, .options = options};
}

void Label_ResizeReposition(Label *label, Vector2 pos, int width) {
	label->pos = pos;
	label->width = width;
	VecStr_Free(label->vecstr);
	label->vecstr = NULL;
	Label_WrapText(label->text, label->options, width, &label->vecstr);
}

Vector2 Label_Size(Label label) {
	VecStr *itr = label.vecstr;
	int y = 0;
	while (itr) {
		Vector2 textSize = MeasureTextEx(label.options.font, itr->str,
										 label.options.fontSize, label.options.textSpacing);
		y += textSize.y + label.options.textSpacingV;
		itr = itr->next;
	}
	return (Vector2){label.width, y+2*label.options.vOffset};
}

void Label_SetOptions(Label *label, LabelOptions options) {
    label->options = options;
}

void Label_WrapText(const char* text, LabelOptions labelOptions,
					int width, VecStr **vecstr) {
    char word[256];
	char *line = (char *)malloc(sizeof(char)*1024);
	if (!line) Voyage_Error("unable to allocate memory for line");
	line[0] = 0;
    int len = strlen(text), wordIndex = 0;
	int maxWidth = width - 2*labelOptions.hOffset;
	for (int i = 0; i <= len; i++) {
        if (text[i] == ' ' || text[i] == 0) {
            word[wordIndex] = 0;
            Vector2 wordSize = MeasureTextEx(labelOptions.font, word,
											 labelOptions.fontSize, labelOptions.textSpacing);
            Vector2 lineSize = MeasureTextEx(labelOptions.font, line,
											 labelOptions.fontSize, labelOptions.textSpacing);
            if (lineSize.x + wordSize.x > maxWidth) {
				VecStr_Add(vecstr, line);
                strcpy(line, word);
            } else strcat(line, word);
			strcat(line, " ");
            wordIndex = 0;
        } else word[wordIndex++] = text[i];
    }
	VecStr_Add(vecstr, line);
	free(line);
}

void Label_Draw(Label label) {
	VecStr *itr = label.vecstr;
	int x = label.pos.x+label.options.hOffset, y = label.pos.y;
	while (itr) {
		y += label.options.textSpacingV;
		Vector2 textSize = MeasureTextEx(label.options.font, itr->str,
										 label.options.fontSize, label.options.textSpacing);
		DrawTextEx(label.options.font, itr->str, (Vector2){x, y},
				   label.options.fontSize, label.options.textSpacing, label.options.fgColor);
		y += textSize.y;
		itr = itr->next;
	}
}

#endif // VOYAGE_LABEL_H_
