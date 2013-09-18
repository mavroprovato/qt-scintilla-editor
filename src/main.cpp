#include "qscintillaeditor.h"
#include "version.h"

#include <QApplication>

/**
 * The application entry point.
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

    // Check the command line arguments
    bool fileOpened = false;
    for (int i = 1; i < argc; i++) {
        QScintillaEditor *w = new QScintillaEditor;
        w->show();
        w->openFile(argv[i]);
        fileOpened = true;
    }

    // If no window has been opened, open one.
    if (!fileOpened) {
        QScintillaEditor *w = new QScintillaEditor;
        w->show();
    }

    return a.exec();
}
