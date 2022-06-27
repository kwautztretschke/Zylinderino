/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
** Manual adjustment to remove bullshit was done afterwards.
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QComboBox *programSelector;
    QStackedWidget *inputStack;
    QWidget *dummyInputPage;
    QMenuBar *menuBar; // naja brauchmer das

    void setupUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle("Amogus");

        centralWidget = new QWidget(MainWindow);
        MainWindow->setCentralWidget(centralWidget);

        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);

        graphicsView = new QGraphicsView(centralWidget);
        verticalLayout->addWidget(graphicsView);

        programSelector = new QComboBox(centralWidget);
        programSelector->addItem(QString("dummy"));
        verticalLayout->addWidget(programSelector);

        inputStack = new QStackedWidget(centralWidget);
        verticalLayout->addWidget(inputStack);
			dummyInputPage = new QWidget(); //* das wird hier als dummy hinzugeböllert
			inputStack->addWidget(dummyInputPage);

        menuBar = new QMenuBar(MainWindow);
        menuBar->setGeometry(QRect(0, 0, 348, 19));
        MainWindow->setMenuBar(menuBar);
        // QMetaObject::connectSlotsByName(MainWindow); //? abababab hier wird nix automatisch connected!
    } // setupUi
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
