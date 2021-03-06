/***************************************************************************//**
 * @file
 * @brief Routines for finding and joining any viable network via scanning, rather
 * than joining a specific network.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef NETWORK_FIND_DOT_H_INCLUDED
#define NETWORK_FIND_DOT_H_INCLUDED

#include "app/framework/include/af.h"

/** @brief Sets the channel mask for "find unused" and "find joinable".
 * Permitted pages are 0 and, if Sub-GHz channels are included, then also 28-31.
 */
EmberStatus emberAfSetFormAndJoinChannelMask(uint8_t page, uint32_t mask);

/** @brief Returns the channel mask for a given page.
 * Only the bottom 27 bits can be set. The top 5 bits are reserved for the page
 * number and are always zero in a returned channel mask. That leaves the value
 * 0xFFFFFFFF free to indicate an invalid page error.
 */
uint32_t emberAfGetFormAndJoinChannelMask(uint8_t page);

/** @brief Sets search mode for "find unused" and "find joinable".
 * Mode is a bitmask. Permitted values are set by the FIND_AND_JOIN_MODE_...
 * macros.
 */
EmberStatus emberAfSetFormAndJoinSearchMode(uint8_t mode);

/** @brief Returns the current search mode.
 */
uint8_t emberAfGetFormAndJoinSearchMode(void);

//------------------------------------------------------------------------------
// Application Framework Internal Functions
//
// The functions below are non-public internal function used by the application
// framework. They are NOT to be used by the application.

/** @brief Is the search for an unused network currently in progress scanning
 *         all channels?
 * @return true if yes, false if the current scan is on preferred channels only
 */
bool emAfIsCurrentSearchForUnusedNetworkScanningAllChannels(void);

/** @brief Returns the channel mask for the current scan.
 * Similar to emberAfGetFormAndJoinChannelMask(), but may return the configured
 * channel mask or all channels mask, depending on the current scan state.
 */
uint32_t emAfGetSearchForUnusedNetworkChannelMask(uint8_t page);

#ifdef EMBER_AF_PLUGIN_NETWORK_FIND_SUB_GHZ
/** @brief Secondary interface formed callback.
 * Called after forming the network to notify the plugin that the secondary
 * interface (in case of a dual-PHY implementation) has been formed. It is used
 * by the plugin to reset its internal state. Strictly for internal use only.
 */
void emAfSecondaryInterfaceFormedCallback(EmberStatus status);
#endif

#endif // NETWORK_FIND_DOT_H_INCLUDED
