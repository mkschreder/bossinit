bin_PROGRAMS = theboss
theboss_SOURCES=fault.c main.c devicetree.c
theboss_LDFLAGS=-Wl,--no-undefined -Wl,-Map,theboss.map
theboss_LDADD=$(WITH_LIBS) -ldriver -lfirmware -lfdt -lm

if WITH_TARGET_LINUX
theboss_LDADD+=-lrt -lpthread
theboss_LDFLAGS+=-Wl,-u,linux_uart_ko,-u,linux_leds_ko
else
theboss_LDFLAGS+=-Wl,-u,stm32_uart_ko,-u,stm32_leds_ko,-u,stm32_gpio_ko,-u,stm32_cpu_ko
endif

if WITH_TARGET_STM32F429ZET6
theboss_SOURCES+=target/stm32f4xx/startup_stm32f429_439xx.s
theboss_LDFLAGS+=-T$(srcdir)/target/stm32f4xx/stm32f429zet6.ld
endif

if WITH_TARGET_STM32F40_41XXX
theboss_SOURCES+=target/stm32f4xx/startup_stm32f40_41xxx.s
theboss_LDFLAGS+=-T$(srcdir)/target/stm32f4xx/stm32f413_320K_1M.ld
endif

if WITH_TARGET_STM32F10X
theboss_SOURCES+=target/stm32f10x/startup_stm32f10x.s
theboss_LDFLAGS+=-T$(srcdir)/target/stm32f10x/stm32f10x_128k.ld
endif

theboss_LDFLAGS+=$(WITH_DRIVERS)

AUTOMAKE_OPTIONS = subdir-objects

devicetree.c: $(WITH_DEVICETREE) 
	@echo "DTB: $(1)"
	$(Q)$(CPP) $(CFLAGS) -nostdinc -undef -x assembler-with-cpp $^ > $@.dtspp && dtc -O dtb $@.dtspp -o $@.dtb
	$(Q)echo "unsigned char _devicetree[] = { $$(cat $@.dtb | xxd -i) };" > $@

.PHONY: theboss
