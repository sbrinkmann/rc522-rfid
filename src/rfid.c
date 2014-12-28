/*
 * rfid.c
 *
 *  Created on: 06.09.2013
 *      Author: alexs
 */
#include "rfid.h"



uint8_t buff[MAXRLEN];


tag_stat find_tag(uint16_t * card_type) {
	tag_stat tmp;
	if ((tmp=PcdRequest(PICC_REQIDL,buff))==TAG_OK) {
		*card_type=(int)(buff[0]<<8|buff[1]);
	}
	return tmp;
}

tag_stat select_tag_sn(uint8_t * sn, uint8_t * len){

	if (PcdAnticoll(PICC_ANTICOLL1,buff)!=TAG_OK) {return TAG_ERR;}
	if (PcdSelect(PICC_ANTICOLL1,buff)!=TAG_OK) {return TAG_ERR;}
	if (buff[0]==0x88) {
		memcpy(sn,&buff[1],3);
		if (PcdAnticoll(PICC_ANTICOLL2,buff)!=TAG_OK) {
			return TAG_ERR;}
		if (PcdSelect(PICC_ANTICOLL2,buff)!=TAG_OK) {return TAG_ERR;}
		if (buff[0]==0x88) {
			memcpy(sn+3,&buff[1],3);
			if (PcdAnticoll(PICC_ANTICOLL3,buff)!=TAG_OK) {
				return TAG_ERR;}
			if (PcdSelect(PICC_ANTICOLL3,buff)!=TAG_OK) {return TAG_ERR;}
			memcpy(sn+6,buff,4);
			*len=10;
		}else{
			memcpy(sn+3,buff,4);
			*len=7;
		}
	}else{
		memcpy(sn,&buff[0],4);
		*len=4;
	}
	return TAG_OK;
}

tag_stat read_tag_str(uint8_t addr, char * str) {
	tag_stat tmp;
	char *p;
	uint8_t i;

	uint8_t buff[MAXRLEN];

	tmp=PcdRead(addr,buff);
	p=str;
	if (tmp==TAG_OK) {
		for (i=0;i<16;i++) {
			sprintf(p,"%02x",(char)buff[i]);
			p+=2;
		}
	}else if (tmp==TAG_ERRCRC){
		sprintf(p,"CRC Error");
	}else{
		sprintf(p,"Unknown error");
	}
	return tmp;
}


