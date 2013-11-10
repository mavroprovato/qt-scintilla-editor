#include "buffer.h"
#include "configuration.h"
#include "icondb.h"
#include "language.h"
#include "util.h"

#include <SciLexer.h>

#include <QBuffer>
#include <QDebug>
#include <QDropEvent>
#include <QFontDatabase>
#include <QTextStream>
#include <QUrl>

#include <algorithm>
#include <cmath>

Buffer::Buffer(QWidget *parent) :
        ScintillaEdit(parent), m_language(0) {
    // Use Unicode code page
    m_encoding = Encoding::fromName("UTF-8");
    setCodePage(SC_CP_UTF8);

    // Load the initial state from the configuration
    loadConfiguration();

    // Setup the margins
    setMarginMaskN(Fold, SC_MASK_FOLDERS);
    setMarginSensitiveN(Icon, true);
    setMarginSensitiveN(Fold, true);
    setupMarginIcons();

    connect(this, SIGNAL(linesAdded(int)), this, SLOT(onLinesAdded(int)));
    connect(this, SIGNAL(marginClicked(int,int,int)), this,
            SLOT(onMarginClicked(int,int,int)));
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
    input.setCodec(m_encoding->name());
    QString content = input.readAll();
    setText(content.toUtf8());
    file.close();

    // File opened succesfully
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
    output.setCodec(m_encoding->name());
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

const Encoding *Buffer::encoding() const {
    return m_encoding;
}

void Buffer::setEncoding(const Encoding *encoding) {
    if (m_encoding != encoding) {
        m_encoding = encoding;
        emit encodingChanged(encoding);
    }
}

bool Buffer::viewWhitespace() const {
    return viewWS() != SCWS_INVISIBLE;
}

void Buffer::setViewWhitespace(bool viewWhitespace) {
    if (viewWhitespace) {
        Configuration *configuration = Configuration::instance();
        if (configuration->viewIndentationWhitespace()) {
            setViewWS(SCWS_VISIBLEALWAYS);
        } else {
            setViewWS(SCWS_VISIBLEAFTERINDENT);
        }
    } else {
        setViewWS(SCWS_INVISIBLE);
    }
}

bool Buffer::viewIndentationGuides() const {
    return indentationGuides() != SC_IV_NONE;
}

void Buffer::setViewIndentationGuides(bool viewIndentationGuides) {
    if (viewIndentationGuides) {
        setIndentationGuides(
                Configuration::instance()->indentationGuidesMode());
    } else {
        setIndentationGuides(SC_IV_NONE);
    }
}

bool Buffer::longLineIndicator() const {
    return edgeMode() != EDGE_NONE;
}

void Buffer::setLongLineIndicator(bool longLineIndicator) {
    Configuration *config = Configuration::instance();
    if (longLineIndicator) {
        if (config->longLineIndicatorLine()) {
            setEdgeMode(EDGE_LINE);
            setEdgeColumn(config->longLineIndicatorColumn());
        } else {
            setEdgeMode(EDGE_BACKGROUND);
        }
    } else {
        setEdgeMode(EDGE_NONE);
    }
}

bool Buffer::showLineNumbers() const {
    return marginWidthN(Line) != 0;
}

void Buffer::setShowLineNumbers(bool showLineNumbers) {
    setMarginWidthN(Line, showLineNumbers ? getLineMarginWidth() : 0);
}

bool Buffer::showIconMargin() const {
    return marginWidthN(Icon) != 0;
}

void Buffer::setShowIconMargin(bool showIconMargin) {
    setMarginWidthN(Icon, showIconMargin ? 16 : 0);
}

bool Buffer::showFoldMargin() const {
    return marginWidthN(Fold) != 0;
}

void Buffer::setShowFoldMargin(bool showFoldMargin) {
    setMarginWidthN(Fold, showFoldMargin ? 16 : 0);
}

void Buffer::setFoldSymbols(Buffer::FoldSymbols foldSymbols) {
    switch(foldSymbols) {
    case Arrows:
        markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_ARROWDOWN);
        markerDefine(SC_MARKNUM_FOLDER, SC_MARK_ARROW);
        markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_ARROWDOWN);
        markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_ARROW);
        break;
    case PlusMinus:
        markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
        markerDefine(SC_MARKNUM_FOLDER, SC_MARK_PLUS);
        markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_MINUS);
        markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_PLUS);
        break;
    case CirclePlusMinus:
        markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_CIRCLEMINUS);
        markerDefine(SC_MARKNUM_FOLDER, SC_MARK_CIRCLEPLUS);
        markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_CIRCLEMINUSCONNECTED);
        markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_CIRCLEPLUSCONNECTED);
        break;
    case BoxPlusMinus:
        markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS);
        markerDefine(SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS);
        markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED);
        markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED);
        break;
    }
}

