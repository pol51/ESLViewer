#include "mainWindow.h"

#include <core/qESLConnection.h>

#include <gui/connectDialog.h>

#include <libesl/include/esl.h>

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
  _lblCallCount = new QLabel("0 call / 0 channel", CentralWidget);
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

void MainWindow::eventReceived(QSharedPointer<ESLevent> event)
{
  const esl_event_types_t EventType = event.data()->event->event_id;

  // update calls/channels count
  switch (EventType)
  {
    case ESL_EVENT_CHANNEL_BRIDGE:    _calls++;     updateCoutLabel(); break;
    case ESL_EVENT_CHANNEL_UNBRIDGE:  _calls--;     updateCoutLabel(); break;
    case ESL_EVENT_CHANNEL_CREATE:    _channels++;  updateCoutLabel(); break;
    case ESL_EVENT_CHANNEL_DESTROY:   _channels--;  updateCoutLabel(); break;
    default: break;
  }

  // drop events without UUID
  if (QString(event.data()->getHeader("Unique-ID")).isEmpty())
    return;

  // find or create the parent node for the event (call)
  QList<QTreeWidgetItem *> ListItems = _treeChannels->findItems(event.data()->getHeader("Unique-ID"), Qt::MatchExactly, 0);
  QTreeWidgetItem *CurrentParent = NULL;
  if (ListItems.isEmpty())
  {
    CurrentParent = new QTreeWidgetItem(QStringList(event.data()->getHeader("Unique-ID")));
    _treeChannels->insertTopLevelItem(_treeChannels->topLevelItemCount(), CurrentParent);
  }
  else
    CurrentParent = ListItems.first();

  // add some info on the channel
  if (EventType == ESL_EVENT_CHANNEL_CREATE)
  {
    CurrentParent->setData(1, 0,
                           QString("[%1] %2 -> %3").
                           arg(QString(event.data()->getHeader("Caller-Direction"))).
                           arg(QString(event.data()->getHeader("Caller-Username"))).
                           arg(QString(event.data()->getHeader("Caller-Destination-Number"))));
  }

  // insert the event in the tree
  QTreeWidgetItem *Event = new QTreeWidgetItem(QStringList(event.data()->getType()));
  CurrentParent->addChild(Event);
  const char* Header = event.data()->firstHeader();
  do
  {
    QStringList L;
    L << QString(Header) << event.data()->getHeader(Header);
    Event->addChild(new QTreeWidgetItem(L));
    Header = event.data()->nextHeader();
  } while (Header);
}

void MainWindow::clear()
{
  _treeChannels->clear();
}

void MainWindow::updateCoutLabel()
{
  _lblCallCount->setText(QString("%1 call%2 / %3 channel%4").
                         arg(_calls).arg(_calls>1?"s":"").
                         arg(_channels).arg(_channels>1?"s":""));
}
