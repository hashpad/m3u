#pragma once
#include <qtmetamacros.h>

#include <QMainWindow>

struct AppContext;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(AppContext &ctx, QWidget *parent = nullptr);
    ~MainWindow() override;
   private slots:
    void on_SettingsButton_clicked();
    void on_LiveStreamButton_clicked();
    void on_MainBackButton_clicked();

   private:
    Ui::MainWindow *ui;
    AppContext &ctx;
};
