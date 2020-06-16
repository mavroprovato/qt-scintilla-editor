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

    QApplication::setOrganizationName(ORGANIZATION_NAME);
    QApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QApplication::setApplicationName(APPLICATION_NAME);
    QApplication::setApplicationVersion(APPLICATION_VERSION);

    // Open file names provided as command line arguments
    if (argc == 1) {
        auto *w = new QScintillaEditor;
        w->show();
    } else {
        for (int i = 1; i < argc; i++) {
            auto *w = new QScintillaEditor;
            w->show();
            w->openFile(argv[i]);
        }
    }

    // Exiting, clean-up static resources
    int exitCode = QApplication::exec();
    Encoding::cleanup();
    Language::cleanup();
    ColorScheme::cleanup();

    return exitCode;
}
