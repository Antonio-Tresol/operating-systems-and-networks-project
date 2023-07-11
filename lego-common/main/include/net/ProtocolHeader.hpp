#pragma once

#include <errno.h>  // For Error Codes

/*---------------------------Broadcast Address--------------------------------*/

#define BROADCAST_ADDR_PREFIX "172.16.123."
#define BROADCAST_ADDR_INCREMENT 16
#define BROADCAST_ADDR_START 15

/*---------------------------------Ports--------------------------------------*/

#define INTERMEDIARY_UDP_PORT 3141  /**< Intermediary Server UDP Port */
#define INTERMEDIARY_TCP_PORT 3142  /**< Intermediary Server TCP Port */

#define PIECES_UDP_PORT 4849  /**< Pieces Server UDP Port */
#define PIECES_TCP_PORT 4850  /**< Pieces Server UDP Port */

/*--------------------------------Timeouts------------------------------------*/

#define FIRST_TIMEOUT 100  /**< First timeout: miliseconds */
#define SECOND_TIMEOUT 200 /**< Second timeout: miliseconds*/
#define THIRD_TIMEOUT 300  /**< Third timeout: miliseconds*/

/*-----------------------------Separator char---------------------------------*/

#define SEPARATOR char(29)  /**< Protocol message separator */

/*-----------------------Socket Connection Refused Error----------------------*/

#define CONNECTION_REFUSED_ERROR ECONNREFUSED /**< From errno ECONNREFUSED */

/*----------------------------Message code enum-------------------------------*/

/**
 * @brief Enum LegoMessageCode
 * @details Defines the protocol types of messages
 * 
 */
enum LegoMessageCode {
  LEGO_DISCOVER,  /**< LEGO_DISCOVER type */
  LEGO_PRESENT,   /**< LEGO_PRESENT type */
  LEGO_REQUEST,   /**< LEGO_REQUEST type */
  LEGO_RESPONSE,  /**< LEGO_RESPONSE type */
  LEGO_RELEASE    /**< LEGO_RELEASE type */
};  // LegoMessageCode