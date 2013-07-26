#ifndef QSCINTILLAEDITOR_H
#define QSCINTILLAEDITOR_H

#include <QMainWindow>

namespace Ui {
class QScintillaEditor;
}

class QScintillaEditor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QScintillaEditor(QWidget *parent = 0);
    ~QScintillaEditor();
    
private:
    Ui::QScintillaEditor *ui;
};

#endif // QSCINTILLAEDITOR_H
