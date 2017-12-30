#ifndef __BDF_BOUNDING_BOX__H__
#define __BDF_BOUNDING_BOX__H__

struct BDFBoundingBox {
    inline BDFBoundingBox() : x(0), y(0), width(0), height(0) {}

    int x;
    int y;
    int width;
    int height;
};

#endif
