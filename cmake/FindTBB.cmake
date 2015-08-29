# - Find TBB
#
#  TBB_INCLUDE_DIR
#  TBB_LIBRARIES
#  TBB_FOUND

if (TBB_INCLUDE_DIR)
  # Already in cache, be silent
  set(TBB_FIND_QUIETLY TRUE)
endif (TBB_INCLUDE_DIR)

find_package(PkgConfig)
PKG_SEARCH_MODULE(Tbb tbb)
SET(TBB_INCLUDE_DIRS ${Tbb_INCLUDE_DIRS})
SET(TBB_LIBRARIES ${Tbb_LIBRARIES} CACHE STRING "")

find_path(TBB_INCLUDE_DIR tbb.h
  /usr/include/tbb
  /usr/local/include/tbb
)

if (TBB_INCLUDE_DIR AND TBB_LIBRARIES)
  set(TBB_FOUND TRUE)
else (TBB_INCLUDE_DIR AND TBB_LIBRARIES)
  set(TBB_FOUND FALSE)
endif (TBB_INCLUDE_DIR AND TBB_LIBRARIES)

if (TBB_FOUND)
  if (NOT TBB_FIND_QUIETLY)
    message(STATUS "Found Thread Building Blocks: ${TBB_LIBRARIES}")
  endif (NOT TBB_FIND_QUIETLY)
else (TBB_FOUND)
  if (TBB_FIND_REQUIRED)
    message(STATUS "Looked for Thread Building Blocks library")
    message(FATAL_ERROR "Could NOT find Thread Building Blocks library")
  endif (TBB_FIND_REQUIRED)
endif (TBB_FOUND)

mark_as_advanced(
  TBB_LIBRARIES
  TBB_INCLUDE_DIR
)