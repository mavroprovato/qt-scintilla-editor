#include <ScintillaEdit.h>

#include <QtGlobal>

#include <QDebug>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QSettings>

#include "aboutdialog.h"
#include "buffer.h"
#include "configuration.h"
#include "encodingdialog.h"
#include "findreplacedialog.h"
#include "icondb.h"
#include "language.h"
#include "languagedialog.h"
#include "qscintillaeditor.h"
#include "ui_qscintillaeditor.h"
#include "util.h"

QScintillaEditor::QScintillaEditor(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::QScintillaEditor), workingDir(QDir::home()), wasMaximized(false), findDlg(0),
        aboutDlg(0), encodingDlg(0), languageDlg(0) {
    ui->setupUi(this);
    edit = new Buffer(parent);
    setCentralWidget(edit);

    IconDb* iconDb = IconDb::instance();
    setWindowIcon(iconDb->getIcon(IconDb::Application));
    setTitle();
    setUpActions();
    setUpMenuBar();
    setUpStatusBar();

    connect(edit, SIGNAL(savePointChanged(bool)), this, SLOT(savePointChanged(bool)));
    connect(edit, SIGNAL(updateUi(int)), this, SLOT(updateUi(int)));
    connect(edit, SIGNAL(fileInfoChanged(QFileInfo)), this, SLOT(onFileInfoChanged(QFileInfo)));
    connect(edit, SIGNAL(encodingChanged(const Encoding *)), this, SLOT(onEncodingChanged(const Encoding *)));
    connect(edit, SIGNAL(languageChanged(const Language *)), this, SLOT(onLanguageChanged(const Language *)));
    connect(edit, SIGNAL(urlsDropped(QList<QUrl>)), this, SLOT(onUrlsDropped(QList<QUrl>)));
}

QScintillaEditor::~QScintillaEditor() {
    delete ui;
}

void QScintillaEditor::openFile(const QString& fileName) {
    if (checkModifiedAndSave()) {
        QString openFileName;
        if (fileName.isEmpty()) {
            // Display the open file dialog
            openFileName = QFileDialog::getOpenFileName(
                        this, tr("Open File"), workingDir.absolutePath(), Language::filterString());
        }
        else {
            openFileName = fileName;
        }
        if (!openFileName.isEmpty()) {
            // Offer to create the file if it does not exist.
            QFileInfo fileInfo(openFileName);
            if (!fileInfo.exists()) {
                QString message(tr("File '%1' does not exist").arg(fileInfo.absoluteFilePath()));
                QMessageBox msgBox;
                msgBox.setText(message);
                msgBox.setInformativeText(tr("Do you want to create it?"));
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Yes);
                if (msgBox.exec() == QMessageBox::Yes) {
                    QFile file(openFileName);
                    if (!file.open(QIODevice::WriteOnly)) {
                        QString message(tr("File '%1' cannot be created").arg(fileInfo.absoluteFilePath()));
                        QMessageBox::critical(this, tr("Create File Error"), message);

                        return;
                    }
                    file.close();
                } else {
                    return;
                }
            }
            // Save the working directory.
            workingDir = fileInfo.absoluteDir();
            // Open the selected file.
            if (!edit->open(openFileName)) {
                QString message(tr("File '%1' cannot be opened").arg(fileInfo.absoluteFilePath()));
                QMessageBox::critical(this, tr("Open File Error"), message);
            }
        }
    }
}

bool QScintillaEditor::eventFilter(QObject *obj, QEvent *event) {
    if (obj == encodingLabel && event->type() == QEvent::MouseButtonDblClick) {
        if (!encodingDlg) {
            encodingDlg = new EncodingDialog(this);
        }
        encodingDlg->setSelectedEncoding(edit->encoding());
        encodingDlg->setCanReopen(!edit->fileInfo().fileName().isEmpty());
        if (encodingDlg->exec() == QDialog::Accepted) {
            edit->setEncoding(encodingDlg->selectedEncoding());
            if (encodingDlg->reopen()) {
                openFile(edit->fileInfo().absoluteFilePath());
            }
        }

        return true;
    } else if (obj == languageLabel && event->type() == QEvent::MouseButtonDblClick) {
        if (!languageDlg) {
            languageDlg = new LanguageDialog(this);
        }
        languageDlg->setSelectedLanguage(edit->language());
        if (languageDlg->exec() == QDialog::Accepted) {
            edit->setLanguage(languageDlg->selectedLanguage());
        }
    }

    return false;
}


