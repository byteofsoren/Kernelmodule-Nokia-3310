obj-m := solidusmodule.o

KERNEL_DIR_ARC=/usr/lib/modules/$(shell uname -r)

all:
	$(MAKE) -C $(KERNEL_DIR_ARC) SUBDIRS=$(PWD) modules

.PHONY: clean

clean:
	rm -rf *.o *.ko *.mod.* *.symveres *.order
