idf_component_register(SRCS ssd1306.c ssd1306_spi.c ssd1306_i2c.c
                       INCLUDE_DIRS "include"
                       REQUIRES driver freertos log)
