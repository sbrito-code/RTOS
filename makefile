CHAIN=arm-none-eabi
CFLAGS=-std=gnu99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8
AFLAGS=-mfpu=neon
OBJ=obj/
BIN=bin/
INC=inc/
SRCBOARD=src/board/
SRCIRQ=src/irq/
SRCKERNEL=src/kernel/
SRCSCHEDULER=src/scheduler/
SRCTASKS=src/tasks/
SRCUTILS=src/utils/
LST=lst/

all: $(BIN)bios.bin $(BIN)bios.MLO $(OBJ)bios.elf

$(BIN)bios.bin: $(OBJ)bios.elf
	$(CHAIN)-objcopy -O binary $< $@

#$(CHAIN)-ld --defsym BOOT_START_ADDR=$(START_ADDR) -T td3bbb_memmap.ld $(OBJ)*.o -o $(OBJ)bios.elf -Map $(LST)bios_ld_map.map 
$(OBJ)bios.elf: $(OBJ)startup.o $(OBJ)reset_vector.o $(OBJ)low_level_cpu_access.o $(OBJ)board_init.o $(OBJ)boot_exception_handlers.o $(OBJ)console_utils.o $(OBJ)ddr.o $(OBJ)debug_tools.o $(OBJ)gpio.o $(OBJ)i2c.o $(OBJ)interrupt.o $(OBJ)led.o $(OBJ)main.o $(OBJ)memcopy.o $(OBJ)mmu_config.o $(OBJ)mmu_tools.o $(OBJ)nvic_config.o $(OBJ)nvic_handlers.o $(OBJ)pll.o $(OBJ)os.o $(OBJ)os_timer_isr.o $(OBJ)switch.o $(OBJ)system_utils.o $(OBJ)task0.o $(OBJ)task1.o $(OBJ)task2.o $(OBJ)task3.o $(OBJ)timertick.o $(OBJ)tps65217.o $(OBJ)uart.o
	@echo "Linkeando..."
	mkdir -p obj
	mkdir -p lst
	$(CHAIN)-ld -T td3bbb_memmap.ld $(OBJ)*.o -o $(OBJ)bios.elf -Map $(LST)bios_ld_map.map
	$(CHAIN)-objdump -d $(OBJ)*.o > $(LST)bios.lst
	$(CHAIN)-objdump -D $(OBJ)bios.elf > $(LST)bios.lst
	@echo "Linkeo finalizado!!"
	@echo ""
	@echo "Generando archivos de información: mapa de memoria y simbolos"
	readelf -a $(OBJ)bios.elf > $(LST)bios_readelf.txt

#
# Ensamblado de código assembler
#

# Ensamblamos: startup.s
$(OBJ)startup.o: $(SRCKERNEL)startup.s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst
	@echo "Ensamblando startup.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRCKERNEL)startup.s -o $(OBJ)startup.o -a > $(LST)startup.lst

# Ensamblamos: reset_vector.s
$(OBJ)reset_vector.o: $(SRCKERNEL)reset_vector.s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Ensamblando reset_vector.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRCKERNEL)reset_vector.s -o $(OBJ)reset_vector.o -a > $(LST)reset_vector.lst

# Ensamblamos: low_level_cpu_access.s
$(OBJ)low_level_cpu_access.o: $(SRCUTILS)low_level_cpu_access.s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Ensamblando low_level_cpu_access.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRCUTILS)low_level_cpu_access.s -o $(OBJ)low_level_cpu_access.o -a > $(LST)low_level_cpu_access.lst

#
# Compìlación de código C
#

# Compilamos: board_init.c
$(OBJ)board_init.o: $(SRCKERNEL)board_init.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando board_init.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCKERNEL)board_init.c -o $(OBJ)board_init.o

# Compilamos: boot_exception_handlers.c
$(OBJ)boot_exception_handlers.o: $(SRCIRQ)boot_exception_handlers.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando boot_exception_handlers.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCIRQ)boot_exception_handlers.c -o $(OBJ)boot_exception_handlers.o

# Compilamos: console_utils.c
$(OBJ)console_utils.o: $(SRCUTILS)console_utils.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando console_utils.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCUTILS)console_utils.c -o $(OBJ)console_utils.o

# Compilamos: ddr.c
$(OBJ)ddr.o: $(SRCBOARD)ddr.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando ddr.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)ddr.c -o $(OBJ)ddr.o

# Compilamos: debug_tools.c
$(OBJ)debug_tools.o: $(SRCUTILS)debug_tools.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando debug_tools.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCUTILS)debug_tools.c -o $(OBJ)debug_tools.o

