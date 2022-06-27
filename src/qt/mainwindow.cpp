#include "qt/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
	setupUi();
}

MainWindow::~MainWindow(){
}

int MainWindow::setupUi(){
	this->setWindowTitle("Zylator - A ZylOS Emulator");

	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);

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

	menuBar = new QMenuBar(this);
	menuBar->setGeometry(QRect(0, 0, 348, 19));
	this->setMenuBar(menuBar);

	return 0; // TODO sensible errorhandling
}
