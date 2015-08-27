BIN = rgba_to_bw_v0 rgba_to_bw_v1 rgba_to_bw_v2 rgba_to_bw_v3

CC = gcc
CFLAGS = -Wall -O0 -g
LDFLAGS =
LIBR = -lpng12

all: $(BIN)

rgba_to_bw_v0: rgba_to_bw.c
	$(CC) $(CFLAGS) -DBW_V0 $(LDFLAGS) -o $@ $^ $(LIBR)

rgba_to_bw_v1: rgba_to_bw.c
	$(CC) $(CFLAGS) -DBW_V1 $(LDFLAGS) -o $@ $^ $(LIBR)

rgba_to_bw_v2: rgba_to_bw.c
	$(CC) $(CFLAGS) -DBW_V2 $(LDFLAGS) -o $@ $^ $(LIBR)

rgba_to_bw_v3: rgba_to_bw.c
	$(CC) $(CFLAGS) -DBW_V3 $(LDFLAGS) -o $@ $^ $(LIBR)

bw: $(BIN)
	./rgba_to_bw_v0 sample_320x213.png
	./rgba_to_bw_v0 sample_640x427.png
	./rgba_to_bw_v0 sample_800x533.png
	./rgba_to_bw_v0 sample_1024x683.png
	./rgba_to_bw_v0 sample_1296x864.png
	./rgba_to_bw_v0 sample_2592x1728.png
	./rgba_to_bw_v0 sample_3888x2592.png
	./rgba_to_bw_v0 sample_5184x3456.png
	./rgba_to_bw_v1 sample_320x213.png
	./rgba_to_bw_v1 sample_640x427.png
	./rgba_to_bw_v1 sample_800x533.png
	./rgba_to_bw_v1 sample_1024x683.png
	./rgba_to_bw_v1 sample_1296x864.png
	./rgba_to_bw_v1 sample_2592x1728.png
	./rgba_to_bw_v1 sample_3888x2592.png
	./rgba_to_bw_v1 sample_5184x3456.png
	./rgba_to_bw_v2 sample_320x213.png
	./rgba_to_bw_v2 sample_640x427.png
	./rgba_to_bw_v2 sample_800x533.png
	./rgba_to_bw_v2 sample_1024x683.png
	./rgba_to_bw_v2 sample_1296x864.png
	./rgba_to_bw_v2 sample_2592x1728.png
	./rgba_to_bw_v2 sample_3888x2592.png
	./rgba_to_bw_v2 sample_5184x3456.png
	./rgba_to_bw_v3 sample_320x213.png
	./rgba_to_bw_v3 sample_640x427.png
	./rgba_to_bw_v3 sample_800x533.png
	./rgba_to_bw_v3 sample_1024x683.png
	./rgba_to_bw_v3 sample_1296x864.png
	./rgba_to_bw_v3 sample_2592x1728.png
	./rgba_to_bw_v3 sample_3888x2592.png
	./rgba_to_bw_v3 sample_5184x3456.png

clean:
	$(RM) $(BIN) bw_v*.png
