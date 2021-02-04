

if (LINUX)
    cmake_minimum_required(VERSION 3.13)
    project(Hubble)

    file(GLOB hubble_src "*.h" "*.cpp")
    option(PLATFORM PLATFORM_RPI)
    # option(OPENGL_VERSION OPENGL_VERSION_OFF)

    find_package(raylib 2.5.0 REQUIRED)
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)

    find_package(PythonLibs REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})

    set(CMAKE_C_STANDARD 11)

    add_executable(Hubble ${hubble_src})

    target_link_libraries(Hubble raylib Threads::Threads X11 ${PYTHON_LIBRARIES})

endif (LINUX)

if (WIN32)
    message(NOTICE "WIN32 detected")
    cmake_minimum_required(VERSION 3.15)
    project(
        Hubble 
        VERSION 2.2 
        DESCRIPTION "Hubble 2.2"
        LANGUAGES CXX C
    )

    set(USE_32_BIT ON)

    set(32_BIT "x86")
    set(64_BIT "x64")

    set(BIT_VAL "${64_BIT}")
    if(NOT "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "AMD64" OR "${USE_32_BIT}")
        set(BIT_VAL "${32_BIT}")
    endif()

    set(RAYLIB_DIR "C:/Users/asus/Desktop/thirdparty/raylib/3.5.0/${BIT_VAL}")
    set(RAYLIB_INCLUDE_DIR "${RAYLIB_DIR}/include")

    set(boop "boop")
    set(beep "${boop}/beep")
    message("boop: ${boop} beep: ${beep}")

    message("raylib_dir: ${RAYLIB_DIR}")
    message("raylib_inc: ${RAYLIB_INCLUDE_DIR}")

    file(GLOB hubble_src "include/*.h" "src/*.cpp" "main.cpp") #BAD
    add_executable(HubbleExe ${hubble_src})
    target_include_directories(HubbleExe PRIVATE include)

    set_property(TARGET HubbleExe PROPERTY CXX_STANDARD 17) 
    get_target_property(cxx_standard_version HubbleExe CXX_STANDARD)
    message("cxx standard: ${cxx_standard_version}")

    set(raylib_DIR "C:/raylib/raylib/cmake")
    # Set this to the minimal version you want to support
    find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

    # You could change the QUIET above to REQUIRED and remove this if() clause
    # This part downloads raylib and builds it if it's not installed on your system
    if (NOT raylib_FOUND) # If there's none, fetch and build raylib
        include(FetchContent)

        FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
        )

        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
            set(FETCHCONTENT_QUIET NO)
            FetchContent_Populate(raylib)

            set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

            # build raylib
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

        endif()

    endif()

    #target_include_directories(HubbleExe PUBLIC RAYLIB_INCLUDE_DIR)
    message("linking now")
    target_link_libraries(HubbleExe PRIVATE raylib)

    get_target_property(linked_libs HubbleExe LINK_LIBRARIES)
    message("linked libs: ${linked_libs}")
    
endif(WIN32)