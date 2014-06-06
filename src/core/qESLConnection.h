#ifndef __QESLCONNECTION_H__
#define __QESLCONNECTION_H__

#include <QtCore/QObject>

class ESLconnection;
class ESLevent;

class QSocketNotifier;

class QESLConnection : public QObject
{
  Q_OBJECT

  public:
    QESLConnection(const QString &host, const int port, const QString &pass, QObject *parent = NULL);

  signals:
    void eventReceived(QSharedPointer<ESLevent>);

  protected slots:
    void readyRead();

  protected:
    ESLconnection *_eslConnection     = NULL;
    QSocketNotifier *_socketNotifier  = NULL;
};

#endif
