#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant> // braucht man das?
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication> // und das?
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
	int				setupUi();

public:
    QWidget 		*centralWidget;
    QVBoxLayout 	*verticalLayout;
    QGraphicsView 	*graphicsView;
    QComboBox 		*programSelector;
    QStackedWidget 	*inputStack;
    QWidget 		*dummyInputPage;
    QMenuBar 		*menuBar; // naja brauchmer das

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
