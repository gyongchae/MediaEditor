# Install script for directory: C:/libraries/SFML-2.4.1/examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SFML")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/libraries/SFML-2.4.1-build/examples/ftp/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/opengl/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/pong/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/shader/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/sockets/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/sound/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/sound_capture/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/voip/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/window/cmake_install.cmake")
  include("C:/libraries/SFML-2.4.1-build/examples/win32/cmake_install.cmake")

endif()

