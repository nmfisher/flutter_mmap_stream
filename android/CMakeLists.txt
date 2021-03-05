cmake_minimum_required(VERSION 3.4.1)  # for example

add_library( 
            mmap_stream
            SHARED
            ../src/mmap_stream.cc 
        )
