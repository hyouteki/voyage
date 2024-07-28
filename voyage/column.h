#ifndef VOYAGE_COLUMN_H_
#define VOYAGE_COLUMN_H_

#include "../cxmlp/node.h"
#include "colors.h"
#include "elements.h"
#include "helper.h"

typedef struct ColumnOptions {
	int hPadding;
	int vPadding;
	int fixedElementGravity;
} ColumnOptions;

#define ColumnDefaultOptions ((ColumnOptions){.hPadding=5, .vPadding=5, .fixedElementGravity=1})

typedef struct Column {
	Vector2 pos;
	Vector2 size;
	Color color;
	ElementList *elements;
	ElementList *fixedElements;
	ColumnOptions options;
} Column;

#define Column_Size(column) (column.size) 
#define Column_SetOptions(column, columnOptions) (column->options = columnOptions)
#define Column_Add(column, element) (Column_AddElement(column, element, 0))
#define Column_AddF(column, element) (Column_AddElement(column, element, 1))

Column Column_Init(Vector2, Vector2, Color);
Column *Column_InitAtr(XmlNode *, u32 *);
void Column_Free(Column *);
void Column_AddElement(Column *, Element *, int);
void Column_Resize(Column *, Vector2);
void Column_Scroll(Column *, Vector2);
void Column_ResizeReposition(Column *, Vector2, Vector2);
void Column_Draw(Column);

Column Column_Init(Vector2 pos, Vector2 size, Color color) {
	return (Column){.pos=pos, .size=size, .color=color, .elements=NULL, .options=ColumnDefaultOptions};
}

Column *Column_InitAtr(XmlNode *root, u32 *weight) {
	if (strcmp(root->name, "column") != 0) {
		Voyage_Xml_ErrorFmt("expected node <column>; but got '<%s>'", root->name);
	}
	Steel_Node *itr = Steel_LL_Head(root->attributes);
	Column *column = (Column *)malloc(sizeof(Column));
	*column = (Column){.pos=Vector2Dummy, .size=Vector2Dummy, .color=Voyage_Color_Default,
					   .elements=NULL, .options=ColumnDefaultOptions};
	while (itr) {
		Attribute *attribute = (Attribute *)itr->data;
		if (strcmp(attribute->name, "horizontal-padding") == 0) {
			column->options.hPadding = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "vertical-padding") == 0) {
			column->options.vPadding = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "gravity") == 0) {
			column->options.fixedElementGravity = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "background") == 0) {
			column->color = Voyage_Color_FromString(attribute->value);
		}
		if (strcmp(attribute->name, "weight") == 0) {
			*weight = atoi(attribute->value);
		}
		Steel_Node_Next(itr);
	}
	ElementList_InitAtr(&column->elements, &column->fixedElements, root->childs);
	return column;
} 

void Column_Free(Column *column) {
	ElementList_Free(column->elements);
}

void Column_AddElement(Column *column, Element *element, int isFixed) {
	if (isFixed) {
		int height = ElementList_TotalHeightTill(column->fixedElements, column->options.vPadding, -1);
		Element_ResizeReposition(element, (Vector2){column->pos.x+column->options.hPadding, column->pos.y+height},
								 (Vector2){column->size.x-2*column->options.hPadding, -1});
		ElementList_Add(&column->fixedElements, element);
	} else {
		int height = ElementList_TotalHeightTill(column->elements, column->options.vPadding, -1);
		int yPos = column->pos.y+height;
		if (column->options.fixedElementGravity)
			yPos = column->pos.y+column->size.y-height-Element_Size(*element).y-column->options.vPadding;
		Element_ResizeReposition(element, (Vector2){column->pos.x+column->options.hPadding, yPos},
								 (Vector2){column->size.x-2*column->options.hPadding, -1});
		ElementList_Add(&column->elements, element);
	}
}

void Column_Resize(Column *column, Vector2 size) {
	column->size=size;
	ElementList *itr = column->elements;
	int _counter = 0;
	while (itr) {
		int height = ElementList_TotalHeightTill(column->elements, column->options.vPadding, _counter);
		Element_ResizeReposition(itr->element, (Vector2){column->pos.x+column->options.hPadding,
														 column->pos.y+height},
								 (Vector2){column->size.x-2*column->options.hPadding, -1});
		itr = itr->next;
		_counter++;
	}
	itr = column->fixedElements;
	_counter = 0;
	while (itr) {
		int height = ElementList_TotalHeightTill(column->fixedElements, column->options.vPadding, _counter);
		int yPos = column->pos.y+height;
		if (column->options.fixedElementGravity)
			yPos = column->pos.y+column->size.y-height-Element_Size(*itr->element).y-column->options.vPadding;
		Element_ResizeReposition(itr->element, (Vector2){column->pos.x+column->options.hPadding, yPos},
								 (Vector2){column->size.x-2*column->options.hPadding, -1});
		itr = itr->next;
		_counter++;
	}
}

void Column_Scroll(Column *column, Vector2 pos) {
	column->pos = pos;
	ElementList *itr = column->elements;
	int _counter = 0;
	while (itr) {
		int height = ElementList_TotalHeightTill(column->elements, column->options.vPadding, _counter);
		Element_Reposition(itr->element, (Vector2){column->pos.x+column->options.hPadding,
												   column->pos.y+height});
		itr = itr->next;
		_counter++;
	}
}

void Column_ResizeReposition(Column *column, Vector2 pos, Vector2 size) {
	column->pos = pos;
	Column_Resize(column, size);
}

void Column_Draw(Column column) {
	int height = ElementList_TotalHeightTill(column.elements, column.options.vPadding, -1);
	DrawRectangleV(column.pos, (Vector2){.x=column.size.x, .y=Voyage_MaxInt(height, column.size.y)},
				   column.color);
	ElementList_Draw(column.elements);
	ElementList_Draw(column.fixedElements);
}

#endif // VOYAGE_COLUMN_H_
