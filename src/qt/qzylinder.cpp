#include "qt/qzylinder.h"

QZylinder::QZylinder(QObject *parent) : QObject(parent) {
	// start timer to continuously render
	m_pT = new QTimer(parent);
	connect(m_pT, SIGNAL(timeout()), this, SLOT(render()));
	m_pT->start(1000); //TODO use a proper framerate

	// initialize zylinder stuff
	init();
}

int QZylinder::init(){
	// TODO zpm stuff
	DPRINT("zylinder init function");
	return 0; //TODO error handling
}

void QZylinder::input(uint8_t op, uint8_t x, uint8_t y, uint8_t z){
	// something zylinder related globally
	switch(op){
		default:
		DPRINT("Wrong Opcode");
	}
}

void QZylinder::programInput(uint8_t x, uint8_t y, uint8_t z){
	// give input to ZPM
	DPRINT("programInput slot");
}

void QZylinder::render(){
	DPRINT("render huiii");
	// zylProgManager::render(m_Fb);
}