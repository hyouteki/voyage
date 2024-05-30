#ifndef VOYAGE_COLUMN_H_
#define VOYAGE_COLUMN_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "elements.h"

typedef struct ColumnOptions {
	int hPadding;
	int vPadding;
} ColumnOptions;

#define ColumnDefaultOptions ((ColumnOptions){.hPadding=5, .vPadding=5})

typedef struct Column {
	Vector2 pos;
	Vector2 size;
	Color color;
	ElementList *elements;
	ColumnOptions options;
} Column;

#define Column_Size(column) (column.size) 
#define Column_SetOptions(column, columnOptions) (column->options = columnOptions)

Column Column_Init(Vector2, Vector2, Color);
void Column_Free(Column *);
void Column_AddElement(Column *, Element *);
void Column_Resize(Column *, Vector2);
void Column_ResizeReposition(Column *, Vector2, Vector2);
void Column_Draw(Column);

Column Column_Init(Vector2 pos, Vector2 size, Color color) {
	return (Column){.pos=pos, .size=size, .color=color, .elements=NULL, .options=ColumnDefaultOptions};
}

void Column_Free(Column *column) {
	ElementList_Free(column->elements);
}

void Column_AddElement(Column *column, Element *element) {
	int height = ElementList_TotalHeightTill(column->elements, column->options.vPadding, -1);
	Element_ResizeReposition(element, (Vector2){column->pos.x+column->options.hPadding, column->pos.y+height},
							 (Vector2){column->size.x-2*column->options.hPadding, -1});
	ElementList_Add(&column->elements, element);
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
}

void Column_ResizeReposition(Column *column, Vector2 pos, Vector2 size) {
	column->pos = pos;
	Column_Resize(column, size);
}

void Column_Draw(Column column) {
	DrawRectangleV(column.pos, column.size, column.color);
	ElementList_Draw(column.elements);
}

#endif // VOYAGE_COLUMN_H_
