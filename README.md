> Simple GUI application framework made on top of Raylib.

<image src="./images/logo.png" width="1000">

## Demo
https://github.com/hyouteki/voyage/assets/108230497/7cec380d-fa85-4ed7-808b-cb2d5e473f27

<image src="./images/demo1.png" width="1000">

``` c
#include "export.h"

char *lorem = "Lorem ipsum dolor sit amet, ...";

void buttonOnClick() {
    printf("Menu button clicked\n");
}

int main() {
    Voyage_Setup(900, 720, 60, "Voyage Demo", FLAG_WINDOW_RESIZABLE);
    
    Column sidebar = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_Black);
    Image image = LoadImage("./images/logo.png");
    Column_AddElement(&sidebar, &ImageContainer_EleInit(&image));
    Column_AddElement(&sidebar, &Button_EleInit("Menu button 1", &buttonOnClick));
    Column_AddElement(&sidebar, &Button_EleInit("Menu button 2", NULL));
    Column_AddElement(&sidebar, &Label_EleInit("Sample label with word wrap"));

    Column canvas = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_DarkBrown);
    Column_AddElement(&canvas, &Button_EleInit("Button inside canvas", NULL));
    Column_AddElement(&canvas, &Heading_EleInit("Lorem Ipsum"));
    Column_AddElement(&canvas, &Label_EleInit(lorem));
    Column_AddElement(&canvas, &Label_EleInit(lorem));
    Column_AddElement(&canvas, &Label_EleInit(lorem));

    Row row = Row_Init(Vector2Dummy, Vector2Dummy, 2,
                       (Column *[]){&sidebar, &canvas}, (u32 []){1, 3});
    
    while (!WindowShouldClose()) {
        Row_Resize(&row, Voyage_ScreenDimen);
        Row_ScrollEventHandler(&row);

        BeginDrawing();
        ClearBackground(BLACK);
        Row_Draw(row);
        EndDrawing();
    }
    CloseWindow();
    Row_Free(&row);
    
    return 0;
}
```

## Quick Start
### Windows
- Build and install [Raylib](https://github.com/raysan5/raylib/wiki/Working-on-Windows).
- Open `w64devkit.exe` in `C:\raylib\w64devkit` then navigate to the **Voyage** dir and type the following.
``` bash
chmod +x build.sh
./build.sh
```

### GNU/Linux
``` bash
chmod +x build.sh
./build.sh
```
