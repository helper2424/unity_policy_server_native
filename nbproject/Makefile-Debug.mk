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
	${OBJECTDIR}/ClientsQueue.o \
	${OBJECTDIR}/Connector.o \
	${OBJECTDIR}/EvThread.o \
	${OBJECTDIR}/Handler.o \
	${OBJECTDIR}/Server.o \
	${OBJECTDIR}/Thread.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -pedantic -pedantic-errors -Wall -Wextra -Wdeprecated -Wno-unknown-pragmas -march=native -O0
CXXFLAGS=-m64 -pedantic -pedantic-errors -Wall -Wextra -Wdeprecated -Wno-unknown-pragmas -march=native -O0

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lev -lboost_program_options

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ClientsQueue.o: ClientsQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -std=c++11 -o ${OBJECTDIR}/ClientsQueue.o ClientsQueue.cpp

${OBJECTDIR}/Connector.o: Connector.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -std=c++11 -o ${OBJECTDIR}/Connector.o Connector.cpp

${OBJECTDIR}/EvThread.o: EvThread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -std=c++11 -o ${OBJECTDIR}/EvThread.o EvThread.cpp

${OBJECTDIR}/Handler.o: Handler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -std=c++11 -o ${OBJECTDIR}/Handler.o Handler.cpp

${OBJECTDIR}/Server.o: Server.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -std=c++11 -o ${OBJECTDIR}/Server.o Server.cpp

${OBJECTDIR}/Thread.o: Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -std=c++11 -o ${OBJECTDIR}/Thread.o Thread.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -std=c++11 -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/unity_policy_server_native

# Subprojects
.clean-subprojects:
