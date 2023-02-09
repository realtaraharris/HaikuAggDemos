#include <iostream>

#include <Application.h>
#include <Menu.h>
#include <MenuItem.h>
#include <View.h>
#include <Alert.h> // BAlert
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>
#include <Box.h>

#include "App.h" // contains message enums

#include "MainWindow.h"
#include "AGGView.h"

MainWindow::MainWindow(void) :
    BWindow(BRect(100, 100, 400, 600), "Main Window", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS, B_CURRENT_WORKSPACE) {
    BRect rect(Bounds());

    menuBar = new BMenuBar(rect, "menubar");
    AddChild(menuBar);

    BMenu *menu = new BMenu("File");
    menu->AddItem(new BMenuItem("Quit", new BMessage(M_QUIT_APP), 'Q'));
    menuBar->AddItem(menu);

    rect.Set(0, 0, 300, 300);
    aggView = new AGGView(rect);

    rect.Set(0, 0, 1, 1);
    sizeSlider = new SmoothSlider(rect, NULL, "Size", new BMessage(SIZE_SLIDER), 20, 120, B_TRIANGLE_THUMB);

    rect.Set(0, 0, 1, 1);
    selectivitySlider = new SmoothSlider(rect, NULL, "Selectivity", new BMessage(SELECTIVITY_SLIDER), 0, 100, B_TRIANGLE_THUMB);

    rect.Set(0, 0, 1, 1);
    generateButton = new BButton(rect, NULL, "Generate Points", new BMessage(GENERATE_BUTTON));

    mainWindowRect = Bounds();

    BBox* divider = new BBox(BRect(0, 0, 1, 1), B_EMPTY_STRING, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS, B_FANCY_BORDER);
    SetLayout(new BGroupLayout(B_VERTICAL));

    AddChild(BGroupLayoutBuilder(B_VERTICAL)
        .Add(aggView)
        .Add(BGroupLayoutBuilder(B_VERTICAL)
            .Add(sizeSlider)
            .Add(selectivitySlider)
            .Add(generateButton)
            .SetInsets(5, 5, 5, 5)
        )
    );
}

void MainWindow::MessageReceived(BMessage *message) {
    switch (message->what) {
        case SIZE_SLIDER: {
            aggView->circleDiameter = sizeSlider->Value();
            aggView->Invalidate();
            break;
        }
        case SELECTIVITY_SLIDER: {
            aggView->selectivity = selectivitySlider->Value();
            aggView->Invalidate();
            break;
        }
        case GENERATE_BUTTON: {
            aggView->GeneratePoints();
            aggView->Invalidate();
            break;
        }
        case M_QUIT_APP: {
            be_app->PostMessage(B_QUIT_REQUESTED);
            break;
        }
        default: {
            BWindow::MessageReceived(message);
            break;
        }
    }
}

bool MainWindow::QuitRequested(void) {
    be_app->PostMessage(B_QUIT_REQUESTED);
    return true;
}
