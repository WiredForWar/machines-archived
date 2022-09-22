
set(STDLIB_SOURCES
    function.hpp
    memory.hpp
    strfwd.hpp
    string.cpp
    string.hpp
    utility.hpp
)

if(USE_EXCEPTIONS)
    list(APPEND STDLIB_SOURCES
        exceptio.cpp
        exceptio.hpp
    )
endif()

add_library(stdlib OBJECT ${STDLIB_SOURCES})
