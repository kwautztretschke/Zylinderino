#ifndef __FARTNET_H__
#define __FARTNET_H__

#include <WiFiUdp.h>

#define DMX_BUFFER_SIZE 1024

class FartnetClass{
private:
	WiFiUDP			m_Udp;
	uint8_t			m_PacketBuffer[DMX_BUFFER_SIZE];
	uint8_t			m_Universe;
	int				getDmxLength();
	// callbacks
	void			(*p_dmx)(const uint8_t* data, const uint16_t size);
public:
	int				init(unsigned int port, uint8_t universe);
	void			loop();
	// callbacks
	void			setDmxCallback(void	(*dmx)(const uint8_t* data, const uint16_t size)) {p_dmx = dmx;}

};

extern FartnetClass Fartnet;



#endif // __FARTNET_H__