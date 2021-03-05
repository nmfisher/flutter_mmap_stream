#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <android/log.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/mman.h>
#include <unistd.h>
#include "mmap/mmap_stream.hpp"
#include <vector>



mmap_stream* map_file(const char* filename, AAssetManager* mgr) {
  long pageSize = sysconf(_SC_PAGE_SIZE);
  size_t result;
  off_t start;
  off_t outLength;

  AAsset *asset = AAssetManager_open(mgr, filename, AASSET_MODE_UNKNOWN);
  if(asset == NULL) {
    __android_log_print(ANDROID_LOG_VERBOSE, "mmap_stream_android", "Couldn't locate asset [ %s ]", filename);
    return NULL;
  }
  int fd = AAsset_openFileDescriptor(asset, &start, &outLength);
  __android_log_print(ANDROID_LOG_VERBOSE, "mmap_stream_android", "Opened file descriptor [ %d ] for [ %s ] with start %lld and length %lld", fd, filename, (long long)start,(long long) outLength);

  off_t startPage = (off_t)(start / pageSize) * pageSize;
  off_t startPageOffset = start - startPage;

  char *mmapped_buffer_ = (char *) mmap(nullptr, outLength + startPageOffset, PROT_READ, MAP_SHARED, fd,
                                       startPage);
  if (mmapped_buffer_ == MAP_FAILED) {
     __android_log_print(ANDROID_LOG_VERBOSE, "mmap_stream_android", "mmap failed");
     return NULL;
  }

  char* stream_start = mmapped_buffer_ + startPageOffset;
  char* stream_end = mmapped_buffer_ + startPageOffset + outLength;
  mmap_stream* mmap_buf = new mmap_stream(stream_start, stream_end);
  __android_log_print(ANDROID_LOG_VERBOSE, "MyApp", "Created stream from %p to %p", stream_start, stream_end);

  // AAsset_close(asset);
  return mmap_buf;
}