#include "ice/init.h"
#include "ice/usb.h"
#include "ice/flash.h"
#include "ice/fpga.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/spi.h"

static void init_rgb_led(void)
{
    gpio_init(ICE_LED_RED_PIN);
    gpio_init(ICE_LED_GREEN_PIN);
    gpio_init(ICE_LED_BLUE_PIN);
    gpio_set_dir(ICE_LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(ICE_LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(ICE_LED_BLUE_PIN, GPIO_OUT);
    gpio_put(ICE_LED_RED_PIN, false);
    gpio_put(ICE_LED_GREEN_PIN, true);
    gpio_put(ICE_LED_BLUE_PIN, true);
}

/**
 * Call all functions below with default values.
 * No need to call any other initialization function when this is called.
 */
void ice_init(void)
{
    init_rgb_led();
    ice_usb_init();
    ice_fpga_init();
    sleep_ms(100); // @TBD: Why is there a delay here?
    ice_flash_init();
}
