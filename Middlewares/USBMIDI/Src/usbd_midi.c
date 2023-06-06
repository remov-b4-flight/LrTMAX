/**
	******************************************************************************
	* @file		usbd_midi.c
	* @author modified by remov-b4-flight
	* @copyright	original copyright below
	******************************************************************************
		(CC at)2016 by D.F.Mac. @@TripArts Music
*/

/* Includes ------------------------------------------------------------------*/
#include <midi.h>
#include "usbd_midi.h"
#include "usbd_desc.h"
#include "stm32f0xx_hal_conf.h"
#include "usbd_ctlreq.h"
#include "stm32f0xx_hal.h"

static uint8_t	USBD_MIDI_Init (USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t	USBD_MIDI_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t	USBD_MIDI_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t	USBD_MIDI_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t	*USBD_MIDI_GetCfgDesc (uint16_t *length);
USBD_HandleTypeDef *pInstance = NULL;

__ALIGN_BEGIN uint8_t USB_Rx_Buffer[MIDI_DATA_OUT_PACKET_SIZE] __ALIGN_END ;

/* USB MIDI interface class callbacks structure */
USBD_ClassTypeDef USBD_MIDI =
{
	USBD_MIDI_Init,
	USBD_MIDI_DeInit,
	NULL,
	NULL,
	NULL,
	USBD_MIDI_DataIn,
	USBD_MIDI_DataOut,
	NULL,
	NULL,
	NULL,
	NULL,// HS
	USBD_MIDI_GetCfgDesc,// FS
	NULL,// OTHER SPEED
	NULL,// DEVICE_QUALIFIER
};

/* USB MIDI device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_MIDI_CfgDesc[USB_MIDI_CONFIG_DESC_SIZE] __ALIGN_END =
{
	0x09, CONFIG, 83, 0, NUM_INTF, CONFIG1, UNUSED_DESC_IDX, (BUSPOWERED | REMOTE_WAKEUP), MIDI_POWER,
	0x09, INTERFACE, INTF0, ALTER0, MS_NUM_EP, AUDIO, MIDI_STREAM, MIDI_UNUSED, MIDI_UNUSED,
	0x07, CS_INTERFACE, HEADER, 0x00, 0x01, 37, 0,
	0x06, CS_INTERFACE, MIDI_IN_JACK, MIDI_JTYPE_ENB, MIDI_JACK_NO_IN_ENB, UNUSED_DESC_IDX,
	0x09, CS_INTERFACE, MIDI_OUT_JACK, MIDI_JTYPE_EXT, MIDI_JACK_NO_OUT_EXT, 0x01, MIDI_JACK_NO_IN_ENB, 0x01, UNUSED_DESC_IDX,
	0x09, CS_INTERFACE, MIDI_OUT_JACK, MIDI_JTYPE_ENB, MIDI_JACK_NO_OUT_ENB, 0x01, MIDI_JACK_NO_IN_EXT, 0x01, UNUSED_DESC_IDX,
	0x06, CS_INTERFACE, MIDI_IN_JACK, MIDI_JTYPE_EXT, MIDI_JACK_NO_IN_EXT, UNUSED_DESC_IDX,
	0x09, ENDPOINT, MIDI_OUT_EP, BULK, 64, 0, INTERVAL, MIDI_UNUSED, MIDI_UNUSED,
	0x05, CS_ENDPOINT, MS_GENERAL, 0x01, MIDI_JACK_NO_IN_ENB,
	0x09, ENDPOINT, MIDI_IN_EP, BULK, 64, 0, INTERVAL, MIDI_UNUSED, MIDI_UNUSED,
	0x05, CS_ENDPOINT, MS_GENERAL, 0x01, MIDI_JACK_NO_OUT_ENB,
};

static uint8_t USBD_MIDI_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx){
	pInstance = pdev;
	USBD_LL_OpenEP(pdev,MIDI_IN_EP,USBD_EP_TYPE_BULK,MIDI_DATA_IN_PACKET_SIZE);
	USBD_LL_OpenEP(pdev,MIDI_OUT_EP,USBD_EP_TYPE_BULK,MIDI_DATA_OUT_PACKET_SIZE);
	USBD_LL_PrepareReceive(pdev,MIDI_OUT_EP,(uint8_t*)(USB_Rx_Buffer),MIDI_DATA_OUT_PACKET_SIZE);
	return 0;
}

static uint8_t USBD_MIDI_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx){
	pInstance = NULL;
	USBD_LL_CloseEP(pdev,MIDI_IN_EP);
	USBD_LL_CloseEP(pdev,MIDI_OUT_EP);
	return 0;
}

static uint8_t USBD_MIDI_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum){
#if 0 //Unused for Lr****
		pmidi->pIf_MidiTx((uint8_t *)&USB_Tx_Buffer, USB_Tx_Cnt);	//call MIDI_DataTx()
#endif
	return USBD_OK;
}

static uint8_t	USBD_MIDI_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum)
{

	USBD_MIDI_ItfTypeDef *pmidi = (USBD_MIDI_ItfTypeDef *)(pdev->pUserData);
	uint16_t USB_Rx_Cnt = ((PCD_HandleTypeDef*)pdev->pData)->OUT_ep[epnum].xfer_count;

	pmidi->pIf_MidiRx((uint8_t *)&USB_Rx_Buffer, USB_Rx_Cnt);	//call MIDI_DataRx()

	USBD_LL_PrepareReceive(pdev,MIDI_OUT_EP,(uint8_t*)(USB_Rx_Buffer),MIDI_DATA_OUT_PACKET_SIZE);
	return USBD_OK;
}

static uint8_t *USBD_MIDI_GetCfgDesc (uint16_t *length){
	*length = sizeof (USBD_MIDI_CfgDesc);
	return USBD_MIDI_CfgDesc;
}

uint8_t USBD_MIDI_RegisterInterface(USBD_HandleTypeDef *pdev, USBD_MIDI_ItfTypeDef *fops)
{
	uint8_t ret = USBD_FAIL;

	if(fops != NULL){
		pdev->pUserData= fops;
		ret = USBD_OK;
	}

	return ret;
}
