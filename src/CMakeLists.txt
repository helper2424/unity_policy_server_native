add_executable(unity_policy main.cpp Thread.cpp Server.cpp Handler.cpp EvThread.cpp Connector.cpp ClientsQueue.cpp)
target_link_libraries(unity_policy ${Boost_LIBRARIES} ${Libev_LIBRARIES} ${TBB_LIBRARIES})
