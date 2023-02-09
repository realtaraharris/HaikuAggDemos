/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "App.h"
#include "MainWindow.h"

App::App(void) : BApplication("application/x-vnd.dw-TestApp") {
    MainWindow *mainwin = new MainWindow();
    mainwin->Show();
}

int main(void) {
    App *app = new App();
    app->Run();
    delete app;
    return 0;
}
