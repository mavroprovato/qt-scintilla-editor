#ifndef UTIL_H
#define UTIL_H

#include <QByteArray>
#include <QColor>
#include <QString>

/**
 * The differenct categories for the encodings.
 */
enum EncodingCategory {
    WestEuropean, EastEuropean, EastAsian, SouthAsian, MiddleEastern, Unicode
};

/**
 * Holds information about the available encodings.
 */
struct Encoding {
    /** The encoding language. */
    QString language;
    /** The encoding display name */
    QString displayName;
    /** The encoding system name. */
    QByteArray name;
    /** The encoding category. */
    EncodingCategory category;
};

/**
 * An array that holds all the available encodings.
 */
extern Encoding G_AVAILABLE_ENCODINGS[];

/**
 * The number of available encodings.
 */
extern size_t G_ENCODING_COUNT;

/**
 * Converts an instance of QColor to a value that can be understood by
 * Scintilla.
 *
 * @param color The color.
 * @return The color value understood by Scintilla.
 */
int convertColor(const QColor& color) ;

#endif // UTIL_H
