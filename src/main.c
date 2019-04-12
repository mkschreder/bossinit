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

int _close (int fd){
	printk("close\n");
	return 0;
}
/*
int _fstat (int fd, struct stat * buf){
	printk("fstat\n");
}
*/
int _isatty (int fd){
	printk("isatty\n");
	return 0;
}
off_t _lseek (int fd, off_t offset, int whence){
	printk("seek\n");
	return 0;
}
int _open (const char * pathname, int flags){
	printk("open\n");
	return 123;
}
ssize_t _read (int fd, void * buf, size_t count){
	printk("read %d", fd);
	return 1;
}
ssize_t _write (int fd, const void * buf, size_t count){
	printk("write %d\n", fd);
	return 1;
}
void * _sbrk (ptrdiff_t increment){
	printk("sbrk %d\n", (int)increment);
	return kzmalloc((size_t)increment);
}

int main(void){
    static struct application app;
	struct application *self = &app;
	memset(self, 0, sizeof(*self));

	thread_create(
		  _init,
		  "init",
		  350,
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

