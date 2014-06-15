#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtCore/QHash>

#include <QtWidgets/QMainWindow>

#include "libesl/include/esl_oop.h"

class EslSettingsDialog;

class QLabel;
class QTreeWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT
    
  public:
    explicit MainWindow(QWidget *parent = NULL);

    QSize sizeHint() const { return QSize(640, 480); }

  protected slots:
    void clear();
    void connectToEsl();
    void openEslSettings();
    void eventReceived(QSharedPointer<ESLevent> event);
    void updateCoutLabel();

  protected:
    int _calls    = 0;
    int _channels = 0;

    QLabel *_lblCallCount;
    QTreeWidget *_treeChannels;
};

#endif
