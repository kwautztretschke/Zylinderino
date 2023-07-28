#include <Fartnet.h>
#include <HardwareSerial.h>

int FartnetClass::init(unsigned int port, uint8_t universe){
	m_Universe = universe;
	m_Udp.begin(port);
	Serial.printf("Listening to Artnet universe %d on Port %d\n", universe, port);
	return 0;
}

void FartnetClass::loop(){
	int packetSize = m_Udp.parsePacket();
	if (packetSize <= 0)
		return; // no packet available

	// read the packet into packetBufffer
	memset(m_PacketBuffer, 0, DMX_BUFFER_SIZE*sizeof(char));
	m_Udp.read(m_PacketBuffer, DMX_BUFFER_SIZE);

	int data_length = getDmxLength();
	if (data_length <= 0)
		return; // packet was not a DMX frame

	// give the dmx data to the callback
	p_dmx((const uint8_t*)m_PacketBuffer+18, (const uint16_t)data_length);
}

int FartnetClass::getDmxLength(){
    // Check the Protocol ID to ensure it's an ArtNet packet
    if (strncmp((const char*)m_PacketBuffer, "Art-Net", 8)){
        return -1; // Invalid protocol ID
	}

	// Extract the Header
	uint16_t opCode = 	m_PacketBuffer[9]<<8 | m_PacketBuffer[8]; 
	uint16_t protVer = 	m_PacketBuffer[10]<<8 | m_PacketBuffer[11];
	uint8_t seqNo = 	m_PacketBuffer[12];
	uint8_t physPort =	m_PacketBuffer[13];
	uint16_t universe = m_PacketBuffer[15]<<8 | m_PacketBuffer[14];
	uint16_t length = 	m_PacketBuffer[16]<<8 | m_PacketBuffer[17];


    // Check the OpCode and version for a valid ArtNet header
    if (opCode != 0x5000 || protVer != 14){
        return -2; // Invalid OpCode or version
	}

	// Is the Packet destined for the right universe?
	if (universe != m_Universe){
		return -3;
	}

	// Packet verified, return datagram length
	return length;
}

FartnetClass Fartnet;