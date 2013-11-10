#include "util.h"

int convertColor(const QString& colorStr) {
    bool ok;
    uint color = colorStr.right(6).toUInt(&ok, 16);
    if (ok) {
        return ((color << 16) & 0xFF0000) | (color & 0x00FF00) |
                ((color >> 16) & 0x0000FF);
    } else {
        return -1;
    }
}
