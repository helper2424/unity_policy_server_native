#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ClientsQueue.o \
	${OBJECTDIR}/src/Connector.o \
	${OBJECTDIR}/src/EvThread.o \
	${OBJECTDIR}/src/Handler.o \
	${OBJECTDIR}/src/Server.o \
	${OBJECTDIR}/src/Thread.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -pedantic -pedantic-errors -Wall -Wextra -Wdeprecated -Wno-unknown-pragmas -march=native -g -O0 -fsanitize=address
CXXFLAGS=-m64 -pedantic -pedantic-errors -Wall -Wextra -Wdeprecated -Wno-unknown-pragmas -march=native -g -O0 -fsanitize=address

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lev -lboost_program_options -lpthread -ltbb

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native ${OBJECTFILES} ${LDLIBSOPTIONS} -fsanitize=address

${OBJECTDIR}/src/ClientsQueue.o: src/ClientsQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -I/usr/include/tbb -std=c++11 -o ${OBJECTDIR}/src/ClientsQueue.o src/ClientsQueue.cpp

${OBJECTDIR}/src/Connector.o: src/Connector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -I/usr/include/tbb -std=c++11 -o ${OBJECTDIR}/src/Connector.o src/Connector.cpp

${OBJECTDIR}/src/EvThread.o: src/EvThread.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -I/usr/include/tbb -std=c++11 -o ${OBJECTDIR}/src/EvThread.o src/EvThread.cpp

${OBJECTDIR}/src/Handler.o: src/Handler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -I/usr/include/tbb -std=c++11 -o ${OBJECTDIR}/src/Handler.o src/Handler.cpp

${OBJECTDIR}/src/Server.o: src/Server.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -I/usr/include/tbb -std=c++11 -o ${OBJECTDIR}/src/Server.o src/Server.cpp

${OBJECTDIR}/src/Thread.o: src/Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -I/usr/include/tbb -std=c++11 -o ${OBJECTDIR}/src/Thread.o src/Thread.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -I/usr/include/tbb -std=c++11 -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native

# Subprojects
.clean-subprojects:
