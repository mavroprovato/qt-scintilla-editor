#include "util.h"

#include <SciLexer.h>

#include <QObject>

Language G_AVAILABLE_LANGUAGES[] = {
    {
        SCLEX_CPP, "C/C++", "*.h *.hh *.hpp *.hxx *.h++ *.c *.cc *.cpp *.cxx *.c++",
        "alignas alignof and and_eq asm auto bitand bitor bool break case "
        "catch char char16_t char32_t class compl const constexpr const_cast "
        "continue decltype default delete do double dynamic_cast else enum "
        "explicit export extern false float for friend goto if inline int "
        "long mutable namespace new noexcept not not_eq nullptr operator or "
        "or_eq private protected public register reinterpret_cast return short "
        "signed sizeof static static_assert static_cast struct switch template "
        "this thread_local throw true try typedef typeid typename union "
        "unsigned using virtual void volatile wchar_t while xor xor_eq"
    },
    {
        SCLEX_CPP, "Java", "*.java",
        "abstract assert boolean break byte case catch char class const "
        "continue default double do else enum extends final finally float for "
        "goto if implements import instanceof int interface long native new "
        "package private protected public return short static strictfp super "
        "switch synchronized this throw throws transient try void volatile "
        "while"
    },
    {
        SCLEX_PYTHON, "Python", "*.py *.pyw",
        "False None True and as assert break class continue def del elif else "
        "except finally for from global if import in is lambda nonlocal not or "
        "pass raise return try while with yield"
    }
};

size_t G_LANGUAGE_COUNT = sizeof(G_AVAILABLE_LANGUAGES) / sizeof(G_AVAILABLE_LANGUAGES[0]);

