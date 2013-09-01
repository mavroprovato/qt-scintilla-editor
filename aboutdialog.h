#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

/**
 * Class for the About dialog.
 */
class AboutDialog : public QDialog {
    Q_OBJECT
    
public:
    /**
     * Creates the About dialog.
     *
     * @param parent The dialog parent.
     */
    explicit AboutDialog(QWidget *parent = 0);

    /**
     * Destructor for the dialog.
     */
    ~AboutDialog();
    
private slots:
    void on_pushButtonClose_clicked();

private:
    /** The dialog UI. */
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
