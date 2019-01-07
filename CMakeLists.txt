# Policy
cmake_minimum_required( VERSION 3.1)

project(libLoraMac LANGUAGES C)

set(LORAMAC_SOURCES
    src/system/crypto/aes.c
    src/system/crypto/cmac.c
    src/system/delay.c
    src/system/fifo.c
    src/system/gpio.c
    src/system/timer.c
    src/radio/sx1272/sx1272.c
    src/mac/region/Region.c
    src/mac/region/RegionCommon.c
    src/mac/region/RegionEU868.c
    src/mac/LoRaMac.c
    src/mac/LoRaMacCrypto.c
)

add_library(loraMac OBJECT ${LORAMAC_SOURCES})

set(LORAMAC_PROJECT_FLAGS ${LORA_STACK_CFG_FLAGS} -Wno-unused)

target_compile_options(loraMac PRIVATE ${ARM_L0_COMMON_FLAGS} ${FW_COMMON_FLAGS} ${LORAMAC_PROJECT_FLAGS} )

target_include_directories(loraMac

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
