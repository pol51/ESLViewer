#include <QtWidgets/QApplication>

#include <gui/mainWindow.h>

int main(int argc, char *argv[])
{
  QApplication App(argc, argv);
  App.setOrganizationName("PLab");
  App.setApplicationName("ESLViewer");

  MainWindow MainWin;
  MainWin.show();

  return App.exec();
}
