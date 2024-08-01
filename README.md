> Minimal GUI application framework made on top of Raylib.

<image src="./resources/logo.png" width="1000">

Voyage is a versatile framework that supports writing GUIs in both C and XML. This allows for flexible and efficient GUI development tailored to various needs.

## Features

- **Hybrid GUI Development**: Design your GUI using XML for layout and style, and enhance it with C for dynamic behavior.
- **Customizable Components**: Easily create and customize buttons, labels, images, inputs, and more.
- **Responsive Design**: Build adaptive interfaces that look great on different screen sizes.

## Cross Platform Support

| Platform | Status             | Notes                            |
|----------|--------------------|----------------------------------|
| Linux    | ✔️Supported | Full functionality available     |
| Windows  | ✔️Supported | Full functionality available     |
| Web      | ✖️Planned   | Future support under development |


## Demo

<image src="./resources/demo1.png" width="1000">

### GUI with C and XML
``` xml
<row id="main">
  <column id="sidebar" weight="1" background="black">
    <image id="logo" src="./resources/logo.png"/>
    <button id="menu-button-1" text="Menu button 1"/>
    <label id="menu-label" text="Sample label with word wrap"/>
  </column>
  <column id="canvas" weight="3" background="dark-brown">
    <button id="button-canvas" text="Button inside Canvas"/>
    <button id="fixed-button" text="Fixed Button inside Canvas" fixed="true"/>
    <label id="lorem-heading" foreground="light-green" font-size="36" text="Lorem Ipsum"/>
    <label id="lorem" text="This is Voyage Demo written with C and XML." font="./resources/PlayFair.ttf"/>
    <label id="input-desc" text="Type something in the bellow input field."/>
    <input id="input"/>
    <space id="space" height="100"/>
    <label id="space-label" text="There's 100 pixels worth of empty space above."/>
    <quote id="quote" text="This is a Quote."/>
  </column>
</row>
```
``` c
#include "export.h"

void buttonOnClick() {
    printf("Menu button clicked\n");
}

int main() {
    Voyage_Setup(900, 720, 60, "Voyage Demo", FLAG_WINDOW_RESIZABLE);
    Voyage_SetContentView("demo_xml_content_view.xml");
    
    Button *menuButton = Voyage_GetElementById("menu-button-1");
    menuButton->onClick = &buttonOnClick;
    
    Voyage_MainLoop();
    
    return 0;
}
```
### GUI solely in C
``` c
#include "export.h"

void buttonOnClick() {
    printf("Menu button clicked\n");
}

int main() {
    Voyage_Setup(900, 720, 60, "Voyage Demo", FLAG_WINDOW_RESIZABLE);
    
    Column sidebar = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_Black);
    Image image = LoadImage("./resources/logo.png");
    Column_Add(&sidebar, &ImageContainer_EleInit(&image));
    Column_Add(&sidebar, &Button_EleInit("Menu button 1", &buttonOnClick));
    Column_Add(&sidebar, &Label_EleInit("Sample label with word wrap"));

    Column canvas = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_DarkBrown);
    Column_AddF(&canvas, &Button_EleInit("Fixed button inside canvas", NULL));
    Column_Add(&canvas, &Button_EleInit("Button inside canvas", NULL));
    Column_Add(&canvas, &Heading_EleInit("Lorem Ipsum"));
    Column_Add(&canvas, &Label_EleInit("This is Voyage Demo written with C."));
    Column_Add(&canvas, &Label_EleInit("Type something in the bellow input field."));
    Column_Add(&canvas, &Input_EleInit("", NULL));
    Column_Add(&canvas, &Space_EleInit(100));
    Column_Add(&canvas, &Label_EleInit("There's 100 pixels worth of empty space above."));
    Column_Add(&canvas, &Quote_EleInit("This is a quote."));

    Row row = Row_Init(Vector2Dummy, Vector2Dummy, 2,
                       (Column *[]){&sidebar, &canvas}, (u32 []){1, 3});
    
    while (!WindowShouldClose()) {
        Row_Resize(&row, Voyage_ScreenDimen);
        Row_AttachListeners(&row);

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

## Getting Started
Ensure you have Raylib installed. Follow the [Raylib installation guide](https://github.com/raysan5/raylib/wiki) for your operating system.	

### GNU/Linux
``` bash
chmod +x build.sh
./build.sh
```

### Windows
- Build and install [Raylib](https://github.com/raysan5/raylib/wiki/Working-on-Windows).
- Open `w64devkit.exe` in `C:\raylib\w64devkit` then navigate to the **Voyage** dir and type the following.
``` bash
chmod +x build.sh
./build.sh
```

## Dependencies
- [Raylib - raysan5](https://github.com/raysan5/raylib)
- [Cxmlp - hyouteki](https://github.com/hyouteki/cxmlp)
- [Steel - hyouteki](https://github.com/hyouteki/steel)
