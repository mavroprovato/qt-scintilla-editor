#ifndef QSCINTILLAEDITOR_H
#define QSCINTILLAEDITOR_H

#include <QCloseEvent>
#include <QFileInfo>
#include <QMainWindow>

class ScintillaEdit;

namespace Ui {
class QScintillaEditor;
}

class QScintillaEditor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QScintillaEditor(QWidget *parent = 0);
    ~QScintillaEditor();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExit_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionGoTo_triggered();
    void on_actionSelectAll_triggered();
    void on_actionWordWrap_triggered();
    void on_actionToolBar_triggered();
    void on_actionStatusBar_triggered();

    void savePointChanged(bool dirty);
    void updateUi();

    void on_actionFullscreen_triggered();

private:
    void setUpEditor();
    bool checkModifiedAndSave();
    bool saveFile(const QString& fileName = "");
    void closeEvent(QCloseEvent* event);

    Ui::QScintillaEditor *ui;
    ScintillaEdit *edit;
    bool nameSet;
    QFileInfo fileInfo;
    bool wasMaximized;
};

#endif // QSCINTILLAEDITOR_H