void QScintillaEditor::on_actionNew_triggered() {
    QScintillaEditor *w = new QScintillaEditor;
    w->show();
}

void QScintillaEditor::on_actionOpen_triggered() {
    openFile("");
}

void QScintillaEditor::on_actionReopen_triggered() {
    openFile(edit->fileInfo().absoluteFilePath());
}

void QScintillaEditor::reopenWithEncoding_triggered() {
    changeEncoding_triggered();
    openFile(edit->fileInfo().absoluteFilePath());
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
    edit->clear();
}

void QScintillaEditor::on_actionQuit_triggered() {
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
        find(lastFindParams.findText, lastFindParams.flags, true, lastFindParams.wrap);
    }
}

void QScintillaEditor::on_actionFindPrevious_triggered() {
    if (!lastFindParams.findText.isEmpty()) {
        find(lastFindParams.findText, lastFindParams.flags, false, lastFindParams.wrap);
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
    int line = QInputDialog::getInt(this, tr("Line number"), tr("Go to line"), 1, 1, lineCount + 1, 1, &ok);
    if (ok) {
        edit->gotoLine(line - 1);
    }
}

void QScintillaEditor::on_actionSelectAll_triggered() {
    edit->selectAll();
}

void QScintillaEditor::on_actionToolBar_triggered() {
    ui->mainToolBar->setVisible(ui->actionToolBar->isChecked());
    Configuration::instance()->setShowToolBar(ui->actionToolBar->isChecked());
}

void QScintillaEditor::on_actionStatusBar_triggered() {
    ui->statusBar->setVisible(ui->actionStatusBar->isChecked());
    Configuration::instance()->setShowStatusBar(ui->actionStatusBar->isChecked());
}

void QScintillaEditor::on_actionFullscreen_triggered() {
    if (ui->actionFullscreen->isChecked()) {
        wasMaximized = isMaximized();
        showFullScreen();
    } else {
        if (wasMaximized) {
            showMaximized();
        } else {
            showNormal();
        }
    }
    Configuration::instance()->setFullscreen(ui->actionFullscreen->isChecked());
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
    edit->setViewWhitespace(ui->actionWhitespace->isChecked());
    Configuration::instance()->setViewWhitespace(ui->actionWhitespace->isChecked());
}

void QScintillaEditor::on_actionIndentationGuides_triggered() {
    edit->setViewIndentationGuides(ui->actionIndentationGuides->isChecked());
    Configuration::instance()->setViewIndentationGuides(ui->actionIndentationGuides->isChecked());
}

void QScintillaEditor::on_actionHighlightCurrentLine_triggered() {
    edit->setCaretLineVisible(ui->actionHighlightCurrentLine->isChecked());
    Configuration::instance()->setCaretLineVisible(ui->actionHighlightCurrentLine->isChecked());
}

void QScintillaEditor::on_actionLongLineIndicator_triggered() {
    edit->setLongLineIndicator(ui->actionLongLineIndicator->isChecked());
    Configuration::instance()->setLongLineIndicator(ui->actionLongLineIndicator->isChecked());
}

void QScintillaEditor::on_actionEndOfLine_triggered() {
    edit->setViewEOL(ui->actionEndOfLine->isChecked());
    Configuration::instance()->setViewEndOfLine(ui->actionEndOfLine->isChecked());
}

void QScintillaEditor::on_actionLineNumbers_triggered() {
    edit->setShowLineNumbers(ui->actionLineNumbers->isChecked());
    Configuration::instance()->setShowLineMargin(ui->actionLineNumbers->isChecked());
}

void QScintillaEditor::on_actionIconMargin_triggered() {
    edit->setShowIconMargin(ui->actionIconMargin->isChecked());
    Configuration::instance()->setShowIconMargin(ui->actionIconMargin->isChecked());
}

void QScintillaEditor::on_actionFoldMargin_triggered() {
    edit->setShowFoldMargin(ui->actionFoldMargin->isChecked());
    Configuration::instance()->setShowFoldMargin(ui->actionFoldMargin->isChecked());
}

void QScintillaEditor::on_actionWordWrap_triggered() {
    edit->setWrapMode(ui->actionWordWrap->isChecked() ? 1 : 0);
    Configuration::instance()->setWrap(ui->actionWordWrap->isChecked());
}

void QScintillaEditor::on_actionFont_triggered() {
    // Read the current font
    QFont initial = edit->styleQFont(STYLE_DEFAULT);
    // Show the font dialog
    bool ok;
    QFont font = QFontDialog::getFont(&ok, initial);
    if (ok) {
        edit->setStyleQFont(STYLE_DEFAULT, font);
        Configuration::instance()->setFont(font);
    }
}

void QScintillaEditor::changeEncoding_triggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    const Encoding *encoding = Encoding::fromName(action->data().toByteArray());
    edit->setEncoding(encoding);
}

