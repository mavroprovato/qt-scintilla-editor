#include "util.h"

int convertColor(const QColor& color) {
    return color.red() | (color.green() << 8) | (color.blue() << 16);
}
