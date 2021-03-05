# flutter_mmap_stream

A Flutter plugin to wrap/build the [mmap_stream library](https://github.com/nmfisher/mmap_stream). Other Flutter projects can link libmmap_stream by simply adding this plugin as a dependency, rather than each Flutter project building/linking its own copy.

Note this probably won't work out-of-the-box on iOS (since Xcode strips all libraries not explicitly called by your plugin code). To fix this, you'll need to modify the project so force load the library (but I haven't done this as this library is only needed for Android).

