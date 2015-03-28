

obj-m := drv.o
drv-objs := driver.o xnotify_drv.o

ifneq ($(KERNELDIR),)
else
KERNELDIR=/lib/modules/`uname -r`/build
endif

EXTRA_CFLAGS += -I$(SUBDIRS)/..

default::
	$(MAKE) -C $(KERNELDIR) SUBDIRS=`pwd` modules
	#$(CROSS_COMPILE)strip --strip-debug *.ko

clean::
	$(MAKE) -C $(KERNELDIR) SUBDIRS=`pwd` clean
