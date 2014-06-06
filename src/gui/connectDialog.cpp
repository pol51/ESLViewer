#include "connectDialog.h"

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDialogButtonBox>

ConnectDialog::ConnectDialog(QWidget *parent) :
  QDialog(parent)
{
  setWindowTitle("Connect");

  QFormLayout *MainLayout = new QFormLayout(this);
  _txtHost  = new QLineEdit("127.0.0.1", this);
  _txtPass  = new QLineEdit("ClueCon", this);
  _spinPort = new QSpinBox(this);
  _btnBox   = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

  _spinPort->setRange(0, 0xffff);
  _spinPort->setValue(8021);

  MainLayout->addRow("Host", _txtHost);
  MainLayout->addRow("Port", _spinPort);
  MainLayout->addRow("Password", _txtPass);
  MainLayout->addRow(_btnBox);

  connect(_btnBox, &QDialogButtonBox::accepted, this, &ConnectDialog::accept);
  connect(_btnBox, &QDialogButtonBox::rejected, this, &ConnectDialog::reject);
}

const QString ConnectDialog::host() const
{
  return _txtHost->text();
}

const int ConnectDialog::port() const
{
  return _spinPort->value();
}

const QString ConnectDialog::pass() const
{
  return _txtPass->text();
}
