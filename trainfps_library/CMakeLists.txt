find_package(Boost COMPONENTS program_options filesystem iostreams REQUIRED )
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv)

# add lib source files
file(GLOB LIB_SOURSEC ${PROJECT_SOURCE_DIR}/trainfps_library/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/trainfps_library/src )

#add library
add_library(trainfps_library SHARED ${LIB_SOURSEC} )

#link 
target_link_libraries(trainfps_library ${Boost_LIBRARIES} ${OPENCV_LIBRARIES} )
