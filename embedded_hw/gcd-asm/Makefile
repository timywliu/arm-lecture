CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -O0 -mcpu=cortex-a15
LDFLAGS = -fno-stack-protector

objs = gcdv1.o gcdv2.o gcdv3.o benchmark.o

default: benchmark

benchmark: $(objs)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.s
	$(CC) -c $(CFLAGS) -o $@ $<

qemu: benchmark
	qemu-arm -L /usr/arm-linux-gnueabihf ./$< 1 1
	qemu-arm -L /usr/arm-linux-gnueabihf ./$< 2 1
	qemu-arm -L /usr/arm-linux-gnueabihf ./$< 3 1

clean:
	rm -rf $(objs) benchmark time_v1 time_v2 time_v3