void QScintillaEditor::changeColorScheme_triggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    const ColorScheme *colorScheme = ColorScheme::getColorScheme(action->text());
    edit->setColorScheme(colorScheme);
    Configuration::instance()->setColorScheme(action->text());
}

void QScintillaEditor::changeLanguage_triggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    const Language *language = Language::fromLanguageId(action->data().toString());
    edit->setLanguage(language);
}

void QScintillaEditor::on_actionEndOfLineWindows_triggered() {
    edit->setEOLMode(SC_EOL_CRLF);
    edit->convertEOLs(SC_EOL_CRLF);
}

void QScintillaEditor::on_actionEndOfLineUnix_triggered() {
    edit->setEOLMode(SC_EOL_LF);
    edit->convertEOLs(SC_EOL_LF);
}

void QScintillaEditor::on_actionEndOfLineMacintosh_triggered() {
    edit->setEOLMode(SC_EOL_CR);
    edit->convertEOLs(SC_EOL_CR);
}

void QScintillaEditor::on_actionToLowercase_triggered() {
    edit->lowerCase();
}

void QScintillaEditor::on_actionToUppercase_triggered() {
    edit->upperCase();
}

void QScintillaEditor::on_actionToggleBookmark_triggered() {
    edit->toggleBookmark(-1);
}

void QScintillaEditor::on_actionPreviousBookmark_triggered() {
    edit->gotoBookmark(false);
}

void QScintillaEditor::on_actionNextBookmark_triggered() {
    edit->gotoBookmark(true);
}

void QScintillaEditor::on_actionClearAllBookmarks_triggered() {
    edit->markerDeleteAll(Buffer::Bookmark);
}

