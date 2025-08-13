#include "ui/AddProviderDialog.h"

#include <qmessagebox.h>

#include "ui_AddProviderDialog.h"

AddProviderDialog::AddProviderDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddProviderDialog) {
    ui->setupUi(this);
}

AddProviderDialog::~AddProviderDialog() { delete ui; }

void AddProviderDialog::on_buttonBox_accepted() { accept(); }

void AddProviderDialog::on_buttonBox_rejected() { reject(); }

QString AddProviderDialog::getUrl() const { return ui->URLAddressEdit->text(); }

bool AddProviderDialog::isActive() const {
    return ui->ActiveCheckBox->isChecked();
}
