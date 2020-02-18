cmake_minimum_required(VERSION 3.15)

project(acb)

if(ACB_BUILD_DLL)
  add_library(acb SHARED
    src/acb.c
  )
else()
  add_library(acb STATIC
    src/acb.c
  )
endif()

# set_target_properties(acb PROPERTIES PREFIX "lib")

if(WIN32 AND MSVC)
  set_target_properties(acb PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  target_compile_options(acb PRIVATE /utf-8)
  target_compile_definitions(acb PRIVATE
    _CRT_SECURE_NO_WARNINGS
    UNICODE
    _UNICODE
  )
else()
  target_link_libraries(acb m)
endif()

if(ACB_BUILD_DLL)
  target_compile_definitions(acb PRIVATE
    ACB_DLL_EXPORT
  )
endif()

target_include_directories(acb
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(acbtest
  test/main.c
)

target_include_directories(acbtest PRIVATE ${PROJECT_SOURCE_DIR}/include)

if(WIN32 AND MSVC)
  set_directory_properties(PROPERTIES VS_STARTUP_PROJECT acbtest)
  set_target_properties(acbtest PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  target_compile_options(acbtest PRIVATE /utf-8)
  target_compile_definitions(acbtest PRIVATE
    _CRT_SECURE_NO_WARNINGS
    UNICODE
    _UNICODE
  )

  if(ACB_BUILD_DLL)
    target_link_options(acbtest PRIVATE /ignore:4199 /DELAYLOAD:acb.dll)
  endif()
endif()

target_link_libraries(acbtest acb)
