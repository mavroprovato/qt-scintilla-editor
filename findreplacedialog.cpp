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
    // Set the search flags
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
    // Emit the signal
    emit find(ui->findLindEdit->text(), flags,
        ui->forwardRadioButton->isChecked(),
        ui->wrapSearchCheckBox->isChecked());
}

void FindReplaceDialog::on_cancelButton_clicked() {
    hide();
}
