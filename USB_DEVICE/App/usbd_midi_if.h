/**
  ******************************************************************************
  * @file	usbd_midi_if.h
  * @brief	Header for usbd_midi_if file.
  * @author modified by remov-b4-flight
  * @copyright  original copyright below
  ******************************************************************************
    (CC at)2016 by D.F.Mac. @@TripArts Music
  ******************************************************************************

    Modified by keshikan (www.keshikan.net) 2018
    The license is (CC BY 4.0), and takes over from original usbd_midi_if.h/c.

    See also original source code page.
    https://github.com/mimuz/mimuz-tuch/blob/master/STM32/

  ******************************************************************************
*/

#ifndef __USBD_MIDI_IF_H
#define __USBD_MIDI_IF_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "usbd_midi.h"
#include "usbd_desc.h"
#include <stdbool.h>

extern USBD_MIDI_ItfTypeDef  USBD_Interface_fops_FS;

#ifdef __cplusplus
}
#endif
  
#endif /* __USBD_MIDI_IF_H */
