#ifndef QSCINTILLAEDITOR_H
#define QSCINTILLAEDITOR_H

#include <QCloseEvent>
#include <QMainWindow>

class AboutDialog;
class Buffer;
class FindReplaceDialog;
class QLabel;

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
     * Called when the action to show/hide the long line indicator is triggered.
     */
    void on_actionLongLineIndicator_triggered();

    /**
     * Called when the View line numbers action is triggered.
     */
    void on_actionLineNumbers_triggered();

    /**
     * Called when the Word wrap action is triggered.
     */
    void on_actionWordWrap_triggered();

    /**
     * Called when the Select font action is triggered.
     */
    void on_actionFont_triggered();

    /**
     * Called when the Change encoding action is triggered.
     */
    void on_changeEncoding_triggered();

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

    void onEncodingChanged(const QByteArray& encoding);
    void on_actionAbout_triggered();

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

    /** The status bar label that displays messages */
    QLabel *messageLabel;

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
};

#endif // QSCINTILLAEDITOR_H
