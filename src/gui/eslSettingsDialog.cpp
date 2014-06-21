#include "eslSettingsDialog.h"

#include <core/settings.h>

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDialogButtonBox>

EslSettingsDialog::EslSettingsDialog(QWidget *parent) :
  QDialog(parent)
{
  setWindowTitle("Connect");

  Settings S(this);

  QFormLayout *MainLayout = new QFormLayout(this);
  _txtHost  = new QLineEdit(S.hostname(), this);
  _txtPass  = new QLineEdit(S.password(), this);
  _spinPort = new QSpinBox(this);
  _btnBox   = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

  _spinPort->setRange(0, 0xffff);
  _spinPort->setValue(S.port());

  MainLayout->addRow("Host", _txtHost);
  MainLayout->addRow("Port", _spinPort);
  MainLayout->addRow("Password", _txtPass);
  MainLayout->addRow(_btnBox);

  connect(_btnBox, &QDialogButtonBox::accepted, this, &EslSettingsDialog::accept);
  connect(_btnBox, &QDialogButtonBox::rejected, this, &EslSettingsDialog::reject);
}

void EslSettingsDialog::accept()
{
  Settings S;
  S.setHostname(_txtHost->text());
  S.setPassword(_txtPass->text());
  S.setPort(_spinPort->value());

  QDialog::accept();
}
