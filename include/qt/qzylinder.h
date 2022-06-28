#ifndef __ZYLINDER_H_
#define __ZYLINDER_H_

#include <QObject>
#include <QTimer>

#include "shared/config.h"
#include "shared/zylFB.h"
#include "shared/zylProg.h"

class QZylinder : public QObject{
	Q_OBJECT

	zylFB	m_Fb;
	QTimer	*m_pT;
	int		init();
public:
	QZylinder(QObject *parent = nullptr);
	// ~QZylinder();
public slots:
	void 	input(uint8_t op, uint8_t x, uint8_t y, uint8_t z);
	void 	programInput(uint8_t, uint8_t, uint8_t);
	void	render();
};



#endif // __ZYLINDER_H_