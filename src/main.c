#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>

#include <libfirmware/serial.h>
#include <libfirmware/math.h>
#include <libfirmware/chip.h>
#include <libfirmware/driver.h>
#include <libfirmware/thread.h>
#include <libfirmware/console.h>
#include <libfirmware/leds.h>
#include <libfirmware/usb.h>
#include <libfirmware/timestamp.h>

struct application {
    led_controller_t leds;
    serial_port_t uart;
};

void vApplicationTaskSWIHook(int task){
	(void)task;
	//swo_sendchar(4, '0'+task);
	//dac_write(&chassis.dac1, 1, task * 500);
	//dac_write(&dac1, 2, task * 100);
}

static void _init(void *ptr){
	probe_device_drivers(_devicetree);

	while(1){
		thread_sleep_ms(1000);
	}
}

int main(void){
    static struct application app;
	struct application *self = &app;
	memset(self, 0, sizeof(*self));

	thread_create(
		  _init,
		  "init",
		  250,
		  &app,
		  2,
		  NULL);

	thread_start_scheduler();

	while(1) {
		thread_sleep_ms(1000);
	}
}

void panic(const char *msg){
	while(1) asm("nop");
}

