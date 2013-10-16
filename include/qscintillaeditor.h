#ifndef QSCINTILLAEDITOR_H
#define QSCINTILLAEDITOR_H

#include <QCloseEvent>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QMainWindow>
#include <QUrl>

class AboutDialog;
class Buffer;
class Encoding;
class EncodingDialog;
class FindReplaceDialog;
class Language;
class QLabel;
class QSettings;

namespace Ui {
class QScintillaEditor;
}

/**
 * A structure to hold the parameters of the last search.
 */
struct FindParams {
    QString findText;
    int flags;
    bool wrap;
};

class QScintillaEditor : public QMainWindow {
    Q_OBJECT

public:
    /**
     * Constructor for the editor.
     *
     * @param parent The parent widget for the editor.
     */
    explicit QScintillaEditor(QWidget *parent = 0);

    /**
     * Destructor for the editor.
     */
    ~QScintillaEditor();

    /**
     * Open a file with the provided file name.
     *
     * @param fileName The file name.
     */
    void openFile(const QString& fileName);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    /**
     * Called when the New file action is triggered.
     */
    void on_actionNew_triggered();

    /**
     * Called when the Open action is triggered.
     */
    void on_actionOpen_triggered();

    /**
     * Called when the Reopen action is triggered.
     */
    void on_actionReopen_triggered();

    /**
     * Called when the Reopen with encoding action is triggered.
     */
    void reopenWithEncoding_triggered();

    /**
     * Called when the Save action is triggered.
     */
    void on_actionSave_triggered();

    /**
     * Called when the Save as action is triggered.
     */
    void on_actionSaveAs_triggered();

    /**
     * Called when the Close action is triggered.
     */
    void on_actionClose_triggered();

    /**
     * Called when the Quit action is triggered.
     */
    void on_actionQuit_triggered();

    /**
     * Called when the Undo action is triggered.
     */
    void on_actionUndo_triggered();

    /**
     * Called when the Redo action is triggered.
     */
    void on_actionRedo_triggered();

    /**
     * Called when the Cut action is triggered.
     */
    void on_actionCut_triggered();

    /**
     * Called when the Copy action is triggered.
     */
    void on_actionCopy_triggered();

    /**
     * Called when the Paste action is triggered.
     */
    void on_actionPaste_triggered();

    /**
     * Called when the Find action is triggered.
     */
    void on_actionFind_triggered();

    /**
     * Called when the Find next action is triggered.
     */
    void on_actionFindNext_triggered();

    /**
     * Called when the Find previous action is triggered.
     */
    void on_actionFindPrevious_triggered();

    /**
     * Called when the replace action is triggered.
     */
    void on_actionReplace_triggered();

    /**
     * Called when the Go to action is triggered.
     */
    void on_actionGoTo_triggered();

    /**
     * Called when the Select all action is triggered.
     */
    void on_actionSelectAll_triggered();

    /**
     * Called when the View tool bar action is triggered.
     */
    void on_actionToolBar_triggered();

    /**
     * Called when the View status bar action is triggered.
     */
    void on_actionStatusBar_triggered();

    /**
     * Called when the View fullscreen action is triggered.
     */
    void on_actionFullscreen_triggered();

    /**
     * Called when the Zoom in action is triggered.
     */
    void on_actionZoomIn_triggered();

    /**
     * Called when the Zoom out action is triggered.
     */
    void on_actionZoomOut_triggered();

    /**
     * Called when the Reset zoom action is triggered.
     */
    void on_actionResetZoom_triggered();

    /**
     * Called when the View whitespace action is triggered.
     */
    void on_actionWhitespace_triggered();

    /**
     * Called when the View indentation guides action is triggered.
     */
    void on_actionIndentationGuides_triggered();

    /**
     * Called when the action to show/hide the long line indicator is triggered.
     */
    void on_actionLongLineIndicator_triggered();

    /**
     * Called when the View line numbers action is triggered.
     */
    void on_actionLineNumbers_triggered();

    /**
     * Called when the View icon margin action is triggered.
     */
    void on_actionIconMargin_triggered();

    /**
     * Called when the View fold margin action is triggered.
     */
    void on_actionFoldMargin_triggered();

    /**
     * Called when the Word wrap action is triggered.
     */
    void on_actionWordWrap_triggered();

    /**
     * Called when the View end of line action is triggered.
     */
    void on_actionEndOfLine_triggered();

    /**
     * Called when the Select font action is triggered.
     */
    void on_actionFont_triggered();

    /**
     * Called when the change language action is triggered.
     */
    void changeLanguage_triggered();

    /**
     * Called when the Change encoding action is triggered.
     */
    void changeEncoding_triggered();

    /**
     * Called when the Windows line ending action is triggered.
     */
    void on_actionEndOfLineWindows_triggered();

    /**
     * Called when the Unix line ending action is triggered.
     */
    void on_actionEndOfLineUnix_triggered();

