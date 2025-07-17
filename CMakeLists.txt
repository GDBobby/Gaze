cmake_minimum_required(VERSION 3.23)

# project(Gaze)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Gaze)
set(is_project_root OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(is_project_root ON)
endif()

message(STATUS "Project source dir : ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE source dir : ${CMAKE_SOURCE_DIR}")

add_library(Gaze-compile-options INTERFACE)
add_library(Gaze::Gaze-compile-options ALIAS Gaze-compile-options)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(Gaze-compile-options INTERFACE
    -Wall 
    -Wextra 
    -Wpedantic 
    -Wconversion 
    -Wunused 
    -Werror=return-type 
    #$<$<NOT:$<CONFIG:Debug>>:-Werror>
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  target_compile_options(Gaze-compile-options INTERFACE
    $<$<NOT:$<CONFIG:Debug>>:/WX>
  )
endif()

add_library(Gaze INTERFACE)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/LAB/*.h)

target_sources(Gaze PUBLIC FILE_SET HEADERS BASE_DIRS LAB FILES ${HEADER_FILES})
target_include_directories(Gaze INTERFACE ${PROJECT_SOURCE_DIR}/include)

set_target_properties(Gaze PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Release"
    VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    DEBUG_POSTFIX "-d"  # Appends "-d" in Debug mode
    RELEASE_POSTFIX ""   # No postfix in Release mode
    LINKER_LANGUAGE CXX
)

if(is_project_root)

  message(STATUS "Gaze is project root")
  project(GazeExample)
  file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
  add_executable(GazeExample ${SOURCES})
  target_link_libraries(GazeExample PUBLIC 
      Gaze
      Gaze-compile-options
  )
  target_link_directories(GazeExample PUBLIC
    $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/Debug>
    $<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/Release>
  )


  message(STATUS "Archive dir? : ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
  message(STATUS "RUNTIME dir : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  message(STATUS "build location : ${CMAKE_CURRENT_BINARY_DIR}")

  # Create source groups to maintain file structure in Visual Studio
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${HEADER_FILES_PP})
endif()

#add_subdirectory(examples)