#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QFrame>
#include "DisplayHost.h"
#include "BDFFile.h"

class DisplayWidget final : public QFrame, public DisplayHost {
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = 0);
    virtual ~DisplayWidget();

    virtual void setFrameBuffer(const std::vector<uint16_t> &frameBuffer) override;
    virtual void updateFrame() override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private slots:
    void doUpdateFrame();

private:
    const std::vector<uint16_t> *m_framebuffer;
    BDFFile m_font;
};

#endif // DISPLAYWIDGET_H
