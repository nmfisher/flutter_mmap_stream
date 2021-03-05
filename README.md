# flutter_mmap_stream

A Flutter plugin to wrap/build the [mmap_stream library](https://github.com/nmfisher/mmap_stream). Other Flutter projects can link libmmap_stream by simply adding this plugin as a dependency, rather than each Flutter project building its own copy.


You will still need to link in libmmap_stream.so - the easiest way to do so is by modifying CMakeLists.txt (or equivalent) in your Flutter project  by adding the following:  

`string(REPLACE "build\\kaldi_asr_ffi" "build\\flutter_mmap_stream" FLUTTER_MMAP_BUILD_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${FLUTTER_MMAP_BUILD_DIR})`

where _your_other_project_ is the package name for the Flutter project that you are building.

Note this probably won't work out-of-the-box on iOS (since Xcode strips all libraries not explicitly called by your plugin code). To fix this, you'll need to modify the project so force load the library (but I haven't done this as this library is only needed for Android).

