> Simple GUI application framework made on top of Raylib.

<image src="./images/logo.png" width="1000">

## Demo
<image src="./images/demo1.png" width="1000">

``` c
#include "voyage/export.h"

void buttonOnClick() {
	printf("Menu button clicked\n");
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(900, 720, "Voyage Demo");
	SetTargetFPS(60);
	
	int width = GetScreenWidth(), height = GetScreenHeight();
	Sidebar sidebar = Sidebar_Init((Vector2){width, height}, Voyage_Brown);
	Image image = LoadImage("./images/logo.png");
	Sidebar_AddElement(&sidebar, &ImageContainer_EleInit(Vector2Dummy, Vector2Dummy, &image));
	Sidebar_AddElement(&sidebar, &Button_EleInit(Vector2Dummy, 0, "Menu button 1", &buttonOnClick));	
	Sidebar_AddElement(&sidebar, &Button_EleInit(Vector2Dummy, 0, "Menu button 2", NULL));
	Sidebar_AddElement(&sidebar, &Label_EleInit(Vector2Dummy, 0, "Sample label with word wrapping"));
	Label label = Label_Init((Vector2){500, 300}, 300, "(c) hyouteki");
	
	while (!WindowShouldClose()) {
		width = GetScreenWidth(), height = GetScreenHeight();
		Sidebar_Resize(&sidebar, (Vector2){width, height});
		
		BeginDrawing();
		ClearBackground(Voyage_DarkBrown);
		Sidebar_Draw(sidebar);
		Label_Draw(label);
		EndDrawing();
	}
	CloseWindow();
	
	return 0;
}
```

## Quick Start
- Build and install [Raylib](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation).
- Run the demo using `make`.
