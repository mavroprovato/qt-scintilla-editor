#ifndef BUFFER_H
#define BUFFER_H

#include "colorscheme.h"
#include "styleinfo.h"
#include "encoding.h"

#include <ScintillaEdit.h>

#include <QFileInfo>
#include <QList>
#include <QUrl>
#include <QWidget>

class Language;

class Buffer : public ScintillaEdit {
    Q_OBJECT

public:
    /**
     * Enumeration that holds the various margins.
     */
    enum Margin {
        Line, Icon, Fold
    };

    /**
     * Enumeration of the various icon markers.
     */
    enum IconMarkers {
        Bookmark
    };

    /**
     * The possible types of fold symbols.
     */
    enum FoldSymbols {
        Arrows, PlusMinus, CirclePlusMinus, BoxPlusMinus
    };

    /**
     * The possible types of fold lines.
     */
    enum FoldLines {
        NoLine, CircleLine, BoxLine
    };

    /**
     * The legal values for the indentation guides mode.
     */
    enum IndentationGuidesMode {
        None, Real, LookForward, LookBoth
    };

    enum Indicators {
        MatchBrace = INDIC_CONTAINER
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
     * Applies the specified color scheme to the buffer.
     *
     * @param colorScheme The color scheme to apply.
     */
    void setColorScheme(const ColorScheme *colorScheme);

    /**
     * Returns the encoding for the buffer.
     *
     * @return The encoding for the buffer.
     */
    const Encoding *encoding() const;

    /**
     * Sets the encoding for the buffer.
     *
     * @param encoding The new encoding for the buffer.
     */
    void setEncoding(const Encoding *encoding);

    /**
     * Returns the language for the buffer.
     *
     * @return The language for the buffer.
     */
    const Language *language() const;

    /**
     * Set the language for the buffer.
     *
     * @param lang The language.
     */
    void setLanguage(const Language *language);

    /**
     * Returns true if the whitespace should be shown.
     *
     * @return true if the whitespace should be shown.
     */
    bool viewWhitespace() const;

    /**
     * Sets whether the whitespace characters should be shown or not.
     *
     * @param viewWhitespace Set to true if the whitespace should be shown.
     */
    void setViewWhitespace(bool viewWhitespace);

    /**
     * Returns whether the indentation guides should be shown or not.
     *
     * @return Whether the indentation guides should be shown or not.
     */
    bool viewIndentationGuides() const;

    /**
     * Sets whether the indentation guides should be shown or not.
     *
     * @param viewIndentationGuides true if the indentation guides should be
     * shown.
     */
    void setViewIndentationGuides(bool viewIndentationGuides);

    /**
     * Returns true if the long line indicator should be shown.
     *
     * @return true if the long line indicator should be shown.
     */
    bool longLineIndicator() const;

    /**
     * Sets whether the long line indicator should be shown.
     *
     * @param longLineIndicator Whether the long line indicator should be shown.
     */
    void setLongLineIndicator(bool longLineIndicator);

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
     * Sets the types of the symbols in the fold margin.
     *
     * @param foldSymbols The types of the symbols in the fold margin.
     */
    void setFoldSymbols(FoldSymbols foldSymbols);

    /**
     * @brief setFoldLines
     * @param foldLines
     */
    void setFoldLines(FoldLines foldLines);

    /**
     * Returns the font for the specific style.
     *
     * @param style The style.
     * @return The font.
     */
    QFont styleQFont(int style) const;

    /**
     * Sets the font for the specific style.
     *
     * @param style The style.
     * @param font The font.
     */
    void setStyleQFont(int style, const QFont& font);

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
     * Toggles a bookmark. If the line number is less than zero, then the
     * bookmark is toggled in the current line.
     *
     * @param line The line to toggle the bookmark.
     */
    void toggleBookmark(int line);

    /**
     * Navigates to the next or previous bookmark.
     *
     * @param next true to navigate to the previous bookmark, false to navigate
     * to the next.
     */
    void gotoBookmark(bool next);

    /**
     * Overriden in order to customize the default implementation in the case
     * when urls are dropped into the editor.
     *
     * @param event The drop event.
     */
    virtual void dropEvent(QDropEvent *event);

signals:
    /**
     * Emitted when the underlying file for this buffer has changed.
     *
     * @param fileInfo The new file information.
     */
    void fileInfoChanged(const QFileInfo& fileInfo);

    /**
     * Called when the encoding for the buffer has changed.
     *
     * @param encoding The new character encoding.
     */
    void encodingChanged(const Encoding *encoding);

    /**
     * Emitted when the Language for this buffer has changed.
     *
     * @param language The new language information.
     */
    void languageChanged(const Language *language);

    /**
     * Called when a list of URLs have been dropped into the editor.
     *
     * @param encoding The new character encoding.
     */
    void urlsDropped(const QList<QUrl>& urls);

public slots:

    /**
     * Called when either the text or styling of the document has changed or
     * the selection range or scroll position has changed.
     */
    void onUpdateUi();

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
     * Loads the editor preferences from the configuration.
     */
    void loadConfiguration();

    /**
     * Sets the file information of the underlying file.
     *
     * @param fileInfo The new file information.
     */
    void setFileInfo(const QFileInfo& fileInfo);

    /**
     * Calculates the width of the line margin, in order to accomodate the
     * largest line number.
     *
     * @return The line width.
     */
    int getLineMarginWidth();

    /**
     * Sets up the icons for the margins.
     */
    void setupMarginIcons();

    int isBrace(sptr_t character);

    /**
     * Applies the specified style to the buffer.
     *
     * @param styleNumber The style number, as defined in the lexer.
     * @param style The style information.
     */
    void applyStyle(int styleNumber, const StyleInfo& style);

    /** The underlying file for this buffer. */
    QFileInfo m_fileInfo;

    /** The encoding for the buffer. */
    const Encoding *m_encoding;

    /** The language for the buffer. */
    const Language *m_language;

    /** If the the line margin width will be changed automatically in order to
     * accomodate the biggest line number */
    bool m_trackLineWidth;

    /** True if the matching brace should be highighted. */
    bool m_braceHighlight;
};

#endif // BUFFER_H
