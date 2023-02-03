/*
#include "agg_rendering_buffer.h"
#include "agg_conv_curve.h"
#include "agg_conv_transform.h"
#include "agg_bspline.h"
#include "agg_gsv_text.h"
*/
#include "agg_ellipse.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_p.h"
#include "agg_renderer_scanline.h"
#include "agg_path_storage.h"
#include "agg_pixfmt_rgba.h"

#include <Bitmap.h>

#include "AGGView.h"

AGGView::AGGView(BRect r) : BView(r, "AGG View", B_FOLLOW_ALL, B_FRAME_EVENTS | B_WILL_DRAW) {}
AGGView::~AGGView() {}

void AGGView::Draw(BRect updateRect) {
    BBitmap* fBitmap = renderCircles(updateRect, 1000);
    DrawBitmap(fBitmap, updateRect, updateRect);
}

BBitmap* renderCircles(BRect r, unsigned m_num_points) {
    BBitmap* bitmap = new BBitmap(r, 0, B_RGBA32);

    agg::rendering_buffer buffer;
    buffer.attach((uint8*)bitmap->Bits(),
                  bitmap->Bounds().IntegerWidth() + 1,
                  bitmap->Bounds().IntegerHeight() + 1,
                  bitmap->BytesPerRow());

    agg::rasterizer_scanline_aa<> pf;
    agg::scanline_p8 sl;

    typedef agg::pixfmt_bgra32 pixel_format_type;
    typedef agg::renderer_base<pixel_format_type> renderer_base;

    pixel_format_type pixf(buffer);
    renderer_base rb(pixf);

    rb.clear(agg::rgba(1,1,1));

    agg::ellipse e1;
    
    const agg::trans_affine resize_mtx = agg::trans_affine_scaling(1.0, 1.0);
    agg::conv_transform<agg::ellipse> t1(e1, resize_mtx);

/*
    unsigned i;
    unsigned n_drawn = 0;
    for(i = 0; i < m_num_points; i++) {
        double z = m_points[i].z;
        double alpha = 1.0;
        if(z < m_scale_ctrl_z.value1()) {
            alpha =
                1.0 -
                (m_scale_ctrl_z.value1() - z) *
                m_slider_ctrl_sel.value() * 100.0;
        }

        if(z > m_scale_ctrl_z.value2()) {
            alpha =
                1.0 -
                (z - m_scale_ctrl_z.value2()) *
                m_slider_ctrl_sel.value() * 100.0;
        }

        if(alpha > 1.0) alpha = 1.0;
        if(alpha < 0.0) alpha = 0.0;

        if(alpha > 0.0) { */
            e1.init(40,
                    40,
                    5 * 5.0,
                    5 * 5.0,
                    80);
            pf.add_path(t1);

            agg::render_scanlines_aa_solid(
                pf, sl, rb,
                agg::rgba(128,
                          128,
                          128,
                          1.0));
/*
            e1.init(m_points[i].x,
                    m_points[i].y,
                    m_slider_ctrl_size.value() * 5.0,
                    m_slider_ctrl_size.value() * 5.0,
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
    txt.start_point(10.0, initial_height() - 20.0);
    agg::gsv_text_outline<> txt_o(txt, trans_affine_resizing());
    pf.add_path(txt_o);
    agg::render_scanlines_aa_solid(pf, sl, rb, agg::rgba(0,0,0));
    */
    return bitmap;
}
