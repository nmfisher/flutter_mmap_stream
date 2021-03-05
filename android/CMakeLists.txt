cmake_minimum_required(VERSION 3.4.1)  # for example

add_library( 
            mmap_stream_android
            SHARED
            ../ios/src/mmap_stream.cc 
            ../ios/src/mmap_stream_android.cc 
        )
