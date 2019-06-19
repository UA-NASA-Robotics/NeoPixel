
/*
 * SDO.c
 *
 * Created: 3/18/2016 10:25:54 PM
 *  Author: reed
 */ 

#include "SDO.h"
#include "general.h"
#include "assert.h"
#include "can.h"

void SDOWritePacketFUll(unsigned int NodeID, unsigned int ObjIndx, char SubIndx, unsigned long Data){
	CAN_packet SDO = {0x600+NodeID, 8, "0"};
	SDO.data[0] = 0x23;
	SDO.data[1] = ObjIndx;
	SDO.data[2] = ObjIndx>>8; 	
	SDO.data[3] = SubIndx;
	SDO.data[4] = Data; 
	SDO.data[5] = Data>>8; 
	SDO.data[6] = Data>>16;
	SDO.data[7] = Data>>24; 
	
	can_tx(14, &SDO);
}

void SDOWritePacket(SDO_packet SDOpacket){
	CAN_packet SDO = {0x600+SDOpacket.NodeID, 8, "0"};
	SDO.data[0] = 0x23;
	SDO.data[1] = SDOpacket.ObjIndx;
	SDO.data[2] = SDOpacket.ObjIndx>>8;
	SDO.data[3] = SDOpacket.SubIndx;
	SDO.data[4] = SDOpacket.Data;
	SDO.data[5] = SDOpacket.Data>>8;
	SDO.data[6] = SDOpacket.Data>>16;
	SDO.data[7] = SDOpacket.Data>>24;
	
	can_tx(14, &SDO);
}

void SDOReadPacket(SDO_packet SDOpacket){
	CAN_packet SDO = {0x600+SDOpacket.NodeID, 8, "0"};
	SDO.data[0] = 0x40;
	SDO.data[1] = SDOpacket.ObjIndx;
	SDO.data[2] = SDOpacket.ObjIndx>>8;
	SDO.data[3] = SDOpacket.SubIndx;
	SDO.data[4] = 0;
	SDO.data[5] = 0;
	SDO.data[6] = 0;
	SDO.data[7] = 0;
	
	can_tx(14, &SDO);
	
}