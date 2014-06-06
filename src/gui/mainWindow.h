#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtCore/QHash>

#include <QtWidgets/QMainWindow>

#include "libesl/include/esl_oop.h"

class ConnectDialog;

class QLabel;
class QTreeWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
  Q_OBJECT
    
  public:
    explicit MainWindow(QWidget *parent = NULL);

    QSize sizeHint() const { return QSize(640, 480); }

  protected slots:
    void connectToEsl();
    void eventReceived(QSharedPointer<ESLevent> event);
    void clear();
    void updateCoutLabel();

  protected:
    int _calls    = 0;
    int _channels = 0;

    QLabel *_lblCallCount;
    QTreeWidget *_treeChannels;
    QPushButton *_btnConnect;
    QPushButton *_btnClear;
    QPushButton *_btnQuit;
};

#endif
