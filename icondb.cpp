#include "icondb.h"

IconDb* IconDb::iconDb = 0;

IconDb* IconDb::instance() {
    if (!iconDb) {
        iconDb = new IconDb;
    }

    return iconDb;
}

QIcon IconDb::getIcon(Icon icon) {
    return iconMap[icon];
}

IconDb::IconDb() {
    QIcon icon = QIcon();
    icon.addFile(":/icons/icons/16x16/accessories-text-editor.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/accessories-text-editor.png", QSize(22, 22));
    icon.addFile(":/icons/icons/32x32/accessories-text-editor.png", QSize(32, 32));
    icon.addFile(":/icons/icons/48x48/accessories-text-editor.png", QSize(48, 48));
    icon.addFile(":/icons/icons/64x64/accessories-text-editor.png", QSize(64, 64));
    iconMap[Application] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/document-new.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/document-new.png", QSize(22, 22));
    iconMap[New] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/document-open.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/document-open.png", QSize(22, 22));
    iconMap[Open] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/view-refresh.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/view-refresh.png", QSize(22, 22));
    iconMap[Reopen] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/document-save.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/document-save.png", QSize(22, 22));
    iconMap[Save] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/document-save-as.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/document-save-as.png", QSize(22, 22));
    iconMap[SaveAs] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/document-print.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/document-print.png", QSize(22, 22));
    iconMap[Print] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/document-close.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/document-close.png", QSize(22, 22));
    iconMap[Close] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/application-exit.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/application-exit.png", QSize(22, 22));
    iconMap[Quit] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/edit-undo.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/edit-undo.png", QSize(22, 22));
    iconMap[Undo] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/edit-redo.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/edit-redo.png", QSize(22, 22));
    iconMap[Redo] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/edit-cut.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/edit-cut.png", QSize(22, 22));
    iconMap[Cut] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/edit-copy.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/edit-copy.png", QSize(22, 22));
    iconMap[Copy] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/edit-paste.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/edit-paste.png", QSize(22, 22));
    iconMap[Paste] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/edit-find.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/edit-find.png", QSize(22, 22));
    iconMap[Find] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/edit-find-replace.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/edit-find-replace.png", QSize(22, 22));
    iconMap[Replace] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/view-fullscreen.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/view-fullscreen.png", QSize(22, 22));
    iconMap[Fullscreen] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/zoom-in.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/zoom-in.png", QSize(22, 22));
    iconMap[ZoomIn] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/zoom-out.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/zoom-out.png", QSize(22, 22));
    iconMap[ZoomOut] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/zoom-original.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/zoom-original.png", QSize(22, 22));
    iconMap[ZoomReset] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/preferences-desktop-font.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/preferences-desktop-font.png", QSize(22, 22));
    iconMap[Font] = icon;

    icon = QIcon();
    icon.addFile(":/icons/icons/16x16/help-about.png", QSize(16, 16));
    icon.addFile(":/icons/icons/22x22/help-about.png", QSize(22, 22));
    iconMap[About] = icon;
}
