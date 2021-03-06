/****************************************************************************
 ************                                                    ************
 ************                   Z146_MP70S_TEST                  ************
 ************                                                    ************
 ****************************************************************************/
/*!
 *         \file z146_mp70s_test.c
 *       \author zhou
 *        $Date: 2016/11/28 15:55:17 $
 *    $Revision: 1.2 $
 *
 *       \brief  Test program for Z146 at MP70S
 *
 *     Required: libraries: mdis_api, usr_oss
 *     \switches (none)
 */
/*-------------------------------[ History ]--------------------------------
 *
 * $Log: z146_mp70s_test.c,v $
 * Revision 1.2  2016/11/28 15:55:17  atlbitbucket
 * Stash autocheckin
 *
 *---------------------------------------------------------------------------
 * (c) Copyright 2003 by MEN mikro elektronik GmbH, Nuernberg, Germany
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <MEN/men_typs.h>
#include <MEN/mdis_api.h>
#include <MEN/usr_oss.h>
#include <MEN/z146_drv.h>
#include <MEN/z246_drv.h>

/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/
#define MAX_DATA_LEN 	4096

/*--------------------------------------+
|   PROTOTYPES                          |
+--------------------------------------*/
static void PrintError(char *info);

/********************************* main ************************************/
/** Program main function
 *
 *  \param argc       \IN  argument counter
 *  \param argv       \IN  argument vector
 *
 *  \return	          success (0) or error (1)
 */
