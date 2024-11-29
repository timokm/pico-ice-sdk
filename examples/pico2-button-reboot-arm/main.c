#include "pico/stdlib.h"
#include "pico/bootrom.h" //neded for reset_usb_boot
#include "timer.h"
#include "button.h"


#define LED_R_PIN 1
#define LED_G_PIN 0
#define LED_B_PIN 9
#define ICE_CRESET 31
#define BTN_PIN 42
#define ON false
#define OFF true


uint64_t button_push_ts = 0;

void reboot() {
    #define AIRCR_Register (*((volatile uint32_t*)(PPB_BASE + 0x0ED0C)))
    AIRCR_Register = 0x5FA0004;    
}

void setup_pin(uint pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, OFF);     
}

void blink(uint pin, int times)
{
    for(int idx=0; idx<times; idx++)
    {
        timer_sleep_ms(50);
        gpio_put(pin, ON);
        timer_sleep_ms(70);
        gpio_put(pin, OFF);
    }  
}

void onchange(button_t *button_p) 
{
    button_t *button = (button_t*)button_p;
    uint64_t at = 0;

    //printf("Button on pin %d changed its state to %d\n", button->pin, button->state);
    switch(button->pin)
    {
        case BTN_PIN:
            //printf("Reboot\n");
            int state = button->state;
            if(button->state == 0)
            {
                at = get_absolute_time();
                button_push_ts = to_us_since_boot(at);
                gpio_put(LED_R_PIN, ON);
            }
            else
            {
                at = get_absolute_time();
                uint64_t elapse_time = to_us_since_boot(at) - button_push_ts;
                gpio_put(LED_R_PIN, OFF);
                if (elapse_time > 1200000) //miliseconds
                {
                    blink(LED_R_PIN,9);
                    reset_usb_boot(0,0);
                }
                else if (elapse_time > 400000) //miliseconds
                {
                    blink(LED_R_PIN,1);
                    reboot(0,0);
                }
                else
                {
                    gpio_put(LED_R_PIN, OFF);  
                }
            }
        break;
    }
}

int main() {
    //stdio_init_all();

    //creset
    setup_pin(ICE_CRESET);

    //setup LED pin
    setup_pin(LED_R_PIN);
    setup_pin(LED_G_PIN);
    setup_pin(LED_B_PIN);

    blink(LED_R_PIN,3);



    //setup BUTTON PIN   
    //gpio_disable_pulls(BTN_PIN);
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    //gpio_disable_pulls(BTN_PIN);

    button_t *play_button = create_button(BTN_PIN, onchange);

    while (true) {
            //do something
    }
}