# Compilamos: gpio.c
$(OBJ)gpio.o: $(SRCBOARD)gpio.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando gpio.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)gpio.c -o $(OBJ)gpio.o

# Compilamos: i2c.c
$(OBJ)i2c.o: $(SRCBOARD)i2c.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando i2c.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)i2c.c -o $(OBJ)i2c.o

# Compilamos: interrupt.c
$(OBJ)interrupt.o: $(SRCIRQ)interrupt.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando interrupt.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCIRQ)interrupt.c -o $(OBJ)interrupt.o

# Compilamos: led.c
$(OBJ)led.o: $(SRCBOARD)led.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando led.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)led.c -o $(OBJ)led.o

# Compilamos: main.c
$(OBJ)main.o: $(SRCKERNEL)main.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando main.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCKERNEL)main.c -o $(OBJ)main.o

# Compilamos: memcopy.c
$(OBJ)memcopy.o: $(SRCUTILS)memcopy.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando memcopy.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCUTILS)memcopy.c -o $(OBJ)memcopy.o

# Compilamos: mmu_config.c
$(OBJ)mmu_config.o: $(SRCUTILS)mmu_config.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando mmu_config.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCUTILS)mmu_config.c -o $(OBJ)mmu_config.o

# Compilamos: mmu_tools.c
$(OBJ)mmu_tools.o: $(SRCUTILS)mmu_tools.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando mmu_tools.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCUTILS)mmu_tools.c -o $(OBJ)mmu_tools.o

# Compilamos: nvic_config.c
$(OBJ)nvic_config.o: $(SRCIRQ)nvic_config.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando nvic_config.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCIRQ)nvic_config.c -o $(OBJ)nvic_config.o

# Compilamos: nvic_handlers.c
$(OBJ)nvic_handlers.o: $(SRCIRQ)nvic_handlers.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando nvic_handlers.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCIRQ)nvic_handlers.c -o $(OBJ)nvic_handlers.o

# Compilamos: os.c
$(OBJ)os.o: $(SRCSCHEDULER)os.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando os.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCSCHEDULER)os.c -o $(OBJ)os.o

# Compilamos: os_timer_isr.c
$(OBJ)os_timer_isr.o: $(SRCSCHEDULER)os_timer_isr.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando os_timer_isr.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCSCHEDULER)os_timer_isr.c -o $(OBJ)os_timer_isr.o

# Compilamos: pll.c
$(OBJ)pll.o: $(SRCBOARD)pll.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando pll.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)pll.c -o $(OBJ)pll.o

# Compilamos: switch.c
$(OBJ)switch.o: $(SRCBOARD)switch.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando switch.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)switch.c -o $(OBJ)switch.o

# Compilamos: system_utils.c
$(OBJ)system_utils.o: $(SRCUTILS)system_utils.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando system_utils.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCUTILS)system_utils.c -o $(OBJ)system_utils.o

# Compilamos: task0.c
$(OBJ)task0.o: $(SRCTASKS)task0.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando task0.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCTASKS)task0.c -o $(OBJ)task0.o

# Compilamos: task1.c
$(OBJ)task1.o: $(SRCTASKS)task1.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando task1.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCTASKS)task1.c -o $(OBJ)task1.o

# Compilamos: task2.c
$(OBJ)task2.o: $(SRCTASKS)task2.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando task2.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCTASKS)task2.c -o $(OBJ)task2.o

# Compilamos: task3.c
$(OBJ)task3.o: $(SRCTASKS)task3.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando task3.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCTASKS)task3.c -o $(OBJ)task3.o

# Compilamos: timertick.c
$(OBJ)timertick.o: $(SRCIRQ)timertick.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando timertick.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCIRQ)timertick.c -o $(OBJ)timertick.o

# Compilamos: tps65217.c
$(OBJ)tps65217.o: $(SRCBOARD)tps65217.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando tps65217.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)tps65217.c -o $(OBJ)tps65217.o

# Compilamos: uart.c
$(OBJ)uart.o: $(SRCBOARD)uart.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando uart.c ..."
	$(CHAIN)-gcc $(CFLAGS) -c $(SRCBOARD)uart.c -o $(OBJ)uart.o

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.objstart
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.bin
	rm -rf $(BIN)*.MLO 
	rm -rf $(LST)*.lst 
	rm -rf $(LST)*.txt 
	rm -rf $(LST)*.map 

$(BIN)bios.MLO: $(BIN)bios.bin
	bin/mk-gpimage 0x402f0400 $< $@

