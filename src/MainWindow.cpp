#include "MainWindow.h"

#include "SettingsDialog.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}
void MainWindow::on_SettingsButton_clicked() {
    SettingsDialog dlg(this);
    dlg.exec();
}
MainWindow::~MainWindow() { delete ui; }
