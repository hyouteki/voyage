#ifndef VOYAGE_ELEMENTS_H_
#define VOYAGE_ELEMENTS_H_

#include <stdio.h>
#include <stdlib.h>
#include "../raylib/include/raylib.h"
#include "sidebar.h"
#include "button.h"

#define BUTTON 0
#define LABEL 1

typedef struct Element {
	int type;
	union {
		Button button;
		int label; // placeholder for now
	};
} Element;

typedef struct ElementList {
	Element *element;
	struct ElementList *next;
}  ElementList;

void ElementList_Add(ElementList **, Element *);
void ElementList_Resize(ElementList **, Vector2);
void ElementList_Draw(ElementList *);

void ElementList_Add(ElementList **list, Element *node) {
	ElementList *listNode = (ElementList *)malloc(sizeof(ElementList));
	listNode->element = node;
	if (*list == NULL) {
		*list = listNode;
		return;
	}
	ElementList *itr = *list;
	while (itr->next) itr = itr->next;
	itr->next = listNode;
}

void ElementList_Draw(ElementList *list) {
	ElementList *itr = list;
	while (itr) {
		Element element = *itr->element;
		switch (element.type) {
		case BUTTON:
			Button_Draw(element.button);
			break;
		default:
			fprintf(stderr, "Error: invalid ElementType(%d) in "
					"Function(ElementList_Draw)\n", element.type);
			exit(1);
		}
		itr = itr->next;
	}
}

#endif // VOYAGE_ELEMENTS_H_
