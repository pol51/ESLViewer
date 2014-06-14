#ifndef __ESLSETTINGSDIALOG_H__
#define __ESLSETTINGSDIALOG_H__

#include <QtWidgets/QDialog>

class QLineEdit;
class QSpinBox;
class QLineEdit;
class QDialogButtonBox;

class EslSettingsDialog : public QDialog
{
  Q_OBJECT
    
  public:
    explicit EslSettingsDialog(QWidget *parent = NULL);

    void accept();

  protected:
    QLineEdit         *_txtHost;
    QLineEdit         *_txtPass;
    QSpinBox          *_spinPort;
    QDialogButtonBox  *_btnBox;
};

#endif
