#include "configuration.h"

#include <QColor>
#include <QDebug>
#include <QFont>

Configuration* Configuration::instance() {
    static Configuration configuration;

    return &configuration;
}

Configuration::Configuration() {
}

bool Configuration::showToolBar() {
    return settings.value("toolbar.visible", "true").toBool();
}

void Configuration::setShowToolBar(bool showToolBar) {
    settings.setValue("toolbar.visible", showToolBar);
}

bool Configuration::showStatusBar() {
    return settings.value("statusbar.visible", true).toBool();
}

void Configuration::setShowStatusBar(bool showStatusBar) {
    settings.setValue("statusbar.visible", showStatusBar);
}

bool Configuration::fullscreen() {
    return settings.value("full.screen", false).toBool();
}

void Configuration::setFullscreen(bool fullscreen) {
    settings.setValue("full.screen", fullscreen);
}

bool Configuration::viewWhitespace() {
    return settings.value("view.whitespace", true).toBool();
}

void Configuration::setViewWhitespace(bool viewWhitespace) {
    settings.setValue("view.whitespace", viewWhitespace);
}

bool Configuration::viewIndentationWhitespace() {
    return settings.value("view.indentation.whitespace", true).toBool();
}

void Configuration::setViewIndentationWhitespace(
        bool viewIndentationWhitespace) {
    settings.setValue("view.indentation.whitespace", viewIndentationWhitespace);
}

bool Configuration::viewIndentationGuides() {
    return settings.value("view.indentation.guides", true).toBool();
}

void Configuration::setViewIndentationGuides(bool viewIndentationGuides) {
    settings.setValue("view.indentation.guides", viewIndentationGuides);
}

Configuration::IndentationGuidesMode Configuration::indentationGuidesMode() {
    int examine = settings.value("view.indentation.examine", LookBoth).toInt();
    switch(examine) {
    case 1:
        return Real;
    case 2:
        return LookForward;
    case 3:
        return LookBoth;
    default:
        return None;
    }
}

void Configuration::setIndentationGuidesMode(Configuration::IndentationGuidesMode mode) {
    settings.setValue("view.indentation.examine", mode);
}

bool Configuration::longLineIndicator() {
    return settings.value("long.line.indicator", true).toBool();
}

void Configuration::setLongLineIndicator(bool longLineIndicator) {
    settings.setValue("long.line.indicator", longLineIndicator);
}

bool Configuration::longLineIndicatorLine() {
    return settings.value("long.line.indicator.line", true).toBool();
}

void Configuration::setLongLineIndicatorLine(bool longLineIndicatorLine) {
    settings.setValue("long.line.indicator.line", longLineIndicatorLine);
}

int Configuration::longLineIndicatorColumn() {
    return settings.value("long.line.indicator.column", 80).toInt();
}

void Configuration::setLongLineIndicatorColumn(int longLineIndicatorColumn) {
    settings.setValue("long.line.indicator.column", longLineIndicatorColumn);
}

bool Configuration::viewEndOfLine() {
    return settings.value("view.eol", false).toBool();
}

void Configuration::setViewEndOfLine(bool endOfLine) {
    settings.setValue("view.eol", endOfLine);
}

bool Configuration::showLineMargin() {
    return settings.value("line.margin.visible", true).toBool();
}

void Configuration::setShowLineMargin(bool showLineMargin) {
    settings.setValue("line.margin.visible", showLineMargin);
}

bool Configuration::showIconMargin() {
    return settings.value("margin", false).toBool();
}

void Configuration::setShowIconMargin(bool showIconMargin) {
    settings.setValue("margin", showIconMargin);
}

bool Configuration::showFoldMargin() {
    return settings.value("fold", true).toBool();
}

void Configuration::setShowFoldMargin(bool showFoldMargin) {
    settings.setValue("fold", showFoldMargin);
}

