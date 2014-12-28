/*
 * rfid.h
 *
 *  Created on: 06.09.2013
 *      Author: alexs
 */

#ifndef RFID_H_
#define RFID_H_

#include <string.h>
#include "rc522.h"
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    tag_stat find_tag(uint16_t *);
    tag_stat select_tag_sn(uint8_t * sn, uint8_t * len);
    tag_stat read_tag_str(uint8_t addr, char * str);
#ifdef __cplusplus
}
#endif

#endif /* RFID_H_ */
