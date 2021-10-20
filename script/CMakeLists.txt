cmake_minimum_required(VERSION 3.16)
project(ALICE_Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ALICE_Simulation ParticleType/ParticleType.cpp Resonancetype/ResonanceType.cpp Particle/Particle.cpp mainE.cpp)
