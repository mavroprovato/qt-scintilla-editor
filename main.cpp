#include "qscintillaeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScintillaEditor w;
    w.show();
    
    return a.exec();
}
