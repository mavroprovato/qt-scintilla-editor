#include "encoding.h"

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

    encodings
    << Encoding("Arabic", "ISO 8859-6", "ISO-8859-6", MiddleEastern)
    << Encoding("Arabic", "ISO 8859-6-I", "ISO-8859-6-I", MiddleEastern)
    << Encoding("Arabic", "Windows-1256", "windows-1256", MiddleEastern)
    << Encoding("Baltic", "ISO-8859-13", "ISO-8859-13", EastEuropean)
    << Encoding("Baltic", "Windows-1257", "windows-1257", EastEuropean)
    << Encoding("Celtic", "ISO-8859-14", "ISO-8859-14", WestEuropean)
    << Encoding("Chinese", "Big5", "Big5", EastAsian)
    << Encoding("Chinese", "CP 950", "CP950", EastAsian)
    << Encoding("Chinese", "GB18030", "GB18030", EastAsian)
    << Encoding("Chinese", "GB2312", "GB2312", EastAsian)
    << Encoding("Chinese", "HKSCS", "Big5-HKSCS", EastAsian)
    << Encoding("Chinese", "CP 936", "CP936", EastAsian)
    << Encoding("Chinese", "GBK", "gbk-0", EastAsian)
    << Encoding("Cyrillic", "ISO 8859-5", "ISO-8859-5", EastEuropean)
    << Encoding("Cyrillic", "Windows-1251", "windows-1251 ", EastEuropean)
    << Encoding("Cyrillic", "CP 866", "CP866", EastEuropean)
    << Encoding("Cyrillic", "KOI8-R", "KOI8-R", EastEuropean)
    << Encoding("Cyrillic Ukrainian", "KOI8-U", "KOI8-U", EastEuropean)
    << Encoding("Eastern European", "ISO 8859-2", "ISO-8859-2", EastEuropean)
    << Encoding("Eastern European", "Windows-1250", "windows-1250 ", EastEuropean)
    << Encoding("Greek", "ISO 8859-7", "ISO-8859-7", WestEuropean)
    << Encoding("Greek", "Windows-1253", "windows-1253", WestEuropean)
    << Encoding("Hebrew", "ISO 8859-8", "ISO-8859-8", MiddleEastern)
    << Encoding("Hebrew", "ISO 8859-8-I", "ISO-8859-8-I", MiddleEastern)
    << Encoding("Hebrew", "Windows-1255", "windows-1255", MiddleEastern)
    << Encoding("Hindi (Bengali)", "ISCII-Bng", "Iscii-Bng", SouthAsian)
    << Encoding("Hindi (Devanagari)", "ISCII-Dev", "Iscii-Dev", SouthAsian)
    << Encoding("Hindi (Gujarati)", "ISCII-Gjr", "Iscii-Gjr", SouthAsian)
    << Encoding("Hindi (Kannada)", "ISCII-Knd", "Iscii-Knd", SouthAsian)
    << Encoding("Hindi (Malayalam)", "ISCII-Mlm", "Iscii-Mlm", SouthAsian)
    << Encoding("Hindi (Oriya)", "ISCII-Ori", "Iscii-Ori", SouthAsian)
    << Encoding("Hindi (Punjabi)", "ISCIIi-Pnj", "Iscii-Pnj", SouthAsian)
    << Encoding("Hindi (Telugu)", "ISCII-Tlg", "Iscii-Tlg", SouthAsian)
    << Encoding("Hindi (Tamil)", "ISCII-Tml", "Iscii-Tml", SouthAsian)
    << Encoding("Japanese", "EUC-JP", "EUC-JP", EastAsian)
    << Encoding("Japanese", "ISO 2022-JP", "ISO-2022-JP", EastAsian)
    << Encoding("Japanese", "JIS X 0201", "jisx0201*-0", EastAsian)
    << Encoding("Japanese", "JIS X 0208", "jisx0208*-0", EastAsian)
    << Encoding("Japanese", "Shift JIS", "Shift_JIS", EastAsian)
    << Encoding("Korean", "EUC-KR", "EUC-KR", EastAsian)
    << Encoding("Korean", "CP 949", "cp949", EastAsian)
    << Encoding("Nordic", "ISO 8859-10", "ISO-8859-10", WestEuropean)
    << Encoding("North European", "ISO 8859-4", "ISO 8859-4", WestEuropean)
    << Encoding("South European", "ISO 8859-3", "ISO-8859-3", WestEuropean)
    << Encoding("South-Eastern European", "ISO 8859-16", "ISO-8859-16", EastEuropean)
    << Encoding("Tamil", "TSCII", "TSCII", SouthAsian)
    << Encoding("Thai", "ISO 8859-11", "ISO-8859-11", SouthAsian)
    << Encoding("Thai", "CP 874", "CP874", SouthAsian)
    << Encoding("Thai", "TIS-620", "TIS-620", SouthAsian)
    << Encoding("Turkish", "ISO 8859-9", "ISO-8859-9", SouthAsian)
    << Encoding("Turkish", "Windows-1254", "windows-1254", SouthAsian)
    << Encoding("Unicode", "UTF-8", "UTF-8", Unicode)
    << Encoding("Unicode", "UTF-16", "UTF-16", Unicode)
    << Encoding("Unicode", "UTF-16BE", "UTF-16BE", Unicode)
    << Encoding("Unicode", "UTF-16LE", "UTF-16LE", Unicode)
    << Encoding("Unicode", "UTF-32", "UTF-32", Unicode)
    << Encoding("Unicode", "UTF-32BE", "UTF-32BE", Unicode)
    << Encoding("Unicode", "UTF-32LE", "UTF-32LE", Unicode)
    << Encoding("Vietnamese", "Windows-1258", "windows-1258", SouthAsian)
    << Encoding("Western European", "ISO 8859-1", "ISO 8859-1", WestEuropean)
    << Encoding("Western European", "ISO 8859-15", "ISO 8859-15", WestEuropean)
    << Encoding("Western European", "Windows 1252", "windows-1252", WestEuropean)
    << Encoding("Western European", "CP 850", "CP850", WestEuropean)
    << Encoding("Western European", "Mac OS Roman", "macintosh", WestEuropean)
    << Encoding("Western European", "HP roman8", "hp-roman8", WestEuropean);

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
