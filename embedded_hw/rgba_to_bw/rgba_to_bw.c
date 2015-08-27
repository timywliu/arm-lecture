#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <png.h>

#define ROUND_VALUE 0.001

/* some file local variable to save tmp image */
int width = 0, height = 0, stride = 0;

png_bytep *row_pointers;
png_byte color_type;
png_byte bit_depth;

#if !defined(BW_V0) && !defined(BW_V1)

#define TABLE_SIZE 256

float mul_299[TABLE_SIZE], mul_587[TABLE_SIZE], mul_114[TABLE_SIZE];

void gen_table(void)
{
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    mul_299[i] = i * 0.299;
    mul_587[i] = i * 0.587;
    mul_114[i] = i * 0.114;
  }
}
#else
void gen_table(void) {}
#endif

#ifdef BW_V0 /* Original version */

#define OUTPUT_NAME "bw_v0.png"
void rgba_to_bw(unsigned int *bitmap, int width, int height, long stride) {
  int row, col;
  unsigned int pixel, r, g, b, a, bw;
  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      pixel = bitmap[col + row * stride / 4];
      a = (pixel >> 24) & 0xff;
      r = (pixel >> 16) & 0xff;
      g = (pixel >> 8) & 0xff;
      b = pixel & 0xff;
      bw = (unsigned int) (r * 0.299 + g * 0.587 + b * 0.114 + ROUND_VALUE);
      bitmap[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
    }
  }
}

#elif defined(BW_V1) /* Use pointer to reduce shift & array position calculation */

#define OUTPUT_NAME "bw_v1.png"
void rgba_to_bw(unsigned int *bitmap, int width, int height, long stride) {
  int row, col;
  unsigned int *pixel = bitmap;
  unsigned char *r, *g, *b, bw;
  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      r = (unsigned char *)pixel + 2;
      g = (unsigned char *)pixel + 1;
      b = (unsigned char *)pixel;
      bw = (unsigned char) (*r * 0.299 + *g * 0.587 + *b * 0.114 + ROUND_VALUE);
      *r = *g = *b = bw;
      pixel++;
    }
  }
}

#elif defined(BW_V2) /* Use table to optimize */

#define OUTPUT_NAME "bw_v2.png"
void rgba_to_bw(unsigned int *bitmap, int width, int height, long stride) {
  int row, col;
  unsigned int pixel, r, g, b, a, bw;
  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      pixel = bitmap[col + row * stride / 4];
      a = (pixel >> 24) & 0xff;
      r = (pixel >> 16) & 0xff;
      g = (pixel >> 8) & 0xff;
      b = pixel & 0xff;
      bw = (unsigned int) (mul_299[r] + mul_587[g] + mul_114[b] + ROUND_VALUE);
      bitmap[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
    }
  }
}

#else /* BW_V3; combine V1 & V2 */

#define OUTPUT_NAME "bw_v3.png"
void rgba_to_bw(unsigned int *bitmap, int width, int height, long stride) {
  int row, col;
  unsigned int *pixel = bitmap;
  unsigned char *r, *g, *b, bw;
  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      r = (unsigned char *)pixel + 2;
      g = (unsigned char *)pixel + 1;
      b = (unsigned char *)pixel;
      bw = (unsigned char) (mul_299[*r] + mul_587[*g] + mul_114[*b] + ROUND_VALUE);
      *r = *g = *b = bw;
      pixel++;
    }
  }
}
#endif

void read_image(const char* filename)
{
  int y;
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    perror("open file");
    return;
  }

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  width      = png_get_image_width(png, info);
  height     = png_get_image_height(png, info);
  color_type = png_get_color_type(png, info);
  bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(bit_depth == 16)
    png_set_strip_16(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  stride = png_get_rowbytes(png, info);
  /* We need a continuous memory for pixels to do rgb_to_bw translation */
  png_bytep pixels = (png_bytep) malloc(height * stride);

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for(y = 0; y < height; y++) {
//    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    row_pointers[y] = pixels + stride * y;
  }

  png_read_image(png, row_pointers);

  fclose(fp);
}

void write_image(const char *filename)
{
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    perror("write file");
    exit(-1);
  }

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();

  png_infop info = png_create_info_struct(png);
  if (!info) abort();

  if (setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR (
    png,
    info,
    width, height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  png_write_image(png, row_pointers);

  png_write_end(png, NULL);

  /*for(int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }*/
  free(row_pointers[0]);
  free(row_pointers);

  fclose(fp);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./rgba_to_bw [png input file name]");
    return 1;
  }

  gen_table();

  read_image(argv[1]);

  clock_t begin = clock();
  rgba_to_bw((unsigned int *) *row_pointers, width, height, stride);
  clock_t end = clock();
  printf("rgba_to_bw time elapsed: %lf\n", (double)(end-begin)/CLOCKS_PER_SEC);

  write_image(OUTPUT_NAME);
  return 0;
}

