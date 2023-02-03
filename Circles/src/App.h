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
    SELECTIVITY_SLIDER='sels'
};

#endif
