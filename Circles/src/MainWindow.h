#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Window.h>
#include <MenuBar.h>
#include <Slider.h>
#include <Button.h>

#include "AGGView.h"

class MainWindow : public BWindow {
public:
    MainWindow(void);
    void MessageReceived(BMessage *msg);
    bool QuitRequested(void);
private:
    BRect mainWindowRect;
    BMenuBar *menuBar;
    BWindow *toolWindow;
    BSlider *sizeSlider;
    BSlider *selectivitySlider;
    BButton *generateButton;
    AGGView* aggView;
};

#endif
