#ifndef VOYAGE_IMAGE_H_
#define VOYAGE_IMAGE_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"

typedef struct ImageContainer {
	Vector2 pos;
	Vector2 size;
	Image *image;
} ImageContainer;

ImageContainer ImageContainer_Init(Vector2, Vector2, Image *);
void ImageContainer_ResizeReposition(ImageContainer *, Vector2, Vector2);
void ImageContainer_Draw(ImageContainer);

ImageContainer ImageContainer_Init(Vector2 pos, Vector2 size, Image *image) {
	if (size.y == -1) {
		size = (Vector2){size.x, image->height/image->width*size.x};
	}
	return (ImageContainer){.pos=pos, .size=size, .image=image};
}

void ImageContainer_ResizeReposition(ImageContainer *imageContainer,
									 Vector2 pos, Vector2 size) {
	if (size.y == -1) {
		Image *image = imageContainer->image;
		size = (Vector2){size.x, ((double)image->height/image->width)*size.x};
	}
	imageContainer->pos = pos;
	imageContainer->size = size;
}

void ImageContainer_Draw(ImageContainer imageContainer) {
	ImageResize(imageContainer.image, imageContainer.size.x,
				imageContainer.size.y);
	Texture2D texture = LoadTextureFromImage(*imageContainer.image);
	DrawTexture(texture, imageContainer.pos.x, imageContainer.pos.y, WHITE);
}

#endif // VOYAGE_IMAGE_H_