Encoding G_AVAILABLE_ENCODINGS[] = {
    { "Arabic", "ISO 8859-6", "ISO-8859-6", MiddleEastern },
    { "Arabic", "ISO 8859-6-I", "ISO-8859-6-I", MiddleEastern },
    { "Arabic", "Windows-1256", "windows-1256", MiddleEastern },
    { "Baltic", "ISO-8859-13", "ISO-8859-13", EastEuropean },
    { "Baltic", "Windows-1257", "windows-1257", EastEuropean },
    { "Celtic", "ISO-8859-14", "ISO-8859-14", WestEuropean },
    { "Chinese", "Big5", "Big5", EastAsian },
    { "Chinese", "CP 950", "CP950", EastAsian },
    { "Chinese", "GB18030", "GB18030", EastAsian },
    { "Chinese", "GB2312", "GB2312", EastAsian },
    { "Chinese", "HKSCS", "Big5-HKSCS", EastAsian },
    { "Chinese", "CP 936", "CP936", EastAsian },
    { "Chinese", "GBK", "gbk-0", EastAsian },
    { "Cyrillic", "ISO 8859-5", "ISO-8859-5", EastEuropean },
    { "Cyrillic", "Windows-1251", "windows-1251 ", EastEuropean },
    { "Cyrillic", "CP 866", "CP866", EastEuropean },
    { "Cyrillic", "KOI8-R", "KOI8-R", EastEuropean },
    { "Cyrillic Ukrainian", "KOI8-U", "KOI8-U", EastEuropean },
    { "Eastern European", "ISO 8859-2", "ISO-8859-2", EastEuropean },
    { "Eastern European", "Windows-1250", "windows-1250 ", EastEuropean },
    { "Greek", "ISO 8859-7", "ISO-8859-7", WestEuropean },
    { "Greek", "Windows-1253", "windows-1253", WestEuropean },
    { "Hebrew", "ISO 8859-8", "ISO-8859-8", MiddleEastern },
    { "Hebrew", "ISO 8859-8-I", "ISO-8859-8-I", MiddleEastern },
    { "Hebrew", "Windows-1255", "windows-1255", MiddleEastern },
    { "Hindi (Bengali)", "ISCII-Bng", "Iscii-Bng", SouthAsian },
    { "Hindi (Devanagari)", "ISCII-Dev", "Iscii-Dev", SouthAsian },
    { "Hindi (Gujarati)", "ISCII-Gjr", "Iscii-Gjr", SouthAsian },
    { "Hindi (Kannada)", "ISCII-Knd", "Iscii-Knd", SouthAsian },
    { "Hindi (Malayalam)", "ISCII-Mlm", "Iscii-Mlm", SouthAsian },
    { "Hindi (Oriya)", "ISCII-Ori", "Iscii-Ori", SouthAsian },
    { "Hindi (Punjabi)", "ISCIIi-Pnj", "Iscii-Pnj", SouthAsian },
    { "Hindi (Telugu)", "ISCII-Tlg", "Iscii-Tlg", SouthAsian },
    { "Hindi (Tamil)", "ISCII-Tml", "Iscii-Tml", SouthAsian },
    { "Japanese", "EUC-JP", "EUC-JP", EastAsian },
    { "Japanese", "ISO 2022-JP", "ISO-2022-JP", EastAsian },
    { "Japanese", "JIS X 0201", "jisx0201*-0", EastAsian },
    { "Japanese", "JIS X 0208", "jisx0208*-0", EastAsian },
    { "Japanese", "Shift JIS", "Shift_JIS", EastAsian },
    { "Korean", "EUC-KR", "EUC-KR", EastAsian },
    { "Korean", "CP 949", "cp949", EastAsian },
    { "Nordic", "ISO 8859-10", "ISO-8859-10", WestEuropean },
    { "North European", "ISO 8859-4", "ISO 8859-4", WestEuropean },
    { "South European", "ISO 8859-3", "ISO-8859-3", WestEuropean },
    { "South-Eastern European", "ISO 8859-16", "ISO-8859-16", EastEuropean },
    { "Tamil", "TSCII", "TSCII", SouthAsian },
    { "Thai", "ISO 8859-11", "ISO-8859-11", SouthAsian },
    { "Thai", "CP 874", "CP874", SouthAsian },
    { "Thai", "TIS-620", "TIS-620", SouthAsian },
    { "Turkish", "ISO 8859-9", "ISO-8859-9", SouthAsian },
    { "Turkish", "Windows-1254", "windows-1254", SouthAsian },
    { "Unicode", "UTF-8", "UTF-8", Unicode },
    { "Unicode", "UTF-16", "UTF-16", Unicode },
    { "Unicode", "UTF-16BE", "UTF-16BE", Unicode },
    { "Unicode", "UTF-16LE", "UTF-16LE", Unicode },
    { "Unicode", "UTF-32", "UTF-32", Unicode },
    { "Unicode", "UTF-32BE", "UTF-32BE", Unicode },
    { "Unicode", "UTF-32LE", "UTF-32LE", Unicode },
    { "Vietnamese", "Windows-1258", "windows-1258", SouthAsian },
    { "Western European", "ISO 8859-1", "ISO 8859-1", WestEuropean },
    { "Western European", "ISO 8859-15", "ISO 8859-15", WestEuropean },
    { "Western European", "Windows 1252", "windows-1252", WestEuropean },
    { "Western European", "CP 850", "CP850", WestEuropean },
    { "Western European", "Mac OS Roman", "macintosh", WestEuropean },
    { "Western European", "HP roman8", "hp-roman8", WestEuropean },
};

size_t G_ENCODING_COUNT = sizeof(G_AVAILABLE_ENCODINGS) / sizeof(G_AVAILABLE_ENCODINGS[0]);

QString filterString() {
    QString filter(QObject::tr("All files (*)"));
    filter.append(";;");

    for (size_t i = 0; i < G_LANGUAGE_COUNT; i++) {
        Language language = G_AVAILABLE_LANGUAGES[i];
        filter.append(QString(QObject::tr("%1 files (%2)")).arg(language.name,
            language.patterns));
        if (i != G_LANGUAGE_COUNT - 1) {
            filter.append(";;");
        }
    }

    return filter;
}

int convertColor(const QColor& color) {
    return color.red() | (color.green() << 8) | (color.blue() << 16);
}
