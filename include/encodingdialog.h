#ifndef ENCODINGDIALOG_H
#define ENCODINGDIALOG_H

#include <QAbstractListModel>
#include <QDialog>
#include <QItemSelection>

class Encoding;
class QSortFilterProxyModel;
class QStandardItemModel;

namespace Ui {
class EncodingDialog;
}

class EncodingDialog : public QDialog {
    Q_OBJECT
    
public:
    /**
     * Creates the encoding dialog.
     *
     * @param parent The parent widget.
     */
    explicit EncodingDialog(QWidget *parent = nullptr);

    /**
     * Destroys the dialog.
     */
    ~EncodingDialog() override;

    /**
     * Returns the selected encoding.
     *
     * @return The selected encoding.
     */
    const Encoding *selectedEncoding() const;

    /**
     * Sets the selected encoding.
     *
     * @param encoding The encoding to select.
     */
    void setSelectedEncoding(const Encoding *encoding);

    /**
     * Returns true, if the user selected to reopen the dialog with the selected encoding.
     *
     * @return true, if the user selected to reopen the dialog with the selected encoding.
     */
    bool reopen() const;

    /**
     * Sets whether the reopen action should be enabled in the dialog or not.
     *
     * @param canReopen Should be set to true in order to enable the reopen action.
     */
    void setCanReopen(bool canReopen);

protected:
    /**
     * Overridden, in order to make sure that filter text is cleared when the dialog is shown.
     *
     * @param e The show event.
     */
    void showEvent(QShowEvent *e) override;

private slots:
    /**
     * Called when the text in the encoding filter edit has changed.
     *
     * @param text The new text.
     */
    void on_encodingFilter_textChanged(const QString &text);

    /**
     * Called when the selection in the list changes. If there is no selection, the select and reopen buttons are
     * disabled.
     *
     * @param selected The selected items.
     * @param deselected The deselected items.
     */
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

    /**
     * Called when the select button has been clicked.
     */
    void on_selectButton_clicked();

    /**
     * Called when the reopen button has been clicked.
     */
    void on_reopenButton_clicked();

    /**
     * Called when the cancel button has been clicked.
     */
    void on_cancelButton_clicked();

private:
    /** The dialog UI. */
    Ui::EncodingDialog *ui;

    /** The list model. */
    QStandardItemModel *m_model;

    /** The proxy model used for filtering of the list. */
    QSortFilterProxyModel *m_proxyModel;

    /** Is true if the reopen option should be available. */
    bool m_canReopen;

    /** true, if the user selected to reopen the dialog with the
     * selected encoding. */
    bool m_reopen;
};

#endif // ENCODINGDIALOG_H
