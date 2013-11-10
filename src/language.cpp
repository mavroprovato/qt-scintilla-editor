#include "language.h"

#include <QFile>
#include <QObject>
#include <QStringList>
#include <QXmlStreamReader>

#include <SciLexer.h>

QString Language::filterString() {
    QString filter(QObject::tr("All files (*)"));
    filter.append(";;");

    for (int i = 0; i < availableLangs.size(); ++i) {
        Language *language = availableLangs.at(i);
        filter.append(QString(QObject::tr("%1 files (%2)")).arg(language->name(),
                language->patterns()));
        if (i != availableLangs.size() - 1) {
            filter.append(";;");
        }
    }

    return filter;
}

QListIterator<Language *> Language::allLanguages() {
    return QListIterator<Language *>(availableLangs);
}

const Language* Language::fromLanguageId(const QString& languageId) {
    for (int i = 0; i < availableLangs.size(); ++i) {
        if (availableLangs.at(i)->langId() == languageId) {
            return availableLangs.at(i);
        }
    }
    // Not found
    return NULL;
}

const Language* Language::fromFilename(const QString& fileName) {
    // Search for all available languages.
    for (int i = 0; i < availableLangs.size(); ++i) {
        Language *currentLang = availableLangs.at(i);
        QStringList extensions = currentLang->patterns().split(' ');
        // Search for all extensions.
        for (int j = 0; j < extensions.size(); ++j) {
            QRegExp re(extensions.at(j));
            re.setPatternSyntax(QRegExp::Wildcard);
            if (re.exactMatch(fileName)) {
                return availableLangs.at(i);
            }
        }
    }
    // Not found
    return NULL;
}

QList<Language*> Language::availableLangs = Language::intializeLangs();

QList<Language*> Language::intializeLangs() {
    QList<Language*> langs;

    // Make sure the resources are initialized
    Q_INIT_RESOURCE(qtscitntillaeditor);
    // Open the encoding xml file for reading
    QFile file(":/conf/conf/languages.xml");
    if (file.open(QFile::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        // Loop through the xml elements
        Language *currentLang = NULL;
        QStringList keywords;
        QList<StyleDescription> styles;
        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                if (xml.name() == "language") {
                    QXmlStreamAttributes attrs = xml.attributes();
                    currentLang = new Language;
                    currentLang->m_langId = attrs.value("id").toString();
                    currentLang->m_name = attrs.value("name").toString();
                    currentLang->m_lexer = attrs.value("lexer").toString();
                } else if (xml.name() == "patterns") {
                    currentLang->m_patterns = xml.readElementText(
                                QXmlStreamReader::ErrorOnUnexpectedElement);
                } else if (xml.name() == "keywordSet") {
                    bool ok;
                    int id = xml.attributes().value("id").toString().toInt(&ok);
                    if (ok) {
                        while (id != keywords.size()) {
                            keywords.append("");
                        }
                        keywords << xml.readElementText(
                            QXmlStreamReader::ErrorOnUnexpectedElement);
                    } else {
                        qWarning("id attribute of keywordSet element is "
                                 "invalid");
                    }
                } else if (xml.name() == "styleDescription") {
                    QXmlStreamAttributes attrs = xml.attributes();
                    QString description = attrs.value("description").toString();
                    bool ok;
                    uint style = attrs.value("style").toString().toUInt(&ok);
                    if (ok && style <= UCHAR_MAX) {
                        styles << StyleDescription((uchar) style, description);
                    } else {
                        qWarning("id attribute of styleDescription element is "
                                 "invalid");
                    }
                }
            } else if (token == QXmlStreamReader::EndElement) {
                if (xml.name() == "keywordSets") {
                    currentLang->m_keywords = keywords.replaceInStrings(
                            QRegExp("\\s+"), " ");;
                    keywords.clear();
                } else if (xml.name() == "styleDescriptions") {
                    currentLang->m_styles = styles;
                    styles.clear();
                } else if (xml.name() == "language") {
                    langs << currentLang;
                }
            }
        }
        if (xml.hasError()) {
            qFatal("Error while parsing the languages configuration file: %s.",
                qPrintable(xml.errorString()));
        }
    } else {
        qFatal("Unable to find the languages configuration file.");
    }

    return langs;
}

void Language::cleanup() {
    for (int i = 0; i < availableLangs.size(); ++i) {
        delete availableLangs.at(i);
    }
}

Language::Language() {
}

Language::~Language() {
}

QString Language::langId() const {
    return m_langId;
}

QString Language::lexer() const {
    return m_lexer;
}

QString Language::name() const {
    return m_name;
}

QString Language::patterns() const {
    return m_patterns;
}

QStringList Language::keywords() const {
    return m_keywords;
}

QList<StyleDescription> Language::styles() const {
    return m_styles;
}
