/*
 * Copyright 2023, Tara Harris <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef SMOOTHSLIDER_H
#define SMOOTHSLIDER_H

#include <Slider.h>

class SmoothSlider : public BSlider {
public:
	SmoothSlider(BRect frame, const char *name, const char *label, BMessage *message, int32 minValue, int32 maxValue,
	thumb_style thumbType = B_BLOCK_THUMB,
	uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
	uint32 flags = B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);

	void MouseDown(BPoint point);
	void MouseMoved(BPoint point, uint32 transit, const BMessage *message);
	void MouseUp(BPoint point);
private:
	bool mouseDown;
};

#endif // SMOOTHSLIDER_H
