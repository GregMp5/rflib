/*
 * messagebuf.c
 *
 *  Created on: 4. 11. 2016
 *      Author: juraj.spuchlak
 */

#include "messagebuf.h"
#include "usbd_cdc_if.h"

User_Message_Buffer uMessBuf;

messagebufresp InitRingBuffer()
	{
	  //init message buffer
		uMessBuf.vWrPt = 0;
		uMessBuf.RdPt = 0;
		uMessBuf.overfl = 0;
		uMessBuf.status  = empty;
		uMessBuf.buffer[uMessBuf.vWrPt].data = (uint8_t *)calloc(0,APP_RX_DATA_SIZE*sizeof(char));

	return (uMessBuf.status);
	}

messagebufresp GetMessageBufferState()
	{
	return (uMessBuf.status);
	}

messagebufresp ReadCDCMessageBuffer (uint8_t* Buf, uint32_t *Len)
{
	if (uMessBuf.status >= datatoread)
	{
		memcpy (Buf, uMessBuf.buffer[uMessBuf.RdPt].data, (size_t)uMessBuf.buffer[uMessBuf.RdPt].lenght);
		*Len = uMessBuf.buffer[uMessBuf.RdPt].lenght;
		free(uMessBuf.buffer[uMessBuf.RdPt].data);

		//increment ring buffer read pointer
		uMessBuf.RdPt=INC_RINGBUF_POINTER(uMessBuf.RdPt);
		//update message buffer status
		(uMessBuf.RdPt != uMessBuf.vWrPt)?(uMessBuf.status = datatoread):(uMessBuf.status = empty);
	}
	return (uMessBuf.status);
}
