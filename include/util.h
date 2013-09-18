#ifndef UTIL_H
#define UTIL_H

#include <QByteArray>
#include <QColor>
#include <QString>

/**
 * Information about the languages that the editor supports.
 */
struct Language {
    /** The lexer for the language. */
    int lexer;
    /** The language name. */
    QString name;
    /** The file patterns for the language. */
    QString patterns;
    /** The keywords for the language, seperated by space. */
    QString keywords;
};

/**
 * An array that holds all the available languages.
 */
extern Language G_AVAILABLE_LANGUAGES[];

/**
 * The number of available languages.
 */
extern size_t G_LANGUAGE_COUNT;

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

QString filterString();

/**
 * Converts an instance of QColor to a value that can be understood by
 * Scintilla.
 *
 * @param color The color.
 * @return The color value understood by Scintilla.
 */
int convertColor(const QColor& color) ;

#endif // UTIL_H