void QScintillaEditor::on_actionAbout_triggered() {
    if (!aboutDlg) {
        aboutDlg = new AboutDialog(this);
    }
    aboutDlg->exec();
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

void QScintillaEditor::replace(const QString& findText, const QString& replaceText, int flags, bool forward,
                               bool wrap) {
    // Only replace if there is selected text
    if (edit->selectionStart() != edit->selectionEnd()) {
        QByteArray replaceArray = replaceText.toUtf8();
        if (flags & SCFIND_REGEXP) {
            edit->replaceTargetRE(replaceArray.length(), replaceArray);
        } else {
            edit->replaceTarget(replaceArray.length(), replaceArray);
        }
        // If searching forward, move the caret after the replacement text
        if (forward) {
            edit->setAnchor(edit->currentPos() + replaceText.length());
            edit->setCurrentPos(edit->currentPos() + replaceText.length());
        }
    }

    // Search again to select the next match
    find(findText, flags, forward, wrap);
}

void QScintillaEditor::replaceAll(const QString& findText, const QString& replaceText, int flags) {
    edit->beginUndoAction();
    edit->setCurrentPos(0);
    edit->setAnchor(0);
    while (edit->find(findText, flags, true, false, NULL)) {
        QByteArray replaceArray = replaceText.toUtf8();
        if (flags & SCFIND_REGEXP) {
            edit->replaceTargetRE(replaceArray.length(), replaceArray);
        } else {
            edit->replaceTarget(replaceArray.length(), replaceArray);
        }
    }
    edit->endUndoAction();
}

void QScintillaEditor::savePointChanged(bool dirty) {
    ui->actionSave->setEnabled(dirty);
    ui->actionUndo->setEnabled(dirty);
    setTitle();
}

void QScintillaEditor::updateUi(int updated) {
    // Set the actions that depend on the buffer state
    ui->actionCut->setEnabled(!edit->selectionEmpty());
    ui->actionCopy->setEnabled(!edit->selectionEmpty());
    // Set the postition indicator
    int position = edit->currentPos();
    positionLabel->setText(QString(tr("Line %1, Col %2").arg(edit->lineFromPosition(position) + 1).arg(
                                       edit->column(position) + 1)));
}

void QScintillaEditor::onFileInfoChanged(const QFileInfo& fileInfo) {
    ui->actionReopen->setEnabled(!fileInfo.fileName().isEmpty());
    ui->menuReopenWithEncoding->setEnabled(!fileInfo.fileName().isEmpty());
}

void QScintillaEditor::onEncodingChanged(const Encoding *encoding) {
    if (encoding) {
        encodingLabel->setText(encoding->toString());
    }
}

void QScintillaEditor::onLanguageChanged(const Language *language) {
    languageLabel->setText(language ? language->name() : tr("Default text"));
}

void QScintillaEditor::onUrlsDropped(const QList<QUrl>& urls) {
    for (int i = 0; i < urls.size(); ++i) {
        QUrl url = urls.at(i);
        if (url.isLocalFile()) {
            if (i == 0) {
                // Reuse the same window for the first file
                if (checkModifiedAndSave()) {
                    edit->open(url.toLocalFile());
                }
            } else {
                // For multiple files, open a new window
                QScintillaEditor *w = new QScintillaEditor;
                w->show();
                w->edit->open(url.toLocalFile());
            }
        }
    }
}

void QScintillaEditor::setUpActions() {
    // Set the icon of the actions.
    IconDb* iconDb = IconDb::instance();
    ui->actionNew->setIcon(iconDb->getIcon(IconDb::New));
    ui->actionOpen->setIcon(iconDb->getIcon(IconDb::Open));
    ui->actionReopen->setIcon(iconDb->getIcon(IconDb::Reopen));
    ui->actionSave->setIcon(iconDb->getIcon(IconDb::Save));
    ui->actionSaveAs->setIcon(iconDb->getIcon(IconDb::SaveAs));
    ui->actionPrint->setIcon(iconDb->getIcon(IconDb::Print));
    ui->actionClose->setIcon(iconDb->getIcon(IconDb::Close));
    ui->actionQuit->setIcon(iconDb->getIcon(IconDb::Quit));
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

    // Read the action status from the settings
    Configuration *configuration = Configuration::instance();
    ui->actionFullscreen->setChecked(configuration->fullscreen());
    on_actionFullscreen_triggered();
    ui->actionToolBar->setChecked(configuration->showToolBar());
    on_actionToolBar_triggered();
    ui->actionStatusBar->setChecked(configuration->showStatusBar());
    on_actionStatusBar_triggered();
    ui->actionWhitespace->setChecked(configuration->viewWhitespace());
    ui->actionIndentationGuides->setChecked(configuration->viewIndentationGuides());
    ui->actionHighlightCurrentLine->setChecked(configuration->caretLineVisible());
    ui->actionLongLineIndicator->setChecked(configuration->longLineIndicator());
    ui->actionEndOfLine->setChecked(configuration->viewEndOfLine());
    ui->actionLineNumbers->setChecked(configuration->showLineMargin());
    ui->actionIconMargin->setChecked(configuration->showIconMargin());
    ui->actionFoldMargin->setChecked(configuration->showFoldMargin());
    ui->actionWordWrap->setChecked(configuration->wrap());
}

void QScintillaEditor::setUpMenuBar() {
    // Add all color schemes to the menu
    QStringList colorSchemeNames = ColorScheme::allColorSchemes();
    for (int i = 0; i < colorSchemeNames.size(); ++i) {
        QAction* action = new QAction(colorSchemeNames.at(i), this);
        ui->menuColorScheme->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(changeColorScheme_triggered()));
    }
    // Add all languages to the menu
    QListIterator<Language*> languages = Language::allLanguages();
    while (languages.hasNext()) {
        Language *language = languages.next();
        QAction* action = new QAction(language->name(), this);
        action->setData(language->langId());
        ui->menuLanguage->addAction(action);
        connect(action, SIGNAL(triggered()), this, SLOT(changeLanguage_triggered()));
    }
    // Add all encodings to the menu.
    setUpEncodingMenu(ui->menuEncoding, SLOT(changeEncoding_triggered()));
    setUpEncodingMenu(ui->menuReopenWithEncoding, SLOT(reopenWithEncoding_triggered()));
    // Set up the end of line menu.
    QActionGroup* group = new QActionGroup(this);
    ui->actionEndOfLineWindows->setActionGroup(group);
    ui->actionEndOfLineUnix->setActionGroup(group);
    ui->actionEndOfLineMacintosh->setActionGroup(group);
#ifdef Q_OS_WIN
    ui->actionEndOfLineWindows->setChecked(true);
#else
    ui->actionEndOfLineUnix->setChecked(true);
#endif
}

