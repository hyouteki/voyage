#include "export.h"

void buttonOnClick() {
	printf("Menu button clicked\n");
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(900, 720, "Voyage Demo");
	SetTargetFPS(60);
	
	int width = GetScreenWidth(), height = GetScreenHeight();
	Column sidebar = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_Black);
	Image image = LoadImage("./images/logo.png");
	Column_AddElement(&sidebar, &ImageContainer_EleInit(Vector2Dummy, Vector2Dummy, &image));
	Column_AddElement(&sidebar, &Button_EleInit(Vector2Dummy, 0, "Menu button 1", &buttonOnClick));	
	Column_AddElement(&sidebar, &Button_EleInit(Vector2Dummy, 0, "Menu button 2", NULL));	
	Column_AddElement(&sidebar, &Label_EleInit(Vector2Dummy, 0, "Sample label with word wrap"));
	Label label = Label_Init((Vector2){500, 300}, 300, "(c) hyouteki");
	Column canvas = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_DarkBrown);
	Row row = Row_Init(Vector2Dummy, (Vector2){width, height}, 2,
					   (Column *[]){&sidebar, &canvas}, (u32 []){1, 3});
	
	while (!WindowShouldClose()) {
		width = GetScreenWidth(), height = GetScreenHeight();
		Row_Resize(&row, (Vector2){.x=width, .y=height});
		
		BeginDrawing();
		Row_Draw(row);
		Label_Draw(label);
		EndDrawing();
	}
	CloseWindow();
	
	return 0;
}
