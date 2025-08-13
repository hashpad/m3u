#pragma once
#include <qtmetamacros.h>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
   private slots:
    void on_SettingsButton_clicked();

   private:
    Ui::MainWindow *ui;
};
