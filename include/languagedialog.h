#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QItemSelection>
#include <QDialog>

class Language;
class QSortFilterProxyModel;
class QStandardItemModel;

namespace Ui {
class LanguageDialog;
}

class LanguageDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * Creates the dialog.
     *
     * @param parent The parent widget.
     */
    explicit LanguageDialog(QWidget *parent = nullptr);

    /**
     * Destroys the dialog.
     */
    ~LanguageDialog() override;

    /**
     * Returns the selected language.
     *
     * @return The selected language.
     */
    const Language *selectedLanguage() const;

    /**
     * Sets the selected language.
     *
     * @param language The language to be seleced.
     */
    void setSelectedLanguage(const Language *language);

protected:

    /**
     * Overridden, in order to make sure that filter text is cleared when the dialog is shown.
     *
     * @param e The show event.
     */
    void showEvent(QShowEvent *e) override;

private slots:

    /**
     * Called when the language filter text has changed.
     *
     * @param text The new text.
     */
    void on_languageFilterEdit_textChanged(const QString &text);

    /**
     * Called when the selection in the list changes. If there is no selection,
     * the select button is disabled.
     *
     * @param selected The selected items.
     * @param deselected The deselected items.
     */
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:

    /** The dialog UI. */
    Ui::LanguageDialog *ui;

    /** The list view model. */
    QStandardItemModel *m_model;

    /** The proxy model used for filtering. */
    QSortFilterProxyModel *m_proxyModel;
};

#endif // LANGUAGEDIALOG_H
