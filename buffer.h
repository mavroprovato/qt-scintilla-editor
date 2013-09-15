#ifndef BUFFER_H
#define BUFFER_H

#include <ScintillaEdit.h>

#include <QFileInfo>
#include <QList>
#include <QUrl>
#include <QWidget>

class Buffer : public ScintillaEdit {
    Q_OBJECT

    Q_PROPERTY(QFileInfo fileInfo READ fileInfo NOTIFY fileInfoChanged)
    Q_PROPERTY(QByteArray encoding READ encoding WRITE setEncoding NOTIFY encodingChanged)
public:
    /**
     * Creates the buffer.
     *
     * @param parent The parent window.
     */
    explicit Buffer(QWidget *parent = 0);

    /**
     * Destructor for the buffer.
     */
    virtual ~Buffer();

    /**
     * Clears the contents of the editor.
     */
    void clear();

    /**
     * Reads the contents of a file into the buffer.
     *
     * @param fileName The name of the file.
     * @return true, if the file has been opened successfully.
     */
    bool open(const QString& fileName);

    /**
     * Saves the contents of the buffer to a file.
     *
     * @param fileName The name of the file to save the contents.
     * @return true, if the file has been saved successfully.
     */
    bool save(const QString& fileName);

    /**
     * Returns the path of the file.
     *
     * @return The path of the file, or a null string if the buffer has not been
     * saved yet.
     */
    QFileInfo fileInfo() const;

    /**
     * Returns the encoding for the buffer.
     *
     * @return The encoding for the buffer.
     */
    QByteArray encoding() const;

    /**
     * Sets the encoding for the buffer.
     *
     * @param encoding The new encoding for the buffer.
     */
    void setEncoding(const QByteArray& encoding);

    /**
     * Finds the occurance of the provided text and selects the match.
     *
     * @param findText The text to find.
     * @param flags The search flags.
     * @param forward If true, perform the search with forward direction.
     * @param wrap If true, wrap the search.
     * @param searchWrapped Input parameter, which is set to true if the search
     * is wrapped.
     * @return true if a match was found.
     */
    bool find(const QString& findText, int flags, bool forward, bool wrap,
        bool *searchWrapped);

    /**
     * Returns true if the line numbers are shown.
     *
     * @return true if the line numbers are shown.
     */
    bool showLineNumbers();

    /**
     * Shows or hides the line numbers.
     *
     * @param show if true, show the line numbers.
     */
    void setShowLineNumbers(bool show);

    /**
     * Overriden in order to customize the default implementation in the case
     * when urls are dropped into the editor.
     *
     * @param event The drop event.
     */
    virtual void dropEvent(QDropEvent *event);

signals:
    /**
     * Emitted when the underlying file for this buffer is changed.
     *
     * @param fileInfo The new file information.
     */
    void fileInfoChanged(const QFileInfo& fileInfo);

    /**
     * Called when the encoding for the buffer has changed.
     *
     * @param encoding The new character encoding.
     */
    void encodingChanged(const QByteArray& encoding);

    /**
     * Called when a list of URLs have been dropped into the editor.
     *
     * @param encoding The new character encoding.
     */
    void urlsDropped(const QList<QUrl>& urls);

public slots:
    /**
     * Called when lines are added to the buffer.
     *
     * @param linesAdded The number of lines added.
     */
    void onLinesAdded(int linesAdded);

private:
    /**
     * Sets the file information of the underlying file.
     *
     * @param fileInfo The new file information.
     */
    void setFileInfo(const QFileInfo& fileInfo);

    /**
     * Set up the lexer for the buffer, depending of the opened file.
     */
    void setupLexer();

    /** The underlying file for this buffer. */
    QFileInfo m_fileInfo;

    /** The encofding for the buffer. */
    QByteArray m_encoding;
};

#endif // BUFFER_H
