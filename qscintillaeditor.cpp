#include <ScintillaEdit.h>

#include <QtGlobal>

#include <QDebug>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>

#include "buffer.h"
#include "findreplacedialog.h"
#include "icondb.h"
#include "qscintillaeditor.h"
#include "ui_qscintillaeditor.h"
#include "util.h"

QScintillaEditor::QScintillaEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QScintillaEditor),
    wasMaximized(false),
    findDlg(0) {

    ui->setupUi(this);
    IconDb* iconDb = IconDb::instance();
    setWindowIcon(iconDb->getIcon(IconDb::Application));
    setUpActions();

    edit = new Buffer(parent);
    setCentralWidget(edit);
    setUpMenuBar();
    setUpStatusBar();
    setTitle();

    connect(edit, SIGNAL(savePointChanged(bool)), this,
        SLOT(savePointChanged(bool)));
    connect(edit, SIGNAL(updateUi()), this, SLOT(updateUi()));
    connect(edit, SIGNAL(encodingChanged(QByteArray)), this,
        SLOT(onEncodingChanged(QByteArray)));
}

QScintillaEditor::~QScintillaEditor() {
    delete ui;
}

void QScintillaEditor::on_actionNew_triggered() {
    QScintillaEditor *w = new QScintillaEditor;
    w->show();
}

void QScintillaEditor::on_actionOpen_triggered() {
    if (checkModifiedAndSave()) {
        // Display the open file dialog
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
        if (!fileName.isEmpty()) {
            if (!edit->open(fileName)) {
                QMessageBox::critical(this, tr("Open File Error"),
                    tr("The file cannot be opened."));
            }
        }
    }
}

void QScintillaEditor::on_actionSave_triggered() {
    saveFile();
}

void QScintillaEditor::on_actionSaveAs_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    if (!fileName.isEmpty()) {
        saveFile(fileName);
    }
}

void QScintillaEditor::on_actionClose_triggered() {
    close();
}

void QScintillaEditor::on_actionUndo_triggered() {
    edit->undo();
    ui->actionRedo->setEnabled(edit->canRedo());
}

void QScintillaEditor::on_actionRedo_triggered() {
    edit->redo();
    ui->actionRedo->setEnabled(edit->canRedo());
}

void QScintillaEditor::on_actionCut_triggered() {
    edit->cut();
}

void QScintillaEditor::on_actionCopy_triggered() {
    edit->copy();
}

void QScintillaEditor::on_actionPaste_triggered() {
    edit->paste();
}

void QScintillaEditor::on_actionFind_triggered() {
    initFindDialog();
    findDlg->setType(FindReplaceDialog::Find);

    findDlg->show();
    findDlg->raise();
    findDlg->activateWindow();
}

void QScintillaEditor::on_actionFindNext_triggered() {
    if (!lastFindParams.findText.isEmpty()) {
        find(lastFindParams.findText, lastFindParams.flags, true,
            lastFindParams.wrap);
    }
}

void QScintillaEditor::on_actionFindPrevious_triggered() {
    if (!lastFindParams.findText.isEmpty()) {
        find(lastFindParams.findText, lastFindParams.flags, false,
            lastFindParams.wrap);
    }
}

void QScintillaEditor::on_actionReplace_triggered() {
    initFindDialog();
    findDlg->setType(FindReplaceDialog::FindReplace);

    findDlg->show();
    findDlg->raise();
    findDlg->activateWindow();
}

void QScintillaEditor::on_actionGoTo_triggered() {
    int lineCount = edit->lineCount();
    bool ok;
    int line = QInputDialog::getInt(this, tr("Line number"), tr("Go to line"),
        1, 1, lineCount + 1, 1, &ok);
    if (ok) {
        edit->gotoLine(line - 1);
    }
}

void QScintillaEditor::on_actionSelectAll_triggered() {
    edit->selectAll();
}

void QScintillaEditor::on_actionToolBar_triggered() {
    ui->mainToolBar->setVisible(ui->actionToolBar->isChecked());
}

void QScintillaEditor::on_actionStatusBar_triggered() {
    ui->statusBar->setVisible(ui->actionStatusBar->isChecked());
}

