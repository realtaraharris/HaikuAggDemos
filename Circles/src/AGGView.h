#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <View.h>
#include <Bitmap.h>

class AGGView : public BView {
public:
    BBitmap* bitty;
    AGGView(BRect r);
    ~AGGView();
    void Draw(BRect updateRect);
};

BBitmap* renderCircles(BRect r, unsigned m_num_points);

#endif // ELLIPSE_H
