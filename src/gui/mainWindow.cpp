#include "mainWindow.h"

#include <core/qESLConnection.h>

#include <gui/connectDialog.h>

#include <libesl/include/esl.h>

#include <QtCore/QDebug>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  QWidget *CentralWidget  = new QWidget(this);
  QVBoxLayout *MainLayout = new QVBoxLayout(CentralWidget);
  QHBoxLayout *BtnLayout  = new QHBoxLayout(CentralWidget);
  _btnClear     = new QPushButton("&Clear", CentralWidget);
  _btnConnect   = new QPushButton("&Connect", CentralWidget);
  _btnQuit      = new QPushButton("&Quit", CentralWidget);
  _lblCallCount = new QLabel("0 active call", CentralWidget);
  _treeChannels = new QTreeWidget(CentralWidget);

  MainLayout->addWidget(_treeChannels);
  MainLayout->addLayout(BtnLayout);

  BtnLayout->addWidget(_lblCallCount);
  BtnLayout->addWidget(_btnConnect);
  BtnLayout->addWidget(_btnClear);
  BtnLayout->addWidget(_btnQuit);

  QStringList Headers;
  Headers << "Key" << "Value";
  _treeChannels->setHeaderLabels(Headers);

  setCentralWidget(CentralWidget);

  connect(_btnQuit,   &QPushButton::clicked, this, &QMainWindow::close);
  connect(_btnClear,  &QPushButton::clicked, this, &MainWindow::clear);
  connect(_btnConnect,&QPushButton::clicked, this, &MainWindow::connectToEsl);
}

void MainWindow::connectToEsl()
{
  ConnectDialog ConnectDBox(this);
  if (ConnectDBox.exec() == QDialog::Accepted)
  {
    QESLConnection *ESLCon = new QESLConnection(ConnectDBox.host(), ConnectDBox.port(), ConnectDBox.pass(), this);
    connect(ESLCon, &QESLConnection::eventReceived, this, &MainWindow::eventReceived);
  }
}

void MainWindow::eventReceived(QSharedPointer<ESLevent> e)
{
  switch (e.data()->event->event_id)
  {
    case ESL_EVENT_CHANNEL_BRIDGE:    _calls++; break;
    case ESL_EVENT_CHANNEL_UNBRIDGE:  _calls--; break;
    default: break;
  }

  _lblCallCount->setText(QString("%1 active call%2").arg(_calls).arg(_calls>1?"s":""));

  if (QString(e.data()->getHeader("Unique-ID")).isEmpty())
    return;

  QList<QTreeWidgetItem *> ListItems = _treeChannels->findItems(e.data()->getHeader("Unique-ID"), Qt::MatchExactly, 0);
  QTreeWidgetItem *CurrentParent = NULL;
  if (ListItems.isEmpty())
  {
    CurrentParent = new QTreeWidgetItem(QStringList(e.data()->getHeader("Unique-ID")));
    _treeChannels->insertTopLevelItem(_treeChannels->topLevelItemCount(), CurrentParent);
  }
  else
  {
    if (ListItems.size() > 1)
    {
      qDebug() << "Error! We have more than one UUID on tree!!!";
      return;
    }
    CurrentParent = ListItems.first();
  }

  QTreeWidgetItem *Event = new QTreeWidgetItem(QStringList(e.data()->getType()));
  CurrentParent->addChild(Event);
  const char* header = e.data()->firstHeader();
  do
  {
    QStringList L;
    L << QString(header) << e.data()->getHeader(header);
    Event->addChild(new QTreeWidgetItem(L));
    header = e.data()->nextHeader();
  } while (header);
}

void MainWindow::clear()
{
  _treeChannels->clear();
}
