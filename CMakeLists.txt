cmake_minimum_required(VERSION 3.29.3)

# Tentukan nama proyek
project(HealthAdmin)

# Tentukan versi proyek
set(VERSION "1.0.0")

# Find dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
set(LIBRARIES ${LIBRARIES} ${GTK3_LIBRARIES})

# Compile
add_executable(HealthAdmin ${PROJECT_SOURCE_DIR}/main.c)
target_link_libraries(HealthAdmin ${LIBRARIES})

# Messages
message(STATUS "GTK include directories: ${GTK3_INCLUDE_DIRS}")

# CPack
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK3_LIBRARIES_DIRS}/gtk-3.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK3_LIBRARIES_DIRS}/glib-2.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK3_LIBRARIES_DIRS}/pango-1.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTK3_LIBRARIES_DIRS}/atk-1.0.0.tar.gz WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)")

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