void Buffer::setFoldLines(FoldLines foldLines) {
    switch(foldLines) {
    case None:
        markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
        markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
        markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
        break;
    case CircleLine:
        markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
        markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNERCURVE);
        markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNERCURVE);
        break;
    case BoxLine:
        markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
        markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER);
        markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER);
        break;
    }
}

QFont Buffer::styleQFont(int style) const {
    QFont font(styleFont(style), styleSize(style),
            styleBold(style) ? QFont::Bold :QFont::Normal, styleItalic(style));
    return font;
}

void Buffer::setStyleQFont(int style, const QFont& font) {
    styleSetFont(style, font.family().toLatin1());
    styleSetSize(style, font.pointSize());
    styleSetBold(style, font.bold());
    styleSetItalic(style, font.italic());
}

bool Buffer::find(const QString& findText, int flags, bool forward,
                  bool wrap, bool *searchWrapped) {
    if (findText.isEmpty()) {
        return false;
    }
    if (searchWrapped) {
        *searchWrapped = false;
    }
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
        if (searchWrapped) {
            *searchWrapped = true;
        }
    }
    if (findPos != -1)  {
        setSel(targetStart(), targetEnd());
        scrollRange(targetStart(), targetEnd());
    }
    return findPos != -1;
}

void Buffer::toggleBookmark(int line) {
    if (line < 0) {
        line = lineFromPosition(currentPos());
    }
    if (markerGet(line) & (1 << Bookmark)) {
        markerDelete(line, Bookmark);
    } else {
        markerAdd(line, Bookmark);
    }
}

void Buffer::gotoBookmark(bool next) {
    // Try to find the bookmark, from the next/previous line
    int line = lineFromPosition(currentPos());
    int markerLine = -1;
    if (next) {
        line = (line == lineCount()) ? 0 : line + 1;
        markerLine = markerNext(line, 1 << Bookmark);
    } else {
        line = (line == 0 ? lineCount() : line - 1);
        markerLine = markerPrevious(line, 1 << Bookmark);
    }

     // Wrap search if a bookmark was not found.
    if (markerLine == -1) {
        if (next) {
            markerLine = markerNext(0, 1 << Buffer::Bookmark);
        } else {
            markerLine = markerPrevious(lineCount(), 1 << Buffer::Bookmark);
        }
    }

    // If the marker was found, go to the line.
    if (markerLine != -1) {
        gotoLine(markerLine);
    }
}


void Buffer::onLinesAdded(int) {
    if (showLineNumbers()) {
        setMarginWidthN(Line, getLineMarginWidth());
    }
}

