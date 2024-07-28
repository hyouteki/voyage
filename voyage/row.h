#ifndef VOYAGE_ROW_H_
#define VOYAGE_ROW_H_

#include <stdlib.h>
#include "column.h"
#include "helper.h"
#include "../cxmlp/node.h"

typedef struct RowOptions {
	u32 hPadding;
	u32 vPadding;
	u32 scrollSpeed;
} RowOptions;

#define RowDefaultOptions ((RowOptions){.hPadding=0, .vPadding=0, .scrollSpeed=20})

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

Row Row_Init(Vector2, Vector2, u32 len, Column *[len], u32[len]);
Row *Row_InitAtr(XmlNode *);
void Row_Free(Row *);
void Row_AddColumn(Row *, Column *, u32);
void Row_ScrollEventHandler(Row *);
void Row_AttachListeners(Row *);
void Row_Resize(Row *, Vector2);
void Row_Draw(Row);

static void ColumnList_Add(ColumnList **list, Column *column, u32 weight) {
	ColumnList *listNode = (ColumnList *)malloc(sizeof(ColumnList));
	listNode->id = Column_Counter++;
	listNode->column = column;
	listNode->weight = weight;
	listNode->next = NULL;
	if (*list == NULL) {
		*list = listNode;
		return;
	}
	ColumnList *itr = *list;
	while (itr->next) itr = itr->next;
	itr->next = listNode;
}

Row Row_Init(Vector2 pos, Vector2 size, u32 len, Column *columns[len], u32 weights[len]) {
	if (len <= 0) Voyage_Error("len(columns) > 0 && len(weights) > 0");
	ColumnList *columnList = NULL;
	for (u32 i = 0; i < len; ++i) ColumnList_Add(&columnList, columns[i], weights[i]);
	return (Row){.pos=pos, .size=size, .columns=columnList, .options=RowDefaultOptions};
}

Row *Row_InitAtr(XmlNode *root) {
	if (strcmp(root->name, "row") != 0) {
		Voyage_Xml_ErrorFmt("expected top level node <row>; but got '<%s>'", root->name);
	}
	Row *row = (Row *)malloc(sizeof(Row));
	*row = (Row){.pos=Vector2Dummy, .size=Vector2Dummy, .columns=NULL,
				 .options = RowDefaultOptions};
	Steel_Node *itr = Steel_LL_Head(root->attributes);
	while (itr) {
		Attribute *attribute = (Attribute *)itr->data;
		if (strcmp(attribute->name, "horizontal-padding") == 0) {
			row->options.hPadding = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "vertical-padding") == 0) {
			row->options.vPadding = atoi(attribute->value);
		}
		if (strcmp(attribute->name, "scroll-speed") == 0) {
			row->options.scrollSpeed = atoi(attribute->value);
		}
		Steel_Node_Next(itr);
	}
	itr = Steel_LL_Head(root->childs);
	while (itr) {
		XmlNode *child = (XmlNode *)itr->data;
		u32 weight = 1;
		Column *column = Column_InitAtr(child, &weight);
		ColumnList_Add(&row->columns, column, weight);
		Steel_Node_Next(itr);
	}
	return row;
} 

void Row_Free(Row *row) {
	ColumnList *columnList = row->columns;
	while (columnList) {
		ColumnList *next = columnList->next;
		Column_Free(columnList->column);
		free(columnList);
		columnList = next;
	}
}

void Row_AddColumn(Row *row, Column *column, u32 weight) {
	ColumnList_Add(&row->columns, column, weight);
	Row_Resize(row, row->size);
}

void Row_ScrollEventHandler(Row *row) {
	ColumnList *itr = row->columns;
	Vector2 mousePoint = GetMousePosition();
	while (itr) {
		if (Voyage_CheckPointRecCollision(mousePoint, (Vector2){.x=itr->column->pos.x, .y=row->pos.y},
										  itr->column->size)) {
			int y = itr->column->pos.y + GetMouseWheelMove()*row->options.scrollSpeed;
			Column_Scroll(itr->column, (Vector2){.x=itr->column->pos.x, .y=y});
			break;
		}
		itr = itr->next;
	}
}

void Row_AttachListeners(Row *row) {
	Row_ScrollEventHandler(row);
	ColumnList *itr = row->columns;
	while (itr) {
		ElementList_AttachListener(itr->column->elements);
		itr = itr->next;
	}
}

void Row_Resize(Row *row, Vector2 size) {
	if (Voyage_Vector2Equal(row->size, size)) return;
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
