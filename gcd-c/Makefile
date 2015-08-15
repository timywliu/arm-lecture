CC = gcc
CFLAGS = -Wall -O0
LDFLAGS =

ARM_CC = arm-linux-gnueabihf-gcc
ARM_CFLAGS = -Wall -O0 -mcpu=cortex-a15
ARM_LDFLAGS = -fno-stack-protector

objs = gcd.o benchmark.o
arm_objs = arm_gcd.o arm_benchmark.o

default: benchmark

benchmark: $(objs)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

arm_benchmark: $(arm_objs)
	$(ARM_CC) $(ARM_LDFLAGS) -o $@ $^

arm_gcd.o: gcd.c
	$(ARM_CC) -c $(ARM_CFLAGS) -o $@ $<
arm_benchmark.o: benchmark.c
	$(ARM_CC) -c $(ARM_CFLAGS) -o $@ $<

x86: benchmark
	./$< 1 1
	./$< 2 1
	./$< 3 1

qemu: arm_benchmark
	qemu-arm -L /usr/arm-linux-gnueabihf ./$< 1 1
	qemu-arm -L /usr/arm-linux-gnueabihf ./$< 2 1
	qemu-arm -L /usr/arm-linux-gnueabihf ./$< 3 1

clean:
	rm -rf $(objs) $(arm_objs) benchmark arm_benchmark time_v1 time_v2 time_v3

