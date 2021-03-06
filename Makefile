PROJECT = kobject_test
obj-m := $(PROJECT).o
PWD := $(shell pwd)
KDIR = /lib/modules/$(shell uname -r)/build

all:
	@echo "Compiling module $(PROJECT)"
	@make -C $(KDIR) M=$(PWD) modules
#usr:
#	gcc vms_usr.c -o vms_usr

install_mod:
	@echo "Installing module......"
	sudo insmod $(PROJECT).ko

uninstall_mod:
	@echo "Uninstalling module....."
	sudo rmmod $(PROJECT).ko
clean:
	rm -rf *.ko  *.mod.c   *.o *.order *.symvers .*.cmd .*.swp .tmp_versions 2> /dev/null
