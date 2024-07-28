#ifndef VOYAGE_IMAGE_H_
#define VOYAGE_IMAGE_H_

#include <stdlib.h>
#include "helper.h"
#include "../cxmlp/node.h"

typedef struct ImageContainer {
	Vector2 pos;
	Vector2 size;
	Image *image;
	Texture2D *texture;
	int *reloadTexture;
} ImageContainer;

ImageContainer ImageContainer_Init(Vector2, Vector2, Image *);
ImageContainer ImageContainer_InitAtr(XmlNode *);
void ImageContainer_ResizeReposition(ImageContainer *, Vector2, Vector2);
void ImageContainer_Draw(ImageContainer);

ImageContainer ImageContainer_Init(Vector2 pos, Vector2 size, Image *image) {
	if (size.y == -1) size = (Vector2){size.x, image->height/image->width*size.x};
	int *reloadTexture = (int *)malloc(sizeof(int));
	Texture2D *texture = (Texture2D *)malloc(sizeof(Texture2D));
	*reloadTexture = 1;
	return (ImageContainer){.pos=pos, .size=size, .image=image, .texture=texture, .reloadTexture=reloadTexture};
}

ImageContainer ImageContainer_InitAtr(XmlNode *root) {
	if (strcmp(root->name, "image") != 0) {
		Voyage_Xml_ErrorFmt("expected node <image>; but got '<%s>'", root->name);
	}
	ImageContainer imageContainer = (ImageContainer){.pos = Vector2Dummy, .size=Vector2Dummy};
	imageContainer.reloadTexture = (int *)malloc(sizeof(int));
	imageContainer.texture = (Texture2D *)malloc(sizeof(Texture2D));
	imageContainer.image = (Image *)malloc(sizeof(Image));
	*imageContainer.reloadTexture = 1;
	Steel_Node *itr = Steel_LL_Head(root->attributes);
	while (itr) {
		Attribute *attribute = (Attribute *)itr->data;
		if (strcmp(attribute->name, "src") == 0) {
			*imageContainer.image = LoadImage(attribute->value);
		}
		Steel_Node_Next(itr);
	}
	return imageContainer;
}

void ImageContainer_ResizeReposition(ImageContainer *imageContainer, Vector2 pos, Vector2 size) {
	if (size.y == -1) {
		Image *image = imageContainer->image;
		size = (Vector2){size.x, ((double)image->height/image->width)*size.x};
	}
	if (!Voyage_Vector2Equal(imageContainer->size, size)) *imageContainer->reloadTexture=1;
	imageContainer->pos = pos;
	imageContainer->size = size;
}

void ImageContainer_Draw(ImageContainer imageContainer) {
	if (*imageContainer.reloadTexture) {
		ImageResize(imageContainer.image, imageContainer.size.x, imageContainer.size.y);
		UnloadTexture(*imageContainer.texture);
		*imageContainer.texture = LoadTextureFromImage(*imageContainer.image);
		*imageContainer.reloadTexture=0;
	}
	DrawTexture(*imageContainer.texture, imageContainer.pos.x, imageContainer.pos.y, WHITE);
}

void ImageContainer_DeInit(ImageContainer imageContainer) {
	free(imageContainer.reloadTexture);
	free(imageContainer.texture);
}

#endif // VOYAGE_IMAGE_H_
