#ifndef VOYAGE_ROW_H_
#define VOYAGE_ROW_H_

#include <stdio.h>
#include <stdlib.h>
#include "../raylib/include/raylib.h"
#include "column.h"
#include "helper.h"

typedef struct RowOptions {
	int hPadding;
	int vPadding;
} RowOptions;

#define RowDefaultOptions ((RowOptions){.hPadding=0, .vPadding=0})

typedef struct ColumnList {
	u32 id;
	Column *column;
	u32 weight;
	struct ColumnList *next;
} ColumnList;

typedef struct Row {
	Vector2 pos;
	Vector2 size;
	ColumnList *columns;
	RowOptions options;
} Row;

static u32 Column_Counter = 0;

static void ColumnList_Add(ColumnList **, Column *, u32);

Row Row_Init(Vector2, Vector2, int, Column *[], u32[]);
void Row_AddColumn(Row *, Column *, u32);
void Row_Resize(Row *, Vector2);
void Row_Draw(Row);

static void ColumnList_Add(ColumnList **list, Column *column, u32 weight) {
	ColumnList *listNode = (ColumnList *)malloc(sizeof(ColumnList));
	listNode->id = Column_Counter++;
	listNode->column = column;
	listNode->weight = weight;
	if (*list == NULL) {
		*list = listNode;
		return;
	}
	ColumnList *itr = *list;
	while (itr->next) itr = itr->next;
	itr->next = listNode;
}

Row Row_Init(Vector2 pos, Vector2 size, int len, Column *columns[len], u32 weights[len]) {
	if (len <= 0) Voyage_Error("len(columns) > 0 && len(weights) > 0");
	ColumnList *columnList = NULL;
	for (int i = 0; i < len; ++i) ColumnList_Add(&columnList, columns[i], weights[i]);
	return (Row){.pos=pos, .size=size, .columns=columnList, .options=RowDefaultOptions};
}

void Row_AddColumn(Row *row, Column *column, u32 weight) {
	ColumnList_Add(&row->columns, column, weight);
	Row_Resize(row, row->size);
}

void Row_Resize(Row *row, Vector2 size) {
	row->size = size;
	ColumnList *itr = row->columns;
	int totalWeight = 0;
	while (itr) {
		totalWeight += itr->weight;
		itr = itr->next;
	}
	itr = row->columns;
	int x = row->pos.x+row->options.hPadding, y = row->pos.y+row->options.vPadding;
	while (itr) {
		int width = row->size.x*((double)itr->weight/totalWeight)-2*row->options.hPadding;
		int height = row->size.y-2*row->options.vPadding;
		Column_ResizeReposition(itr->column, (Vector2){.x=x, .y=y}, (Vector2){.x=width, .y=height});
		x += row->size.x*((double)itr->weight/totalWeight);
		itr = itr->next;
	}
}

void Row_Draw(Row row) {
	ColumnList *itr = row.columns;
	while (itr) {
		Column_Draw(*itr->column);
		itr = itr->next;
	}
}

#endif // VOYAGE_ROW_H_
