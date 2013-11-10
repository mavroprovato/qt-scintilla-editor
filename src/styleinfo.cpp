#include "styleinfo.h"
#include "util.h"

#include <QDebug>
#include <QStringList>

StyleDescription::StyleDescription(unsigned char stl, QString desc)
    : style(stl), description(desc) {

}

StyleInfo::StyleInfo(int foregroundColor, int backgroundColor, bool bold,
                     bool italic, bool underline, bool eolFilled) :
    m_foregroundColor(foregroundColor), m_backgroundColor(backgroundColor),
    m_bold(bold), m_italic(italic), m_underline(underline),
    m_eolFilled(eolFilled) {
}

int StyleInfo::foregroundColor() const {
    return m_foregroundColor;
}

void StyleInfo::setForegroundColor(int foregroundColor) {
    m_foregroundColor = foregroundColor;
}

int StyleInfo::backgroundColor() const {
    return m_backgroundColor;
}

void StyleInfo::setBackgroundColor(int backgroundColor) {
    m_backgroundColor = backgroundColor;
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
