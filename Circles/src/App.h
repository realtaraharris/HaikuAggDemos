/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef APP_H
#define APP_H

#include <Application.h>

class App : public BApplication {
public:
    App(void);
};

enum {
    ASDF='asf',
    M_QUIT_APP='mqa',
    SIZE_SLIDER='sizs',
    SELECTIVITY_SLIDER='sels',
    GENERATE_BUTTON='gbtn'
};

#endif
