#include <ScintillaEdit.h>

#include "findreplacedialog.h"
#include "ui_findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindReplaceDialog) {
    ui->setupUi(this);
}

FindReplaceDialog::~FindReplaceDialog() {
    delete ui;
}

void FindReplaceDialog::setType(Type type) {
    // Set the visiblility of the replace controlls
    ui->replaceLabel->setVisible(type == FindReplace);
    ui->replaceLineEdit->setVisible(type == FindReplace);
    ui->replacePushButton->setVisible(type == FindReplace);
    ui->replaceAllPushButton->setVisible(type == FindReplace);
}

void FindReplaceDialog::showEvent(QShowEvent *e) {
    QDialog::showEvent(e);
    ui->findLindEdit->setFocus(Qt::ActiveWindowFocusReason);
}

void FindReplaceDialog::on_findPushButton_clicked() {
    QString findText = ui->findLindEdit->text();
    if (!findText.isEmpty()) {
        // Emit the signal
        emit find(findText, searchFlags(),
            ui->forwardRadioButton->isChecked(),
            ui->wrapSearchCheckBox->isChecked());
    }
}

void FindReplaceDialog::on_replacePushButton_clicked() {
    QString findText = ui->findLindEdit->text();
    QString replaceText = ui->replaceLineEdit->text();
    if (!replaceText.isEmpty()) {
        // Emit the signal
        emit replace(findText, replaceText, searchFlags(),
            ui->forwardRadioButton->isChecked(),
            ui->wrapSearchCheckBox->isChecked());
    }
}


void FindReplaceDialog::on_replaceAllPushButton_clicked() {
    QString findText = ui->findLindEdit->text();
    QString replaceText = ui->replaceLineEdit->text();
    if (!replaceText.isEmpty()) {
        // Emit the signal
        emit replaceAll(findText, replaceText, searchFlags());
    }
}

void FindReplaceDialog::on_cancelButton_clicked() {
    hide();
}

int FindReplaceDialog::searchFlags() {
    int flags = 0;
    if (ui->matchCaseCheckBox->isChecked()) {
        flags |= SCFIND_MATCHCASE;
    }
    if (ui->matchWordCheckBox->isChecked()) {
        flags |= SCFIND_WHOLEWORD;
    }
    if (ui->regularExpressionCheckBox->isChecked()) {
        flags |= SCFIND_REGEXP;
    }
    return flags;
}