    /**
     * Called when the Macintosh line ending action is triggered.
     */
    void on_actionEndOfLineMacintosh_triggered();

    /**
     * Called when the To lower case action is triggered.
     */
    void on_actionToLowercase_triggered();

    /**
     * Called when the To upper case action is triggered.
     */
    void on_actionToUppercase_triggered();

    /**
     * Called when the Toggle bookmark action is triggered.
     */
    void on_actionToggleBookmark_triggered();

    /**
     * Called when the Previous Bookmark action is triggered.
     */
    void on_actionPreviousBookmark_triggered();

    /**
     * Called when the Next Bookmark action is triggered.
     */
    void on_actionNextBookmark_triggered();

    /**
     * Called when the Clear All Bookmark action is triggered.
     */
    void on_actionClearAllBookmarks_triggered();

    /**
     * Called when the About action is triggered.
     */
    void on_actionAbout_triggered();

    /**
     * Called when the user searches for text.
     *
     * @param findText The text to search for.
     * @param flags The search flags.
     * @param forward true if the search must be performed towards the end of
     * the document.
     * @param wrap true if the search should wrap.
     */
    void find(const QString& findText, int flags, bool forward, bool wrap);

    /**
     * Called when the user wants to replace the found text.
     *
     * @param findText The text to search for.
     * @param replaceText The text to replace the found text with.
     * @param flags The search flags.
     * @param forward true if the search must be performed towards the end of
     * the document.
     * @param wrap true if the search should wrap.
     */
    void replace(const QString& findText, const QString& replaceText, int flags,
        bool forward, bool wrap);

    /**
     * Called when the user wants to replace all occurences of the text.
     *
     * @param findText The text to search for.
     * @param replaceText The text to replace the found text with.
     * @param flags The search flags.
     */
    void replaceAll(const QString& findText, const QString& replaceText,
        int flags);

    /**
     * Triggered when the save point is changed.
     *
     * @param dirty true if a save point is reached, false otherwise.
     */
    void savePointChanged(bool dirty);

    /**
     * Triggered when either the text or styling of the document has changed
     * or the selection range or scroll position has changed.
     */
    void updateUi();

    /**
     * Triggered when the opened file in the editor has changed.
     *
     * @param fileInfo The new file information.
     */
    void onFileInfoChanged(const QFileInfo& fileInfo);

    /**
     * Called when the encoding of the buffer has changed.
     *
     * @param encoding The new encoding.
     */
    void onEncodingChanged(const Encoding *encoding);

    /**
     * Called when the language of the buffer has changed.
     *
     * @param encoding The new language.
     */
    void onLanguageChanged(const Language *language);

    /**
     * Triggered when URL are dropped in the editor.
     *
     * @param uls The list of URLs that were dropped.
     */
    void onUrlsDropped(const QList<QUrl>& uls);

private:
    /**
     * Sets up the actions for the window.
     */
    void setUpActions();

    /**
     * Set up the menu bar.
     */
    void setUpMenuBar();

    /**
     * Sets up the encoding menu.
     *
     * @param parent The parent menu to which the menus and actions will be
     * added.
     * @param slot The slot to call when an action is triggered.
     */
    void setUpEncodingMenu(QMenu *parent, const char* slot);

    /**
     * Set up the status bar.
     */
    void setUpStatusBar();

    /**
     * Sets the window title.
     */
    void setTitle();

    /**
     * Checks if the current editor is modified and saves it if necessary.
     *
     * @return true if the file was saved or if the user did not want to save the
     * file, false otherwise.
     */
    bool checkModifiedAndSave();

    /**
     * Saves the file.
     *
     * @param fileName The file name under which to save the file.
     * @return true if the file was saved, false otherwise.
     */
    bool saveFile(const QString& fileName = "");

    /**
     * Initializes the find dialog.
     */
    void initFindDialog();

    /**
     * Called when the user tries to close the application.
     *
     * @param event The close event.
     */
    void closeEvent(QCloseEvent* event);

    /** The window UI. */
    Ui::QScintillaEditor *ui;

    /** The editor control. */
    Buffer *edit;

    /** The working directory. */
    QDir workingDir;

    /** The status bar label that displays messages */
    QLabel *messageLabel;

    /** The status bar label that displays the current language*/
    QLabel *languageLabel;

    /** The status bar label that displays the current encoding */
    QLabel *encodingLabel;

    /** The status bar label that displays the current position */
    QLabel *positionLabel;

    /** true if the window was maximized before foing full screen. */
    bool wasMaximized;

    /** The find/replace dialog. */
    FindReplaceDialog *findDlg;

    /** The last find parameters. */
    FindParams lastFindParams;

    /** The about dialog. */
    AboutDialog *aboutDlg;

    EncodingDialog *encodingDlg;
};

#endif // QSCINTILLAEDITOR_H
