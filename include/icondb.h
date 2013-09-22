#ifndef ICONDB_H
#define ICONDB_H

#include <QIcon>
#include <QMap>

/**
 * A class that holds all the application icons.
 */
class IconDb {
public:
    /**
     * Enumeration of all the application icons.
     */
    enum Icon {
        Application, New, Open, Reopen, Save, SaveAs, Print, Close, Quit, Undo,
        Redo, Cut, Copy, Paste, Find, Replace, Fullscreen, ZoomIn, ZoomOut,
        ZoomReset, Font, About
    };

    /**
     * Returns an instance of the icon database.
     *
     * @return An instance of the icon database.
     */
    static IconDb* instance();

    /**
     * Returns an icon.
     *
     * @param icon The icon to get.
     * @return The icon.
     */
    QIcon getIcon(Icon icon);

private:
    /**
     * Private constructor to prevent instantiation.
     */
    IconDb();

    /**
     * Private copy constructor to prevent instantiation.
     */
    IconDb(const IconDb&);

    /**
     * Private equals operator to prevent instantiation.
     */
    IconDb& operator=(const IconDb&);

    /** The single static instance of this class. */
    static IconDb* iconDb;

    /** The map that stores the various icons. */
    QMap<Icon, QIcon> iconMap;
};

#endif // ICONDB_H
