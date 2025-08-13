#include "ui/MainWindow.h"

#include <qmainwindow.h>
#include <qwidget.h>

#include "ui/MainWindow.h"
#include "ui/SettingsDialog.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(AppContext& ctx, QWidget* parent)
    : QMainWindow(parent), ctx(ctx), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}
MainWindow::~MainWindow() { delete ui; }
void MainWindow::on_SettingsButton_clicked() {
    SettingsDialog dlg(ctx, this);
    dlg.exec();
}
void MainWindow::on_LiveStreamButton_clicked() {
    ui->MainStackedWidget->setCurrentWidget(ui->LiveStreamPage);
}
void MainWindow::on_MainBackButton_clicked() {
    ui->MainStackedWidget->setCurrentWidget(ui->MainPage);
}
