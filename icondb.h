#ifndef ICONDB_H
#define ICONDB_H

#include <QIcon>
#include <QMap>

class IconDb
{
public:
    enum Icon {
        Application, New, Open, Save, SaveAs, Print, Close, Undo, Redo, Cut,
        Copy, Paste, Find, Replace, Fullscreen, ZoomIn, ZoomOut, ZoomReset,
        Font, About
    };
    static IconDb* instance();

    QIcon getIcon(Icon icon);

private:
    IconDb();

    IconDb(const IconDb&);
    IconDb& operator=(const IconDb&);

    static IconDb* iconDb;
    QMap<Icon, QIcon> iconMap;
};

#endif // ICONDB_H
