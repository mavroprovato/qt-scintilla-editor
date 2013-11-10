#ifndef UTIL_H
#define UTIL_H

#include <QColor>

/**
 * Converts a hexademical representation of a color to the color format
 * understood by Scintilla.
 *
 * @param color The hexademical representation of the color.
 * @return The color value understood by Scintilla.
 */
int convertColor(const QString& colorStr) ;

#endif // UTIL_H
