project(test CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("TESTING = ${TESTING}")

# Choose which test .cpp file based on the exercise.
if(${TESTING} STREQUAL "RouteModel")
  add_executable(${PROJECT_NAME} utest_route_model_class.cpp)
elseif(${TESTING} STREQUAL "RMNodeClass")
  add_executable(${PROJECT_NAME} utest_rm_node_class.cpp)
elseif(${TESTING} STREQUAL "RMSNodes")
  add_executable(${PROJECT_NAME} utest_rm_snodes.cpp)
elseif(${TESTING} STREQUAL "NodeDist")
  add_executable(${PROJECT_NAME} utest_rm_node_dist.cpp)
elseif(${TESTING} STREQUAL "NodeToRoad")
  add_executable(${PROJECT_NAME} utest_rm_hashmap.cpp)
elseif(${TESTING} STREQUAL "FindNeighbors")
  add_executable(${PROJECT_NAME} utest_rm_find_neighbors.cpp)
elseif(${TESTING} STREQUAL "FindClosest")
  add_executable(${PROJECT_NAME} utest_rm_find_closest_node.cpp)
elseif(${TESTING} STREQUAL "AStarStub")
  add_executable(${PROJECT_NAME} utest_rp_a_star_stub.cpp)
elseif(${TESTING} STREQUAL "AStarSearch")
  add_executable(${PROJECT_NAME} utest_rp_a_star_search.cpp)
else()
  # If the user calls CMake with no flags, don't compile any test files.
  add_executable(${PROJECT_NAME})
endif()

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        route_planner
        ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../include)
add_test(
  NAME    ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND ${PROJECT_NAME}
)

unset(TESTING CACHE)
