cmake_minimum_required(VERSION 2.6)

project(Graph)
set(EXECUTABLE_OUTPUT_PATH ../bin)

include_directories(headers templates includes/headers)

cmake_policy(SET CMP0015 NEW)

file(
  GLOB_RECURSE
  sources
  src/*
  includes/src/*
  )

add_executable(
  test_directed
  tests/test_directed.cpp
  ${sources}
  )

add_executable(
  test_acm
  tests/test_acm.cpp
  ${sources}
  )

add_executable(
  test_coloring
  tests/test_coloring.cpp
  ${sources}
  )

add_executable(
  test_dijkstra
  tests/test_dijkstra.cpp
  ${sources}
  )

add_executable(
  test_dijkstra_maximize
  tests/test_dijkstra_maximize.cpp
  ${sources}
  )

add_executable(
  test_bellman
  tests/test_bellman.cpp
  ${sources}
  )

add_executable(
  test_Xdijkstra
  tests/test_Xdijkstra.cpp
  ${sources}
  )

add_executable(
  test_Xbellman
  tests/test_Xbellman.cpp
  ${sources}
  )

add_executable(
  test_weights_transformations
  tests/test_weights_transformations.cpp
  ${sources}
  )

add_executable(
  test_preceedence_table
  tests/test_preceedence_table.cpp
  ${sources}
  )

add_executable(
  test_network_builder
  tests/test_network_builder.cpp
  ${sources}
  )

add_executable(
  test_flow_network
  tests/test_flow_network.cpp
  ${sources}
  )

add_executable(
  residual_graph
  tests/test_fn_residual_builder.cpp
  ${sources}
  )

add_executable(
  ford_fulkerson
  tests/test_ford_fulkerson.cpp
  ${sources}
  )

add_executable(
  reseau_routier
  tests/reseau_routier.cpp
  ${sources}
  )

add_executable(
  feux_tricolores
  tests/feux_tricolores.cpp
  ${sources}
  )

add_executable(
  gps
  tests/gps.cpp
  ${sources}
  )

add_executable(
  gps_multichemin
  tests/gps_multichemin.cpp
  ${sources}
  )

add_executable(
  plannification
  tests/plannification.cpp
  ${sources}
  )

add_executable(
  plannification_interfaced
  tests/plannification_interfaced.cpp
  ${sources}
  )

