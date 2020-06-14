#include "qscintillaeditor.h"

#include "colorscheme.h"
#include "encoding.h"
#include "language.h"
#include "version.h"

#include <QApplication>
#include <QDebug>

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

    a.setOrganizationName(ORGANIZATION_NAME);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);
    a.setApplicationName(APPLICATION_NAME);
    a.setApplicationVersion(APPLICATION_VERSION);

    // Open file names provided as command line arguments
    if (argc == 1) {
        QScintillaEditor *w = new QScintillaEditor;
        w->show();
    } else {
        for (int i = 1; i < argc; i++) {
            QScintillaEditor *w = new QScintillaEditor;
            w->show();
            w->openFile(argv[i]);
        }
    }

    // Exiting, clean-up static resources
    int exitCode = a.exec();
    Encoding::cleanup();
    Language::cleanup();
    ColorScheme::cleanup();

    return exitCode;
}
