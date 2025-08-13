#include "SettingsDialog.h"
#include "m3u/M3UUtils.h"

#include <QMessageBox>
#include <QSettings>

#include "AddProviderDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsDialog), settings("m3u") {
    ui->setupUi(this);
}
SettingsDialog::~SettingsDialog() { delete ui; }

void SettingsDialog::updateProvidersList() {
    ui->ProvidersList->clear();
    QUrl url = settings.value("provider/url").toUrl();
    ui->ProvidersList->addItem(url.toString());
}
void SettingsDialog::on_SettingsList_clicked() {
    // we get the item that was clicked
    QListWidgetItem *item = ui->SettingsList->currentItem();
    if (item) {
        ui->rootStack->setCurrentWidget(ui->PagePanel);

        QString itemText = item->text();
        if (itemText == "Provider") {
            updateProvidersList();

            ui->Pages->setCurrentWidget(ui->ProviderPage);
        }
    }
}

void SettingsDialog::on_BackButton_clicked() {
    // go back to the previous page
    ui->rootStack->setCurrentWidget(ui->PageMenu);
}

void SettingsDialog::on_AddProviderButton_clicked() {
    AddProviderDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QUrl url(dlg.getUrl());
        bool isActive = dlg.isActive();
        if (url.isValid()){
            settings.setValue("provider/url", url);
            settings.setValue("provider/active", isActive);

            downloadM3U(url, this, [this](const QVector<M3UEntry>& vec){
                // QMessageBox::information(this, "Provider Added", QString("The provider has been successfully added. %1").arg(vec.at(0).name));
            });

            QMessageBox::information(this, "Provider Added", "The provider has been successfully added.");
            
            updateProvidersList();
        }


    }
}
