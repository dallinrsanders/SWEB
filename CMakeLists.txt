cmake_minimum_required(VERSION 3.0.0)
project(SWeb VERSION 0.1.0)
include(CTest)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
add_executable(SWeb WebServer.cpp
system/HSTS.cpp
system/HTMLResponse.cpp
system/Router.cpp
system/Server.cpp
system/session.cpp
system/Utilities.cpp
system/WebSession.cpp
system/URLParameter.cpp
pages/DefaultPage.cpp
pages/StaticPage.cpp
pages/E404.cpp


)
target_include_directories(SWeb PRIVATE "includes")
if(WIN32)
  target_link_libraries(SWeb wsock32 ws2_32 crypto ssl)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
