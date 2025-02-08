cmake_minimum_required(VERSION 3.10)

# Set project name
project(dsp)

# Find all header files
file(GLOB HEADER_FILES include/*.h)

# Define the output file
set(MERGED_HEADER ${CMAKE_BINARY_DIR}/dsp.h)

add_custom_command(
    OUTPUT ${MERGED_HEADER}
    # COMMAND cat ${HEADER_FILES} >> ${MERGED_HEADER}
    COMMAND cat "../include/constants.h" > ${MERGED_HEADER}
    COMMAND cat "../include/oscillators.h" >> ${MERGED_HEADER}
    COMMAND cat "../include/transformer.h" >> ${MERGED_HEADER}
    COMMAND cat "../include/filter.h" >> ${MERGED_HEADER}
    COMMAND cat "../include/modulation.h" >> ${MERGED_HEADER}
    COMMAND cat "../include/sampler.h" >> ${MERGED_HEADER}
    DEPENDS ${HEADER_FILES}
    COMMENT "Merging headers into dsp.h"
)

# Create a target to trigger the header merge
add_custom_target(merge_headers ALL DEPENDS ${MERGED_HEADER})

# Library source files
file(GLOB SOURCES src/*.c)
add_library(dsp STATIC ${SOURCES})

target_link_libraries(dsp m)

# Ensure merged header is installed
install(TARGETS dsp DESTINATION lib)
install(FILES ${MERGED_HEADER} DESTINATION include)
