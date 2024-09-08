set(COMPONENT_SRCS "main.c")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
#idf_component_register(SRCS "freetype-example.c" INCLUDE_DIRS "." PRIV_REQUIRES spiffs)

# Download the example font into a directory "spiffs" in the build directory
#set(URL "https://github.com/espressif/esp-docs/raw/f036a337d8bee5d1a93b2264ecd29255baec4260/src/esp_docs/fonts/DejaVuSans.ttf")
#set(FILE "DejaVuSans.ttf")
set(SPIFFS_DIR "../spiffs")
#message(SPIFFS_DIR="${SPIFFS_DIR}")
#file(MAKE_DIRECTORY ${SPIFFS_DIR})
#file(DOWNLOAD ${URL} ${SPIFFS_DIR}/${FILE} SHOW_PROGRESS)

# Create a partition named "fonts" with the example font
#spiffs_create_partition_image(fonts ${SPIFFS_DIR} FLASH_IN_PROJECT)
