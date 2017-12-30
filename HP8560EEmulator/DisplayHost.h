#ifndef DISPLAY_HOST__H
#define DISPLAY_HOST__H

#include <vector>

class DisplayHost {
protected:
    DisplayHost();
    ~DisplayHost();

public:
    DisplayHost(const DisplayHost &other) = delete;
    DisplayHost &operator =(const DisplayHost &other) = delete;

    virtual void setFrameBuffer(const std::vector<uint16_t> &frameBuffer) = 0;
    virtual void updateFrame() = 0;
};

#endif
