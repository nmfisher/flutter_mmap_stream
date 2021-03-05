"# mmap_stream" 

Simple C++ library for exposing a memory mapped file as a stream buffer. This is mostly useful when working with Android assets and C++ libraries that expect files (since bundled assets are only available via the AssetManager and can't be accessed directly via the filesystem).