#include "buffer.h"
#include "util.h"

#include <QFontDatabase>
#include <QTextStream>

Buffer::Buffer(QWidget *parent) :
        ScintillaEdit(parent) {
    // Use Unicode code page
    setCodePage(SC_CP_UTF8);
    // Do not display any margin
    setMarginWidthN(1, 0);
    // Track the scroll width
    setScrollWidth(1);
    setScrollWidthTracking(true);
    // Set a monospaced font
    QFontDatabase fontDb;
#ifdef Q_OS_WIN
    if (fontDb.families(QFontDatabase::Any).contains("Consolas")) {
        styleSetFont(STYLE_DEFAULT, "Consolas");
    } else {
        styleSetFont(STYLE_DEFAULT, "Courier New");
    }
#elif Q_OS_MAC
    if (fontDb.families(QFontDatabase::Any).contains("Menlo")) {
        styleSetFont(STYLE_DEFAULT, "Menlo");
    } else {
        styleSetFont(STYLE_DEFAULT, "Monaco");
    }
#else
    styleSetFont(STYLE_DEFAULT, "Monospace");
#endif
    // Set font size.
    styleSetSize(STYLE_DEFAULT, 10);
    // View whitespace
    setViewWS(SCWS_VISIBLEALWAYS);
    setWhitespaceFore(true, convertColor(Qt::lightGray));
}

Buffer::~Buffer() {

}

void Buffer::clear() {
    // Clear the file name and the editor
    clearAll();
    setSavePoint();
    fileInfo.setFile("");
}

bool Buffer::open(const QString &fileName) {
    // Open the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    setText(content.toUtf8());
    file.close();

    // File saved succesfully
    setSavePoint();
    fileInfo.setFile(fileName);

    return true;
}

bool Buffer::save(const QString &fileName) {
    // Save the file
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    // Save the text to a file.
    QTextStream stream(&file);
    QByteArray content = getText(textLength() + 1);
    stream << QString::fromUtf8(content);
    stream.flush();
    file.close();

    // File saved
    setSavePoint();
    fileInfo.setFile(fileName);

    return true;
}

QString Buffer::displayName() {
    return fileInfo.fileName().isNull() ? tr("Untitled") : fileInfo.fileName();
}

QString Buffer::filePath() {
    return fileInfo.filePath();
}
