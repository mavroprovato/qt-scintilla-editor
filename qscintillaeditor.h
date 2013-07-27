#ifndef QSCINTILLAEDITOR_H
#define QSCINTILLAEDITOR_H

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

private:
    bool checkModifiedAndSave();
    bool saveFile();

    Ui::QScintillaEditor *ui;
    ScintillaEdit *edit;
    bool nameSet;
    QFileInfo fileInfo;
};

#endif // QSCINTILLAEDITOR_H
