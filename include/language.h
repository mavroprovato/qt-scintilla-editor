#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QList>
#include <QString>
#include <QStringList>

#include "styleinfo.h"

/**
 * Holds information about the available languages that are supported by the
 * editor.
 */
class Language {
public:
    /**
     * Returns a filter string, created from all the available languages, that
     * can be used in a file dialog.
     *
     * @return The filter string.
     */
    static QString filterString();

    /**
     * Returns all languages that are available.
     *
     * @return All languages that are available.
     */
    static QListIterator<Language> allLanguages();

    /**
     * Returns the language from the language identifier.
     *
     * @param languageId The language identifier.
     * @return The language
     */
    static const Language* fromLanguageId(const QString& languageId);

    /**
     * Returns the language that correspond to the file with the specific name.
     *
     * @param fileName The file name.
     * @return The corresponding language.
     */
    static const Language* fromFilename(const QString& fileName);

    /**
     * Constructor for the language.
     *
     * @param langId The language identifier.
     * @param lexer The lexer for the language.
     * @param name The language name.
     * @param patterns The file patterns for the language.
     * @param keywords The keywords for the language, seperated by space.
     * @param styles The list of lexer styles available for this language.
     */
    Language(QString langId, int lexer, QString name, QString patterns,
             QStringList keywords, QList<StyleDescription> styles);

    /**
     * Returns the language identifier.
     *
     * @return The language identifier.
     */
    QString langId() const;

    /**
     * Returns the lexer for the language.
     *
     * @return the lexer for the language.
     */
    int lexer() const;

    /**
     * Returns the name of the language.
     *
     * @return The name of the language.
     */
    QString name() const;

    /**
     * Returns the file patterns for the language.
     *
     * @return the file patterns for the language.
     */
    QString patterns() const;

    /**
     * Returns the keywords for the language, seperated by space.
     *
     * @return keywords for the language, seperated by space.
     */
    QStringList keywords() const;

    /**
     * Returns the list of styles available for this language.
     *
     * @return The list of styles available for this language.
     */
    QList<StyleDescription> styles() const;

private:
    /**
     * Initializes the available languages list
     */
    static QList<Language> intializeLangs();

    /** Holds all the available languages. */
    static QList<Language> availableLangs;

    /** The language identifier */
    QString m_langId;

    /** The lexer for the language. */
    int m_lexer;

    /** The language name. */
    QString m_name;

    /** The file patterns for the language. */
    QString m_patterns;

    /** The keywords for the language, seperated by space. */
    QStringList m_keywords;

    /** The list of styles available for this language. */
    QList<StyleDescription> m_styles;
};

#endif // LANGUAGE_H
