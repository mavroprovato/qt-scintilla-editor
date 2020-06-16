#include "encoding.h"
#include "encodingdialog.h"
#include "icondb.h"
#include "ui_encodingdialog.h"

#include <QDebug>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

EncodingDialog::EncodingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EncodingDialog), m_canReopen(true),
                                                  m_reopen(false) {
    ui->setupUi(this);

    IconDb *iconDb = IconDb::instance();
    ui->cancelButton->setIcon(iconDb->getIcon(IconDb::DialogCancel));
    ui->reopenButton->setIcon(iconDb->getIcon(IconDb::Reopen));
    ui->selectButton->setIcon(iconDb->getIcon(IconDb::DialogOk));

    m_model = new QStandardItemModel();
    QStandardItem *parentItem = m_model->invisibleRootItem();
    QListIterator<Encoding*> encodings = Encoding::allEncodings();
    while (encodings.hasNext()) {
        Encoding *encoding = encodings.next();
        auto *item = new QStandardItem(encoding->toString());
        item->setData(encoding->name());
        parentItem->appendRow(item);
    }

    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
    ui->encodingListView->setModel(m_proxyModel);

    connect(ui->encodingListView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
        this, SLOT(selectionChanged(const QItemSelection&, const QItemSelection&)));
}

EncodingDialog::~EncodingDialog() {
    delete ui;
}

const Encoding *EncodingDialog::selectedEncoding() const {
    QModelIndexList selectedIndexes = ui->encodingListView->selectionModel()->selectedIndexes();
    if (!selectedIndexes.empty()) {
        QModelIndex sourceIndex = m_proxyModel->mapToSource(selectedIndexes.at(0));
        QStandardItem *item = m_model->itemFromIndex(sourceIndex);

        return Encoding::fromName(item->data().toByteArray());
    }

    return nullptr;
}

void EncodingDialog::setSelectedEncoding(const Encoding *encoding) {
    // Search for the encoding in the model
    for (int i = 0; i < m_model->rowCount(); i++) {
        QStandardItem *item = m_model->item(i);
        if (item->data() == encoding->name()) {
            QModelIndex proxyIndex = m_proxyModel->mapFromSource(m_model->index(i, 0));
            if (!proxyIndex.isValid()) {
                // The index is not valid, because the value is filtered, so
                // clear the filter first.
                ui->encodingFilter->clear();
                proxyIndex = m_proxyModel->mapFromSource(m_model->index(i, 0));
            }
            ui->encodingListView->selectionModel()->setCurrentIndex(proxyIndex, QItemSelectionModel::SelectCurrent);
        }
    }
}

void EncodingDialog::on_encodingFilter_textChanged(const QString &text) {
    m_proxyModel->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
}

bool EncodingDialog::reopen() const {
    return m_reopen;
}

void EncodingDialog::setCanReopen(bool canReopen) {
    if (m_canReopen != canReopen) {
        m_canReopen = canReopen;

        ui->reopenButton->setEnabled(canReopen);
    }
}

void EncodingDialog::showEvent(QShowEvent *e) {
    QDialog::showEvent(e);

    ui->encodingFilter->clear();
}

void EncodingDialog::selectionChanged(const QItemSelection& selected, const QItemSelection&) {
    ui->selectButton->setEnabled(!selected.isEmpty());
    ui->reopenButton->setEnabled(m_canReopen && !selected.isEmpty());
}

void EncodingDialog::on_selectButton_clicked() {
    m_reopen = false;

    accept();
}

void EncodingDialog::on_reopenButton_clicked() {
    m_reopen = true;

    accept();
}

void EncodingDialog::on_cancelButton_clicked() {
    reject();
}
