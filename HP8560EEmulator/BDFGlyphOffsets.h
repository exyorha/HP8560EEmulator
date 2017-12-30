#ifndef __BDF_GLYPH_OFFSETS__H__
#define __BDF_GLYPH_OFFSETS__H__

struct BDFGlyphOffsets {
    inline BDFGlyphOffsets() : scalableWidthX(0), scalableWidthY(0), deviceWidthX(0), deviceWidthY(0),
                               mode1ScalableWidthX(0), mode1ScalableWidthY(0), mode1DeviceWidthX(0), mode1DeviceWidthY(0),
                               mode0to1OffsetX(0), mode0to1OffsetY(0) {}

    int scalableWidthX;
    int scalableWidthY;
    int deviceWidthX;
    int deviceWidthY;
    int mode1ScalableWidthX;
    int mode1ScalableWidthY;
    int mode1DeviceWidthX;
    int mode1DeviceWidthY;
    int mode0to1OffsetX;
    int mode0to1OffsetY;
};

#endif
