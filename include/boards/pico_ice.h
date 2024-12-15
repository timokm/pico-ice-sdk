/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 * Copyright (c) 2023 TinyVision.ai Inc.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef PICO_ICE_H_
#define PICO_ICE_H_
#include "ice40up5k.h"

// For board detection
#ifndef PICO_ICE
#define PICO_ICE            1
#endif
#ifndef PICO_ICE_BOARD_ID
#define PICO_ICE_BOARD_ID    PICO_ICE
#endif
#define PICO_ICE_BOARD_NAME          "pico-ice"

// --- LED ---
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 15
#endif

// --- I2C ---
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 12
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 13
#endif

// --- SPI ---
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 0
#endif
#ifndef PICO_DEFAULT_SPI_SCK_PIN
#define PICO_DEFAULT_SPI_SCK_PIN 18
#endif
#ifndef PICO_DEFAULT_SPI_TX_PIN
#define PICO_DEFAULT_SPI_TX_PIN 19
#endif
#ifndef PICO_DEFAULT_SPI_RX_PIN
#define PICO_DEFAULT_SPI_RX_PIN 16
#endif
#ifndef PICO_DEFAULT_CSN_PIN
#define PICO_DEFAULT_CSN_PIN 17
#endif

// --- FLASH ---
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1
#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (4 * 1024 * 1024)
#endif
#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif
#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 1
#endif
#ifndef PICO_RP2040_B1_SUPPORTED
#define PICO_RP2040_B1_SUPPORTED 0
#endif

// --- BOARD SPECIFIC ---
// LED
#define ICE_LED_RED_PIN 13
#define ICE_LED_GREEN_PIN 12
#define ICE_LED_BLUE_PIN 15
// SPI
#ifndef ICE_SPI_RX_PIN
#define ICE_SPI_RX_PIN 8
#endif
#ifndef ICE_SPI_SCK_PIN
#define ICE_SPI_SCK_PIN 10
#endif
#ifndef ICE_SPI_TX_PIN
#define ICE_SPI_TX_PIN 11
#endif
#ifndef ICE_FLASH_CSN_PIN
#define ICE_FLASH_CSN_PIN 9
#endif
#ifndef ICE_CRAM_CSN_PIN
#define ICE_CRAM_CSN_PIN ICE_FLASH_CSN_PIN
#endif
#ifndef ICE_FPGA_CSN_PIN
#define ICE_FPGA_CSN_PIN ICE_LED_RED_PIN // shared usage
#endif
#ifndef ICE_SRAM_CS_PIN
#define ICE_SRAM_CS_PIN 14 // active-high
#endif
// FLASH
#ifndef ICE_FLASH_SIZE_BYTES
#define ICE_FLASH_SIZE_BYTES (4 * 1024 * 1024)
#endif
// SRAM
#ifndef ICE_SRAM_SIZE_BYTES
#define ICE_SRAM_SIZE_BYTES (8 * 1024 * 1024)
#endif
// MISC
#define ICE_GPOUT_CLOCK_PIN 25
#define ICE_RESET_BUTTON_PIN 28
// ICE40 FPGA (SYSTEM)
#ifndef ICE_FPGA_CLOCK_PIN
#define ICE_FPGA_CLOCK_PIN 24
#endif
#ifndef ICE_FPGA_CDONE_PIN
#define ICE_FPGA_CDONE_PIN 26
#endif
#ifndef ICE_FPGA_CRESET_B_PIN
#define ICE_FPGA_CRESET_B_PIN 27
#endif

#endif
