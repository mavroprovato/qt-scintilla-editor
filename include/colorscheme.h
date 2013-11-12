#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include "styleinfo.h"

#include <QHash>
#include <QStringList>
#include <QXmlStreamReader>

class ColorScheme {
public:
    /**
     * Returns the names of the color shemes available.
     *
     * @return The names of the color shemes available.
     */
    static QStringList allColorSchemes();

    /**
     * Returns the color scheme from its name.
     *
     * @param name The name of the color scheme.
     * @return The color scheme.
     */
    static const ColorScheme *getColorScheme(const QString &name);

    /**
     * Cleans up the static resources.
     */
    static void cleanup();

public:

    /**
     * Returns the foreground color.
     *
     * @return The foreground color.
     */
    int foreground() const;

    /**
     * Returns the background color.
     *
     * @return The background color.
     */
    int background() const;

    /**
     * Returns the caret color.
     *
     * @return The caret color.
     */
    int caret() const;

    /**
     * Returns the current caret line color.
     *
     * @return The current caret line color.
     */
    int caretLine() const;

    /**
     * Returns the selection background color.
     *
     * @return The selection background color.
     */
    int selection() const;

    /**
     * Returns the styles for a language.
     *
     * @param lang The language identifier.
     * @return The styles.
     */
    QHash<int, StyleInfo> stylesForLanguage(const QString& lang) const;

private:
    /**
     * Constructor for the color scheme.
     */
    ColorScheme();

    /**
     * Destructor for the color scheme.
     */
    ~ColorScheme();

    /**
     * Initializes the available color schemes.
     */
    static QHash<QString, ColorScheme*> initializeColorSchemes();

    static void processColorSchemeXml(QXmlStreamReader &xml,
            QHash<QString, ColorScheme *> &colorSchemes);

    /** Contains all the color chemes available. */
    static QHash<QString, ColorScheme*> colorSchemes;

    /** The foreground color. */
    int m_foreground;

    /** The background color. */
    int m_background;

    /** The caret color. */
    int m_caret;

    /** The current caret line color. */
    int m_caretLine;

    /** The selection background color. */
    int m_selection;

    /** The styles for all languages. */
    QHash<QString, QHash<int, StyleInfo> > m_languagesStyles;
};

#endif // COLORSCHEME_H
