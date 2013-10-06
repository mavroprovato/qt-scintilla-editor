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
    static StyleInfo fromString(const QString& string);

    StyleInfo(int foregroundColour = -1, int backgroundColour = -1,
              bool bold = false, bool italic = false, bool underline = false,
              bool eolFilled = false);

    int foregroundColour() const;

    void setForegroundColour(int foregroundColour);

    int backgroundColour() const;

    void setBackgroundColour(int backgroundColour);

    bool bold() const;

    void setBold(bool bold);

    bool italic() const;

    void setItalic(bool italic);

    bool underline() const;

    void setUnderline(bool underline);

    bool eolFilled() const;

    void setEolFilled(bool eolFilled);

private:

    int m_foregroundColour;

    int m_backgroundColour;

    bool m_bold;

    bool m_italic;

    bool m_underline;

    bool m_eolFilled;
};

#endif // STYLEINFO_H
