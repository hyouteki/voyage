#ifndef VOYAGE_ELEMENTS_H_
#define VOYAGE_ELEMENTS_H_

#include <stdio.h>
#include <stdlib.h>
#include "../raylib/include/raylib.h"
#include "button.h"
#include "image.h"
#include "label.h"

typedef enum {
	BUTTON,
	IMAGE_CONTAINER,
	LABEL
} Element_Type;

typedef struct Element {
	int id;
	Element_Type type;
	union {
		Button button;
		ImageContainer imageContainer;
		Label label;
	};
} Element;

typedef struct ElementList {
	Element *element;
	struct ElementList *next;
} ElementList;

static int Element_Counter = 0;

void Element_Reposition(Element *, Vector2);
void Element_ResizeReposition(Element *, Vector2, Vector2);
Vector2 Element_Size(Element);

void ElementList_Add(ElementList **, Element *);
void ElementList_Free(ElementList *);
int ElementList_TotalHeightTill(ElementList *, int, int);
void ElementList_Resize(ElementList **, Vector2);
void ElementList_Draw(ElementList *);

void Element_Reposition(Element *element, Vector2 pos) {
	switch (element->type) {
	case BUTTON:
		element->button.pos = pos;
		break;
	case IMAGE_CONTAINER:
		element->imageContainer.pos = pos;
		break;
	case LABEL:
		element->label.pos = pos;
		break;
	default:
		fprintf(stderr, "Error: invalid ElementType(%d) in "
				"Function(%s)\n", element->type, __func__);
		exit(1);
	}
}

void Element_ResizeReposition(Element *element, Vector2 pos, Vector2 size) {
	switch (element->type) {
	case BUTTON:
		element->button.pos = pos;
		element->button.width = size.x;
		break;
	case IMAGE_CONTAINER:
		ImageContainer_ResizeReposition(&element->imageContainer, pos, size);
		break;
	case LABEL:
		Label_ResizeReposition(&element->label, pos, size.x);
		break;
	default:
		fprintf(stderr, "Error: invalid ElementType(%d) in "
				"Function(%s)\n", element->type, __func__);
		exit(1);
	}
}

Vector2 Element_Size(Element element) {
	switch (element.type) {
	case BUTTON: return Button_Size(element.button);
	case IMAGE_CONTAINER: return element.imageContainer.size;
	case LABEL: return Label_Size(element.label);
	default:
		fprintf(stderr, "Error: invalid ElementType(%d) in "
				"Function(%s)\n", element.type, __func__);
		exit(1);
	}
}

void ElementList_Add(ElementList **list, Element *node) {
	ElementList *listNode = (ElementList *)malloc(sizeof(ElementList));
	node->id = Element_Counter++;
	listNode->next = NULL;
	listNode->element = node;
	if (*list == NULL) {
		*list = listNode;
		return;
	}
	ElementList *itr = *list;
	while (itr->next) itr = itr->next;
	itr->next = listNode;
}

void ElementList_Free(ElementList *elementList) {
	while (elementList) {
		ElementList *next = elementList->next;
		free(elementList);
		elementList = next;
	}
}

int ElementList_TotalHeightTill(ElementList *list, int padding, int id) {
	ElementList *itr = list;
	int height = padding, _Element_Counter = 0;
	while (itr && _Element_Counter != id) {
		height += Element_Size(*itr->element).y+padding;
		itr = itr->next;
		_Element_Counter++;
	}
	return height;
} 

void ElementList_Draw(ElementList *list) {
	ElementList *itr = list;
	while (itr) {
		Element element = *itr->element;
		switch (element.type) {
		case BUTTON:
			Button_Draw(element.button);
			break;
		case IMAGE_CONTAINER:
			ImageContainer_Draw(element.imageContainer);
			break;
		case LABEL:
			Label_Draw(element.label);
			break;
		default:
			fprintf(stderr, "Error: invalid ElementType(%d) in "
					"Function(%s)\n", element.type, __func__);
			exit(1);
		}
		itr = itr->next;
	}
}

#endif // VOYAGE_ELEMENTS_H_
