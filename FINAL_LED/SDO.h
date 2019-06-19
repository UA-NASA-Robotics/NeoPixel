typedef struct
{
	unsigned int NodeID;	
	unsigned int ObjIndx;
	unsigned char SubIndx;	
	unsigned long Data; 
}
SDO_packet;

void SDOWritePacketFull(unsigned int NodeID, unsigned int ObjIndx, char SubIndx, unsigned long Data); 
void SDOWritePacket(SDO_packet SDOpacket);
void SDOReadPacket(SDO_packet SDOpacket); 