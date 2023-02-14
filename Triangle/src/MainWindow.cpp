/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
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
#include "TriangleView.h"

MainWindow::MainWindow(void) :
    BWindow(BRect(100, 100, 400, 600), "Triangle", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS, B_CURRENT_WORKSPACE) {
    BRect rect(Bounds());

    menuBar = new BMenuBar(rect, "menubar");
    AddChild(menuBar);

    BMenu *menu = new BMenu("App");
    menu->AddItem(new BMenuItem("Quit", new BMessage(M_QUIT_APP), 'Q'));
    menuBar->AddItem(menu);

    rect.Set(0, 0, 300, 300);
    triangleView = new TriangleView(rect);

    rect.Set(0, 0, 1, 1);
    pixelSizeSlider = new SmoothSlider(rect, NULL, "Pixel Size", new BMessage(PIXEL_SIZE_SLIDER), 8.0, 100.0, B_TRIANGLE_THUMB);

    rect.Set(0, 0, 1, 1);
    gammaSlider = new SmoothSlider(rect, NULL, "Gamma", new BMessage(GAMMA_SLIDER), 0.1, 3.0, B_TRIANGLE_THUMB);

    mainWindowRect = Bounds();

    BBox* divider = new BBox(BRect(0, 0, 1, 1), B_EMPTY_STRING, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS, B_FANCY_BORDER);
    SetLayout(new BGroupLayout(B_VERTICAL));

    AddChild(BGroupLayoutBuilder(B_VERTICAL)
        .Add(triangleView)
        .Add(BGroupLayoutBuilder(B_VERTICAL)
            .Add(pixelSizeSlider)
            .Add(gammaSlider)
            .SetInsets(5, 5, 5, 5)
        )
    );
}

void MainWindow::MessageReceived(BMessage *message) {
    switch (message->what) {
        case PIXEL_SIZE_SLIDER: {
            triangleView->pixelSize = pixelSizeSlider->Value();
            triangleView->Invalidate();
            break;
        }
        case GAMMA_SLIDER: {
            triangleView->gamma = gammaSlider->Value();
            triangleView->Invalidate();
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
