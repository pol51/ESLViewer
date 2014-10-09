#include "mainWindow.h"

#include <core/qESLConnection.h>
#include <core/settings.h>

#include <gui/eslSettingsDialog.h>

#include <libesl/include/esl.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  // Main UI
  _treeChannels   = new QTreeView(this);
  QStringList Headers;
  Headers << "Key" << "Value";
  //_treeChannels->setHeaderLabels(Headers);
  _treeChannels->setColumnWidth(0, 270);
  _treeChannels->setModel(&_eventsModel);
  setCentralWidget(_treeChannels);

  // Menu
  QMenuBar *MenuBar = new QMenuBar(this);
  QMenu *FileMenu = MenuBar->addMenu("&File");
  QAction *ESLConnectAction = FileMenu->addAction("Co&nect to ESL");
  QAction *ClearAction = FileMenu->addAction("&Clear");
  FileMenu->addSeparator();
  QAction *ESLSettingsAction = FileMenu->addAction("ESL &Settings");
  FileMenu->addSeparator();
  QAction *QuitAction = FileMenu->addAction("&Quit");
  setMenuBar(MenuBar);

  // StatusBar
  QStatusBar *StatusBar = new QStatusBar(this);
  _lblCallCount = new QLabel("0 call / 0 channel", StatusBar);
  StatusBar->addWidget(_lblCallCount);
  setStatusBar(StatusBar);

  // Shortcuts
  ClearAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_X);
  QuitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
  ESLSettingsAction->setShortcut(Qt::CTRL + Qt::Key_S);
  ESLConnectAction->setShortcut(Qt::CTRL + Qt::Key_C);

  // Signals/Slots connections
  connect(ESLSettingsAction,  &QAction::triggered,  this, &MainWindow::openEslSettings);
  connect(ESLConnectAction,   &QAction::triggered,  this, &MainWindow::connectToEsl);
  connect(QuitAction,         &QAction::triggered,  this, &QMainWindow::close);
  connect(ClearAction,        &QAction::triggered,  this, &MainWindow::clear);

  // Resources init
  Q_INIT_RESOURCE(res);
  setWindowIcon(QIcon(":/logo.svg"));

  // Command-line params handling
  const QStringList &AppParams(QApplication::instance()->arguments());
  foreach (const QString &Param, AppParams)
    if (Param == "-a")
      connectToEsl();
}

void MainWindow::clear()
{
  //_treeChannels->clear();
  _calls = _channels = 0;
}

void MainWindow::connectToEsl()
{
  Settings S(this);
  QESLConnection *ESLCon = new QESLConnection(S.hostname(), S.port(), S.password(), this);
  connect(ESLCon, &QESLConnection::eventReceived, this, &MainWindow::eventReceived);
}

void MainWindow::openEslSettings()
{
  EslSettingsDialog(this).exec();
}

void MainWindow::eventReceived(QSharedPointer<ESLevent> event)
{
  const esl_event_types_t EventType(event.data()->event->event_id);
  QString UUID(event.data()->getHeader("Unique-ID"));

  // update calls/channels count
  switch (EventType)
  {
    case ESL_EVENT_CHANNEL_BRIDGE:    _calls++;     updateCoutLabel(); break;
    case ESL_EVENT_CHANNEL_UNBRIDGE:  _calls--;     updateCoutLabel(); break;
    case ESL_EVENT_CHANNEL_CREATE:    _channels++;  updateCoutLabel(); break;
    case ESL_EVENT_CHANNEL_DESTROY:   _channels--;  updateCoutLabel(); break;
    default: break;
  }

  if (UUID.isEmpty()) UUID = "_";
#if 0
  // find or create the parent node for the event (call)
  QList<QTreeWidgetItem *> ListItems = _treeChannels->findItems(UUID, Qt::MatchExactly, 0);
  QTreeWidgetItem *CurrentParent = NULL;
  if (!ListItems.isEmpty())
    CurrentParent = ListItems.first();
  else
  {
    CurrentParent = new QTreeWidgetItem(QStringList(UUID));
    _treeChannels->insertTopLevelItem(UUID != "_" ? _treeChannels->topLevelItemCount() : 0, CurrentParent);
  }

  // add some info on the channel
  switch (EventType)
  {
    case ESL_EVENT_CHANNEL_CREATE:
      CurrentParent->setBackgroundColor(0, QColor(Qt::green));
      CurrentParent->setData(1, 0,
                             QString("[%1] %2 -> %3").
                             arg(event.data()->getHeader("Caller-Direction")).
                             arg(event.data()->getHeader("Caller-Username")).
                             arg(event.data()->getHeader("Caller-Destination-Number")));
      break;
    case ESL_EVENT_CHANNEL_DESTROY:
      CurrentParent->setBackgroundColor(0, QColor(Qt::transparent));
      break;
    default:
      break;
  }

  // insert the event in the tree
  //QTreeWidgetItem *Event = new QTreeWidgetItem(QStringList(event.data()->getType()));
  CurrentParent->addChild(Event);
  const char* Header = event.data()->firstHeader();
  do
  {
    QStringList L;
    L << QString(Header) << event.data()->getHeader(Header);
    Event->addChild(new QTreeWidgetItem(L));
    Header = event.data()->nextHeader();
  } while (Header);

#endif
}

void MainWindow::updateCoutLabel()
{
  _lblCallCount->setText(QString("%1 call%2 / %3 channel%4").
                         arg(_calls).arg(_calls>1?"s":"").
                         arg(_channels).arg(_channels>1?"s":""));
}
