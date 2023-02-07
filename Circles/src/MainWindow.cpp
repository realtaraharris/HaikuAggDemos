#include <iostream>

#include <Application.h>
#include <Menu.h>
#include <MenuItem.h>
#include <View.h>
#include <Alert.h> // BAlert
#include "App.h" // contains message enums

#include "MainWindow.h"
#include "AGGView.h"

MainWindow::MainWindow(void) :
    BWindow(BRect(100, 100, 600, 800), "Main Window", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS, B_CURRENT_WORKSPACE) {
    BRect rect(Bounds());

    rect.bottom = 20;
    menuBar = new BMenuBar(rect, "menubar");
    AddChild(menuBar);

    BMenu *menu = new BMenu("File");
    menu->AddItem(new BMenuItem("Quit", new BMessage(M_QUIT_APP), 'Q'));
    menuBar->AddItem(menu);

    rect.Set(0, 20, 500, 520);
    aggView = new AGGView(rect);
    AddChild(aggView);

    rect.Set(5, 520, 255, 55);
    sizeSlider = new BSlider(rect, NULL, "Size", new BMessage(SIZE_SLIDER), 20, 120);
    AddChild(sizeSlider);

    rect.Set(5, 560, 255, 55);
    selectivitySlider = new BSlider(rect, NULL, "Selectivity", new BMessage(SELECTIVITY_SLIDER), 0, 20);
    AddChild(selectivitySlider);

    rect.Set(5, 600, 100, 55);
    generateButton = new BButton(rect, NULL, "Generate Points", new BMessage(GENERATE_BUTTON));
    AddChild(generateButton);

    mainWindowRect = Bounds();
}

void MainWindow::MessageReceived(BMessage *message) {
    switch (message->what) {
        case SIZE_SLIDER: {
            aggView->circleDiameter = sizeSlider->Value();
            aggView->Draw(BRect(0, 20, 500, 520));
            break;
        }
        case SELECTIVITY_SLIDER: {
            aggView->selectivity = selectivitySlider->Value();
            aggView->Draw(BRect(0, 20, 500, 520));
            break;
        }
        case GENERATE_BUTTON: {
            aggView->GeneratePoints();
            aggView->Draw(BRect(0, 20, 500, 520));
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
