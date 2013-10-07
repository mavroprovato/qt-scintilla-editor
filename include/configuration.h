#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "buffer.h"
#include "language.h"
#include "styleinfo.h"

#include <QHash>
#include <QSettings>

class Configuration {
public:
    /**
     * The legal values for the indentation guides mode.
     */
    enum IndentationGuidesMode {
        None, Real, LookForward, LookBoth
    };

    /**
     * Returns an instance of the configuration.
     *
     * @return An instance of the configuration.
     */
    static Configuration* instance();

    /**
     * Returns true if the tool bar should be shown.
     *
     * @return true if the tool bar should be shown.
     */
    bool showToolBar();

    /**
     * Used to set whether the tool bar should be shown.
     *
     * @param showToolBar Boolean flag to control whether the tool bar should be
     * shown.
     */
    void setShowToolBar(bool showToolBar);

    /**
     * Returns true if the status bar should be shown.
     *
     * @return true if the status bar should be shown.
     */
    bool showStatusBar();

    /**
     * Used to set whether the status bar should be shown.
     *
     * @param showToolBar Boolean flag to control whether the status bar should
     * be shown.
     */
    void setShowStatusBar(bool showStatusBar);

    /**
     * Returns whether the window should be initially displayed full screen.
     *
     * @return true if the window should be initially displayed full screen.
     */
    bool fullscreen();

    /**
     * Sets whether the window should be initially displayed full screen.
     *
     * @param fullscreen Boolean flag to control whether the window should be
     *initially displayed full screen.
     */
    void setFullscreen(bool fullscreen);

    /**
     * Returns true if the whitespace should be shown.
     *
     * @return true if the whitespace should be shown.
     */
    bool viewWhitespace();

    /**
     * Sets whether the whitespace characters should be displayed or not.
     *
     * @param viewWhitespace Boolean flag to control whether the whitespace
     * characters should be displayed or not.
     */
    void setViewWhitespace(bool viewWhitespace);

    /**
     * Returns whether visible whitespace inside indentation should be shown
     * or not.
     *
     * @return true if visible whitespace inside indentation should be shown.
     */
    bool viewIndentationWhitespace();

    /**
     * Sets whether visible whitespace inside indentation should be shown
     * or not.
     *
     * @param viewIndentationWhitespace Boolean flag to control whether visible
     * whitespace inside indentation should be shown or not.
     */
    void setViewIndentationWhitespace(bool viewIndentationWhitespace);

    /**
     * Returns true if the indentation guides should be shown.
     *
     * @return true if the indentation guides should be shown.
     */
    bool viewIndentationGuides();

    /**
     * Sets whether the indentation guides should be shown or not.
     *
     * @param viewIndentationGuides
     */
    void setViewIndentationGuides(bool viewIndentationGuides);

    /**
     * Returns the indentation guides mode.
     *
     * @return The indentation guides mode.
     */
    IndentationGuidesMode indentationGuidesMode();

    /**
     * Sets the indentation guides mode.
     *
     * @param mode The new indentation guides mode.
     */
    void setIndentationGuidesMode(IndentationGuidesMode mode);

    bool longLineIndicator();

    void setLongLineIndicator(bool longLineIndicator);

    bool longLineIndicatorLine();

    void setLongLineIndicatorLine(bool longLineIndicatorLine);

    int longLineIndicatorColumn();

    void setLongLineIndicatorColumn(int longLineIndicatorColumn);

    /**
     * Returns true if the end of line characters should be shown.
     *
     * @return true if the end of line characters should be shown.
     */
    bool viewEndOfLine();

    /**
     * Sets whether the end of line characters should be visible.
     *
     * @param endOfLine true if the end of line characters should be visible.
     */
    void setViewEndOfLine(bool endOfLine);

    /**
     * Returns true if the line margin should be shown.
     *
     * @return true if the line margin should be shown.
     */
    bool showLineMargin();

    void setShowLineMargin(bool showLineMargin);

    /**
     * Returns true if the icon margin should be shown.
     *
     * @return true if the icon margin should be shown.
     */
    bool showIconMargin();

    void setShowIconMargin(bool showIconMargin);

    /**
     * Returns true if the fold margin should be shown.
     *
     * @return true if the fold margin should be shown.
     */
    bool showFoldMargin();

    void setShowFoldMargin(bool showFoldMargin);

    Buffer::FoldSymbols foldSymbols();

    void setFoldSymbols(Buffer::FoldSymbols foldSymbols);

    Buffer::FoldLines foldLines();

    void setFoldLines(Buffer::FoldLines foldLines);

    bool wrap();

    void setWrap(bool wrap);

    int tabWidth() const;

    void setTabWidth(int tabWidth);

    int indentationWidth() const;

    void setIndentationWidth(int indentationWidth);

    bool useTabs() const;

    void setUseTabs(bool useTabs);

    int scrollWidth() const;

    void setScrollWidth(int scrollWidth);

    bool scrollWidthTracking() const;

    void setScrollWidthTracking(bool scrollWidthTracking);

    QFont font() const;

    void setFont(const QFont &font);

    QColor whitespaceForeground() const;

    void setWhitespaceForeground(const QColor& whitespaceForeground);

    QColor whitespaceBackground() const;

    void setWhitespaceBackground(const QColor& whitespaceBackground);

    /**
     * Returns a hash with the styles information for a specific language. In
     * the return hash, the key is the scitilla style identifier and the value
     * is the style information.
     *
     * @param language The language.
     * @return The
     */
    QHash<int, StyleInfo> styleForLanguage(const Language& language);

private:
    /**
     * Creates the configuration
     */
    Configuration();

    /**
     * Private copy constructor to prevent instantiation.
     */
    Configuration(const Configuration&);

    /**
     * Private equals operator to prevent instantiation.
     */
    Configuration& operator=(const Configuration&);

    /** The application settings. */
    QSettings settings;
};

#endif // CONFIGURATION_H
