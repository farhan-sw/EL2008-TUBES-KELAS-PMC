cmake_minimum_required(VERSION 3.29.3)
project(GTKTutorial)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(GTK3_INCLUDE_DIRS "C:/msys64/mingw64/include/")
set(GTK3_LIBRARY_DIRS "C:/msys64/mingw64/lib")
set(ENV{PKG_CONFIG_PATH} "C:/msys64/mingw64/lib/pkgconfig")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_BIN_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(HealthAdmin main.c)
# set_target_properties(HealthAdmin PROPERTIES WIN32_EXECUTABLE true)  # If you dont want console to run with your .exe
target_link_libraries(HealthAdmin ${GTK4_LIBRARIES})

# CPack
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK4_LIBRARIES_DIRS}/gtk-4.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK4_LIBRARIES_DIRS}/glib-2.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK4_LIBRARIES_DIRS}/pango-1.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK4_LIBRARIES_DIRS}/atk-1.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")

# CPack configuration
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "HealthAdmin")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATOR "NSIS") # Choose the installer generator, NSIS for Windows
set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME} ${CPACK_PACKAGE_VERSION}")
set(CPACK_NSIS_HELP_LINK "http://www.example.com/help")
set(CPACK_NSIS_URL_INFO_ABOUT "http://www.example.com")
set(CPACK_NSIS_CONTACT "support@example.com")
set(CPACK_NSIS_MODIFY_PATH ON)

# Specify installation directories and files
install(TARGETS HealthAdmin DESTINATION bin)
install(DIRECTORY ${GTK4_INCLUDE_DIRS} DESTINATION include)
install(DIRECTORY ${GTK4_LIBRARY_DIRS} DESTINATION lib)
install(FILES ${GTK4_LIBRARIES} DESTINATION bin)

include(CPack)
