#include "encoding.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

QListIterator<Encoding> Encoding::allEncodings() {
    return QListIterator<Encoding>(availableEncodings);
}

const Encoding *Encoding::fromName(const QByteArray& name) {
    for (int i = 0; i < availableEncodings.size(); i++) {
        if (availableEncodings.at(i).name() == name) {
            return &availableEncodings.at(i);
        }
    }
    // Encoding not found.
    return NULL;
}

QString Encoding::language() const {
    return m_language;
}

QString Encoding::displayName() const {
    return m_displayName;
}

QByteArray Encoding::name() const {
    return m_name;
}

QList<Encoding> Encoding::availableEncodings = Encoding::intializeEncodings();

QList<Encoding> Encoding::intializeEncodings(){
    QList<Encoding> encodings;

    // Make sure the resources are initialized
    Q_INIT_RESOURCE(qtscitntillaeditor);
    // Open the encoding xml file for reading
    QFile file(":/conf/conf/encodings.xml");
    if (file.open(QFile::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        EncodingCategory currentCategory = WestEuropean;
        // Loop through the xml elements
        while(!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                if (xml.name() == "category") {
                    // New category element, get the id
                    QString value = xml.attributes().value("id").toString();
                    bool ok;
                    int intValue = value.toInt(&ok);
                    if (ok && intValue >= 0 && intValue <= 5) {
                        currentCategory = (EncodingCategory) intValue;
                    }
                } else if (xml.name() == "encoding") {
                    // New encoding element, add it to the list
                    QString language = xml.attributes().value("language").toString();
                    QString displayName = xml.attributes().value("displayName").toString();
                    QByteArray name = xml.attributes().value("name").toLocal8Bit();
                    encodings << Encoding(language, displayName, name,
                                          currentCategory);
                }
            }
        }
    }

    return encodings;
}

Encoding::EncodingCategory Encoding::category() const {
    return m_category;
}

QString Encoding::toString() const {
    return QString("%1 (%2)").arg(m_language, m_displayName);
}

Encoding::Encoding(QString language, QString displayName, QByteArray name,
        Encoding::EncodingCategory category) :
    m_language(language), m_displayName(displayName), m_name(name),
    m_category(category) {

}
