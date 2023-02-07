#include <iostream>
#include <Bitmap.h>
#include "AGGView.h"

AGGView::AGGView(BRect rect) : BView(rect, "AGG View", B_FOLLOW_ALL_SIDES, B_FRAME_EVENTS | B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE), pointCount(2000), circleDiameter(20), selectivity(0) {
    m_points = new scatter_point[pointCount];

    m_spline_r.init(6, spline_r_x, spline_r_y);
    m_spline_g.init(6, spline_g_x, spline_g_y);
    m_spline_b.init(6, spline_b_x, spline_b_y);

    initialRect = rect;
    currentRect = rect;

    trans_affine_resizing(rect.Width(), rect.Height(), true);

    this->generate();
}

AGGView::~AGGView() {
    delete [] m_points;
}

/*
void AGGView::AttachedToWindow() {
   if (Parent()) {
      SetViewColor(Parent()->ViewColor());
    }
    BView::AttachedToWindow();
}

void AGGView::DetachedFromWindow() {}
*/

void AGGView::Draw(BRect updateRect) {
    BBitmap* bitmap = renderCircles(updateRect, 1.0, 1.0);
    DrawBitmap(bitmap, updateRect, updateRect);
    delete bitmap;
}

void AGGView::FrameMoved(BPoint newLocation) {
    currentRect.SetLeftTop(newLocation);
}

void AGGView::FrameResized(float width, float height) {
    currentRect.SetRightBottom(initialRect.LeftTop() + BPoint(width, height));
    trans_affine_resizing(width + 1, height + 1, true);
    Draw(currentRect);
}

double random_dbl(double start, double end) {
    unsigned r = rand() & 0x7FFF;
    return double(r) * (end - start) / 32768.0 + start;
}

void AGGView::generate() {
    unsigned i;

    double width = initialRect.Width();
    double height = initialRect.Height();
    double rx = width/3.5;
    double ry = height/3.5;

    for(i = 0; i < pointCount; i++) {
        double z = m_points[i].z = random_dbl(0.0, 1.0);
        double x = cos(z * 2.0 * agg::pi) * rx;
        double y = sin(z * 2.0 * agg::pi) * ry;

        double dist  = random_dbl(0.0, rx/2.0);
        double angle = random_dbl(0.0, agg::pi * 2.0);

        m_points[i].x = width/2.0  + x + cos(angle) * dist;
        m_points[i].y = height/2.0 + y + sin(angle) * dist;
        m_points[i].color = agg::rgba(m_spline_r.get(z)*0.8,
                                      m_spline_g.get(z)*0.8,
                                      m_spline_b.get(z)*0.8,
                                      1.0);
    }
}

void AGGView::trans_affine_resizing(unsigned width, unsigned height, bool keepAspectRatio) {
    if (keepAspectRatio) {
        agg::trans_viewport vp;
        vp.preserve_aspect_ratio(0.5, 0.5, agg::aspect_ratio_meet);
        vp.device_viewport(0, 0, width, height);
        vp.world_viewport(0, 0, initialRect.Width(), initialRect.Height());
        resizeMatrix = vp.to_affine();
    } else {
        resizeMatrix = agg::trans_affine_scaling(
            width / initialRect.Width(),
            height / initialRect.Height());
    }
}

const agg::trans_affine& AGGView::trans_affine_resizing() const {
    return resizeMatrix;
}

BBitmap* AGGView::renderCircles(BRect r, unsigned m_scale_ctrl_z_value1, unsigned m_scale_ctrl_z_value2) {
    BBitmap* bitmap = new BBitmap(r, 0, B_RGBA32);

    agg::rendering_buffer buffer;
    buffer.attach((uint8*)bitmap->Bits(),
                  bitmap->Bounds().IntegerWidth() + 1,
                  bitmap->Bounds().IntegerHeight() + 1,
                  - bitmap->BytesPerRow());

    agg::rasterizer_scanline_aa<> pf;
    agg::scanline_p8 sl;

    typedef agg::pixfmt_bgra32 pixel_format_type;
    typedef agg::renderer_base<pixel_format_type> renderer_base;

    pixel_format_type pixf(buffer);
    renderer_base rb(pixf);

    rb.clear(agg::rgba(1.0, 1.0, 1.0));

    agg::ellipse e1;

    const agg::trans_affine resize_mtx = trans_affine_resizing();
    agg::conv_transform<agg::ellipse> t1(e1, resize_mtx);

    unsigned i;
    unsigned n_drawn = 0;
    for(i = 0; i < pointCount; i++) {
        double z = m_points[i].z;
        double alpha = 1.0;
        if(z < m_scale_ctrl_z_value1) {
            alpha =
                1.0 -
                (m_scale_ctrl_z_value1 - z) *
                selectivity;
        }

        if(z > m_scale_ctrl_z_value2) {
            alpha =
                1.0 -
                (z - m_scale_ctrl_z_value2) *
                selectivity;
        }

        if(alpha > 1.0) alpha = 1.0;
        if(alpha < 0.0) alpha = 0.0;

        if(alpha > 0.0) {
            e1.init(m_points[i].x,
                    m_points[i].y,
                    circleDiameter / 20,
                    circleDiameter / 20,
                    8);
            pf.add_path(t1);

            agg::render_scanlines_aa_solid(
                pf, sl, rb,
                agg::rgba(m_points[i].color.r,
                          m_points[i].color.g,
                          m_points[i].color.b,
                          alpha));
            n_drawn++;
        }
    }

    char buf[10];
    sprintf(buf, "%08u", n_drawn);

    agg::gsv_text txt;
    txt.size(15.0);
    txt.text(buf);
    txt.start_point(10.0, (initialRect.Height() - 20.0) * 1);
    agg::gsv_text_outline<> txt_o(txt, trans_affine_resizing());
    pf.add_path(txt_o);
    agg::render_scanlines_aa_solid(pf, sl, rb, agg::rgba(0,0,0));

    return bitmap;
}
