/*
 * Copyright 2023, Tara Harris <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "SmoothSlider.h"

SmoothSlider::SmoothSlider(BRect frame, const char *name, const char *label, BMessage *message, int32 minValue, int32 maxValue, thumb_style thumbType, uint32 resizingMode, uint32 flags) :
    BSlider(frame, name, label, message, minValue, maxValue, thumbType, resizingMode, flags),
    mouseDown(false) {}

void SmoothSlider::MouseDown(BPoint point) {
	mouseDown = true;
	BSlider::MouseDown(point);
	Invoke();
}

void SmoothSlider::MouseMoved(BPoint point, uint32 transit, const BMessage *message) {
	if (mouseDown) {
		Invoke();
	}
	BSlider::MouseMoved(point, transit, message);
}

void SmoothSlider::MouseUp(BPoint point) {
	mouseDown = false;
	BSlider::MouseUp(point);
	Invoke();
}
