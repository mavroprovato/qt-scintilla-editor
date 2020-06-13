#include "colorscheme.h"

#include "styleinfo.h"
#include "util.h"

#include <QDebug>
#include <QDir>
#include <QXmlStreamReader>

QStringList ColorScheme::allColorSchemes() {
    // Sort the keys and return them.
    QStringList list = colorSchemes.keys();
    qSort(list.begin(), list.end());

    return list;
}

const ColorScheme *ColorScheme::getColorScheme(const QString &name) {
    return colorSchemes[name];
}

void ColorScheme::cleanup() {
    QHashIterator<QString, ColorScheme*> iter(colorSchemes);
    while (iter.hasNext()) {
        delete iter.next().value();
    }
}

int ColorScheme::foreground() const {
    return m_foreground;
}

int ColorScheme::background() const {
    return m_background;
}

int ColorScheme::caret() const {
    return m_caret;
}

int ColorScheme::caretLine() const {
    return m_caretLine;
}

int ColorScheme::selection() const {
    return m_selection;
}

int ColorScheme::whitespaceForeground() const {
    return m_whitespaceForeground;
}

QHash<int, StyleInfo> ColorScheme::stylesForLanguage(const QString& lang) const {
    return m_languagesStyles[lang];
}

ColorScheme::ColorScheme() {

}

ColorScheme::~ColorScheme() {

}

QHash<QString, ColorScheme*> ColorScheme::colorSchemes = ColorScheme::initializeColorSchemes();

QHash<QString, ColorScheme*> ColorScheme::initializeColorSchemes() {
    QHash<QString, ColorScheme*> colorSchemes;

    // Make sure the resources are initialized
    Q_INIT_RESOURCE(qtscitntillaeditor);
    // List all the color scheme files
    QDir dir(":/colorschemes/colorschemes");
    QStringList colorSchemeFiles = dir.entryList();
    for (int i = 0; i < colorSchemeFiles.size(); ++i) {
        QFile file(dir.absolutePath() + "/" + colorSchemeFiles.at(i));
        if (file.open(QFile::ReadOnly | QIODevice::Text)) {
            QXmlStreamReader xml(&file);
            processColorSchemeXml(xml, colorSchemes);
            if (xml.hasError()) {
                qCritical("Color scheme file %s cannot be parsed", qUtf8Printable(file.fileName()));
            }
        } else {
            qCritical("Cannot open color scheme file %s.",
                    qPrintable(file.fileName()));
        }
    }

    return colorSchemes;
}

void ColorScheme::processColorSchemeXml(QXmlStreamReader &xml,
        QHash<QString, ColorScheme *> &colorSchemes) {
    // The color scheme
    ColorScheme *colorScheme = new ColorScheme;
    // The styles defined
    QHash<QString, StyleInfo> definedStyles;

    QString langId;
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (xml.name() == "colorscheme") {
                QString name = xml.attributes().value("name").toString();
                colorSchemes[name] = colorScheme;
            } else if (xml.name() == "color") {
                QString type = xml.attributes().value("type").toString();
                QString text = xml.readElementText(
                            QXmlStreamReader::ErrorOnUnexpectedElement);
                if (type == "foreground") {
                    colorScheme->m_foreground = convertColor(text);
                } else if (type == "background") {
                    colorScheme->m_background = convertColor(text);
                } else if (type == "caret") {
                    colorScheme->m_caret = convertColor(text);
                } else if (type == "caretLine") {
                    colorScheme->m_caretLine = convertColor(text);
                } else if (type == "selection") {
                    colorScheme->m_selection = convertColor(text);
                } else if (type == "whitespace") {
                    colorScheme->m_whitespaceForeground = convertColor(text);
                }
            } else if (xml.name() == "style") {
                StyleInfo styleInfo;
                QXmlStreamAttributes attrs = xml.attributes();
                QString name = attrs.value("name").toString();
                if (attrs.hasAttribute("foreground")) {
                    styleInfo.setForegroundColor(
                            convertColor(attrs.value("foreground").toString()));
                }
                if (attrs.hasAttribute("background")) {
                    styleInfo.setBackgroundColor(
                            convertColor(attrs.value("background").toString()));
                }
                if (attrs.hasAttribute("bold")) {
                    styleInfo.setBold(attrs.value("bold").toString() == "true");
                }
                if (attrs.hasAttribute("italic")) {
                    styleInfo.setItalic(
                            attrs.value("italic").toString() == "true");
                }
                if (attrs.hasAttribute("underline")) {
                    styleInfo.setUnderline(
                            attrs.value("underline").toString() == "true");
                }
                if (attrs.hasAttribute("eolFilled")) {
                    styleInfo.setEolFilled(
                            attrs.value("eolFilled").toString() == "true");
                }
                definedStyles[name] = styleInfo;
            } else if (xml.name() == "language") {
                langId = xml.attributes().value("id").toString();
                colorScheme->m_languagesStyles[langId] = QHash<int, StyleInfo>();
            } else if (xml.name() == "styleInfo") {
                QString idStr = xml.attributes().value("id").toString();
                bool ok;
                int id = idStr.toInt(&ok);
                if (ok) {
                    QXmlStreamAttributes attrs = xml.attributes();
                    if (attrs.hasAttribute("styleRef")) {
                        QString styleRef = attrs.value("styleRef").toString();
                        colorScheme->m_languagesStyles[langId][id] = definedStyles[styleRef];
                    }
                }
            }
        }
    }
}
