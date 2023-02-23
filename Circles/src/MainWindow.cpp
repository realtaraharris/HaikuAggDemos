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
#include "CirclesView.h"

MainWindow::MainWindow(void) :
    BWindow(BRect(100, 100, 400, 600), "Circles", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS, B_CURRENT_WORKSPACE) {
    BRect rect(Bounds());

    menuBar = new BMenuBar(rect, "menubar");
    AddChild(menuBar);

    BMenu *menu = new BMenu("App");
    menu->AddItem(new BMenuItem("Add Points", new BMessage(M_ADD_POINTS), 'A'));
    menu->AddItem(new BMenuItem("Subtract Points", new BMessage(M_SUB_POINTS), 'S'));
    menu->AddItem(new BMenuItem("Write to Png", new BMessage(M_WRITE_PNG), 'P'));
    menu->AddItem(new BMenuItem("Quit", new BMessage(M_QUIT_APP), 'Q'));
    menuBar->AddItem(menu);

    rect.Set(0, 0, 300, 300);
    circlesView = new CirclesView(rect);

    rect.Set(0, 0, 1, 1);
    sizeSlider = new SmoothSlider(rect, NULL, "Size", new BMessage(SIZE_SLIDER), 20, 120, B_TRIANGLE_THUMB);

    rect.Set(0, 0, 1, 1);
    selectivitySlider = new SmoothSlider(rect, NULL, "Selectivity", new BMessage(SELECTIVITY_SLIDER), 0, 100, B_TRIANGLE_THUMB);

    mainWindowRect = Bounds();

    BBox* divider = new BBox(BRect(0, 0, 1, 1), B_EMPTY_STRING, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS, B_FANCY_BORDER);
    SetLayout(new BGroupLayout(B_VERTICAL));

    AddChild(BGroupLayoutBuilder(B_VERTICAL)
        .Add(circlesView)
        .Add(BGroupLayoutBuilder(B_VERTICAL)
            .Add(sizeSlider)
            .Add(selectivitySlider)
            .SetInsets(5, 5, 5, 5)
        )
    );
}

void MainWindow::MessageReceived(BMessage *message) {
    switch (message->what) {
        case SIZE_SLIDER: {
            circlesView->circleDiameter = sizeSlider->Value();
            circlesView->Invalidate();
            break;
        }
        case SELECTIVITY_SLIDER: {
            circlesView->selectivity = selectivitySlider->Value();
            circlesView->Invalidate();
            break;
        }
        case M_ADD_POINTS: {
            circlesView->ChangePointCount(1000);
            circlesView->Invalidate();
            break;
        }
        case M_SUB_POINTS: {
            circlesView->ChangePointCount(-1000);
            circlesView->Invalidate();
            break;
        }
        case M_WRITE_PNG: {
            circlesView->SaveToPng();
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
