/*
 * Copyright 2002-2006 Maxim Shemanarev
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "agg_basics.h"
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_u.h"
#include "agg_renderer_scanline.h"
#include "agg_pixfmt_rgb.h"

namespace agg {
    class square {
    public:
        square(double size) : m_size(size) {}

        template<class Rasterizer, class Scanline, class Renderer, class ColorT> 
        void draw(Rasterizer& ras, Scanline& sl, Renderer& ren, ColorT color, 
                  double x, double y) {
            ras.reset();
            ras.move_to_d(x*m_size,        y*m_size);
            ras.line_to_d(x*m_size+m_size, y*m_size);
            ras.line_to_d(x*m_size+m_size, y*m_size+m_size);
            ras.line_to_d(x*m_size,        y*m_size+m_size);
            agg::render_scanlines_aa_solid(ras, sl, ren, color);
        }

    private:
        double m_size;
    };

    template<class Renderer> class renderer_enlarged {
    public:
        renderer_enlarged(Renderer& ren, double size) : 
            m_ren(ren),
            m_square(size), 
            m_size(size) {}

        void color(rgba8 c) { m_color = c; }

        void prepare() {}

        template<class Scanline> void render(const Scanline& sl) {
            int y = sl.y();

            unsigned num_spans = sl.num_spans();
            typename Scanline::const_iterator span = sl.begin();

            do {
                int x = span->x;
                const typename Scanline::cover_type* covers = span->covers;
                int num_pix = span->len;
                
                do {
                    int a = (*covers++ * m_color.a) >> 8;
                    m_square.draw(m_ras, m_sl, m_ren, 
                                  rgba8(m_color.r, m_color.g, m_color.b, a),
                                  x, y);
                    ++x;
                }
                while(--num_pix);
            }
            while(--num_spans);
        }

    private:
        rasterizer_scanline_aa<> m_ras;
        scanline_u8 m_sl;
        Renderer&   m_ren;
        square      m_square;
        rgba8       m_color;
        double      m_size;
    };
};
