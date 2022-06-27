#include "qt/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
	setupUi();
}

MainWindow::~MainWindow(){
}

int MainWindow::setupUi(){
	// main window properties
	this->setWindowTitle("Zylator - A ZylOS Emulator");

	// central widget (fills entire window)
	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);

	// vertical layout to arrange items in full rows
	verticalLayout = new QVBoxLayout(centralWidget);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);

	// the graphics box where the framebuffer is displayed
	graphicsView = new QGraphicsView(centralWidget);
	verticalLayout->addWidget(graphicsView);

	// a dropdown box to select programs
	programSelector = new QComboBox(centralWidget);
	programSelector->addItem(QString("dummy"));
	verticalLayout->addWidget(programSelector);

	// a stacked widget, where new zylProg input widgets are added
	inputStack = new QStackedWidget(centralWidget);
	verticalLayout->addWidget(inputStack);
	dummyInputPage = new QWidget(); //* das wird hier als dummy hinzugeböllert
	inputStack->addWidget(dummyInputPage);

	// a menu bar. why not.
	menuBar = new QMenuBar(this);
	menuBar->setGeometry(QRect(0, 0, 348, 19));
	this->setMenuBar(menuBar);

	return 0; // TODO sensible errorhandling
}
