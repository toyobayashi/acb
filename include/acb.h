#ifndef __ACB_H__
#define __ACB_H__

#ifdef __cplusplus
#define ACB_EXTERN_C_START extern "C" {
#define ACB_EXTERN_C_END }
#else
#define ACB_EXTERN_C_START
#define ACB_EXTERN_C_END
#endif

#ifdef _WIN32
  #ifdef ACB_DLL_EXPORT
    #define ACB_API __declspec(dllexport)
  #else
    #define ACB_API
    // #define ACB_API __declspec(dllimport)
  #endif
#else
  #ifdef ACB_DLL_EXPORT
  #define ACB_API __attribute__((visibility("default")))
  #else
  #define ACB_API
  #endif
#endif

#ifdef _WIN32
#define MAX_PATH_LENGTH 260
#else
#define MAX_PATH_LENGTH 1024
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

ACB_EXTERN_C_START

typedef struct acb_file_header {
  uint32_t size;
  uint32_t magic;
} acb_file_header;

typedef struct acb_utf_header {
  uint16_t unknown1;
  uint16_t table_data_offset;
  uint32_t string_data_offset;
  uint32_t binary_data_offset;
  uint32_t table_name_string_offset;
  uint16_t column_length;
  uint16_t row_total_byte;
  uint32_t row_length;
} acb_utf_header;

typedef struct acb_utf_column {
  char* name;
  uint32_t index;
  uint8_t type;
  void* const_value;
} acb_utf_column;

typedef struct acb_track {
  int32_t cue_id;
  char cue_name[64];
  uint16_t wav_id;
  uint8_t encode_type;
  uint8_t streaming;
} acb_track;

typedef struct acb_awb_wav_file {
  uint16_t id;
  uint32_t start;
  uint32_t length;
} acb_awb_wav_file;

typedef struct acb {
  char path[MAX_PATH_LENGTH];

  FILE* f;
  long start;
  long size;
  long pos;

  acb_file_header file_header;
  acb_utf_header utf_header;
  char* name;
  acb_utf_column* columns;
} acb;

typedef struct acb_utf_binary_desc {
  uint32_t offset;
  uint32_t length;
} acb_utf_binary_desc;

typedef void (*acb_extract_callback)(uint32_t completed, uint32_t total, const char* file, bool status);

ACB_API acb* acb_open(const char* path);
ACB_API acb* acb_open_awb(const char* path);
ACB_API acb* acb_memopen(acb* parent, long start, long size);
ACB_API acb* acb_memopen_awb(acb* parent, long start, long size);
ACB_API void acb_close(acb* acbp);
ACB_API void acb_read_file_header(acb* acbp, acb_file_header* header);
ACB_API void acb_read_utf_header(acb* acbp, acb_utf_header* header);
ACB_API char* acb_read_string(acb* acbp, uint32_t offset);
ACB_API void acb_read_column(acb* acbp, acb_utf_column* columns, int column_length);
ACB_API int acb_get_row_data(acb* acbp, uint32_t row_index, const char* column_name, void* out, size_t buf_size);
ACB_API uint32_t acb_get_size(acb* acbp);
ACB_API acb_track* acb_get_track_list(acb* acbp, uint32_t* len);
ACB_API int acb_extract(acb* acbp, const char* target_dir, acb_extract_callback callback);

ACB_EXTERN_C_END

#endif
