#include <QtWidgets/QApplication>

#include <gui/mainWindow.h>

int main(int argc, char *argv[])
{
  QApplication App(argc, argv);
  MainWindow MainWin;
  MainWin.show();

  return App.exec();
}
