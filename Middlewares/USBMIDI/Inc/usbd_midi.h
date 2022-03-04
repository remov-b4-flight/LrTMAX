/**
  ******************************************************************************
  * @file   usbd_midi.h
  * @author modified by remov-b4-flight
  * @copyright  original copyright below
  ******************************************************************************
  (CC at)2016 by D.F.Mac. @@TripArts Music
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_MIDI_H
#define __USB_MIDI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

#define MIDI_IN_EP									0x82  /* EP1 for data IN */
#define MIDI_OUT_EP									0x01  /* EP1 for data OUT */

#define MIDI_DATA_FS_MAX_PACKET_SIZE				64 /* Endpoint IN & OUT Packet size */
#define MIDI_CMD_PACKET_SIZE						8  /* Control Endpoint Packet size */

#define USB_MIDI_CONFIG_DESC_SIZ					86
#define MIDI_DATA_IN_PACKET_SIZE					MIDI_DATA_FS_MAX_PACKET_SIZE
#define MIDI_DATA_OUT_PACKET_SIZE					MIDI_DATA_FS_MAX_PACKET_SIZE

typedef struct _USBD_MIDI_ItfTypeDef{
  uint16_t (*pIf_MidiRx)    (uint8_t *msg, uint16_t length);
  uint16_t (*pIf_MidiTx)    (uint8_t *msg, uint16_t length);
}USBD_MIDI_ItfTypeDef;

extern USBD_ClassTypeDef	USBD_MIDI;
#define USBD_MIDI_CLASS		&USBD_MIDI

#define UNUSED_DESC_IDX	0

uint8_t  USBD_MIDI_RegisterInterface  (USBD_HandleTypeDef   *pdev,
                                      USBD_MIDI_ItfTypeDef *fops);

#ifdef __cplusplus
}
#endif

#endif  /* __USB_MIDI_H */
