#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "version.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog) {
    ui->setupUi(this);

    ui->labelApplication->setText(QString("%1 v%2").arg(APPLICATION_NAME, APPLICATION_VERSION));
    ui->labelQt->setText(tr("<html><head/><body><p>Built with <a href=\"""https://www.qt.io/product/framework\">"
                            "Qt Framework</a> version " QT_VERSION_STR "</p></body></html>"));
}

AboutDialog::~AboutDialog() {
    delete ui;
}

void AboutDialog::on_pushButtonClose_clicked() {
    hide();
}
