#include "qt/qzylinder.h"

#define ZOOMFACTOR 10


QZylinder::QZylinder(QObject *parent) : QObject(parent) {
	// start timer to continuously render
	m_pT = new QTimer(parent);
	connect(m_pT, SIGNAL(timeout()), this, SLOT(render()));
	m_pT->start(1000); //TODO use a proper framerate

	// initialize Image Stuff
	m_pI = new QImage(X_RES, Y_RES, QImage::Format_RGB888);
	m_GPI.setPixmap(QPixmap::fromImage(
		m_pI->scaled(ZOOMFACTOR*X_RES, ZOOMFACTOR*Y_RES)
		));
	m_Scene.addItem(&m_GPI);

	// initialize zylinder stuff
	init();
}

int QZylinder::init(){
	zylProgManager::initPrograms();
	zylProgManager::init();
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
	zylProgManager::input(x, y, z);
}

void QZylinder::render(){
	zylProgManager::render(&m_Fb);

	// convert zylFB to QImage
	QColor c;
	zylPel p;
	for (int x = 0; x < X_RES; x++){
		for (int y = 0; y < Y_RES; y++){
			p = m_Fb(x, y);
			c.setRgb(p.r, p.g, p.b);
			m_pI->setPixelColor(x, y, c);
		}
	}
	// convert QImage to QPixmap to QGraphicsPixmapItem (wtf)
	m_GPI.setPixmap(QPixmap::fromImage(
		m_pI->scaled(ZOOMFACTOR*X_RES, ZOOMFACTOR*Y_RES)
		));

	// emit imageChanged(); //*somehow this is done automatically?
}