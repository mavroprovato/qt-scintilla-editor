#ifndef BUFFER_H
#define BUFFER_H

#include <ScintillaEdit.h>

#include <QFileInfo>
#include <QWidget>

class Buffer : public ScintillaEdit
{
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

signals:

public slots:

private:
    /** Contains the file information, if the file has been set. */
    QFileInfo fileInfo;
};

#endif // BUFFER_H
