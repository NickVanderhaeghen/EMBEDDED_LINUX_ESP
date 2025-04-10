#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#pragma once



void led_config();

void led_blink(); //gaat de leds 5X laten blinken

void led_test();

void led_all_on();

void led_all_off();