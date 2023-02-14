/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include <MenuBar.h>
#include <Button.h>

#include "TriangleView.h"
#include "SmoothSlider.h"

class MainWindow : public BWindow {
public:
    MainWindow(void);
    void MessageReceived(BMessage *msg);
    bool QuitRequested(void);
private:
    BRect mainWindowRect;
    BMenuBar *menuBar;
    BWindow *toolWindow;
    SmoothSlider *pixelSizeSlider;
    SmoothSlider *gammaSlider;
    BButton *generateButton;
    TriangleView* triangleView;
};

#endif