Buffer::FoldSymbols Configuration::foldSymbols() {
    int value = settings.value("fold.symbols", Buffer::Arrows).toInt();
    switch (value) {
    case 0:
        return Buffer::Arrows;
    case 1:
        return Buffer::PlusMinus;
    case 2:
        return Buffer::CirclePlusMinus;
    case 3:
        return Buffer::BoxPlusMinus;
    default:
        return Buffer::Arrows;
    }
}

void Configuration::setFoldSymbols(Buffer::FoldSymbols foldSymbols) {
    settings.setValue("fold.symbols", foldSymbols);
}

Buffer::FoldLines Configuration::foldLines() {
    int value = settings.value("fold.lines", Buffer::BoxLine).toInt();
    switch (value) {
    case 0:
        return Buffer::None;
    case 1:
        return Buffer::CircleLine;
    case 2:
        return Buffer::BoxLine;
    default:
        return Buffer::BoxLine;
    }
}

void Configuration::setFoldLines(Buffer::FoldLines foldLines) {
    settings.setValue("fold.lines", foldLines);
}

bool Configuration::wrap() {
    return settings.value("wrap", false).toBool();
}

void Configuration::setWrap(bool wrap) {
    settings.setValue("wrap", wrap);
}

int Configuration::tabWidth() const {
    return settings.value("tab.size", 4).toInt();
}

void Configuration::setTabWidth(int tabWidth) {
    settings.setValue("tab.size", tabWidth);
}

int Configuration::indentationWidth() const {
    return settings.value("indent.size", 4).toInt();
}

void Configuration::setIndentationWidth(int indentationWidth) {
    settings.setValue("indent.size", indentationWidth);
}

bool Configuration::useTabs() const {
    return settings.value("use.tabs", false).toBool();
}

void Configuration::setUseTabs(bool useTabs) {
    settings.setValue("use.tabs", useTabs);
}

int Configuration::scrollWidth() const {
    return settings.value("horizontal.scroll.width", 1).toInt();
}

void Configuration::setScrollWidth(int scrollWidth) {
    settings.setValue("horizontal.scroll.width", scrollWidth);
}

bool Configuration::scrollWidthTracking() const {
    return settings.value("horizontal.scroll.width.tracking", true).toBool();
}

void Configuration::setScrollWidthTracking(bool scrollWidthTracking) {
    settings.setValue("horizontal.scroll.width.tracking", scrollWidthTracking);
}

QFont Configuration::font() const {
    if (settings.contains("font.default")) {
        QFont font;
        font.fromString(settings.value("font.default").toString());
        return font;
    } else {
        QString family;
#ifdef Q_OS_WIN
        QFontDatabase fontDb;
        if (fontDb.families(QFontDatabase::Any).contains("Consolas")) {
            family = "Consolas";
        } else {
            family = "Courier New";
        }
#elif Q_OS_MAC
        QFontDatabase fontDb;
        if (fontDb.families(QFontDatabase::Any).contains("Menlo")) {
            family = "Menlo";
        } else {
            family = "Monaco";
        }
#else
        family = "Monospace";
#endif
        return QFont(family, 10);
    }
}

void Configuration::setFont(const QFont &font) {
    settings.setValue("font.default", font.toString());
}

QColor Configuration::whitespaceForeground() const {
    return QColor(settings.value("whitespace.fore", "#c0c0c0").toString());
}

void Configuration::setWhitespaceForeground(const QColor& whitespaceForeground) {
    settings.setValue("whitespace.fore", whitespaceForeground.name());
}

QColor Configuration::whitespaceBackground() const {
    return QColor(settings.value("whitespace.back", "#ffffff").toString());
}

void Configuration::setWhitespaceBackground(const QColor& whitespaceBackground) {
    settings.setValue("whitespace.back", whitespaceBackground.name());
}

QHash<int, StyleInfo> Configuration::styleForLanguage(const Language& language) {
    QHash<int, StyleInfo> styles;
    for (int i = 0; i < language.styles().length(); ++i) {
        int style = language.styles().at(i).style;
        QString key = QString("style.%1.%2").arg(language.langId()).arg(style);
        StyleInfo info = StyleInfo::fromString(settings.value(key, "").toString());
        styles[style] = info;
    }
    return styles;
}
