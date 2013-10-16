#ifndef UTIL_H
#define UTIL_H

#include <QColor>

/**
 * Converts an instance of QColor to a value that can be understood by
 * Scintilla.
 *
 * @param color The color.
 * @return The color value understood by Scintilla.
 */
int convertColor(const QColor& color) ;

#endif // UTIL_H
