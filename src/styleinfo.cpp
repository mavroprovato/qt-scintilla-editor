#include "styleinfo.h"

#include <QDebug>
#include <QStringList>

StyleDescription::StyleDescription(unsigned char stl, QString desc)
    : style(stl), description(desc) {

}

StyleInfo StyleInfo::fromString(const QString& string) {
    QStringList tokens = string.split(',', QString::SkipEmptyParts);
    StyleInfo style;
    for (int i = 0; i < tokens.length(); ++i) {
        QString token = tokens[i].trimmed();
        if (token.startsWith("fore:")) {
            bool ok;
            uint colour = token.right(6).toUInt(&ok, 16);
            if (ok) {
                colour = ((colour << 16) & 0xFF0000) |
                         (colour & 0x00FF00) |
                         ((colour >> 16) & 0x0000FF);
                style.setForegroundColour(colour);
            }
        } else if (token.startsWith("back:")) {
            bool ok;
            uint colour = token.right(6).toUInt(&ok, 16);
            if (ok) {
                colour = ((colour << 16) & 0xFF0000) |
                         (colour & 0x00FF00) |
                         ((colour >> 16) & 0x0000FF);
                style.setBackgroundColour(colour);
            }
        } else if (token == "bold") {
            style.setBold(true);
        } else if (token == "italic") {
            style.setItalic(true);
        } else if (token == "eolfilled") {
            style.setEolFilled(true);
        }
    }

    return style;
}

StyleInfo::StyleInfo(int foregroundColour, int backgroundColour, bool bold,
                     bool italic, bool underline, bool eolFilled) :
    m_foregroundColour(foregroundColour), m_backgroundColour(backgroundColour),
    m_bold(bold), m_italic(italic), m_underline(underline),
    m_eolFilled(eolFilled) {
}

int StyleInfo::foregroundColour() const {
    return m_foregroundColour;
}

void StyleInfo::setForegroundColour(int foregroundColour) {
    m_foregroundColour = foregroundColour;
}

int StyleInfo::backgroundColour() const {
    return m_backgroundColour;
}

void StyleInfo::setBackgroundColour(int backgroundColour) {
    m_backgroundColour = backgroundColour;
}

bool StyleInfo::bold() const {
    return m_bold;
}

void StyleInfo::setBold(bool bold) {
    m_bold = bold;
}

bool StyleInfo::italic() const {
    return m_italic;
}

void StyleInfo::setItalic(bool italic) {
    m_italic = italic;
}

bool StyleInfo::underline() const {
    return m_underline;
}

void StyleInfo::setUnderline(bool underline) {
    m_underline = underline;
}

bool StyleInfo::eolFilled() const {
    return m_eolFilled;
}

void StyleInfo::setEolFilled(bool eolFilled) {
    m_eolFilled = eolFilled;
}
