#include <QApplication>
#include "main_window.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	CORE::MainWindow mainwindow;
	mainwindow.show();
	return app.exec();
}
