#include <ScintillaEdit.h>

#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QMessageBox>

#include "qscintillaeditor.h"
#include "ui_qscintillaeditor.h"

/**
 * Constructor for the editor.
 *
 * @param parent The parent widget for the editor.
 */
QScintillaEditor::QScintillaEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QScintillaEditor),
    nameSet(false),
    wasMaximized(false) {
    ui->setupUi(this);

    edit = new ScintillaEdit(this);
    setCentralWidget(edit);

    setUpEditor();

    QObject::connect(edit, SIGNAL(savePointChanged(bool)), this,
        SLOT(savePointChanged(bool)));
    QObject::connect(edit, SIGNAL(updateUi()), this, SLOT(updateUi()));
}

/**
 * Destructor for the editor.
 */
QScintillaEditor::~QScintillaEditor() {
    delete ui;
}

/**
 * Called when the New file action is triggered.
 */
void QScintillaEditor::on_actionNew_triggered() {
    if (checkModifiedAndSave()) {
        // Clear the file name and the editor
        edit->clearAll();
        edit->setSavePoint();
        nameSet = false;
        fileInfo.setFile("");
    }
}

/**
 * Called when the Open action is triggered.
 */
void QScintillaEditor::on_actionOpen_triggered() {
    if (checkModifiedAndSave()) {
        // Display the open file dialog
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
        if (!fileName.isEmpty()) {
            // Save the file
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Open File Error"),
                    tr("The file cannot be opened."));
                return;
            }
            QTextStream in(&file);
            QString content = in.readAll();
            edit->setText(content.toUtf8());
            file.close();

            // File saved succesfully
            edit->setSavePoint();
            nameSet = true;
            fileInfo.setFile(fileName);
        }
    }
}

/**
 * Called when the save action is triggered.
 */
void QScintillaEditor::on_actionSave_triggered() {
    saveFile();
}

/**
 * Called when the save as action is triggered.
 */
void QScintillaEditor::on_actionSaveAs_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    if (!fileName.isEmpty()) {
        saveFile(fileName);
    }
}

/**
 * Called when the exit action is triggered.
 */
void QScintillaEditor::on_actionExit_triggered() {
    qApp->quit();
}

/**
 * Called when the undo action is triggered.
 */
void QScintillaEditor::on_actionUndo_triggered() {
    edit->undo();
    ui->actionRedo->setEnabled(edit->canRedo());
}

/**
 * Called when the redo action is triggered.
 */
void QScintillaEditor::on_actionRedo_triggered() {
    edit->redo();
    ui->actionRedo->setEnabled(edit->canRedo());
}

/**
 * Called when the cut action is triggered.
 */
void QScintillaEditor::on_actionCut_triggered() {
    edit->cut();
}

/**
 * Called when the copy action is triggered.
 */
void QScintillaEditor::on_actionCopy_triggered() {
    edit->copy();
}

/**
 * Called when the paste action is triggered.
 */
void QScintillaEditor::on_actionPaste_triggered() {
    edit->paste();
}

/**
 * Called when the go to action is triggered.
 */
void QScintillaEditor::on_actionGoTo_triggered() {
    int lineCount = edit->lineCount();
    bool ok;
    int line = QInputDialog::getInt(this, tr("Line number"), tr("Go to line"),
        1, 1, lineCount + 1, 1, &ok);
    if (ok) {
        edit->gotoLine(line - 1);
    }
}

/**
 * Called when the select all action is triggered.
 */
void QScintillaEditor::on_actionSelectAll_triggered() {
    edit->selectAll();
}

/**
 * Called when the view status bar action is triggered.
 */
void QScintillaEditor::on_actionStatusBar_triggered() {
    ui->statusBar->setVisible(ui->actionStatusBar->isChecked());
}

/**
 * Called when the view tool bar action is triggered.
 */
void QScintillaEditor::on_actionToolBar_triggered() {
    ui->mainToolBar->setVisible(ui->actionToolBar->isChecked());
}

