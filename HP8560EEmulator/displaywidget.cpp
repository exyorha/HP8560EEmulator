#include "displaywidget.h"

#include <QPainter>
#include <unordered_map>
#include <QKeyEvent>

#include <sstream>

DisplayWidget::DisplayWidget(QWidget *parent) : QFrame(parent), m_framebuffer(nullptr) {
    setFocusPolicy(Qt::StrongFocus);

    /*QFile fontFile(":/ter-u24n.bdf");
    fontFile.open(QIODevice::ReadOnly);
    std::stringstream stream(QString::fromLatin1(fontFile.readAll()).toStdString());
    fontFile.close();

    m_font = BDFFile::parse(stream);*/
}

DisplayWidget::~DisplayWidget() {

}

void DisplayWidget::paintEvent(QPaintEvent *event) {
    static const std::unordered_map<uint16_t, uint32_t> charToUnicode = {
      { 0x2b, 0x20 },
      { 0x2c, 0x21 },
      { 0x32, 0x22 },
      { 0x37, 0x23 },
      { 0x44, 0x24 },
      { 0x52, 0x25 },
      { 0x5a, 0x26 },
      { 0x67, 0x27 },
      { 0x6a, 0x28 },
      { 0x6f, 0x29 },
      { 0x74, 0x2a },
      { 0x7b, 0x2b },
      { 0x82, 0x2c },
      { 0x88, 0x2d },
      { 0x8c, 0x2e },
      { 0x91, 0x2f },
      { 0x95, 0x30 },
      { 0xa1, 0x31 },
      { 0xa8, 0x32 },
      { 0xb2, 0x33 },
      { 0xbe, 0x34 },
      { 0xc6, 0x35 },
      { 0xd1, 0x36 },
      { 0xdc, 0x37 },
      { 0xe2, 0x38 },
      { 0xef, 0x39 },
      { 0xfa, 0x3a },
      { 0x103, 0x3b },
      { 0x10d, 0x3c },
      { 0x113, 0x3d },
      { 0x11a, 0x3e },
      { 0x120, 0x3f },
      { 0x129, 0x40 },
      { 0x137, 0x41 },
      { 0x140, 0x42 },
      { 0x14e, 0x43 },
      { 0x157, 0x44 },
      { 0x160, 0x45 },
      { 0x16b, 0x46 },
      { 0x174, 0x47 },
      { 0x17f, 0x48 },
      { 0x189, 0x49 },
      { 0x191, 0x4a },
      { 0x198, 0x4b },
      { 0x1a2, 0x4c },
      { 0x1a8, 0x4d },
      { 0x1b2, 0x4e },
      { 0x1ba, 0x4f },
      { 0x1c5, 0x50 },
      { 0x1cd, 0x51 },
      { 0x1da, 0x52 },
      { 0x1e5, 0x53 },
      { 0x1ef, 0x54 },
      { 0x1f6, 0x55 },
      { 0x1fe, 0x56 },
      { 0x204, 0x57 },
      { 0x20e, 0x58 },
      { 0x215, 0x59 },
      { 0x21d, 0x5a },
      { 0x225, 0x5b },
      { 0x22c, 0x5c },
      { 0x230, 0x5d },
      { 0x237, 0x5e },
      { 0x23d, 0x5f },
      { 0x241, 0x60 },
      { 0x244, 0x61 },
      { 0x24e, 0x62 },
      { 0x258, 0x63 },
      { 0x25f, 0x64 },
      { 0x269, 0x65 },
      { 0x272, 0x66 },
      { 0x27a, 0x67 },
      { 0x286, 0x68 },
      { 0x28e, 0x69 },
      { 0x294, 0x6a },
      { 0x29c, 0x6b },
      { 0x2a4, 0x6c },
      { 0x2a8, 0x6d },
      { 0x2b3, 0x6e },
      { 0x2ba, 0x6f },
      { 0x2c2, 0x70 },
      { 0x2cc, 0x71 },
      { 0x2d6, 0x72 },
      { 0x2dc, 0x73 },
      { 0x2e5, 0x74 },
      { 0x2ec, 0x75 },
      { 0x2f3, 0x76 },
      { 0x2f7, 0x77 },
      { 0x2fd, 0x78 },
      { 0x304, 0x79 },
      { 0x30c, 0x7a },
      { 0x314, 0x7b },
      { 0x31c, 0x7c },
      { 0x320, 0x7d },
      { 0x328, 0x7e },
      { 0x399, 0x7f },
      { 0x32e, 0x80 },
      { 0x32f, 0x81 },
      { 0x330, 0x82 },
      { 0x331, 0x83 },
      { 0x332, 0x84 },
      { 0x333, 0x85 },
      { 0x334, 0x86 },
      { 0x335, 0x87 },
      { 0x336, 0x88 },
      { 0x337, 0x89 },
      { 0x338, 0x8a },
      { 0x339, 0x8b },
      { 0x33a, 0x8c },
      { 0x33b, 0x8d },
      { 0x33c, 0x8e },
      { 0x33d, 0x8f },
      { 0x33e, 0x90 },
      { 0x33f, 0x91 },
      { 0x341, 0x92 },
      { 0x343, 0x93 },
      { 0x345, 0x94 },
      { 0x347, 0x95 },
      { 0x348, 0x96 },
      { 0x349, 0x97 },
      { 0x34a, 0x98 },
      { 0x34b, 0x99 },
      { 0x34c, 0x9a },
      { 0x34d, 0x9b },
      { 0x34e, 0x9c },
      { 0x34f, 0x9d },
      { 0x350, 0x9e },
      { 0x351, 0x9f },
      { 0x352, 0xa0 },
      { 0x358, 0xa1 },
      { 0x35c, 0xa2 },
      { 0x361, 0xa3 },
      { 0x36b, 0xa4 },
      { 0x377, 0xa5 },
      { 0x381, 0xa6 },
      { 0x38f, 0xa7 },
      { 0x392, 0xa8 },
      { 0x399, 0xa9 },
      { 0x3a0, 0xaa },
      { 0x3af, 0xab },
      { 0x3b9, 0xac },
      { 0x3bf, 0xad },
      { 0x3c3, 0xae },
      { 0x3c8, 0xaf },
      { 0x3d0, 0xb0 },
      { 0x3d8, 0xb1 },
      { 0x3db, 0xb2 },
      { 0x3e1, 0xb3 },
      { 0x3e8, 0xb4 },
      { 0x3ed, 0xb5 },
      { 0x3f3, 0xb6 },
      { 0x3fa, 0xb7 },
      { 0x3ff, 0xb8 },
      { 0x404, 0xb9 },
      { 0x40c, 0xba },
      { 0x413, 0xbb },
      { 0x41a, 0xbc },
      { 0x423, 0xbd },
      { 0x42d, 0xbe },
      { 0x436, 0xbf },
      { 0x43a, 0xc0 },
      { 0x440, 0xc1 },
      { 0x446, 0xc2 },
      { 0x44f, 0xc3 },
      { 0x458, 0xc4 },
      { 0x460, 0xc5 },
      { 0x461, 0xc6 },
      { 0x462, 0xc7 },
      { 0x46d, 0xc8 },
      { 0x475, 0xc9 },
      { 0x47a, 0xca },
      { 0x47b, 0xcb },
      { 0x47c, 0xcc },
      { 0x480, 0xcd },
      { 0x487, 0xce },
      { 0x48e, 0xcf },
      { 0x496, 0xd0 },
      { 0x49f, 0xd1 },
      { 0x4ab, 0xd2 },
      { 0x4b1, 0xd3 },
      { 0x4b8, 0xd4 },
      { 0x4bd, 0xd5 },
      { 0x4c7, 0xd6 },
      { 0x4cb, 0xd7 },
      { 0x4cc, 0xd8 },
      { 0x4d3, 0xd9 },
      { 0x4da, 0xda },
      { 0x4db, 0xdb },
      { 0x4e9, 0xdc },
      { 0x4f5, 0xdd },
      { 0x502, 0xde },
      { 0x510, 0xdf },
      { 0x512, 0xe0 },
      { 0x51c, 0xe1 },
      { 0x526, 0xe2 },
      { 0x534, 0xe3 },
      { 0x53b, 0xe4 },
      { 0x546, 0xe5 },
      { 0x54f, 0xe6 },
      { 0x559, 0xe7 },
      { 0x560, 0xe8 },
      { 0x567, 0xe9 },
      { 0x56c, 0xea },
      { 0x577, 0xeb },
      { 0x57e, 0xec },
      { 0x585, 0xed },
      { 0x590, 0xee },
      { 0x596, 0xef },
      { 0x59e, 0xf0 },
      { 0x5a6, 0xf1 },
      { 0x5b2, 0xf2 },
      { 0x5bb, 0xf3 },
      { 0x5c4, 0xf4 },
      { 0x5cb, 0xf5 },
      { 0x5d3, 0xf6 },
      { 0x5e0, 0xf7 },
      { 0x5ea, 0xf8 },
      { 0x5f4, 0xf9 },
      { 0x5fc, 0xfa },
      { 0x607, 0xfb },
      { 0x614, 0xfc },
      { 0x61e, 0xfd },
      { 0x62a, 0xfe },
      { 0x638, 0xff },
    };

    QPainter painter;
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QFont font("Lucida Console");
    font.setPixelSize(16);
    font.setStretch(125);

    QFontMetrics metrics(font);

    //qDebug("height: %d", metrics.height());
    //qDebug("width: %d", metrics.width('M'));

    //font.setStretch(100 * metrics.width('M') * 1.0f / metrics.height() / 0.8f);

    setFont(font);


    QBrush brush(Qt::black);
    painter.fillRect(0, 0, width(), height(), brush);

    painter.setCompositionMode(QPainter::CompositionMode_Plus);
    QPen pen(Qt::white);
    painter.setPen(pen);

    if(m_framebuffer) {
       //QPainterPath path;

        float xHold = 0;
        float yHold = 0;
        bool active = false;

        QPointF prevPoint(0, 0);

        for(unsigned int ip = 0; ip < 8192; ip += 2) {
            unsigned int word = (*m_framebuffer)[ip / 2];
            auto instr = word >> 12;
            auto arg = word & 4095;

            switch(instr >> 1) {
                default:
                    //qDebug("%d %d", instr, arg);
                    break;

            case 0:
                yHold = 480.f - arg * 0.75f * 0.8f;

                if(active) {
                    QPointF newPoint(xHold, yHold);
                    painter.drawLine(prevPoint, newPoint);
                    prevPoint = newPoint;
                    //path.lineTo(xHold, yHold);
                } else {
                    prevPoint.setX(xHold);
                    prevPoint.setY(yHold);
                    //path.moveTo(xHold, yHold);
                }
                break;

            case 2:
                if((instr & 1)) {
                    QPen pen(0x00aaaa);
                    painter.setPen(pen);
                } else {
                    QPen pen(0xffff55);
                    painter.setPen(pen);
                }

                active = true;
                xHold = (arg - 64) * 0.8f;
                break;

            case 3:
                active = false;
                xHold = (arg - 64) * 0.8f;
                break;

            case 5:
                arg |= (word & 4096);
                if(arg == 0) {
                    goto breakOuter;
                } else {
                    ip = arg - 2;
                }
                break;

            case 6:
            {
                //const BDFCharacter *ch;

                auto it = charToUnicode.find(arg);
                if(it != charToUnicode.end()/* && m_font.lookupCodePoint(it->second, ch)*/) {

                    if((instr & 1)) {
                        QPen pen(0xAAAAAA);
                        painter.setPen(pen);
                    } else {
                        QPen pen(0xFFFFFF);
                        painter.setPen(pen);
                    }

                    QString text(it->second);

                    auto boundingBox = painter.boundingRect(QRect(0, 0, 0, 0), text);
                    xHold += painter.fontMetrics().width(text);
                    painter.drawText(QRect(xHold, yHold, boundingBox.width(), boundingBox.height()),
                                     Qt::AlignLeft, text);
/*
                    xHold += m_font.fontBoundingBox().width;

                    QImage glyphImage(
                            m_font.fontBoundingBox().width,
                            m_font.fontBoundingBox().height,
                            QImage::Format_Mono);

                    auto bytesPerLine = (m_font.fontBoundingBox().width + 7) / 8;

                    for(unsigned int line = 0; line < m_font.fontBoundingBox().height; line++) {
                        memcpy(glyphImage.scanLine(line), &ch->bitmapData()[bytesPerLine * line], bytesPerLine);
                    }

                    glyphImage.setColor(0, 0x00000000);

                    if((instr & 1)) {
                        glyphImage.setColor(1, 0xFFAAAAAA);
                    } else {
                        glyphImage.setColor(1, 0xFFFFFFFF);
                    }


                    //painter.drawImage(xHold, yHold, glyphImage);

                    painter.drawImage(QRectF(roundf(xHold), roundf(yHold),
                                             m_font.fontBoundingBox().width,
                                             0.666f * m_font.fontBoundingBox().height),
                                      glyphImage);

                    //xHold++;
*/
                }

                    break;
            }
            }
        }
breakOuter:;
    }

    painter.end();
}

void DisplayWidget::setFrameBuffer(const std::vector<uint16_t> &frameBuffer) {
    m_framebuffer = &frameBuffer;
}

void DisplayWidget::updateFrame() {
    metaObject()->invokeMethod(this, "doUpdateFrame", Qt::QueuedConnection);
}

void DisplayWidget::doUpdateFrame() {
    update();
}

void DisplayWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Space && m_framebuffer) {
        FILE *dump = fopen("C:\\re\\hp8560e\\vector\\dump.bin", "wb");
        if(dump) {
            fwrite(m_framebuffer->data(), sizeof(uint16_t), m_framebuffer->size(), dump);
            fclose(dump);
        }
    }
}
