#pragma once

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}
class SettingsDialog : public QDialog {
    Q_OBJECT

   public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() override;

   private:
    Ui::SettingsDialog *ui;
    QSettings settings;

    void updateProvidersList();

   private slots:
    void on_SettingsList_clicked();
    void on_BackButton_clicked();
    void on_AddProviderButton_clicked();
};
