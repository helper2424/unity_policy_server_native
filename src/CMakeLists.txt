add_executable(unity_policy_server ClientsQueue.cpp Connector.cpp EvThread.cpp Handler.cpp Server.cpp Thread.cpp main.cpp)
target_link_libraries(unity_policy_server ${Boost_LIBRARIES} ${TBB_LIBRARIES} ${LIBEV_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

install (TARGETS unity_policy_server RUNTIME DESTINATION bin)