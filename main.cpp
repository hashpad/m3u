#include <QApplication>

#include "AppContext.h"
#include "ui/MainWindow.h"

const QString DATABASE_PATH = "db.sql";

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    AppContext ctx(DATABASE_PATH);

    MainWindow mainWindow(ctx);

    mainWindow.setWindowTitle("OTT Navigator");
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
