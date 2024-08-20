cmake_minimum_required(VERSION 3.5)
project(flow_test)


add_compile_options(-std=c++20 -g -Wno-deprecated)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_SYSTEM_NO_DEPRECATED -DUSE_UCONTEXT -DNO_INTELLISENSE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# message(${CMAKE_CURRENT_SOURCE_DIR}/include/flow)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/flow)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/fmt)
find_package(Boost 1.71 REQUIRED)
if(Boost_FOUND)
    # message("Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS}) 
endif()


file(GLOB CPP_SOURCES "*.cpp")
foreach(SOURCE ${CPP_SOURCES})
    # get the extension name
    get_filename_component(EXTENSION ${SOURCE} EXT)

    # get the file name without ext
    get_filename_component(FILENAME ${SOURCE} NAME_WE)

    # get the file name with ext
    get_filename_component(FILENAME_WITH_EXT ${SOURCE} NAME)

    # skip *.out.cpp
    if(SOURCE MATCHES "\\.out\\.cpp$")
        continue()
    endif()


    # get the output name
    string(REPLACE ".cpp" ".out.cpp" OUT_CPP_FILE ${FILENAME_WITH_EXT})
    string(REGEX REPLACE "\\.cpp$" "" FILENAME_WITHOUT_EXT ${FILENAME_WITH_EXT})
    

    # command for mono
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/tmp/${OUT_CPP_FILE}
        COMMAND mono ${CMAKE_CURRENT_SOURCE_DIR}/lib/actorcompiler.exe ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME_WITH_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/tmp/${OUT_CPP_FILE}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME_WITH_EXT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running actorcompiler on counting_server.actor.cpp"
    )
    add_executable(${FILENAME_WITHOUT_EXT} tmp/${OUT_CPP_FILE})


    # link libraries and options
    find_package(OpenSSL REQUIRED)
    if(OPENSSL_FOUND)
        target_include_directories(${FILENAME_WITHOUT_EXT} PRIVATE ${OPENSSL_INCLUDE_DIR})
        target_link_libraries(${FILENAME_WITHOUT_EXT} ${OPENSSL_LIBRARIES})
    endif()
    find_package(Boost REQUIRED COMPONENTS filesystem)
    if(Boost_FOUND)
        target_link_libraries(${FILENAME_WITHOUT_EXT} ${Boost_LIBRARIES} Boost::filesystem)
    endif()

    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${COREFOUNDATION_FRAMEWORK})

    find_library(IOKIT_FRAMEWORK IOKit)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${IOKIT_FRAMEWORK})
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/format.cc.o)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/os.cc.o)

    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libflow.a)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfdbrpc.a)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblibb64.a)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfdbrpc_sampling.a)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcrc32.a)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libeio.a)
    target_link_libraries(${FILENAME_WITHOUT_EXT} -ldl -lpthread -lm)
    target_link_libraries(${FILENAME_WITHOUT_EXT} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfdb_c.dylib)
    target_link_options(${FILENAME_WITHOUT_EXT} PRIVATE -Bstatic -Bdynamic)

endforeach()

# add_test(NAME hashmap_test_out COMMAND hashmap_test)