void QScintillaEditor::on_actionFullscreen_triggered() {
    if (ui->actionFullscreen->isChecked()) {
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

void QScintillaEditor::on_actionZoomIn_triggered() {
    edit->zoomIn();
    if (edit->zoom() == 20) {
        ui->actionZoomIn->setEnabled(false);
    }
    ui->actionZoomOut->setEnabled(true);
}

void QScintillaEditor::on_actionZoomOut_triggered() {
    edit->zoomOut();
    if (edit->zoom() == -10) {
        ui->actionZoomOut->setEnabled(false);
    }
    ui->actionZoomIn->setEnabled(true);
}

void QScintillaEditor::on_actionResetZoom_triggered() {
    edit->setZoom(0);
    ui->actionZoomOut->setEnabled(true);
    ui->actionZoomIn->setEnabled(true);
}

void QScintillaEditor::on_actionWhitespace_triggered() {
    if (ui->actionWhitespace->isChecked()) {
        edit->setViewWS(SCWS_VISIBLEALWAYS);
    } else {
        edit->setViewWS(SCWS_INVISIBLE);
    }
}

void QScintillaEditor::on_actionLongLineIndicator_triggered() {
    if (ui->actionLongLineIndicator->isChecked()) {
        edit->setEdgeMode(EDGE_LINE);
    } else {
        edit->setEdgeMode(EDGE_NONE);
    }
}

void QScintillaEditor::on_actionLineNumbers_triggered() {
    edit->setShowLineNumbers(ui->actionLineNumbers->isChecked());
}

void QScintillaEditor::on_actionWordWrap_triggered() {
    edit->setWrapMode(ui->actionWordWrap->isChecked() ? 1 : 0);
}

void QScintillaEditor::on_actionFont_triggered() {
    // Read the current font
    QString family = edit->styleFont(STYLE_DEFAULT);
    int pointSize = edit->styleSize(STYLE_DEFAULT);
    bool bold = edit->styleBold(STYLE_DEFAULT);
    bool italic = edit->styleItalic(STYLE_DEFAULT);
    QFont initial(family, pointSize,
        bold ? QFont::Bold : QFont::Normal, italic);
    // Show the font dialog
    bool ok;
    QFont font = QFontDialog::getFont(&ok, initial);
    if (ok) {
        edit->styleSetFont(STYLE_DEFAULT, font.family().toLatin1());
        edit->styleSetSize(STYLE_DEFAULT, font.pointSize());
        edit->styleSetBold(STYLE_DEFAULT, font.bold());
        edit->styleSetItalic(STYLE_DEFAULT, font.italic());
    }
}

void QScintillaEditor::on_changeEncoding_triggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    edit->setEncoding(action->data().toByteArray());
}

void QScintillaEditor::find(const QString& findText, int flags, bool forward,
        bool wrap) {
    bool searchWrapped;
    bool found = edit->find(findText, flags, forward, wrap, &searchWrapped);
    if (found) {
        messageLabel->setText(searchWrapped ? tr("Search wrapped.") : tr(""));
    } else {
        messageLabel->setText(tr("The text was not found."));
    }

    // Save the last search parameters
    lastFindParams.findText = findText;
    lastFindParams.flags = flags;
    lastFindParams.wrap = wrap;

}

void QScintillaEditor::replace(const QString& findText,
        const QString& replaceText, int flags, bool forward, bool wrap) {
    // Only replace if there is selected text
    if (edit->selectionStart() != edit->selectionEnd()) {
        QByteArray replaceArray = replaceText.toUtf8();
        edit->replaceTarget(replaceArray.length(), replaceArray);
        // If searching forward, move the caret after the replacement text
        if (forward) {
            edit->setAnchor(edit->currentPos() + replaceText.length());
            edit->setCurrentPos(edit->currentPos() + replaceText.length());
        }
    }

    // Search again to select the next match
    find(findText, flags, forward, wrap);
}

void QScintillaEditor::replaceAll(const QString& findText,
        const QString& replaceText, int flags) {
    while (edit->find(findText, flags, true, true, NULL)) {
        QByteArray replaceArray = replaceText.toUtf8();
        edit->replaceTarget(replaceArray.length(), replaceArray);
    }
}

void QScintillaEditor::savePointChanged(bool dirty) {
    ui->actionSave->setEnabled(dirty);
    ui->actionUndo->setEnabled(dirty);
    setTitle();
}

void QScintillaEditor::updateUi() {
    // Set the actions that depend on the buffer state
    ui->actionCut->setEnabled(!edit->selectionEmpty());
    ui->actionCopy->setEnabled(!edit->selectionEmpty());
    // Set the postition indicator
    int position = edit->currentPos();
    positionLabel->setText(QString(tr("Line %1, Col %2").arg(
        edit->lineFromPosition(position) + 1).arg(edit->column(position) + 1)));
}

void QScintillaEditor::onEncodingChanged(const QByteArray& encoding) {
    encodingLabel->setText(encoding);
}

void QScintillaEditor::setUpActions() {
    IconDb* iconDb = IconDb::instance();
    ui->actionNew->setIcon(iconDb->getIcon(IconDb::New));
    ui->actionOpen->setIcon(iconDb->getIcon(IconDb::Open));
    ui->actionSave->setIcon(iconDb->getIcon(IconDb::Save));
    ui->actionSaveAs->setIcon(iconDb->getIcon(IconDb::SaveAs));
    ui->actionPrint->setIcon(iconDb->getIcon(IconDb::Print));
    ui->actionClose->setIcon(iconDb->getIcon(IconDb::Close));
    ui->actionUndo->setIcon(iconDb->getIcon(IconDb::Undo));
    ui->actionRedo->setIcon(iconDb->getIcon(IconDb::Redo));
    ui->actionCut->setIcon(iconDb->getIcon(IconDb::Cut));
    ui->actionCopy->setIcon(iconDb->getIcon(IconDb::Copy));
    ui->actionPaste->setIcon(iconDb->getIcon(IconDb::Paste));
    ui->actionFind->setIcon(iconDb->getIcon(IconDb::Find));
    ui->actionReplace->setIcon(iconDb->getIcon(IconDb::Replace));
    ui->actionFullscreen->setIcon(iconDb->getIcon(IconDb::Fullscreen));
    ui->actionZoomIn->setIcon(iconDb->getIcon(IconDb::ZoomIn));
    ui->actionZoomOut->setIcon(iconDb->getIcon(IconDb::ZoomOut));
    ui->actionResetZoom->setIcon(iconDb->getIcon(IconDb::ZoomReset));
    ui->actionFont->setIcon(iconDb->getIcon(IconDb::Font));
    ui->actionAbout->setIcon(iconDb->getIcon(IconDb::About));
}

void QScintillaEditor::setUpMenuBar() {
    // Add a menu for each encoding category
    QMenu* encodingCategories[] = {
        new QMenu(tr("West European"), this),
        new QMenu(tr("East European"), this),
        new QMenu(tr("East Asian"), this),
        new QMenu(tr("South Asian"), this),
        new QMenu(tr("Middle Eastern"), this),
        new QMenu(tr("Unicode"), this),
    };
    for (size_t i = 0; i < sizeof(encodingCategories) / sizeof(QAction*); i++) {
        ui->menuEncoding->addMenu(encodingCategories[i]);
    }
    // Add a menu for each encoding
    for (size_t i = 0; i < G_ENCODING_COUNT; i++) {
        Encoding encoding = G_AVAILABLE_ENCODINGS[i];
        QString text = QString("%1 (%2)").arg(encoding.language,
            encoding.displayName);
        QAction* action = new QAction(text, this);
        action->setData(encoding.name);
        encodingCategories[encoding.category]->addAction(action);
        connect(action, SIGNAL(triggered()), this,
            SLOT(on_changeEncoding_triggered()));
    }
}

void QScintillaEditor::setUpStatusBar() {
    messageLabel = new QLabel(this);
    encodingLabel = new QLabel(edit->encoding(), this);
    positionLabel = new QLabel(this);

    statusBar()->addPermanentWidget(messageLabel, 1);
    statusBar()->addPermanentWidget(encodingLabel);
    statusBar()->addPermanentWidget(positionLabel);
}

void QScintillaEditor::setTitle() {
    QFileInfo fileInfo = edit->fileInfo();
    QString name = fileInfo.fileName().isEmpty() ? tr("Untitled") :
                                                   fileInfo.fileName();
    QString title = QString("%1 - %2").arg(name).arg(qApp->applicationName())
        .append(edit->modify() ? " *" : "");
    setWindowTitle(title);
}

bool QScintillaEditor::checkModifiedAndSave() {
    // If the file has been modified, promt the user to save the changes
    if (edit->modify()) {
        // Ask the user if the file should be saved
        QFileInfo fileInfo = edit->fileInfo();
        QString message = QString(tr("File '%1' has been modified"))
                .arg(fileInfo.filePath().isEmpty() ? tr("Untitled") :
                                                     fileInfo.fileName());
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
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
            // Discard the file contents
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

bool QScintillaEditor::saveFile(const QString &fileName) {
    // Get a file name if there is none
    QString newFileName;
    if (!fileName.isEmpty()) { // Save with the provided file name.
        newFileName = fileName;
    } else {
        newFileName = edit->fileInfo().filePath();

        if (newFileName.isEmpty()) {
            QString selectedFileName = QFileDialog::getSaveFileName(this,
                tr("Save File"));
            if (selectedFileName.isEmpty()) {
                return false;
            }
            newFileName = selectedFileName;
        }
    }

    if (!edit->save(newFileName)) {
        // Cannot write file, display an error message
        QMessageBox::critical(this, tr("Save File Error"),
            tr("The file cannot be saved"));
        return false;
    }

    return true;
}

void QScintillaEditor::initFindDialog() {
    if (!findDlg) {
        findDlg = new FindReplaceDialog(this);
        connect(findDlg, SIGNAL(find(const QString&, int, bool, bool)), this,
            SLOT(find(const QString&, int, bool, bool)));
        connect(findDlg, SIGNAL(replace(const QString&, const QString&, int, bool, bool)),
            this, SLOT(replace(const QString&, const QString&, int, bool, bool)));
        connect(findDlg, SIGNAL(replaceAll(const QString&, const QString&, int)),
            this, SLOT(replaceAll(const QString&, const QString&, int)));
    }
}

void QScintillaEditor::closeEvent(QCloseEvent *event) {
    if (!checkModifiedAndSave()) {
        // If the user canceled any dialog, do not exit the application
        event->ignore();
    }
}
