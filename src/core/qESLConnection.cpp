#include "qESLConnection.h"

#include <libesl/include/esl_oop.h>

#include <QtCore/QSocketNotifier>
#include <QtCore/QSharedPointer>

QESLConnection::QESLConnection(const QString &host, const int port, const QString &pass, QObject *parent) :
  QObject(parent)
{
  qRegisterMetaType<QSharedPointer<ESLevent> >("QSharedPointer<ESLevent>");

  _eslConnection = new ESLconnection(host.toUtf8().constData(),
                                     QString::number(port).toUtf8().constData(),
                                     pass.toUtf8().constData());

  _socketNotifier = new QSocketNotifier(_eslConnection->socketDescriptor(), QSocketNotifier::Read, this);

  connect(_socketNotifier, &QSocketNotifier::activated, this, &QESLConnection::readyRead);

  _eslConnection->events("plain", "all");
}

void QESLConnection::readyRead()
{
  emit eventReceived(QSharedPointer<ESLevent>(_eslConnection->recvEvent()));
}
