#include "buffer.h"
#include "util.h"

#include <QDebug>
#include <QDropEvent>
#include <QFontDatabase>
#include <QTextStream>
#include <QUrl>

#include <cmath>

Buffer::Buffer(QWidget *parent) :
        ScintillaEdit(parent), m_encoding("UTF-8") {
    // Use Unicode code page
    setCodePage(SC_CP_UTF8);
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
    // Set up identation
    setTabWidth(4);
    setUseTabs(false);
    setIndent(4);
    setIndentationGuides(SC_IV_LOOKBOTH);
    // Set long line indicator
    setEdgeMode(EDGE_LINE);
    setEdgeColumn(80);

    // Setup the margins
    setShowLineNumbers(true);
    setMarginWidthN(1, 0);

    connect(this, SIGNAL(linesAdded(int)), this, SLOT(onLinesAdded(int)));
}

Buffer::~Buffer() {

}

void Buffer::clear() {
    // Clear the file name and the editor
    clearAll();
    setFileInfo(QFileInfo(""));
    setSavePoint();
}

bool Buffer::open(const QString &fileName) {
    // Open the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QTextStream input(&file);
    input.setCodec(m_encoding);
    QString content = input.readAll();
    setText(content.toUtf8());
    file.close();

    // File saved succesfully
    setFileInfo(QFileInfo(fileName));
    emptyUndoBuffer();
    setSavePoint();

    return true;
}

bool Buffer::save(const QString &fileName) {
    // Save the file
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    // Save the text to a file.
    QTextStream output(&file);
    QByteArray content = getText(textLength() + 1);
    output.setCodec(m_encoding);
    output << QString::fromUtf8(content);
    output.flush();
    file.close();

    // File saved
    setFileInfo(QFileInfo(fileName));
    setSavePoint();

    return true;
}

QFileInfo Buffer::fileInfo() const {
    return m_fileInfo;
}

QByteArray Buffer::encoding() const {
    return m_encoding;
}

void Buffer::setEncoding(const QByteArray& encoding) {
    if (m_encoding != encoding) {
        m_encoding = encoding;
        emit encodingChanged(encoding);
    }
}

bool Buffer::showLineNumbers() {
    return marginWidthN(0) != 0;
}

void Buffer::setShowLineNumbers(bool show) {
    if (show) {
        int width = ((int) std::log10(lineCount())) + 1;
        QString text;
        text.fill('9', width).prepend('_');
        setMarginWidthN(0, textWidth(STYLE_LINENUMBER, text.toLatin1()));
    } else {
        setMarginWidthN(0, 0);
    }
}

bool Buffer::find(const QString& findText, int flags, bool forward,
                  bool wrap, bool *searchWrapped) {
    if (findText.isEmpty()) {
        return false;
    }
    *searchWrapped = false;
    // Perform the search
    setSearchFlags(flags);
    setTargetStart(forward ? currentPos() : currentPos() - 1);
    setTargetEnd(forward ? length() : 0);
    QByteArray findArray = findText.toUtf8();
    int findPos = searchInTarget(findArray.length(), findArray);
    // If the search should wrap, perform the search again.
    if (findPos == -1 && wrap) {
        setTargetStart(forward ? 0 : length());
        setTargetEnd(forward ? currentPos() : currentPos() - 1);
        findPos = searchInTarget(findArray.length(), findArray);
        if (searchWrapped != NULL) {
            *searchWrapped = true;
        }
    }
    if (findPos != -1)  {
        setSel(targetStart(), targetEnd());
        scrollRange(targetStart(), targetEnd());
    }
    return findPos != -1;
}

void Buffer::onLinesAdded(int) {
    if (showLineNumbers()) {
        setShowLineNumbers(true);
    }
}

void Buffer::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasUrls()) {
        // If the user is dropping URLs, emit a signal
        QList<QUrl> urls = event->mimeData()->urls();
        emit urlsDropped(urls);
    } else {
        // Do the default action
        ScintillaEditBase::dropEvent(event);
    }
 }

void Buffer::setFileInfo(const QFileInfo& fileInfo) {
    if (m_fileInfo != fileInfo) {
        m_fileInfo = fileInfo;
        emit fileInfoChanged(fileInfo);
    }
}
