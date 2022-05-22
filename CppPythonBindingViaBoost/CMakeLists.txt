cmake_minimum_required(VERSION 3.10)

#You should declare a project. cmake says it is mandatory and it will define convenient variables PROJECT_NAME, PROJECT_VERSION and PROJECT_DESCRIPTION (this latter variable necessitate cmake 3.9):
project(CppPythonBinding VERSION 1.0.0 DESCRIPTION "C++ PythonBinding Library")

# To ignore lib prefix added to static/shared library names.
#set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Find python and Boost - both are required dependencies
find_package(PythonLibs 3.8 REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)

#Declare a new library target. Please avoid the use of file(GLOB ...). This feature does not provide attended mastery of the compilation process. If you are lazy, copy-paste output of ls -1 sources/*.cpp :
#Build Output Path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld)

add_library(hello SHARED ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld/Hello.cpp)

# Set up the libraries and header search paths for this target
target_link_libraries(hello ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(hello PRIVATE ${PYTHON_INCLUDE_DIRS})

# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
# Set VERSION property (optional but it is a good practice):
# 
# set_target_properties(mylib PROPERTIES VERSION ${PROJECT_VERSION})
# You can also set SOVERSION to a major number of VERSION. So libmylib.so.1 will be a symlink to libmylib.so.1.0.0.
# 
# set_target_properties(mylib PROPERTIES SOVERSION 1)
# Declare public API of your library. This API will be installed for the third-party application. It is a good practice to isolate it in your project tree (like placing it include/ directory). Notice that, private headers should not be installed and I strongly suggest to place them with the source files.
# 
# set_target_properties(mylib PROPERTIES PUBLIC_HEADER include/mylib.h)
# If you work with subdirectories, it is not very convenient to include relative paths like "../include/mylib.h". So, pass a top directory in included directories:
# 
# target_include_directories(mylib PRIVATE .)
# or
# 
# target_include_directories(mylib PRIVATE include)
# target_include_directories(mylib PRIVATE src)
# Create an install rule for your library. I suggest to use variables CMAKE_INSTALL_*DIR defined in GNUInstallDirs:
# 
# include(GNUInstallDirs)
# And declare files to install:
# 
# install(TARGETS mylib
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})