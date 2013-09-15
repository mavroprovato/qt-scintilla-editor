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
     * Enumeration that holds the various margins.
     */
    enum Margin {
        Line = 0, Icon = 1, Fold = 2
    };

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
     * Returns true if the line numbers are shown.
     *
     * @return true if the line numbers are shown.
     */
    bool showLineNumbers() const;

    /**
     * Shows or hides the line numbers.
     *
     * @param showLineNumbers if true, show the line numbers.
     */
    void setShowLineNumbers(bool showLineNumbers);

    /**
     * Returns true if the icon margin is shown.
     *
     * @return true if the icon margin is shown.
     */
    bool showIconMargin() const;

    /**
     * Shows or hides the icon margin.
     *
     * @param showIconMargin if true, show the icon margin.
     */
    void setShowIconMargin(bool showIconMargin);

    /**
     * Returns true if the fold margin is shown.
     *
     * @return true if the fold margin is shown.
     */
    bool showFoldMargin() const;

    /**
     * Shows or hides the fold margin.
     *
     * @param showIconMargin if true, show the fold margin.
     */
    void setShowFoldMargin(bool showFoldMargin);

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

    /**
     * Called when a margin is clicked.
     *
     * @param position The position of the start of the line in the document
     * that corresponds to the margin click.
     * @param modifiers The appropriate combination of SCI_SHIFT, SCI_CTRL and
     * SCI_ALT to indicate the keys that were held down at the time of the
     * margin click.
     * @param margin The margin number that was clicked.
     */
    void onMarginClicked(int position, int modifiers, int margin);

private:
    /**
     * Sets the file information of the underlying file.
     *
     * @param fileInfo The new file information.
     */
    void setFileInfo(const QFileInfo& fileInfo);

    /**
     * Set up the lexer for the buffer, depending on the opened file name.
     */
    void setupLexer();

    int getLineMarginWidth();

    /** The underlying file for this buffer. */
    QFileInfo m_fileInfo;

    /** The encofding for the buffer. */
    QByteArray m_encoding;

    /** Flag to display line numbers */
    bool m_showLineNumbers;

    /** Flag to display the icon margin */
    bool m_showIconMargin;

    /** Flag to display the fold margin */
    bool m_showFoldMargin;
};

#endif // BUFFER_H
