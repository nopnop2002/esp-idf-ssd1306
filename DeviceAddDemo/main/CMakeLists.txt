set(srcs "main.c")

# get IDF version for comparison
set(idf_version "${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}")

if(idf_version VERSION_GREATER_EQUAL "5.2")
	if(CONFIG_LEGACY_DRIVER)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D LEGACY_DRIVER")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D NEW_DRIVER")
	endif()
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D LEGACY_DRIVER")
endif()

idf_component_register(SRCS "${srcs}" INCLUDE_DIRS ".")

