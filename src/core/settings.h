#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <QtCore/QSettings>

class Settings : public QSettings
{
  Q_OBJECT

  Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged)
  Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
  Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)

  public:
    Settings(QObject *parent = NULL) : QSettings(parent) {}

    const QString hostname() const;
    const QString password() const;
    const quint16 port() const;

    void setHostname(const QString &value);
    void setPassword(const QString &value);
    void setPort(const quint16 value);

  signals:
    void hostnameChanged(const QString &value);
    void passwordChanged(const QString &value);
    void portChanged(const quint16 value);
};

#endif
