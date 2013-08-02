#ifndef QSCINTILLAEDITOR_H
#define QSCINTILLAEDITOR_H

#include <QCloseEvent>
#include <QFileInfo>
#include <QMainWindow>

class ScintillaEdit;
class FindReplaceDialog;

namespace Ui {
class QScintillaEditor;
}

class QScintillaEditor : public QMainWindow
{
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
     * Called when the Exit action is triggered.
     */
    void on_actionExit_triggered();

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
     * Called when the Word wrap action is triggered.
     */
    void on_actionWordWrap_triggered();

    /**
     * Called when the Select font action is triggered.
     */
    void on_actionFont_triggered();

    /**
     * Called when the user searches for text.
     */
    void find();

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

private:
    /**
     * Sets up the initial settings for the editor.
     */
    void setUpEditor();

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
     * Called when the user tries to close the application.
     *
     * @param event The close event.
     */
    void closeEvent(QCloseEvent* event);

    /** The window UI. */
    Ui::QScintillaEditor *ui;

    /** The editor control. */
    ScintillaEdit *edit;

    /** true if the file name has been set. */
    bool nameSet;

    /** Contains the file information, if the file has been set. */
    QFileInfo fileInfo;

    /** true if the window was maximized before foing full screen. */
    bool wasMaximized;

    /** The find/replace dialog. */
    FindReplaceDialog *findDlg;
};

#endif // QSCINTILLAEDITOR_H
