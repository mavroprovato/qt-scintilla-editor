#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class FindReplaceDialog;
}

class FindReplaceDialog : public QDialog {
    Q_OBJECT
    
public:
    /**
     * Enumeration for the dialog type, either a find or a find/replace
     * dialog.
     */
    enum Type {
        Find = 0,
        FindReplace = 1
    };

    /**
     * Constructor for the dialog.
     *
     * @param parent The parent widget.
     */
    explicit FindReplaceDialog(QWidget *parent = 0);

    /**
     * Destructor for the dialog.
     */
    ~FindReplaceDialog();

    /**
     * Sets the type for the dialog.
     *
     * @param type The dialog type.
     */
    void setType(Type type);

signals:
    /**
     * This signal is emitted when the find button is pressed.
     *
     * @param findText The text to search for.
     * @param flags The search flags.
     * @param forward true if the search must be performed towards the end of
     * the document.
     * @param wrap true if the search should wrap.
     */
    void find(const QString& findText, int flags, bool forward, bool wrap);

protected:

    /**
     * Overriden, in order to make sure that the find line edit always takes
     * focus when the dialog is shown.
     *
     * @param e The show event.
     */
    virtual void showEvent(QShowEvent *e);

private slots:
    /**
     * Called when the find button is clicked.
     */
    void on_findPushButton_clicked();

    /**
     * Called when the cancel button is clicked.
     */
    void on_cancelButton_clicked();

private:
    Ui::FindReplaceDialog *ui;
};

#endif // FINDREPLACEDIALOG_H
