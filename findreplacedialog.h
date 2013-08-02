#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class FindReplaceDialog;
}

class FindReplaceDialog : public QDialog
{
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

    /**
     * Returns the text to find.
     *
     * @return The text to find.
     */
    QString findText() const;

    /**
     * Returns the text to replace the matched text with.
     *
     * @return The text to replace the matched text with.
     */
    QString replaceText() const;

    /**
     * Returns true if the search should be performed towards the end of the
     * document.
     *
     * @return true if the search should be performed towards the end of the
     * document.
     */
    bool directionForward() const;

    /**
     * Returns true if the search should be case sensitive.
     *
     * @return  true if the search should be case sensitive.
     */
    bool matchCase() const;

    /**
     * Retruns true if the whole word should be matched.
     *
     * @return true if the whole word should be matched.
     */
    bool wholeWord() const;

    /**
     * Returns true if the search string should be considered as a regular
     * expression.
     *
     * @return true if the search string should be considered as a regular
     * expression.
     */
    bool regularExpression() const;

    /**
     * Returns true if the search should wrap around the start or the end of the
     * document.
     *
     * @return true if the search should wrap around the start or the end of the
     * document.
     */
    bool wrapSearch() const;

signals:
    /**
     * This signal is emitted when the find button is pressed.
     */
    void findPressed();

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
