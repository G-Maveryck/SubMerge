#include "SM_MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SM_MainWindow MainWindow;
    MainWindow.show();

    return app.exec();
}
