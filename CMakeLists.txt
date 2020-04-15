set(srcs "ssd1306.c")

if(CONFIG_I2C_INTERFACE)
    list(APPEND srcs "ssd1306_i2c.c")
elseif(CONFIG_SPI_INTERFACE)
    list(APPEND srcs "ssd1306_spi.c")
endif()

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "include"
                       REQUIRES )