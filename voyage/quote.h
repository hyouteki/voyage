#ifndef VOYAGE_QUOTE_H_
#define VOYAGE_QUOTE_H_

#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "helper.h"
#include "label.h"
#include "quote.h"
#include "../cxmlp/node.h"

typedef struct QuoteOptions {
    Color bgColor;
    Color fgColor;
	Color accent;
    Font font;
    u32 fontSize;
    u32 textSpacing;
	u32 textSpacingV;
	u32 accentWidth;
    u32 hOffset;
    u32 vOffset;
} QuoteOptions;

typedef struct Quote {
    Vector2 pos;
	u32 width;
	char *text;
	char *id;
	Label label;
    QuoteOptions options;
} Quote;

#define QuoteDefaultOptions ((QuoteOptions)								\
                             {.bgColor=Voyage_OffBrown, .fgColor=Voyage_White, \
							  .font=GetFontDefault(), .fontSize=24, .textSpacing=3, \
							  .textSpacingV=5, .hOffset=10, .vOffset=10, \
							  .accent=Voyage_White, .accentWidth=10})

static void Quote_LabelReposition(Quote *);

Quote Quote_Init(Vector2, u32, char *);
Quote Quote_InitAtr(XmlNode *);
void Quote_Reposition(Quote *, Vector2);
void Quote_ResizeReposition(Quote *, Vector2, int);
Vector2 Quote_Size(Quote);
void Quote_SetOptions(Quote *, QuoteOptions);
void Quote_Draw(Quote);

static void Quote_LabelReposition(Quote *quote) {
	u32 hPadding = quote->options.accentWidth+2*quote->options.hOffset;
	Label_ResizeReposition(&quote->label,
						   (Vector2){.x=quote->pos.x+hPadding,
									 .y=quote->pos.y+ quote->options.vOffset},
						   quote->width-hPadding-quote->options.hOffset);
}

Quote Quote_Init(Vector2 pos, u32 width, char *text) {
	Label label = Label_Init(pos, width, text);
	return (Quote){.pos=pos, .width=width, .text=text, .label=label,
				   .options=QuoteDefaultOptions};
}

Quote Quote_InitAtr(XmlNode *root) {
	if (strcmp(root->name, "quote") != 0) {
		Voyage_Xml_ErrorFmt("expected node <quote>; but got '<%s>'", root->name);
	}
	QuoteOptions options = QuoteDefaultOptions;
	Steel_Node *itr = Steel_LL_Head(root->attributes);
	char *fontPath = NULL, *text = NULL, *id = NULL;
	while (itr) {
		Attribute *attribute = (Attribute *)itr->data;
		if (strcmp(attribute->name, "background") == 0) {
			options.bgColor = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "foreground") == 0) {
			options.fgColor = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "accent") == 0) {
			options.accent = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "font") == 0) {
			fontPath = strdup(attribute->value);
		}
		if (strcmp(attribute->name, "font-size") == 0) {
			options.fontSize = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "text-spacing") == 0) {
			options.textSpacing = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "vertical-text-spacing") == 0) {
			options.textSpacingV = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "horizontal-offset") == 0) {
			options.hOffset = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "vertical-offset") == 0) {
			options.vOffset = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "accent-width") == 0) {
			options.accentWidth = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "text") == 0) {
			text = strdup(attribute->value);
		}
		if (strcmp(attribute->name, "id") == 0) {
			id = strdup(attribute->value);
		}
		Steel_Node_Next(itr);
	}
	if (fontPath) {
		options.font = LoadFontEx(fontPath, options.fontSize, NULL, 0);
	}
	Label label = Label_Init(Vector2Dummy, 0, text);
	return (Quote){.pos=Vector2Dummy, .width=0, .text=text, .id=id, .label=label, .options=options};
} 

void Quote_Reposition(Quote *quote, Vector2 pos) {
	quote->pos = pos;
	Quote_LabelReposition(quote);
}

void Quote_ResizeReposition(Quote *quote, Vector2 pos, int width) {
	quote->pos = pos;
	quote->width = width;
	Quote_LabelReposition(quote);
}

Vector2 Quote_Size(Quote quote) {
	return (Vector2){.x=quote.width, .y=Label_Size(quote.label).y+2*quote.options.vOffset};
}

void Quote_SetOptions(Quote *quote, QuoteOptions options) {
    quote->options = options;
}

void Quote_Draw(Quote quote) {
	u32 labelHeight = Label_Size(quote.label).y;
	Rectangle accentContainer = (Rectangle){.x=quote.pos.x+quote.options.hOffset,
											.y=quote.pos.y, .width=quote.options.accentWidth,
										   .height=labelHeight};
	Rectangle quoteContainer = (Rectangle){.x=quote.pos.x+quote.options.hOffset,
										   .y=quote.pos.y,
										   .width=quote.width-2*quote.options.hOffset,
										   .height=labelHeight};
	DrawRectangleRec(quoteContainer, quote.options.bgColor);
	DrawRectangleRec(accentContainer, quote.options.accent);
	Label_Draw(quote.label);
}

#endif // VOYAGE_QUOTE_H_
