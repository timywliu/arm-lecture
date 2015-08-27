CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -O0 -mcpu=cortex-a15
LDFLAGS = -fno-stack-protector

objs = clz.o main.o

default: clz

clz: $(objs)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.s
	$(CC) -c $(CFLAGS) -o $@ $<

qemu: clz
	qemu-arm -L /usr/arm-linux-gnueabihf ./$<

clean:
	rm -rf $(objs) clz

