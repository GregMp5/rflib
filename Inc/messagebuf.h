/*
 * messagebuf.h
 *
 *  Created on: 4. 11. 2016
 *      Author: juraj.spuchlak
 */

#ifndef MESSAGEBUF_H_
#define MESSAGEBUF_H_

#include "usbd_cdc.h"

#define APP_RX_DATA_SIZE  0xff
#define APP_TX_DATA_SIZE  0xff

//maximum 0xffff
#define MAX_RXMESSAGEBUFFER_SIZE 0x0f

#define INC_RINGBUF_POINTER(pointer)	((pointer+1)%MAX_RXMESSAGEBUFFER_SIZE)

typedef enum {
 	empty = 0,
 	datatoread,
 	full,
 } messagebufresp;

 typedef struct{
 	uint32_t lenght;
 	uint8_t * data;
 }RxData;

 typedef struct {
 	uint16_t vWrPt;
 	uint16_t RdPt;
 	uint16_t overfl;
 	messagebufresp status;
 	RxData buffer[MAX_RXMESSAGEBUFFER_SIZE];
 }User_Message_Buffer;

 messagebufresp InitRingBuffer();
 messagebufresp GetMessageBufferState();
 messagebufresp ReadCDCMessageBuffer (uint8_t* Buf, uint32_t *Len);


#endif /* MESSAGEBUF_H_ */
