#ifndef __CONNECTDIALOG_H__
#define __CONNECTDIALOG_H__

#include <QtWidgets/QDialog>

class QLineEdit;
class QSpinBox;
class QLineEdit;
class QDialogButtonBox;

class ConnectDialog : public QDialog
{
  Q_OBJECT
    
  public:
    explicit ConnectDialog(QWidget *parent = NULL);

    const QString host() const;
    const QString pass() const;
    const int port() const;

  protected:
    QLineEdit         *_txtHost;
    QLineEdit         *_txtPass;
    QSpinBox          *_spinPort;
    QDialogButtonBox  *_btnBox;
};

#endif
