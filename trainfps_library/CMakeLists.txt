find_package(Boost COMPONENTS program_options system filesystem iostreams REQUIRED )
find_package(PkgConfig REQUIRED)
#pkg_check_modules(LIBXML++ REQUIRED libxml++-2.6)
pkg_check_modules(YAML REQUIRED yaml-cpp)

# add lib source files
file(GLOB LIB_SOURSEC ${PROJECT_SOURCE_DIR}/trainfps_library/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/trainfps_library/src ${LIBXML++_INCLUDE_DIRS})

#add library
add_library(trainfps_library SHARED ${LIB_SOURSEC} )

#link 
target_link_libraries(trainfps_library ${Boost_LIBRARIES} ${YAML_LIBRARIES} )