void QScintillaEditor::setUpEncodingMenu(QMenu *parent, const char* slot) {
    // Add a menu for each encoding category
    QMenu* encodingCategories[] = {
        new QMenu(tr("West European"), this),
        new QMenu(tr("East European"), this),
        new QMenu(tr("East Asian"), this),
        new QMenu(tr("South Asian"), this),
        new QMenu(tr("Middle Eastern"), this),
        new QMenu(tr("Unicode"), this),
    };
    // Add a menu for each encoding
    QListIterator<Encoding*> encodings = Encoding::allEncodings();
    while (encodings.hasNext()) {
        Encoding *encoding = encodings.next();
        QAction* action = new QAction(encoding->toString(), this);
        action->setData(encoding->name());
        encodingCategories[encoding->category()]->addAction(action);
        connect(action, SIGNAL(triggered()), this, slot);
    }
    // Add all the categories to the encoding menu
    for (size_t i = 0; i < sizeof(encodingCategories) / sizeof(QMenu*); i++) {
        parent->addMenu(encodingCategories[i]);
    }
}

void QScintillaEditor::setUpStatusBar() {
    messageLabel = new QLabel(this);
    languageLabel = new QLabel(edit->language() ? edit->language()->name() : tr("Default text"), this);
    languageLabel->installEventFilter(this);
    encodingLabel = new QLabel(edit->encoding()->toString(), this);
    encodingLabel->installEventFilter(this);
    positionLabel = new QLabel(this);

    statusBar()->addPermanentWidget(messageLabel, 1);
    statusBar()->addPermanentWidget(languageLabel);
    statusBar()->addPermanentWidget(encodingLabel);
    statusBar()->addPermanentWidget(positionLabel);
}

void QScintillaEditor::setTitle() {
    QFileInfo fileInfo = edit->fileInfo();
    QString name = fileInfo.fileName().isEmpty() ? tr("Untitled") : fileInfo.fileName();
    QString title = QString("%1 - %2").arg(name).arg(qApp->applicationName()).append(edit->modify() ? " *" : "");
    setWindowTitle(title);
}

bool QScintillaEditor::checkModifiedAndSave() {
    // If the file has been modified, prompt the user to save the changes
    if (edit->modify()) {
        // Ask the user if the file should be saved
        QFileInfo fileInfo = edit->fileInfo();
        QString message = QString(tr("File '%1' has been modified")).arg(
                    fileInfo.filePath().isEmpty() ? tr("Untitled") : fileInfo.fileName());
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
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
            QString selectedFileName = QFileDialog::getSaveFileName(this, tr("Save File"));
            if (selectedFileName.isEmpty()) {
                return false;
            }
            newFileName = selectedFileName;
        }
    }

    if (!edit->save(newFileName)) {
        // Cannot write file, display an error message
        QMessageBox::critical(this, tr("Save File Error"), tr("The file cannot be saved"));

        return false;
    }

    return true;
}

void QScintillaEditor::initFindDialog() {
    if (!findDlg) {
        findDlg = new FindReplaceDialog(this);
        connect(findDlg, SIGNAL(find(const QString&, int, bool, bool)), this,
                SLOT(find(const QString&, int, bool, bool)));
        connect(findDlg, SIGNAL(replace(const QString&, const QString&, int, bool, bool)), this,
                SLOT(replace(const QString&, const QString&, int, bool, bool)));
        connect(findDlg, SIGNAL(replaceAll(const QString&, const QString&, int)), this,
                SLOT(replaceAll(const QString&, const QString&, int)));
    }
}

void QScintillaEditor::closeEvent(QCloseEvent *event) {
    if (!checkModifiedAndSave()) {
        // If the user canceled any dialog, do not exit the application
        event->ignore();
    }
}
