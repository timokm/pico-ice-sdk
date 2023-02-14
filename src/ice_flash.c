#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/structs/spi.h"
#include "boards/pico_ice.h"
#include "ice_spi.h"
#include "ice_flash.h"

#define FLASH_CMD_PROGRAM_PAGE       0x02
#define FLASH_CMD_READ               0x03
#define FLASH_CMD_ENABLE_WRITE       0x06
#define FLASH_CMD_STATUS             0x05
#define FLASH_CMD_SECTOR_ERASE       0x20
#define FLASH_CMD_CHIP_ERASE         0xC7
#define FLASH_CMD_RELEASE_POWERDOWN  0xAB
#define FLASH_CMD_POWERDOWN          0xB9

#define FLASH_STATUS_BUSY_MASK       0x01

void ice_flash_init(void)
{
    // Setup the CSN pin to GPIO mode for software control
    gpio_init(ICE_FLASH_SPI_CSN_PIN);
    gpio_put(ICE_FLASH_SPI_CSN_PIN, true);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_OUT);

    // Flash might be asleep as a successful FPGA boot will put it to sleep as the last command!
    ice_flash_wakeup();
}

void ice_flash_enable_write(void)
{
    uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };

    ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);
}

static void ice_flash_wait(void)
{
    uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
    uint8_t buf[2];

    do {
        ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
        ice_spi_write_blocking(cmds, sizeof(cmds));
        ice_spi_read_blocking(0x00, buf, sizeof(buf));
        ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);
    } while (buf[1] & FLASH_STATUS_BUSY_MASK);
}

void ice_flash_erase_sector(uint32_t addr)
{
    uint8_t cmds[] = { FLASH_CMD_SECTOR_ERASE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_SECTOR_SIZE == 0);

    ice_flash_enable_write();

    ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);

    ice_flash_wait();
}

void ice_flash_program_page(uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE])
{
    uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_PAGE_SIZE == 0);

    ice_flash_enable_write();

    ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_write_blocking(page, ICE_FLASH_PAGE_SIZE);
    ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);

    ice_flash_wait();
}

void ice_flash_read(uint32_t addr, uint8_t *buf, size_t sz)
{
    uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

    ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_read_blocking(0x00, buf, sz);
    ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);
}

void ice_flash_erase_chip(void)
{
    uint8_t cmds[] = { FLASH_CMD_CHIP_ERASE };

    ice_flash_enable_write();

    ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);

    ice_flash_wait();
}

void ice_flash_wakeup(void)
{
    uint8_t cmds[] = { FLASH_CMD_RELEASE_POWERDOWN };

    ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);

    ice_flash_wait();
}

void ice_flash_sleep(void)
{
    uint8_t cmds[] = { FLASH_CMD_POWERDOWN };

    ice_spi_chip_select(ICE_FLASH_SPI_CSN_PIN);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(ICE_FLASH_SPI_CSN_PIN);

    ice_flash_wait();
}