/**
 * Called when the view fullscreen action is triggered.
 */
void QScintillaEditor::on_actionFullscreen_triggered() {
    if (isFullScreen()) {
        if (wasMaximized) {
            showMaximized();
        } else {
            showNormal();
        }
    } else {
        wasMaximized = isMaximized();
        showFullScreen();
    }
}
/**
 * Called when the word wrap action is triggered.
 */
void QScintillaEditor::on_actionWordWrap_triggered() {
    edit->setWrapMode(ui->actionWordWrap->isChecked() ? 1 : 0);
}

/**
 * Triggered when the save point is changed.
 *
 * @param dirty true if a save point is reached, false otherwise.
 */
void QScintillaEditor::savePointChanged(bool dirty) {
    ui->actionSave->setEnabled(dirty);
    ui->actionUndo->setEnabled(dirty);
}

/**
 * Either the text or styling of the document has changed or the selection range
 * or scroll position has changed.
 */
void QScintillaEditor::updateUi() {
    ui->actionCut->setEnabled(!edit->selectionEmpty());
    ui->actionCopy->setEnabled(!edit->selectionEmpty());
    ui->actionDelete->setEnabled(!edit->selectionEmpty());
}

/**
 * Sets up the initial settings for the editor.
 */
void QScintillaEditor::setUpEditor() {
    // Use Unicode code page
    edit->setCodePage(SC_CP_UTF8);
    // Do not display any margin
    edit->setMarginWidthN(1, 0);
    // Track the scroll width
    edit->setScrollWidth(1);
    edit->setScrollWidthTracking(true);
    // Set a monospaced font
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    edit->styleSetFont(STYLE_DEFAULT, font.family().toAscii());
    edit->styleSetSize(STYLE_DEFAULT, 10);
}

/**
 * Checks if the current editor is modified and saves it if necessary.
 *
 * @return true if the file was saved or if the user did not want to save the
 * file, false otherwise.
 */
bool QScintillaEditor::checkModifiedAndSave() {
    // If the file has been modified, promt the user to save the changes
    if (edit->modify()) {
        // Ask the user if the file should be saved
        QString message = QString(tr("File %1 has been modified"))
                .arg(nameSet ? tr("Untitled") : fileInfo.fileName());
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
            QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        // Get the user response
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            // Try to save the file
            return saveFile();
        case QMessageBox::Discard:
            return true;
        case QMessageBox::Cancel:
            // User canceled, do not clear
            return false;
        default:
            // Should never be reached
            break;
        }
    }

    return true;
}

/**
 * Saves the file.
 *
 * @param fileName The file name under which to save the file.
 * @return true if the file was saved, false otherwise.
 */
bool QScintillaEditor::saveFile(const QString &fileName) {
    // Get a file name if there is none
    QString newFileName;
    if (!fileName.isEmpty()) {
        newFileName = fileName;
    } else if (nameSet) {
        newFileName = fileInfo.filePath();
    } else {
        QString selectedFileName = QFileDialog::getSaveFileName(this,
            tr("Save File"));
        if (selectedFileName.isEmpty()) {
            return false;
        }
        newFileName = selectedFileName;
    }

    // Save the file
    QFile file(newFileName);
    if (!file.open(QIODevice::WriteOnly)) {
        // Cannot write file, display an error message
        QMessageBox::critical(this, tr("Save File Error"),
            tr("The file cannot be saved"));
        return false;
    }

    // Save the text to a file.
    QTextStream stream(&file);
    QByteArray content = edit->getText(edit->textLength() + 1);
    stream << QString::fromUtf8(content);
    stream.flush();
    file.close();

    // File saved
    edit->setSavePoint();
    fileInfo.setFile(newFileName);
    nameSet = true;

    return true;
}

/**
 * Called when the user tries to close the application.
 *
 * @param event The close event.
 */
void QScintillaEditor::closeEvent(QCloseEvent *event) {
    if (!checkModifiedAndSave()) {
        event->ignore();
    }
}
