#include "settings.h"

#define ESL_HOSTNAME_KEY "esl/hostname"
#define ESL_PASSWORD_KEY "esl/password"
#define ESL_PORT_KEY     "esl/port"

const QString Settings::hostname() const
{
  return value(ESL_HOSTNAME_KEY, "127.0.0.1").toString();
}

const QString Settings::password() const
{
  return value(ESL_PASSWORD_KEY, "ClueCon").toString();
}

const quint16 Settings::port() const
{
  bool Ok(false);
  quint16 Port = value(ESL_PORT_KEY, 8021).toInt(&Ok);
  return Ok ? Port : 8021;
}

void Settings::setHostname(const QString &value)
{
  setValue(ESL_HOSTNAME_KEY, value);
  emit hostnameChanged(value);
}

void Settings::setPassword(const QString &value)
{
  setValue(ESL_PASSWORD_KEY, value);
  emit passwordChanged(value);
}

void Settings::setPort(const quint16 value)
{
  setValue(ESL_PORT_KEY, value);
  emit portChanged(value);
}
