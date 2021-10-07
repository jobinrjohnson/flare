add_library(
        capi
        SHARED

        libflare.cpp
        flare_string.cpp
        flare_array.cpp flare.h flare_auto_parallel.cpp)
