/*
 * Copyright 2023, Tara Harris <3769985+realtaraharris@users.noreply.github.com>
 * Portions copyright 2002-2006 Maxim Shemanarev
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "TriangleView.h"

#include "Renderer.cpp"

static double splineRX[] = { 0.000000, 0.200000, 0.400000, 0.910484, 0.957258, 1.000000 };
static double splineRY[] = { 1.000000, 0.800000, 0.600000, 0.066667, 0.169697, 0.600000 };

static double splineGX[] = { 0.000000, 0.292244, 0.485655, 0.564859, 0.795607, 1.000000 };
static double splineGY[] = { 0.000000, 0.607260, 0.964065, 0.892558, 0.435571, 0.000000 };

static double splineBX[] = { 0.000000, 0.055045, 0.143034, 0.433082, 0.764859, 1.000000 };
static double splineBY[] = { 0.385480, 0.128493, 0.021416, 0.271507, 0.713974, 1.000000 };

double randomDouble(double start, double end) {
    unsigned r = rand() & 0x7FFF;
    return double(r) * (end - start) / 32768.0 + start;
}

void attachBufferToBBitmap(agg::rendering_buffer& buffer, BBitmap* bitmap) {
    uint8* bits = (uint8*)bitmap->Bits();
    uint32 width = bitmap->Bounds().IntegerWidth() + 1;
    uint32 height = bitmap->Bounds().IntegerHeight() + 1;
    int32 bpr = bitmap->BytesPerRow();
    buffer.attach(bits, width, height, -bpr);
}

TriangleView::TriangleView(BRect rect) :
	BView(rect, "Triangle View", B_FOLLOW_ALL_SIDES, B_FRAME_EVENTS | B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
	pixelSize(32.0),
	gamma(1.0) {
    initialRect = rect;
    currentRect = rect;

    SetTransAffineResizingMatrix(rect.Width(), rect.Height(), true);

    InitBitmapAndBuffer();
}

TriangleView::~TriangleView() {}

void TriangleView::InitBitmapAndBuffer() {
    retainedBitmap = new BBitmap(currentRect, 0, B_RGBA32);
    if (retainedBitmap->IsValid()) {
        attachBufferToBBitmap(buffer, retainedBitmap);
    } else {
        delete retainedBitmap;
        retainedBitmap = NULL;
    }
}

//void TriangleView::AttachedToWindow() {}

//void TriangleView::DetachedFromWindow() {}

void TriangleView::Draw(BRect updateRect) {
    RenderCircles(updateRect);
    DrawBitmap(retainedBitmap, updateRect, updateRect);
}

// this is never actually called in this example because nothing moves the view frame
void TriangleView::FrameMoved(BPoint newLocation) {
    currentRect.SetLeftTop(newLocation);
}

void TriangleView::FrameResized(float width, float height) {
    currentRect.SetRightBottom(initialRect.LeftTop() + BPoint(width, height));
    SetTransAffineResizingMatrix(width + 1, height + 1, true);
    InitBitmapAndBuffer(); // do this before drawing
    Draw(currentRect);
}

void TriangleView::SetTransAffineResizingMatrix(unsigned width, unsigned height, bool keepAspectRatio) {
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

const agg::trans_affine& TriangleView::GetTransAffineResizingMatrix() const {
    return resizeMatrix;
}

void TriangleView::RenderCircles(BRect rect) {
    agg::rasterizer_scanline_aa<> pf; // aka ras?
    agg::scanline_p8 sl;

    typedef agg::pixfmt_bgra32 pixel_format_type;
    typedef agg::renderer_base<pixel_format_type> renderer_base;

    pixel_format_type pixf(buffer);
    renderer_base rb(pixf); // aka ren

    rb.clear(agg::rgba(1.0, 1.0, 1.0));
    
    pf.gamma(agg::gamma_power(gamma));

	mX[0] = 57; mY[0] = 100;
	mX[1] = 269; mY[1] = 170;
	mX[2] = 143; mY[2] = 310;

    pf.reset();
    pf.move_to_d(mX[0], mY[0]);
    pf.move_to_d(mX[1], mY[1]);
    pf.move_to_d(mX[2], mY[2]);

	int size_mul = int(pixelSize);
    agg::renderer_enlarged<renderer_base> ren_en(rb, size_mul);

	pf.reset();
	pf.move_to_d(mX[0] / size_mul, mY[0] / size_mul);
	pf.line_to_d(mX[1] / size_mul, mY[1] / size_mul);
	pf.line_to_d(mX[2] / size_mul, mY[2] / size_mul);
	ren_en.color(agg::rgba8(0, 0, 0, 255));
	agg::render_scanlines(pf, sl, ren_en);

	agg::render_scanlines_aa_solid(pf, sl, rb, agg::rgba8(0, 0, 0));

	pf.gamma(agg::gamma_none());
 
	agg::path_storage ps;
	agg::conv_stroke<agg::path_storage> pg(ps);
	pg.width(2.0);
	
	ps.remove_all();
	ps.move_to(mX[0], mY[0]);
	ps.line_to(mX[1], mY[1]);
	pf.add_path(pg);
    agg::render_scanlines_aa_solid(pf, sl, rb, agg::rgba8(0, 150, 160, 200));

	ps.remove_all();
	ps.move_to(mX[1], mY[1]);
	ps.line_to(mX[2], mY[2]);
	pf.add_path(pg);
    agg::render_scanlines_aa_solid(pf, sl, rb, agg::rgba8(0, 150, 160, 200));

	ps.remove_all();
	ps.move_to(mX[2], mY[2]);
	ps.line_to(mX[0], mY[0]);
	pf.add_path(pg);
    agg::render_scanlines_aa_solid(pf, sl, rb, agg::rgba8(0, 150, 160, 200));
}
