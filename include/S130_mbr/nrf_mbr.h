/*
 * Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
/**
  @defgroup nrf_mbr_api Master Boot Record API
  @{
     
  @brief APIs for updating SoftDevice and BootLoader
 
*/

/* Header guard */
#ifndef NRF_MBR_H__
#define NRF_MBR_H__


/** @addtogroup NRF_MBR_DEFINES Defines
 * @{ */

/**@brief MBR SVC Base number. */
#define MBR_SVC_BASE 0x18   
/** @} */

#ifndef ASSEMBLER_PREPROC__     // This region is removed when run from assembler preprocessing 
                                // (everything above this is used in assembler files and shall not contain anything C specific)
#include "nrf_svc.h"
#include <stdint.h>

/** @addtogroup NRF_MBR_ENUMS Enumerations
 * @{ */

/**@brief nRF Master Boot Record API SVC numbers. */
enum NRF_MBR_SVCS
{
  SD_MBR_COMMAND = MBR_SVC_BASE, /**< ::sd_mbr_command */
};

/**@brief Possible values for ::sd_mbr_command_t.command */
enum NRF_MBR_COMMANDS
{
  SD_MBR_COMMAND_COPY_BL,  /**< Copy a new a new BootLoader. @see sd_mbr_command_copy_bl_t */
  SD_MBR_COMMAND_COPY,     /**< Copy a new SoftDevice. @see ::sd_mbr_command_copy_t*/
  SD_MBR_START_SD,         /**< Start forwarding interrupts to SD, and run resetfunction in SD*/
  SD_MBR_COMMAND_VERIFY,   /**< This command works like memcmp. @see ::sd_mbr_command_verify_t*/
};

/** @} */

/** @addtogroup NRF_MBR_TYPES Types
 * @{ */

/**@brief This command copies part of a new SoftDevice
 * The destination area is erased before copying. 
 * 
 * The user of this function is responsible for setting the PROTENSET registers.
 * 
 * @retval ::NRF_SUCCESS indicates that the contents of the memory blocks where copied correctly.
 * @retval ::NRF_ERROR_INTERNAL indicates that the contents of the memory blocks where not verified correctly after copying.
 */
typedef struct
{
  uint32_t *src;  /**< Pointer to the source of data to be copied.*/
  uint32_t *dst;  /**< Pointer to the destination where the content is to be copied.*/
  uint32_t len;   /**< Number of 32 bit words to copy. Must be a multiple of 256 words*/
}sd_mbr_command_copy_t;


/**@brief This command works like memcmp, but takes the length in words.
 *
 * @retval ::NRF_SUCCESS indicates that the contents of both memory blocks are equal.
 * @retval ::NRF_ERROR_NULL indicates that the contents of the memory blocks are not equal.
 */
typedef struct
{
  uint32_t *ptr1; /**< Pointer to block of memory */
  uint32_t *ptr2; /**< Pointer to block of memory */
  uint32_t len;   /**< Number of 32 bit words to compare*/
}sd_mbr_command_verify_t;


/**@brief This command copies a new BootLoader.
 *  With this command, destination of BootLoader is always the address written in NRF_UICR->BOOTADDR.
 *
 *  Destination is erased by this function.
 *
 *  This function will use PROTENSET to protect the flash that is not intended to be written.
 * 
 *  On Success, this function will not return. It will start the new BootLoader from reset-vector as normal.
 *
 * @retval ::NRF_ERROR_INVALID_STATE indicates that something was wrong.
 * @retval ::NRF_ERROR_INTERNAL indicates an internal error that should not happen.
 * @retval ::NRF_ERROR_FORBIDDEN if NRF_UICR->BOOTADDR is not set
 * @retval ::NRF_ERROR_INVALID_LENGTH is invalid.
 */
typedef struct
{
  uint32_t   *bl_src;  /**< Pointer to the source of the Bootloader to be be copied.*/
  uint32_t   bl_len;   /**< Number of 32 bit words to copy for BootLoader */
}sd_mbr_command_copy_bl_t;

typedef struct
{
  uint32_t command;  /**< type of command to be issued see @ref NRF_MBR_COMMANDS. */
  union 
  {
    sd_mbr_command_copy_t copy;        /**< Parameters for copy*/
    sd_mbr_command_copy_bl_t copy_bl;  /**< Parameters for copy SoftDevice and BootLoader*/
    sd_mbr_command_verify_t verify;    /**< Parameters for verify*/
  } params;
}sd_mbr_command_t;

/** @} */

/** @addtogroup NRF_MBR_FUNCTIONS Functions
 * @{ */

/**@brief Issue Master Boot Record commands
 *
 * Commands used when updating a SoftDevice and bootloader
 *
 * @param[in]  param Pointer to a struct describing the command
 *
 *@note for retvals see ::sd_mbr_command_copy_t ::sd_mbr_command_copy_bl_t ::sd_mbr_command_verify_t

*/
SVCALL(SD_MBR_COMMAND, uint32_t, sd_mbr_command(sd_mbr_command_t* param));

/** @} */
#endif  // ASSEMBLER_PREPROC__
#endif // NRF_MBR_H__

/**
  @}
*/
