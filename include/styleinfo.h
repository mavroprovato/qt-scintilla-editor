#ifndef STYLEINFO_H
#define STYLEINFO_H

#include <QString>

/**
 * Contains information about a style for a language.
 */
struct StyleDescription {
    /**
     * Creates the style description.
     *
     * @param stl The Scintilla identifier of the style.
     * @param desc he description for the style.
     */
    StyleDescription(unsigned char stl, QString desc);

    /** The Scintilla identifier of the style */
    unsigned char style;

    /** The description for the style. */
    QString description;
};

class StyleInfo {
public:

    /**
     * Creates the style information.
     *
     * @param foregroundColor The foreground color. Set to less than zero to use
     * the default.
     * @param backgroundColor The backgroung color. Set to less that zero to use
     * the default.
     * @param bold True in order to set the style to bold.
     * @param italic True in order to set the style to italic.
     * @param underline True in order to set the style to underline.
     * @param eolFilled True in order for the remainder of the line up to the
     * right edge of the window to be filled with the background color set for
     * the last character.
     */
    StyleInfo(int foregroundColor = -1, int backgroundColor = -1,
              bool bold = false, bool italic = false, bool underline = false,
              bool eolFilled = false);

    /**
     * Returns the foreground color in the format expected by Scintilla. If the
     * value is less than zero, then this color has not been set.
     *
     * @return The foreground color in the format expected by Scintilla.
     */
    int foregroundColor() const;

    /**
     * Sets the foreground color, in the format expected by Scintilla.
     *
     * @param foregroundColor The foreground color, in the format expected by
     * Scintilla. If the value is less than zero, then the default is used.
     */
    void setForegroundColor(int foregroundColor);

    /**
     * Returns the background color in the format expected by Scintilla. If -1,
     * then this color has not been set.
     *
     * @return The background color in the format expected by Scintilla.
     */
    int backgroundColor() const;

    /**
     * Sets the background color, in the format expected by Scintilla.
     *
     * @param backgroundColor The background color, in the format expected by
     * Scintilla. If the value is less than zero, then the default is used.
     */
    void setBackgroundColor(int backgroundColor);

    /**
     * Returns true if the style should be bolded.
     *
     * @return true if the style should be bolded.
     */
    bool bold() const;

    /**
     * Sets whether the style should be bolded or not.
     *
     * @param bold true if the style should be bolded.
     */
    void setBold(bool bold);

    /**
     * Returns true if the style should be italicized.
     *
     * @return true if the style should be italicized.
     */
    bool italic() const;

    /**
     * Sets whether the style should be italicized or not.
     *
     * @param bold true if the style should be italicized.
     */
    void setItalic(bool italic);

    /**
     * Returns true if the style should be underlined.
     *
     * @return true if the style should be underlined.
     */
    bool underline() const;

    /**
     * Sets whether the style should be underlined or not.
     *
     * @param bold true if the style should be underlined.
     */
    void setUnderline(bool underline);

    /**
     * Returns true if the remainder of the line up to the right edge of the
     * window is filled with the background color set for the last character.
     *
     * @return true if the remainder of the line up to the right edge of the
     * window is filled with the background color set for the last character.
     */
    bool eolFilled() const;

    /**
     * Sets the remainder of the line up to the right edge of the window is
     * filled with the background color set for the last character or not.
     *
     * @param bold true if the remainder of the line up to the right edge of the
     * window is filled with the background color set for the last character.
     */
    void setEolFilled(bool eolFilled);

private:
    /** Holds the foreground color. */
    int m_foregroundColor;
    /** Holds the background color. */
    int m_backgroundColor;
    /** true for bold style. */
    bool m_bold;
    /** true for italic style. */
    bool m_italic;
    /** true for underline style. */
    bool m_underline;
    /** true if the remainder of the line up to the right edge of the window is
     * filled with the background color set for the last character. */
    bool m_eolFilled;
};

#endif // STYLEINFO_H
