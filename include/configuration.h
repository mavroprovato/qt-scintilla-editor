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
     * Returns true if the background color of the line containing the caret
     * should have a different background.
     *
     * @return true if the background color of the line containing the caret
     * should have a different background.
     */
    bool caretLineVisible();

    /**
     * Sets whether the background color of the line containing the caret
     * should have a different background.
     *
     * @param caretLineVisible whether the background color of the line
     * containing the caret should have a different background.
     */
    void setCaretLineVisible(bool caretLineVisible);

    bool braceHighlight();

    void setBraceHighlight(bool braceHighlight);

    /**
     * Returns the indentation guides mode.
     *
     * @return The indentation guides mode.
     */
    Buffer::IndentationGuidesMode indentationGuidesMode();

    /**
     * Sets the indentation guides mode.
     *
     * @param mode The new indentation guides mode.
     */
    void setIndentationGuidesMode(Buffer::IndentationGuidesMode mode);

    /**
     * Returns whether the long line indicator should be shown or not.
     *
     * @return true if the long line indicator should be shown.
     */
    bool longLineIndicator();

    /**
     * Sets the flag to show or hide the long line indicator.
     *
     * @param longLineIndicator true if the long line indicator should be shown,
     * false otherwise.
     */
    void setLongLineIndicator(bool longLineIndicator);

    /**
     * If this method returns true, then the long line indicator should be
     * displayed as a horizontal line. If false, the background color changes
     * after the limit.
     *
     * @return The type of the long line indicator.
     */
    bool longLineIndicatorLine();

    /**
     * Sets the long line indicator type. If this true, then the long line
     * indicator should be displayed as a horizontal line. If false,
     * the background color changes after the limit.
     *
     * @param longLineIndicatorLine The new type of the long line indicator.
     */
    void setLongLineIndicatorLine(bool longLineIndicatorLine);

    /**
     * Retruns the column number at which to display the long line marker.
     *
     * @return the column number at which to display the long line marker.
     */
    int longLineIndicatorColumn();

    /**
     * Sets the column number at which to display the long line marker.
     *
     * @param longLineIndicatorColumn The column number at which to display the
     * long line marker.
     */
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

    /**
     * Sets whether the line margin should be displayed or not.
     *
     * @param showLineMargin Set to true if the line margin should be shown.
     */
    void setShowLineMargin(bool showLineMargin);

    /**
     * Returns the width of the line margin, in number of characters that can
     * be displayed.
     *
     * @return The width of the line margin, in number of characters that can
     * be displayed.
     */
    int lineMarginWidth();

    /**
     * Sets the line margin width.
     *
     * @param lineMarginWidth The width of the line margin, in number of
     * characters that can be displayed.
     */
    void setLineMarginWidth(int lineMarginWidth);

    /**
     * Returns whether the line margin width should be changed automatically in
     * order to accomodate the biggest line number.
     *
     * @return true if the line margin width should be changed automatically in
     * order to accomodate the biggest line number.
     */
    bool trackLineMarginWidth();

    /**
     * Sets whether the line margin width should be change automatically
     * in order to accomodate the biggest line number or not.
     *
     * @param trackLineMarginWidth If true, the line margin width will be
     * changed automatically in order to accomodate the biggest line number.
     */
    void setTrackLineMarginWidth(bool trackLineMarginWidth);

    /**
     * Returns true if the icon margin should be shown.
     *
     * @return true if the icon margin should be shown.
     */
    bool showIconMargin();

    /**
     * Sets whether the icon margin should be displayed or not.
     *
     * @param showLineMargin Set to true if the icon margin should be shown.
     */
    void setShowIconMargin(bool showIconMargin);

    /**
     * Returns the icon margin width in pixels.
     *
     * @return The icon margin width in pixels.
     */
    int iconMarginWidth();

    /**
     * Sets the icon margin width, in pixels.
     *
     * @param iconMarginWidth The icon margin width, in pixels.
     */
    void setIconMarginWidth(int iconMarginWidth);

    /**
     * Returns true if the fold margin should be shown.
     *
     * @return true if the fold margin should be shown.
     */
    bool showFoldMargin();

    /**
     * Sets whether the fold margin should be displayed or not.
     *
     * @param showLineMargin Set to true if the fold margin should be shown.
     */
    void setShowFoldMargin(bool showFoldMargin);

    /**
     * Returns the fold margin width in pixels.
     *
     * @return The fold margin width in pixels.
     */
    int foldMarginWidth();

    /**
     * Sets the fold margin width, in pixels.
     *
     * @param foldMarginWidth The fold margin width, in pixels.
     */
    void setFoldMarginWidth(int foldMarginWidth);

    /**
     * Returns the type of the fold symbols.
     *
     * @return The type of the fold symbols.
     */
    Buffer::FoldSymbols foldSymbols();

    /**
     * Sets the type of the fold symbols.
     *
     * @param foldSymbols The type of the fold symbols.
     */
    void setFoldSymbols(Buffer::FoldSymbols foldSymbols);

    /**
     * Returns the type of the fold lines.
     *.
     * @return The type of the fold lines.
     */
    Buffer::FoldLines foldLines();

    /**
     * Sets the type of the fold lines.
     *
     * @param foldLines The type of the fold lines.
     */
    void setFoldLines(Buffer::FoldLines foldLines);

    /**
     * Returns true if the long lines should be wrapped.
     *
     * @return true if the long lines should be wrapped.
     */
    bool wrap();

    /**
     * Sets whether the long lines should be wrapped.
     *
     * @param wrap true if the long lines should be wrapped.
     */
    void setWrap(bool wrap);

    /**
     * Returns the width of the tab charachter.
     *
     * @return The width of the tab charachter.
     */
    int tabWidth() const;

    /**
     * Sets the width of the tab character.
     *
     * @param tabWidth The new width of the tab character.
     */
    void setTabWidth(int tabWidth);

    /**
     * Returns the identation width.
     *
     * @return The identation width.
     */
    int indentationWidth() const;

    /**
     * Sets the width of the identation character.
     *
     * @param indentationWidth The width of the identation character.
     */
    void setIndentationWidth(int indentationWidth);

    /**
     * Returns true if tabs should be used for identation, false if spaces
     * should be used.
     *
     * @return true if tabs should be used for identation, false if spaces
     * should be used.
     */
    bool useTabs() const;

    /**
     * Set to true if tabs should be used for identation. Set to false if
     * spaces should be used for identation.
     *
     * @param useTabs true, if tabs should be used for identation, false if
     * spaces should be used for identation.
     */
    void setUseTabs(bool useTabs);

    /**
     * Returns the assumed width of the scrollable area.
     *
     * @return The assumed width of the scrollable area.
     */
    int scrollWidth() const;

    /**
     * Sets the assumed width of the scrollable area.
     *
     * @param scrollWidth The assumed width of the scrollable area.
     */
    void setScrollWidth(int scrollWidth);

    /**
     * Returns whether the horizontal size of the scollable area should be
     * tracked or not.
     * @return Whether the horizontal size of the scollable area should be
     * tracked or not.
     */
    bool scrollWidthTracking() const;

    /**
     * Sets whether the horizontal size of the scollable area should be tracked
     *or not.
     * @param scrollWidthTracking true to track the horizontal size of the
     * scrollable area, false otherwise.
     */
    void setScrollWidthTracking(bool scrollWidthTracking);

    /**
     * Returns the font that should be used in the editor.
     *
     * @return The font that should be used in the editor.
     */
    QFont font() const;

    /**
     * Set the font to be used for the editor.
     *
     * @param font The font to be used for the editor.
     */
    void setFont(const QFont &font);

    /**
     * Returns the name of the selected color scheme.
     *
     * @return The name of the selected color scheme.
     */
    QString colorScheme() const;

    /**
     * Sets the initialy selected color scheme by name.
     *
     * @param name The name of the initialy selected color scheme.
     */
    void setColorScheme(const QString &name);

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
