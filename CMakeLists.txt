# Policy
cmake_minimum_required( VERSION 3.1)

project(libLoraMac LANGUAGES C)

set(LORAMAC_COMMON_SOURCES
    src/system/crypto/aes.c
    src/system/crypto/cmac.c
    src/system/delay.c
    src/system/fifo.c
    src/system/gpio.c
    src/system/timer.c
    src/radio/sx1272/sx1272.c
)

set(LORAMAC_REGION_SOURCES
    src/mac/region/Region.c
    src/mac/region/RegionCommon.c
    src/mac/region/RegionEU868.c
    src/mac/region/RegionUS915.c
    src/mac/LoRaMac.c
    src/mac/LoRaMacCrypto.c
)

add_library(loraMacCommon OBJECT ${LORAMAC_COMMON_SOURCES})
add_library(loraMacEU868 OBJECT EXCLUDE_FROM_ALL ${LORAMAC_REGION_SOURCES})
add_library(loraMacUS915 OBJECT EXCLUDE_FROM_ALL ${LORAMAC_REGION_SOURCES})

set(LORAMAC_PROJECT_FLAGS ${LORA_STACK_CFG_FLAGS} -Wno-unused)

target_compile_options(loraMacCommon PRIVATE ${ARM_L0_COMMON_FLAGS} ${FW_COMMON_FLAGS} ${LORAMAC_PROJECT_FLAGS})
target_compile_options(loraMacEU868 PRIVATE ${ARM_L0_COMMON_FLAGS} ${FW_COMMON_FLAGS} ${LORAMAC_PROJECT_FLAGS} -DREGION_EU868)
target_compile_options(loraMacUS915 PRIVATE ${ARM_L0_COMMON_FLAGS} ${FW_COMMON_FLAGS} ${LORAMAC_PROJECT_FLAGS} -DREGION_US915)

target_include_directories(loraMacCommon

  # This sets the external interface include directory of the library
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/radio
  ${CMAKE_CURRENT_SOURCE_DIR}/src/system
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mac
  ${CMAKE_CURRENT_SOURCE_DIR}/src/system/crypto

  # These are the include paths we need to build the library itself
  PRIVATE
  # CMAKE_SOURCE_DIR is the location of the top level CMakeLists.txt, ie where the
  # project specific file is located. We need the project include directory to
  # find the "board" specific includes
  ${CMAKE_SOURCE_DIR}/src/board/
  $<TARGET_PROPERTY:L0HAL,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:FwCommon,INTERFACE_INCLUDE_DIRECTORIES>
  )

target_include_directories(loraMacEU868

  # This sets the external interface include directory of the library
  PUBLIC
  $<TARGET_PROPERTY:loraMacCommon,INTERFACE_INCLUDE_DIRECTORIES> 
  
  # These are the include paths we need to build the library itself
  PRIVATE
  $<TARGET_PROPERTY:FwCommon,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:L0HAL,INTERFACE_INCLUDE_DIRECTORIES>
  )

target_include_directories(loraMacUS915

  # This sets the external interface include directory of the library
  PUBLIC
  $<TARGET_PROPERTY:loraMacCommon,INTERFACE_INCLUDE_DIRECTORIES> 
  
  # These are the include paths we need to build the library itself
  PRIVATE
  $<TARGET_PROPERTY:FwCommon,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:L0HAL,INTERFACE_INCLUDE_DIRECTORIES>
  )
  