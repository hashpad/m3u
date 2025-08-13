#pragma once

#include <qwidget.h>

#include <QDialog>
#include <QSettings>

#include "ui/MainWindow.h"

namespace Ui {
class SettingsDialog;
}
class SettingsDialog : public QDialog {
    Q_OBJECT

   public:
    explicit SettingsDialog(AppContext &ctx, QWidget *parent = nullptr);
    ~SettingsDialog() override;

   private:
    Ui::SettingsDialog *ui;
    QSettings settings;
    AppContext &ctx;

    void updateProvidersList();

   private slots:
    void on_SettingsList_clicked();
    void on_BackButton_clicked();
    void on_AddProviderButton_clicked();
};
