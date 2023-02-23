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
    SIZE_SLIDER='sizs',
    SELECTIVITY_SLIDER='sels',
    M_ADD_POINTS='apts',
    M_SUB_POINTS='spts',
    M_WRITE_PNG='wpng',
    M_QUIT_APP='mqap'
};

#endif
