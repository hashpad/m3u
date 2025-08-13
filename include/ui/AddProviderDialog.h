#pragma once

#include <QDialog>
namespace Ui {
class AddProviderDialog;
}
class AddProviderDialog : public QDialog {
    Q_OBJECT

   public:
    explicit AddProviderDialog(QWidget *parent = nullptr);
    ~AddProviderDialog() override;
    QString getUrl() const;
    bool isActive() const;

   private:
    Ui::AddProviderDialog *ui;
    private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};
