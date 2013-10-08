#include "language.h"

#include <QObject>
#include <QStringList>

#include <SciLexer.h>

QString Language::filterString() {
    QString filter(QObject::tr("All files (*)"));
    filter.append(";;");

    for (int i = 0; i < availableLangs.size(); ++i) {
        Language language = availableLangs.at(i);
        filter.append(QString(QObject::tr("%1 files (%2)")).arg(language.name(),
                language.patterns()));
        if (i != availableLangs.size() - 1) {
            filter.append(";;");
        }
    }

    return filter;
}

QListIterator<Language> Language::allLanguages() {
    return QListIterator<Language>(availableLangs);
}

const Language* Language::fromLanguageId(const QString& languageId) {
    for (int i = 0; i < availableLangs.size(); ++i) {
        if (availableLangs.at(i).langId() == languageId) {
            return &availableLangs.at(i);
        }
    }
    // Not found
    return NULL;
}

const Language* Language::fromFilename(const QString& fileName) {
    // Search for all available languages.
    for (int i = 0; i < availableLangs.size(); ++i) {
        Language currentLang = availableLangs.at(i);
        QStringList extensions = currentLang.patterns().split(' ');
        // Search for all extensions.
        for (int j = 0; j < extensions.size(); ++j) {
            QRegExp re(extensions.at(j));
            re.setPatternSyntax(QRegExp::Wildcard);
            if (re.exactMatch(fileName)) {
                return &availableLangs.at(i);
            }
        }
    }
    // Not found
    return NULL;
}

QList<Language> Language::availableLangs = Language::intializeLangs();

