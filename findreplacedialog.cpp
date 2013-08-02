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

void FindReplaceDialog::on_findPushButton_clicked() {
    findPressed();
    hide();
}

void FindReplaceDialog::on_cancelButton_clicked() {
    hide();
}

QString FindReplaceDialog::findText() const {
    return ui->findLindEdit->text();
}

QString FindReplaceDialog::replaceText() const {
    return ui->replaceLineEdit->text();
}

bool FindReplaceDialog::directionForward() const {
    return ui->forwardRadioButton->isChecked();
}

bool FindReplaceDialog::matchCase() const {
    return ui->matchCaseCheckBox->isChecked();
}

bool FindReplaceDialog::wholeWord() const {
    return ui->matchWordCheckBox->isChecked();
}

bool FindReplaceDialog::regularExpression() const {
    return ui->regularExpressionCheckBox->isChecked();
}

bool FindReplaceDialog::wrapSearch() const {
    return ui->wrapSearchCheckBox->isChecked();
}
