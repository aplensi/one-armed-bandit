cmake_minimum_required (VERSION 3.8)


if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("one-armed bandit")

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/lib/cmake/SFML")

find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_executable (CMakeTarget "one-armed bandit.cpp" "one-armed bandit.h" "button.cpp" "button.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(CMakeTarget sfml-graphics sfml-window sfml-system)