#***************************  M a k e f i l e  *******************************
#
#         Author: ap
#          $Date: 2015/10/16 18:09:09 $
#      $Revision: 1.1 $
#
#    Description: Makefile definitions for the Z146 test program
#
#---------------------------------[ History ]---------------------------------
#
#   $Log: program.mak,v $
#   Revision 1.1  2015/10/16 18:09:09  ts
#   Initial Revision
#
#
#-----------------------------------------------------------------------------
#   (c) Copyright 2000 by MEN mikro elektronik GmbH, Nuernberg, Germany
#*****************************************************************************

MAK_NAME=z146_12KHz_test

MAK_LIBS=$(LIB_PREFIX)$(MEN_LIB_DIR)/mdis_api$(LIB_SUFFIX)	\
			$(LIB_PREFIX)$(MEN_LIB_DIR)/usr_oss$(LIB_SUFFIX)	\

MAK_INCL=$(MEN_INC_DIR)/z146_drv.h	\
         $(MEN_INC_DIR)/men_typs.h	\
         $(MEN_INC_DIR)/mdis_api.h	\
         $(MEN_INC_DIR)/usr_oss.h	\

MAK_INP1=z146_12KHz_test$(INP_SUFFIX)

MAK_INP=$(MAK_INP1)
 
 