void Buffer::onMarginClicked(int position, int, int margin) {
    if (margin == Fold) {
        toggleFold(lineFromPosition(position));
    } else if (margin == Icon) {
        toggleBookmark(lineFromPosition(position));
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

void Buffer::loadConfiguration() {
    Configuration *config = Configuration::instance();
    setStyleQFont(STYLE_DEFAULT, config->font());
    setViewWhitespace(config->viewWhitespace());
    setViewIndentationGuides(config->viewIndentationGuides());
    setCaretLineVisible(config->caretLineVisible());
    setLongLineIndicator(config->longLineIndicator());
    setViewEOL(config->viewEndOfLine());
    setShowLineNumbers(config->showLineMargin());
    setShowIconMargin(config->showIconMargin());
    setShowFoldMargin(config->showFoldMargin());
    setTabWidth(config->tabWidth());
    setIndent(config->indentationWidth());
    setUseTabs(config->useTabs());
    setScrollWidth(config->scrollWidth());
    setScrollWidthTracking(config->scrollWidthTracking());
    setFoldSymbols(config->foldSymbols());
    setFoldLines(config->foldLines());
    applyColorScheme(ColorScheme::getColorScheme(config->colorScheme()));
}

void Buffer::setFileInfo(const QFileInfo& fileInfo) {
    if (m_fileInfo != fileInfo) {
        m_fileInfo = fileInfo;
        // Set up the lexer for the buffer
        setLanguage(Language::fromFilename(m_fileInfo.fileName()));
        emit fileInfoChanged(fileInfo);
    }
}

const Language *Buffer::language() const {
    return m_language;
}

void Buffer::setLanguage(const Language *language) {
    if (m_language != language) {
        // Set all styles to default
        styleClearAll();
        // Find the language from the filename
        if (language) {
            setLexerLanguage(language->lexer().toLocal8Bit());
            for (int i = 0; i < language->keywords().size(); ++i) {
                setKeyWords(i, language->keywords().at(i).toLatin1());
            }
            setProperty("fold", "1");
            setProperty("fold.compact", "0");
        } else {
            setLexer(SCLEX_NULL);
            setKeyWords(0, "");
            setProperty("fold", "0");
        }

        m_language = language;
        emit languageChanged(language);
    }
}

int Buffer::getLineMarginWidth() {
    int width = ((int) std::log10(lineCount())) + 1;
    QString text;
    text.fill('9', width).prepend('_');

    return textWidth(STYLE_LINENUMBER, text.toLatin1());
}

void Buffer::setupMarginIcons() {
    QIcon bookmarkIcon = IconDb::instance()->getIcon(IconDb::Bookmark);
    QImage image = bookmarkIcon.pixmap(16).toImage();
    int dim = std::min(textHeight(0), marginWidthN(Icon));
    image = image.scaled(dim, dim);
    rGBAImageSetWidth(dim);
    rGBAImageSetHeight(dim);
    markerDefineRGBAImage(Bookmark, reinterpret_cast<const char*>(
            image.rgbSwapped().bits()));
}

void Buffer::applyColorScheme(ColorScheme *colorScheme) {
    if (colorScheme->foreground() != -1) {
        styleSetFore(STYLE_DEFAULT, colorScheme->foreground());
    }
    if (colorScheme->background() != -1) {
        styleSetBack(STYLE_DEFAULT, colorScheme->background());
    }
    if (colorScheme->caret() != -1) {
        setCaretFore(colorScheme->caret());
    }
    if (colorScheme->caretLine() != -1) {
        setCaretLineBack(colorScheme->caretLine());
    }
    if (colorScheme->selection() == -1) {
        setSelBack(false, 0);
    } else {
        setSelBack(true, colorScheme->selection());
    }
}

void Buffer::applyStyle(int styleNumber, const StyleInfo& style) {
    if (style.foregroundColor() >= 0) {
        styleSetFore(styleNumber, style.foregroundColor());
    }
    if (style.backgroundColor() >=0) {
        styleSetBack(styleNumber, style.backgroundColor());
    }
    styleSetBold(styleNumber, style.bold());
    styleSetItalic(styleNumber, style.italic());
    styleSetUnderline(styleNumber, style.underline());
    styleSetEOLFilled(styleNumber, style.eolFilled());
}
