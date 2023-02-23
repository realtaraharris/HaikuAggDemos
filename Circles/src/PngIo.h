/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef PNGIO_H
#define PNGIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <png.h>

#include <Bitmap.h>
#include <InterfaceDefs.h>
#include <SupportDefs.h>

int writePng(BBitmap *bitmap, char* outFilename);

#endif // PNGIO_H
