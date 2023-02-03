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

struct scatter_point {
    double     x;
    double     y;
    double     z;
    agg::rgba  color;
};

static double spline_r_x[] = { 0.000000, 0.200000, 0.400000, 0.910484, 0.957258, 1.000000 };
static double spline_r_y[] = { 1.000000, 0.800000, 0.600000, 0.066667, 0.169697, 0.600000 };

static double spline_g_x[] = { 0.000000, 0.292244, 0.485655, 0.564859, 0.795607, 1.000000 };
static double spline_g_y[] = { 0.000000, 0.607260, 0.964065, 0.892558, 0.435571, 0.000000 };

static double spline_b_x[] = { 0.000000, 0.055045, 0.143034, 0.433082, 0.764859, 1.000000 };
static double spline_b_y[] = { 0.385480, 0.128493, 0.021416, 0.271507, 0.713974, 1.000000 };

class AGGView : public BView {
public:
    AGGView(BRect r);
    ~AGGView();
    void Draw(BRect updateRect);
    void generate();
    BBitmap* renderCircles(BRect r, unsigned m_num_points, unsigned m_scale_ctrl_z_value1, unsigned m_scale_ctrl_z_value2, unsigned m_slider_ctrl_sel_value, unsigned m_slider_ctrl_size_value);
private:
    unsigned m_num_points;
    scatter_point* m_points;

    agg::bspline m_spline_r;
    agg::bspline m_spline_g;
    agg::bspline m_spline_b;
};

#endif // ELLIPSE_H
