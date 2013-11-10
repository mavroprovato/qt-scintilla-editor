#ifndef ENCODING_H
#define ENCODING_H

#include <QByteArray>
#include <QListIterator>
#include <QString>

class Encoding {
public:
    /**
     * The differenct categories for the encodings.
     */
    enum EncodingCategory {
        WestEuropean = 0, EastEuropean = 1, EastAsian = 2, SouthAsian = 3,
        MiddleEastern = 4, Unicode = 5
    };

    /**
     * Returns all encodings that are available.
     *
     * @return All encodings that are available.
     */
    static QListIterator<Encoding*> allEncodings();

    /**
     * Returns the encoding, given its system name.
     *
     * @param name The encoding system name.
     * @return The encoding.
     */
    static const Encoding *fromName(const QByteArray& name);

    /**
     * Cleans up the static recources.
     */
    static void cleanup();

    /**
     * Returns the encoding language.
     *
     * @return The encoding language.
     */
    QString language() const;

    /**
     * Returns the encoding display name.
     *
     * @return The encoding display name.
     */
    QString displayName() const;

    /**
     * Returns the encoding system name.
     *
     * @return The encoding system name.
     */
    QByteArray name() const;

    /**
     * Returns the encoding category.
     *
     * @return The encoding category.
     */
    EncodingCategory category() const;

    /**
     * Returns the string represenatation for this encoding.
     *
     * @return The string represenatation for this encoding.
     */
    QString toString() const;

private:

    /**
     * Initializes the available languages list
     */
    static QList<Encoding*> intializeEncodings();

    /** Holds all the available languages. */
    static QList<Encoding*> availableEncodings;

    /**
     * Creates the encoding.
     *
     * @param language The encoding language.
     * @param displayName The encoding display name.
     * @param name The encoding system name.
     * @param category The encoding category.
     */
    Encoding(QString language, QString displayName, QByteArray name,
            EncodingCategory category);
    /**
     * Destructor for the encoding.
     */
    ~Encoding();

    /**
     * Private copy constructor, not implemented.
     */
    Encoding(Encoding const&);

    /**
     * Private assgnement operator, not implemented.
     */
    void operator=(Encoding const&);

    /** The encoding language. */
    QString m_language;

    /** The encoding display name */
    QString m_displayName;

    /** The encoding system name. */
    QByteArray m_name;

    /** The encoding category. */
    EncodingCategory m_category;
};

#endif // ENCODING_H
