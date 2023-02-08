#ifndef ELLIPSE_H
#define ELLIPSE_H

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

static double splineRX[] = { 0.000000, 0.200000, 0.400000, 0.910484, 0.957258, 1.000000 };
static double splineRY[] = { 1.000000, 0.800000, 0.600000, 0.066667, 0.169697, 0.600000 };

static double splineGX[] = { 0.000000, 0.292244, 0.485655, 0.564859, 0.795607, 1.000000 };
static double splineGY[] = { 0.000000, 0.607260, 0.964065, 0.892558, 0.435571, 0.000000 };

static double splineBX[] = { 0.000000, 0.055045, 0.143034, 0.433082, 0.764859, 1.000000 };
static double splineBY[] = { 0.385480, 0.128493, 0.021416, 0.271507, 0.713974, 1.000000 };

class AGGView : public BView {
public:
    AGGView(BRect rect);
    ~AGGView();
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

#endif // ELLIPSE_H