QList<Language> Language::intializeLangs() {
    QList<Language> langs;

    langs.append(Language(
        "cpp", SCLEX_CPP, "C/C++",
        "*.h *.hh *.hpp *.hxx *.h++ *.c *.cc *.cpp *.cxx *.c++",
        QStringList() <<
        // Keywords
        "alignas alignof and and_eq asm auto bitand bitor bool break case "
        "catch char char16_t char32_t class compl const constexpr const_cast "
        "continue decltype default delete do double dynamic_cast else enum "
        "explicit export extern false float for friend goto if inline int "
        "long mutable namespace new noexcept not not_eq nullptr operator or "
        "or_eq private protected public register reinterpret_cast return short "
        "signed sizeof static static_assert static_cast struct switch template "
        "this thread_local throw true try typedef typeid typename union "
        "unsigned using virtual void volatile wchar_t while xor xor_eq"
        << "" <<
        // Doxygen Keywords
        "a addindex addtogroup anchor arg attention author authors b brief bug "
        "c callgraph callergraph category cite class code cond copybrief "
        "copydetails copydoc copyright date def defgroup deprecated details "
        "dir docbookonly dontinclude dot dotfile e else elseif em endcode "
        "endcond enddocbookonly enddot endhtmlonly endif endinternal "
        "endlatexonly endlink endmanonly endmsc endrtfonly endsecreflist "
        "endverbatim endxmlonly enum example exception extends f$ f[ f] f{ f} "
        "file fn headerfile hideinitializer htmlinclude htmlonly idlexcept "
        "if ifnot image implements include includelineno ingroup internal "
        "invariant interface latexonly li line link mainpage manonly memberof "
        "msc mscfile n name namespace nosubgrouping note overload p package "
        "page par paragraph param post pre private privatesection property "
        "protected protectedsection protocol public publicsection pure ref "
        "refitem related relates relatedalso relatesalso remark remarks result "
        "return returns retval rtfonly sa secreflist section see short "
        "showinitializer since skip skipline snippet struct subpage subsection "
        "subsubsection tableofcontents test throw throws todo tparam typedef "
        "union until var verbatim verbinclude version vhdlflow warning "
        "weakgroup xmlonly xrefitem $ @ \\ &amp; ~ < > # % \" . :: |",
        QList<StyleDescription>()
        << StyleDescription(SCE_C_DEFAULT, "Whitespace")
        << StyleDescription(SCE_C_COMMENT, "Comment")
        << StyleDescription(SCE_C_COMMENTLINE, "Line Comment")
        << StyleDescription(SCE_C_COMMENTDOC, "Documentation Comment")
        << StyleDescription(SCE_C_NUMBER, "Number")
        << StyleDescription(SCE_C_WORD, "Keyword")
        << StyleDescription(SCE_C_STRING, "String")
        << StyleDescription(SCE_C_CHARACTER, "Character")
        << StyleDescription(SCE_C_PREPROCESSOR, "Preprocessor")
        << StyleDescription(SCE_C_OPERATOR, "Operators")
        << StyleDescription(SCE_C_IDENTIFIER, "Identifiers")
        << StyleDescription(SCE_C_STRINGEOL, "Unclosed String Literal")
        << StyleDescription(SCE_C_COMMENTLINEDOC, "Documentation Comment Line")
        << StyleDescription(SCE_C_COMMENTDOCKEYWORD, "Comment Keyword")
        << StyleDescription(SCE_C_COMMENTDOCKEYWORDERROR, "Comment Keyword error")
        << StyleDescription(SCE_C_STRINGRAW, "Raw strings")
    ));
    langs.append(Language(
        "java", SCLEX_CPP, "Java", "*.java",
        QStringList() <<
        // Keywords
        "abstract assert boolean break byte case catch char class const "
        "continue default double do else enum extends final finally float for "
        "goto if implements import instanceof int interface long native new "
        "package private protected public return short static strictfp super "
        "switch synchronized this throw throws transient try void volatile "
        "while" << "" <<
        // Javadoc keywords
        "author code docRoot deprecated exception inheritDoc link linkplain "
        "literal param return see serial serialData serialField since throws "
        "value version",
        QList<StyleDescription>()
        << StyleDescription(SCE_C_DEFAULT, "Whitespace")
        << StyleDescription(SCE_C_COMMENT, "Comment")
        << StyleDescription(SCE_C_COMMENTLINE, "Line Comment")
        << StyleDescription(SCE_C_COMMENTDOC, "Documentation Comment")
        << StyleDescription(SCE_C_NUMBER, "Number")
        << StyleDescription(SCE_C_WORD, "Keyword")
        << StyleDescription(SCE_C_STRING, "String")
        << StyleDescription(SCE_C_CHARACTER, "Character")
        << StyleDescription(SCE_C_OPERATOR, "Operators")
        << StyleDescription(SCE_C_IDENTIFIER, "Identifiers")
        << StyleDescription(SCE_C_STRINGEOL, "Unclosed String Literal")
        << StyleDescription(SCE_C_COMMENTLINEDOC, "Documentation Comment Line")
        << StyleDescription(SCE_C_COMMENTDOCKEYWORD, "Comment Keyword")
        << StyleDescription(SCE_C_COMMENTDOCKEYWORDERROR, "Comment Keyword error")
    ));
    langs.append(Language(
        "python", SCLEX_PYTHON, "Python", "*.py *.pyw",
        QStringList() <<
        "False None True and as assert break class continue def del elif else "
        "except finally for from global if import in is lambda nonlocal not or "
        "pass raise return try while with yield",
        QList<StyleDescription>()
        << StyleDescription(SCE_P_DEFAULT, "Whitespace")
        << StyleDescription(SCE_P_COMMENTLINE, "Comment")
        << StyleDescription(SCE_P_NUMBER, "Number")
        << StyleDescription(SCE_P_STRING, "String")
        << StyleDescription(SCE_P_CHARACTER, "Character")
        << StyleDescription(SCE_P_WORD, "Keyword")
        << StyleDescription(SCE_P_TRIPLE, "Triple Quotes")
        << StyleDescription(SCE_P_TRIPLEDOUBLE, "Triple Double quotes")
        << StyleDescription(SCE_P_CLASSNAME, "Class Name")
        << StyleDescription(SCE_P_DEFNAME, "Function or Method")
        << StyleDescription(SCE_P_OPERATOR, "Operators")
        << StyleDescription(SCE_P_IDENTIFIER, "Identifiers")
        << StyleDescription(SCE_P_COMMENTBLOCK, "Comment-blocks")
        << StyleDescription(SCE_P_STRINGEOL, "Unclosed String literal")
        << StyleDescription(SCE_P_DECORATOR, "Decorators")
    ));

    return langs;
}

Language::Language(QString langId, int lexer, QString name, QString patterns,
                   QStringList keywords, QList<StyleDescription> styles)
    : m_langId(langId), m_lexer(lexer), m_name(name), m_patterns(patterns),
      m_keywords(keywords), m_styles(styles) {
}

QString Language::langId() const {
    return m_langId;
}

int Language::lexer() const {
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
