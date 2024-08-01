#ifndef VOYAGE_SPACE_H_
#define VOYAGE_SPACE_H_

#include "colors.h"
#include "helper.h"
#include "../cxmlp/node.h"

typedef struct SpaceOptions {
	Color bgColor;
	u32 hOffset;
	u32 transparent;
} SpaceOptions;

typedef struct Space {
	Vector2 pos;
	u32 width;
	u32 height;
	char *id;
	SpaceOptions options;
} Space;

#define SpaceDefaultOptions ((SpaceOptions){.bgColor=Voyage_LightGrey, .hOffset=10, .transparent=1})

Space Space_Init(Vector2, u32, u32);
Space Space_InitAtr(XmlNode *);
void Space_SetOptions(Space *, SpaceOptions);
void Space_Resize(Space *, u32);
void Space_Reposition(Space *, Vector2);
void Space_ResizeReposition(Space *, Vector2, u32);
Vector2 Space_Size(Space);
void Space_Draw(Space);

Space Space_Init(Vector2 pos, u32 width, u32 height) {
	return (Space){.pos=pos, .width=width, .height=height, .options=SpaceDefaultOptions};
}

Space Space_InitAtr(XmlNode *root) {
	if (strcmp(root->name, "space") != 0) {
		Voyage_Xml_ErrorFmt("expected node <space>; but got '<%s>'", root->name);
	}
	Space space = (Space){.pos = Vector2Dummy, .width=0, .height=0, 
						  .options=SpaceDefaultOptions};
	Steel_Node *itr = Steel_LL_Head(root->attributes);
	while (itr) {
		Attribute *attribute = (Attribute *)itr->data;
		if (strcmp(attribute->name, "background") == 0) {
			space.options.bgColor = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "horizontal-offset") == 0) {
			space.options.hOffset = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "transparent") == 0) {
			space.options.transparent = strcmp(attribute->value, "true") == 0;
		}
		if (strcmp(attribute->name, "height") == 0) {
			space.height = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "id") == 0) {
			space.id = strdup(attribute->value);
		}
		Steel_Node_Next(itr);
	}
	return space;
} 

void Space_SetOptions(Space *space, SpaceOptions options) {
	space->options = options;
}

void Space_Resize(Space *space, u32 width) {
	space->width = width;
}

void Space_Reposition(Space *space, Vector2 pos) {
	space->pos = pos;
}

void Space_ResizeReposition(Space *space, Vector2 pos, u32 width) {
	space->pos = pos;
	space->width = width;
}

Vector2 Space_Size(Space space) {
	return (Vector2){.x=space.width, .y=space.height};
}

void Space_Draw(Space space) {
	if (space.options.transparent) return;
	DrawRectangleRec((Rectangle){.x=space.pos.x+space.options.hOffset, .y=space.pos.y,
								 .width=space.width-2*space.options.hOffset, .height=space.height},
		space.options.bgColor);
}

#endif // VOYAGE_SPACE_H_
