#include <ScintillaEdit.h>

#include "qscintillaeditor.h"
#include "ui_qscintillaeditor.h"

QScintillaEditor::QScintillaEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QScintillaEditor)
{
    ui->setupUi(this);

    ScintillaEdit *edit = new ScintillaEdit(this);
    setCentralWidget(edit);
}

QScintillaEditor::~QScintillaEditor()
{
    delete ui;
}
