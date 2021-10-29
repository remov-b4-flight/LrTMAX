/**
  ******************************************************************************
  * @file    usbd_midi.c
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

static uint8_t  USBD_MIDI_Init (USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t  USBD_MIDI_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t  USBD_MIDI_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t  USBD_MIDI_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  *USBD_MIDI_GetCfgDesc (uint16_t *length);
//uint8_t  *USBD_MIDI_GetDeviceQualifierDescriptor (uint16_t *length);
USBD_HandleTypeDef *pInstance = NULL; 
#if 0 //Unused for Lr****
uint32_t APP_Rx_ptr_in  = 0;
uint32_t APP_Rx_ptr_out = 0;
uint32_t APP_Rx_length  = 0;
uint8_t  USB_Tx_State = 0;
__ALIGN_BEGIN uint8_t APP_Rx_Buffer[APP_RX_DATA_SIZE] __ALIGN_END ;
#endif

__ALIGN_BEGIN uint8_t USB_Rx_Buffer[MIDI_DATA_OUT_PACKET_SIZE] __ALIGN_END ;

/* USB Standard Device Descriptor */
/*
__ALIGN_BEGIN static uint8_t USBD_MIDI_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};
*/

/* USB MIDI interface class callbacks structure */
USBD_ClassTypeDef  USBD_MIDI = 
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
__ALIGN_BEGIN uint8_t USBD_MIDI_CfgDesc[USB_MIDI_CONFIG_DESC_SIZ] __ALIGN_END =
{
  // configuration descriptor
  0x09, CONFIG, 0x53, 0x00, 0x01, CONFIG1, 0x00, BUSPOWERED, MIDI_POWER,

  // The Audio Interface Collection
  0x09, INTERFACE	, INTF0,  0x00, 0x02, AUDIO, MIDI_STREAM, MIDI_UNUSED, MIDI_UNUSED,	// MIDIStreaming Interface Descriptors
  0x07, CS_INTERFACE, HEADER, 0x00, 0x01, 0x41, 0x00,   								// Class-Specific MS Interface Header Descriptor

  // MIDI IN JACKS
  0x06, CS_INTERFACE, MIDI_IN_JACK, MIDI_JACK_ENB, 0x01, 3,//MIDI-IN 1 (embedded)
  0x06, CS_INTERFACE, MIDI_IN_JACK, MIDI_JACK_EXT, 0x02, MIDI_UNUSED,//MIDI-IN 1 (external)
  // MIDI OUT JACKS
  0x09, CS_INTERFACE, MIDI_OUT_JACK, MIDI_JACK_ENB, 0x03, 0x01, 0x02, 0x01, 0x04,//MIDI-OUT 1 (embedded)
  0x09, CS_INTERFACE, MIDI_OUT_JACK, MIDI_JACK_EXT, 0x04, 0x01, 0x01, 0x01, MIDI_UNUSED,//MIDI-OUT 1 (external)

  // IN endpoint descriptor
  0x09, ENDPOINT, MIDI_IN_EP, 0x02, 0x40, 0x00, 0x01, MIDI_UNUSED, MIDI_UNUSED,
  0x05, CS_ENDPOINT, MS_GENERAL, 0x01, 0x03,
  // OUT endpoint descriptor
  0x09, ENDPOINT, MIDI_OUT_EP, 0x02, 0x40, 0x00, 0x01, MIDI_UNUSED, MIDI_UNUSED,
  0x05, CS_ENDPOINT, MS_GENERAL, 0x01, 0x01,
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
  if (USB_Tx_State == 1){
    USB_Tx_State = 0;
  }
#endif
  return USBD_OK;
}

static uint8_t  USBD_MIDI_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum)
{      
  uint16_t USB_Rx_Cnt;

  USBD_MIDI_ItfTypeDef *pmidi;
  pmidi = (USBD_MIDI_ItfTypeDef *)(pdev->pUserData);

  USB_Rx_Cnt = ((PCD_HandleTypeDef*)pdev->pData)->OUT_ep[epnum].xfer_count;

  pmidi->pIf_MidiRx((uint8_t *)&USB_Rx_Buffer, USB_Rx_Cnt);	//call MIDI_DataRx()

  USBD_LL_PrepareReceive(pdev,MIDI_OUT_EP,(uint8_t*)(USB_Rx_Buffer),MIDI_DATA_OUT_PACKET_SIZE);
  return USBD_OK;
}
#if 0 //Unused for Lr****
void USBD_MIDI_SendPacket (){
  uint16_t USB_Tx_ptr;
  uint16_t USB_Tx_length;

  if(USB_Tx_State != 1){
    if (APP_Rx_ptr_out == APP_RX_DATA_SIZE){
      APP_Rx_ptr_out = 0;
    }

    if(APP_Rx_ptr_out == APP_Rx_ptr_in){
      USB_Tx_State = 0;
      return;
    }

    if(APP_Rx_ptr_out > APP_Rx_ptr_in){
      APP_Rx_length = APP_RX_DATA_SIZE - APP_Rx_ptr_out;
    }else{
      APP_Rx_length = APP_Rx_ptr_in - APP_Rx_ptr_out;
    }

    if (APP_Rx_length > MIDI_DATA_IN_PACKET_SIZE){
      USB_Tx_ptr = APP_Rx_ptr_out;
      USB_Tx_length = MIDI_DATA_IN_PACKET_SIZE;
      APP_Rx_ptr_out += MIDI_DATA_IN_PACKET_SIZE;
      APP_Rx_length -= MIDI_DATA_IN_PACKET_SIZE;
    }else{
      USB_Tx_ptr = APP_Rx_ptr_out;
      USB_Tx_length = APP_Rx_length;
      APP_Rx_ptr_out += APP_Rx_length;
      APP_Rx_length = 0;
    }
    USB_Tx_State = 1;
    USBD_LL_Transmit (pInstance, MIDI_IN_EP,(uint8_t*)&APP_Rx_Buffer[USB_Tx_ptr],USB_Tx_length);
  }
}
#endif
static uint8_t *USBD_MIDI_GetCfgDesc (uint16_t *length){
  *length = sizeof (USBD_MIDI_CfgDesc);
  return USBD_MIDI_CfgDesc;
}

//uint8_t *USBD_MIDI_GetDeviceQualifierDescriptor (uint16_t *length){
//  *length = sizeof (USBD_MIDI_DeviceQualifierDesc);
//  return USBD_MIDI_DeviceQualifierDesc;
//}

uint8_t USBD_MIDI_RegisterInterface(USBD_HandleTypeDef *pdev, USBD_MIDI_ItfTypeDef *fops)
{
  uint8_t ret = USBD_FAIL;
  
  if(fops != NULL){
    pdev->pUserData= fops;
    ret = USBD_OK;    
  }
  
  return ret;
}
