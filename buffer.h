#ifndef BUFFER_H
#define BUFFER_H

#include <ScintillaEdit.h>

#include <QFileInfo>
#include <QWidget>

class Buffer : public ScintillaEdit {
    Q_OBJECT
public:
    explicit Buffer(QWidget *parent = 0);

    /**
     * Destructor for the buffer.
     */
    virtual ~Buffer();

    /**
     * Clears the contents of the editor.
     */
    void clear();

    /**
     * Reads the contents of a file into the buffer.
     *
     * @param fileName The name of the file.
     * @return true, if the file has been opened successfully.
     */
    bool open(const QString& fileName);

    /**
     * Saves the contents of the buffer to a file.
     *
     * @param fileName The name of the file to save the contents.
     * @return true, if the file has been saved successfully.
     */
    bool save(const QString& fileName);

    /**
     * Returns the path of the file.
     *
     * @return The path of the file, or a null string if the buffer has not been
     * saved yet.
     */
    QFileInfo getFileInfo();

    /**
     * Finds the occurance of the provided text and selects the match.
     *
     * @param findText The text to find.
     * @param flags The search flags.
     * @param forward If true, perform the search with forward direction.
     * @param wrap If true, wrap the search.
     * @param searchWrapped Input parameter, which is set to true if the search
     * is wrapped.
     * @return true if a match was found.
     */
    bool find(const QString& findText, int flags, bool forward, bool wrap,
        bool *searchWrapped);

    /**
     * Returns true if the line numbers are shown.
     *
     * @return true if the line numbers are shown.
     */
    bool showLineNumbers();

    /**
     * Shows or hides the line numbers.
     *
     * @param show if true, show the line numbers.
     */
    void setShowLineNumbers(bool show);
signals:

public slots:

    /**
     * Called when lines are added to the buffer.
     *
     * @param linesAdded The number of lines added.
     */
    void onLinesAdded(int linesAdded);

private:
    /** Contains the file information, if the file has been set. */
    QFileInfo fileInfo;
};

#endif // BUFFER_H
