/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef TRIANGLEVIEW_H
#define TRIANGLEVIEW_H

#include <cstdio>

#include <Bitmap.h>
#include <View.h>

#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_conv_transform.h"
#include "agg_conv_curve.h"
#include "agg_bspline.h"
#include "agg_ellipse.h"
#include "agg_gsv_text.h"
#include "agg_scanline_p.h"
#include "agg_renderer_scanline.h"
#include "agg_path_storage.h"
#include "agg_pixfmt_rgba.h"
#include "agg_trans_viewport.h"

class TriangleView : public BView {
public:
    unsigned pixelSize;
    unsigned gamma;

    TriangleView(BRect rect);
    ~TriangleView();
//  void AttachedToWindow();
//  void DetachedFromWindow();
    void Draw(BRect updateRect);
    void FrameMoved(BPoint newLocation);
    void FrameResized(float width, float height);
private:
	double mX[3];
	double mY[3];
    BRect initialRect;
    BRect currentRect;
    agg::trans_affine resizeMatrix;
    BBitmap* retainedBitmap;
    agg::rendering_buffer buffer;

    void GeneratePoints();
    void InitBitmapAndBuffer();
    const agg::trans_affine& GetTransAffineResizingMatrix() const;
    void SetTransAffineResizingMatrix(unsigned width, unsigned height, bool keepAspectRatio);
    void RenderCircles(BRect rect);
};

#endif // TRIANGLEVIEW_H