int main(int argc, char *argv[])
{
	MDIS_PATH rxPath1, rxPath2, rxPath3, rxPath4, rxPath5, rxPath6;
	MDIS_PATH txPath;
	char	*rxDevice1 = NULL;
	char	*rxDevice2 = NULL;
	char	*rxDevice3 = NULL;
	char	*rxDevice4 = NULL;
	char	*txDevice = NULL;
	int32 result = 0;
	int i = 0;
	u_int32 label = 1;
	u_int32 n, dataLen = 0;
	u_int32 txDataArray[MAX_DATA_LEN];
	u_int32 rxDataArray[MAX_DATA_LEN];

	if (argc < 2 || strcmp(argv[1],"-?")==0) {
		printf("Syntax: z146_mp70s_test  <txDevice> <rxDevice_1> [<rxDevice_2> <rxDevice_3> <rxDevice_4>]\n");
		printf("Function: Test program for Z146 at MP70S\n");
		printf("\n");
		return(1);
	}

	txDevice = argv[1];
	rxDevice1 = argv[2];
	if(argc >= 4){
		rxDevice2 = argv[3];
	}
	if(argc >= 5){
		rxDevice3 = argv[4];
	}
	if(argc >= 6){
		rxDevice4 = argv[5];
	}

	/*--------------------+
	|  open               |
	+--------------------*/
	if ((rxPath1 = M_open(rxDevice1)) < 0) {
		PrintError("open");
		return(1);
	} else {
		M_setstat(rxPath1, Z146_RX_SET_LABEL, label);
	}
	if (rxDevice2 != NULL) {
		if ((rxPath2 = M_open(rxDevice2)) < 0) {
			PrintError("open");
			return(1);
		} else {
			M_setstat(rxPath2, Z146_RX_SET_LABEL, label);
		}
	}
	if (rxDevice3 != NULL) {
		if ((rxPath3 = M_open(rxDevice3)) < 0) {
			PrintError("open");
			return(1);
		}else {
			M_setstat(rxPath3, Z146_RX_SET_LABEL, label);
		}
	}
	if (rxDevice4 != NULL) {
		if ((rxPath4 = M_open(rxDevice4)) < 0) {
			PrintError("open");
			return(1);
		}else {
			M_setstat(rxPath4, Z146_RX_SET_LABEL, label);
		}
	}

	/* open TX path */
	if ((txPath = M_open(txDevice)) < 0) {
		PrintError("open");
		return(1);
	} else {
		M_setstat(txPath, Z246_TX_LABEL, label);
	}

	/*--------------------+
	|  config             |
	+--------------------*/
	printf("############# Transmit-1 ###############\n");
	dataLen   = 4;
	printf("User data length = %ld and dataptr = 0x%lx\n", dataLen *4, txDataArray);
	for(n=0;n<dataLen;n++){
		txDataArray[n] = n + 7;
		printf(" 0x%lx", txDataArray[i]);
	}
	printf("\n");
	printf("\n");
	result = M_setblock(txPath, (u_int8*)txDataArray, (dataLen * 4));
	if(result > 0){
		printf("Transmitted %ld bytes successfully\n", dataLen *4);
	}else{
		printf("Write failed with result %ld\n", result);
	}
	printf("--------------------------------\n");
	printf("\n");
	printf("\n");
	UOS_Delay(1000);

	result = M_getblock( rxPath1, (u_int8*)rxDataArray, (dataLen * 4)); 
	if(result > 0){
		printf("############# Receive-1 ###############\n");
		printf("Receiving = %ld bytes data\n", result);
		for(i=0;i<result/4;i++){
			printf(" 0x%lx", rxDataArray[i]);
			if(txDataArray[i] != ((rxDataArray[i] >> 8) & 0x7FFFFF)){
				printf("\nExpected txDataArray[%d] = 0x%lx but received rxDataArray[%d] = 0x%lx\n",
					i, txDataArray[i], i, ((rxDataArray[i] >> 8) & 0x7FFFFF));
			}
			rxDataArray[i] = 0;
		}
		printf("\n");
		printf("\n");
		printf("Received %ld bytes successfully on %s\n", result, rxDevice1);
		printf("--------------------------------\n");
	}else{
		printf("Read failed on %s with the result = %ld\n", rxDevice1, result);
	}
	if (M_close(rxPath1) < 0){
		PrintError("close");
	}


	if (rxDevice2 != NULL) {
		result = M_getblock( rxPath2, (u_int8*)rxDataArray, (dataLen * 4)); 
		if(result > 0){
			printf("############# Receive-2 ###############\n");
			printf("Receiving = %ld bytes data\n", result);
			for(i=0;i<result/4;i++){
				printf(" 0x%lx", rxDataArray[i]);
				if(txDataArray[i] != ((rxDataArray[i] >> 8) & 0x7FFFFF)){
					printf("\nExpected txDataArray[%d] = 0x%lx but received rxDataArray[%d] = 0x%lx\n",
						i, txDataArray[i], i, ((rxDataArray[i] >> 8) & 0x7FFFFF));
				}
				rxDataArray[i] = 0;
			}
			printf("\n");
			printf("\n");
			printf("Received %ld bytes successfully on %s\n", result, rxDevice2);
			printf("--------------------------------\n");
		}else{
			printf("Read failed on %s with the result = %ld\n", rxDevice2, result);
		}
		if (M_close(rxPath2) < 0){
			PrintError("close");
		}
	}


	if (rxDevice3 != NULL) {
		result = M_getblock( rxPath3, (u_int8*)rxDataArray, (dataLen * 4)); 
		if(result > 0){
			printf("############# Receive-3 ###############\n");
			printf("Receiving = %ld bytes data\n", result);
			for(i=0;i<result/4;i++){
				printf(" 0x%lx", rxDataArray[i]);
				if(txDataArray[i] != ((rxDataArray[i] >> 8) & 0x7FFFFF)){
					printf("\nExpected txDataArray[%d] = 0x%lx but received rxDataArray[%d] = 0x%lx\n",
						i, txDataArray[i], i, ((rxDataArray[i] >> 8) & 0x7FFFFF));
				}
				rxDataArray[i] = 0;
			}
			printf("\n");
			printf("\n");
			printf("Received %ld bytes successfully on %s\n", result, rxDevice3);
			printf("--------------------------------\n");
		}else{
			printf("Read failed on %s with the result = %ld\n", rxDevice3, result);
		}
		if (M_close(rxPath3) < 0){
			PrintError("close");
		}
	}


	if (rxDevice4 != NULL) {
		result = M_getblock( rxPath4, (u_int8*)rxDataArray, (dataLen * 4)); 
		if(result > 0){
			printf("############# Receive-4 ###############\n");
			printf("Receiving = %ld bytes data\n", result);
			for(i=0;i<result/4;i++){
				printf(" 0x%lx", rxDataArray[i]);
				if(txDataArray[i] != ((rxDataArray[i] >> 8) & 0x7FFFFF)){
					printf("\nExpected txDataArray[%d] = 0x%lx but received rxDataArray[%d] = 0x%lx\n",
						i, txDataArray[i], i, ((rxDataArray[i] >> 8) & 0x7FFFFF));
				}
				rxDataArray[i] = 0;
			}
			printf("\n");
			printf("\n");
			printf("Received %ld bytes successfully on %s\n", result, rxDevice4);
			printf("--------------------------------\n");
		}else{
			printf("Read failed on %s with the result = %ld\n", rxDevice4, result);
		}
		if (M_close(rxPath4) < 0){
			PrintError("close");
		}
	}

	if (M_close(txPath) < 0){
		PrintError("close");
	}
	return(0);
}

/********************************* PrintError ******************************/
/** Print MDIS error message
 *
 *  \param info       \IN  info string
 */
static void PrintError(char *info)
{
	printf("*** can't %s: %s\n", info, M_errstring(UOS_ErrnoGet()));
}
