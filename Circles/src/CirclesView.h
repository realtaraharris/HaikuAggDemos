/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef CIRCLESVIEW_H
#define CIRCLESVIEW_H

#include <View.h>
#include <Bitmap.h>

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

struct ScatterPoint {
    double x;
    double y;
    double z;
    agg::rgba color;
};

class CirclesView : public BView {
public:
    CirclesView(BRect rect);
    ~CirclesView();
//  void AttachedToWindow();
//  void DetachedFromWindow();
    void InitBitmapAndBuffer();
    void Draw(BRect updateRect);
    void FrameMoved(BPoint newLocation);
    void FrameResized(float width, float height);
    const agg::trans_affine& GetTransAffineResizingMatrix() const;
    void SetTransAffineResizingMatrix(unsigned width, unsigned height, bool keepAspectRatio);
    void GeneratePoints();
    void RenderCircles(BRect rect);

    unsigned circleDiameter;
    unsigned selectivity;
    unsigned z1;
    unsigned z2;
private:
    unsigned pointCount;
    ScatterPoint* scatterPoints;
    agg::bspline splineR;
    agg::bspline splineG;
    agg::bspline splineB;
    BRect initialRect;
    BRect currentRect;
    agg::trans_affine resizeMatrix;
    BBitmap* retainedBitmap;
    agg::rendering_buffer buffer;
};

#endif // CIRCLESVIEW_H
