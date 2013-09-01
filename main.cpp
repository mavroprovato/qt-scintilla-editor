#include "qscintillaeditor.h"
#include "version.h"

#include <QApplication>

/**
 * The main application version.
 *
 * @param argc The argument count.
 * @param argv The arguments.
 * @return The exit code.
 */
int main(int argc, char *argv[]) {
    // Initialize the application
    QApplication a(argc, argv);
    a.setApplicationName(APPLICATION_NAME);
    a.setApplicationVersion(APPLICATION_VERSION);

    // Create and show the main window.
    QScintillaEditor w;
    w.show();
    
    return a.exec();
}
