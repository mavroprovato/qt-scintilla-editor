#include "qscintillaeditor.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName("Editor");
    QScintillaEditor w;
    w.show();
    
    return a.exec();
}
