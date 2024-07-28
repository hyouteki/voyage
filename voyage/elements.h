#ifndef VOYAGE_ELEMENTS_H_
#define VOYAGE_ELEMENTS_H_

#include <stdlib.h>
#include <string.h>
#include "column.h"
#include "button.h"
#include "image.h"
#include "label.h"
#include "quote.h"
#include "space.h"
#include "input.h"
#include "../cxmlp/node.h"

typedef enum {
	Element_Button,
	Element_ImageContainer,
	Element_Label,
	Element_Quote,
	Element_Space,
	Element_Input
} Element_Type;

typedef struct Element {
	int id;
	Element_Type type;
	union {
		Button button;
		ImageContainer imageContainer;
		Label label;
		Quote quote;
		Space space;
		Input input;
	};
} Element;

typedef struct ElementList {
	Element *element;
	struct ElementList *next;
} ElementList;

static int Element_Counter = 0;

void ElementList_InitAtr(ElementList **, ElementList **, Steel_LL *);
void Element_Reposition(Element *, Vector2);
void Element_ResizeReposition(Element *, Vector2, Vector2);
Vector2 Element_Size(Element);
void Element_DeInit(Element *);
void ElementList_Draw(ElementList *);
void ElementList_AttachListener(ElementList *);

void ElementList_Add(ElementList **, Element *);
void ElementList_Free(ElementList *);
int ElementList_TotalHeightTill(ElementList *, int, int);
void ElementList_Resize(ElementList **, Vector2);

void ElementList_InitAtr(ElementList **elements, ElementList **fixedElements,
						 Steel_LL *childs) {
	Steel_Node *itr = Steel_LL_Head(childs);
	while (itr) {
		XmlNode *child = (XmlNode *)itr->data;
		Element *element = (Element *)malloc(sizeof(Element));
		int fixed = 0;
		{
			Steel_Node *itr = Steel_LL_Head(child->attributes);
			while (itr) {
				Attribute *child = (Attribute *)itr->data;
				if (strcmp(child->name, "fixed") == 0) {
					fixed = strcmp(child->value, "true") == 0;
				}
				Steel_Node_Next(itr);
			} 
		}
		if (strcmp(child->name, "button") == 0) {
			element->type = Element_Button;
			element->button = Button_InitAtr(child);
		}
		if (strcmp(child->name, "image") == 0) {
			element->type = Element_ImageContainer;
			element->imageContainer = ImageContainer_InitAtr(child);
		}
		if (strcmp(child->name, "label") == 0) {
			element->type = Element_Label;
			element->label = Label_InitAtr(child);
		}
		ElementList_Add(fixed? fixedElements: elements, element);
		Steel_Node_Next(itr);
	}
}

void Element_Reposition(Element *element, Vector2 pos) {
	switch (element->type) {
	case Element_Button:
		element->button.pos = pos;
		break;
	case Element_ImageContainer:
		element->imageContainer.pos = pos;
		break;
	case Element_Label:
		element->label.pos = pos;
		break;
	case Element_Quote:
		Quote_Reposition(&element->quote, pos);
		break;
	case Element_Space:
		Space_Reposition(&element->space, pos);
		break;
	case Element_Input:
		element->input.pos = pos;
		break;
	default:
		fprintf(stderr, "Error: invalid ElementType(%d) in "
				"Function(%s)\n", element->type, __func__);
		exit(1);
	}
}

void Element_ResizeReposition(Element *element, Vector2 pos, Vector2 size) {
	switch (element->type) {
	case Element_Button:
		Button_ResizeReposition(&element->button, pos, size.x);
		break;
	case Element_ImageContainer:
		ImageContainer_ResizeReposition(&element->imageContainer, pos, size);
		break;
	case Element_Label:
		Label_ResizeReposition(&element->label, pos, size.x);
		break;
	case Element_Quote:
		Quote_ResizeReposition(&element->quote, pos, size.x);
		break;
	case Element_Space:
		Space_ResizeReposition(&element->space, pos, size.x);
		break;
	case Element_Input:
		Input_ResizeReposition(&element->input, pos, size.x);
		break;
	default:
		fprintf(stderr, "Error: invalid ElementType(%d) in "
				"Function(%s)\n", element->type, __func__);
		exit(1);
	}
}

Vector2 Element_Size(Element element) {
	switch (element.type) {
	case Element_Button: return Button_Size(element.button);
	case Element_ImageContainer: return element.imageContainer.size;
	case Element_Label: return Label_Size(element.label);
	case Element_Quote: return Quote_Size(element.quote);
	case Element_Space: return Space_Size(element.space);
	case Element_Input: return Input_Size(element.input);
	default:
		fprintf(stderr, "Error: invalid ElementType(%d) in "
				"Function(%s)\n", element.type, __func__);
		exit(1);
	}
}

void Element_DeInit(Element *element) {
	switch (element->type) {
	case Element_Button:
		break;
	case Element_ImageContainer:
		ImageContainer_DeInit(element->imageContainer);
		break;
	case Element_Label:
	case Element_Quote:
	case Element_Space:
	case Element_Input:
		break;
	default:
		fprintf(stderr, "Error: invalid ElementType(%d) in "
				"Function(%s)\n", element->type, __func__);
		exit(1);
	}
}

void ElementList_Draw(ElementList *list) {
	ElementList *itr = list;
	while (itr) {
		Element element = *itr->element;
		switch (element.type) {
		case Element_Button:
			Button_Draw(element.button);
			break;
		case Element_ImageContainer:
			ImageContainer_Draw(element.imageContainer);
			break;
		case Element_Label:
			Label_Draw(element.label);
			break;
		case Element_Quote:
			Quote_Draw(element.quote);
			break;
		case Element_Space:
			Space_Draw(element.space);
			break;
		case Element_Input:
			Input_Draw(element.input);
			break;
		default:
			fprintf(stderr, "Error: invalid ElementType(%d) in "
					"Function(%s)\n", element.type, __func__);
			exit(1);
		}
		itr = itr->next;
	}
}

void ElementList_AttachListener(ElementList *list) {
	ElementList *itr = list;
	while (itr) {
		Element *element = itr->element;
		switch (element->type) {
		case Element_Button:
		case Element_ImageContainer:
		case Element_Label:
		case Element_Quote:
		case Element_Space:
			break;
		case Element_Input:
			Input_TypeEventListener(&element->input);
			break;
		default:
			fprintf(stderr, "Error: invalid ElementType(%d) in "
					"Function(%s)\n", element->type, __func__);
			exit(1);
		}
		itr = itr->next;
	}
}

void ElementList_Add(ElementList **list, Element *node) {
	ElementList *listNode = (ElementList *)malloc(sizeof(ElementList));
	node->id = Element_Counter++;
	listNode->next = NULL;
	listNode->element = (Element *)malloc(sizeof(Element));
	memcpy(listNode->element, node, sizeof(Element));
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
		Element_DeInit(elementList->element);
		free(elementList->element);
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

#endif // VOYAGE_ELEMENTS_H_
