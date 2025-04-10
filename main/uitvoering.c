#include "./include/uitvoering.h"



static int status = 0;

void led_config(){
    gpio_config_t config ={
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pin_bit_mask = 1ULL << 47 | 1ULL << 48 | 1ULL << 45 | 1ULL << 0 | 
                        1ULL << 35 | 1ULL << 36 | 1ULL << 37 | 1ULL << 38,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&config);
    status = 1;
    led_all_off();
}



void led_blink(){
    if(status == 0){led_config();}
    led_all_off();

    for (int i = 0; i < 10; i++)
    {
        gpio_set_level(47, !gpio_get_level(47));
        gpio_set_level(48, !gpio_get_level(48));
        gpio_set_level(45, !gpio_get_level(45));
        gpio_set_level(0, !gpio_get_level(0));
        gpio_set_level(35, !gpio_get_level(35));
        gpio_set_level(36, !gpio_get_level(36));
        gpio_set_level(37, !gpio_get_level(37));
        gpio_set_level(38, !gpio_get_level(38));
        vTaskDelay(50);
    }
    led_all_off();
};

void led_test(){
    if(status == 0){led_config();}
    led_all_off();
    for (int i = 3; i < 15; i+=3)
    {
        if(i % 12 == 0){
            gpio_set_level(45, !gpio_get_level(45));
            gpio_set_level(0, !gpio_get_level(0));
            gpio_set_level(35, !gpio_get_level(35));
            gpio_set_level(36, !gpio_get_level(36));
        }
        else if(i % 9 == 0){
            gpio_set_level(48, !gpio_get_level(48));
            gpio_set_level(45, !gpio_get_level(45));
            gpio_set_level(36, !gpio_get_level(36));
            gpio_set_level(37, !gpio_get_level(37));
        }
        else if (i % 6 == 0){
            gpio_set_level(47, !gpio_get_level(47));
            gpio_set_level(48, !gpio_get_level(48));
            gpio_set_level(37, !gpio_get_level(37));
            gpio_set_level(38, !gpio_get_level(38));
            
        }
        else if (i % 3 == 0){
            gpio_set_level(47, !gpio_get_level(47));
            gpio_set_level(38, !gpio_get_level(38));
        }
        vTaskDelay(50);
    }
    led_all_off();
}

void led_all_on(){
    if(status == 0){led_config();}
    gpio_set_level(47, 1);
    gpio_set_level(48, 1);
    gpio_set_level(45, 1);
    gpio_set_level(0, 1);
    gpio_set_level(35, 1);
    gpio_set_level(36, 1);
    gpio_set_level(37, 1);
    gpio_set_level(38, 1);
}

void led_all_off(){
    if(status == 0){led_config();}
    gpio_set_level(47, 0);
    gpio_set_level(48, 0);
    gpio_set_level(45, 0);
    gpio_set_level(0, 0);
    gpio_set_level(35, 0);
    gpio_set_level(36, 0);
    gpio_set_level(37, 0);
    gpio_set_level(38, 0);
}