
cmake_minimum_required(VERSION 3.16)
project(ALICE_Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ROOT 6.22 CONFIG REQUIRED COMPONENTS)
  if(ROOT_FOUND)
    message(STATUS "ROOT had been found")
  endif()

include("${ROOT_USE_FILE}")
separate_arguments(ROOT_EXE_LINKER_FLAGS)

add_executable(ALICE_Simulation mainE.cpp)

add_subdirectory(Particle)
add_subdirectory(ParticleType)
add_subdirectory(ResonanceType)

target_link_libraries(ALICE_Simulation Particle ParticleType ResonanceType ${ROOT_LIBRARIES} ${ROOT_EXE_LINKER_FLAGS})
