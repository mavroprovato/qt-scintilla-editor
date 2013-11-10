#include "icondb.h"
#include "language.h"
#include "languagedialog.h"
#include "ui_languagedialog.h"

#include <QSortFilterProxyModel>
#include <QStandardItem>
#include <QStandardItemModel>

LanguageDialog::LanguageDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LanguageDialog) {
    ui->setupUi(this);

    IconDb *iconDb = IconDb::instance();
    ui->cancelButton->setIcon(iconDb->getIcon(IconDb::DialogCancel));
    ui->selectButton->setIcon(iconDb->getIcon(IconDb::DialogOk));

    m_model = new QStandardItemModel();
    QStandardItem *parentItem = m_model->invisibleRootItem();
    QListIterator<Language*> languages = Language::allLanguages();
    while (languages.hasNext()) {
        Language *language = languages.next();
        QStandardItem *item = new QStandardItem(language->name());
        item->setData(language->langId());
        parentItem->appendRow(item);
    }

    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
    ui->languageListView->setModel(m_proxyModel);

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->selectButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->languageListView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
        this, SLOT(selectionChanged(const QItemSelection&, const QItemSelection&)));
}

LanguageDialog::~LanguageDialog() {
    delete ui;
}

const Language *LanguageDialog::selectedLanguage() const {
    QModelIndexList selectedIndexes = ui->languageListView->selectionModel()->selectedIndexes();
    if (!selectedIndexes.empty()) {
        QModelIndex sourceIndex = m_proxyModel->mapToSource(
            selectedIndexes.at(0));
        QStandardItem *item = m_model->itemFromIndex(sourceIndex);

        return Language::fromLanguageId(item->data().toString());
    }

    return NULL;
}

void LanguageDialog::setSelectedLanguage(const Language *language) {
    if (!language) {
        return;
    }
    // Search for the encoding in the model
    for (int i = 0; i < m_model->rowCount(); i++) {
        QStandardItem *item = m_model->item(i);
        if (item->data() == language->langId()) {
            QModelIndex proxyIndex = m_proxyModel->mapFromSource(
                        m_model->index(i, 0));
            if (!proxyIndex.isValid()) {
                // The index is not valid, because the value is filtered, so
                // clear the filter first.
                ui->languageFilterEdit->clear();
                proxyIndex = m_proxyModel->mapFromSource(m_model->index(i, 0));
            }
            ui->languageListView->selectionModel()->setCurrentIndex(
                    proxyIndex, QItemSelectionModel::SelectCurrent);
        }
    }
}

void LanguageDialog::showEvent(QShowEvent *e) {
    QDialog::showEvent(e);

    ui->languageFilterEdit->clear();
}

void LanguageDialog::on_languageFilterEdit_textChanged(const QString &text) {
    m_proxyModel->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive,
            QRegExp::FixedString));
}

void LanguageDialog::selectionChanged(const QItemSelection& selected,
        const QItemSelection&) {
    ui->selectButton->setEnabled(!selected.isEmpty());
}
