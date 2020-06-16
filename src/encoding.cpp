#include "encoding.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <utility>

QListIterator<Encoding*> Encoding::allEncodings() {
    return QListIterator<Encoding*>(availableEncodings);
}

const Encoding *Encoding::fromName(const QByteArray& name) {
    for (auto availableEncoding : availableEncodings) {
        if (availableEncoding->name() == name) {
            return availableEncoding;
        }
    }

    // Encoding not found.
    return nullptr;
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

QList<Encoding*> Encoding::availableEncodings = Encoding::initializeEncodings();

QList<Encoding*> Encoding::initializeEncodings(){
    QList<Encoding*> encodings;

    // Make sure the resources are initialized
    Q_INIT_RESOURCE(qtscitntillaeditor);
    // Open the encoding xml file for reading
    QFile file(":/conf/conf/encodings.xml");
    if (file.open(QFile::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        EncodingCategory currentCategory = WestEuropean;
        // Loop through the xml elements
        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                if (xml.name() == "category") {
                    // New category element, get the id
                    bool ok;
                    int id = xml.attributes().value("id").toString().toInt(&ok);
                    if (ok && id >= 0 && id <= 5) {
                        currentCategory = (EncodingCategory) id;
                    } else {
                        qWarning("id attribute of category element is invalid");
                    }
                } else if (xml.name() == "encoding") {
                    // New encoding element, add it to the list
                    QString language = xml.attributes().value("language").toString();
                    QString displayName = xml.attributes().value("displayName").toString();
                    QByteArray name = xml.attributes().value("name").toLocal8Bit();
                    encodings << new Encoding(language, displayName, name, currentCategory);
                }
            }
        }
        if (xml.hasError()) {
            qFatal("Error while parsing the encodings configuration file: %s.",
                qPrintable(xml.errorString().toLatin1()));
        }
    } else {
        qFatal("Unable to open the encodings configuration file.");
    }

    return encodings;
}

void Encoding::cleanup() {
    for (auto availableEncoding : availableEncodings) {
        delete availableEncoding;
    }
}

Encoding::EncodingCategory Encoding::category() const {
    return m_category;
}

QString Encoding::toString() const {
    return QString("%1 (%2)").arg(m_language, m_displayName);
}

Encoding::Encoding(QString language, QString displayName, QByteArray name, Encoding::EncodingCategory category) :
    m_language(std::move(language)), m_displayName(std::move(displayName)), m_name(std::move(name)),
    m_category(category) {

}

Encoding::~Encoding() = default;
