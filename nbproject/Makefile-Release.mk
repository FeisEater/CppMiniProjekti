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
CND_PLATFORM=Cygwin_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/gstring.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/nvwa/bool_array.o \
	${OBJECTDIR}/nvwa/debug_new.o \
	${OBJECTDIR}/nvwa/mem_pool_base.o \
	${OBJECTDIR}/nvwa/static_mem_pool.o \
	${OBJECTDIR}/string_test.o \
	${OBJECTDIR}/testdriver.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppminiprojekti.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppminiprojekti.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppminiprojekti ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/gstring.o: gstring.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gstring.o gstring.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/nvwa/bool_array.o: nvwa/bool_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/nvwa
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nvwa/bool_array.o nvwa/bool_array.cpp

${OBJECTDIR}/nvwa/debug_new.o: nvwa/debug_new.cpp 
	${MKDIR} -p ${OBJECTDIR}/nvwa
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nvwa/debug_new.o nvwa/debug_new.cpp

${OBJECTDIR}/nvwa/mem_pool_base.o: nvwa/mem_pool_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/nvwa
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nvwa/mem_pool_base.o nvwa/mem_pool_base.cpp

${OBJECTDIR}/nvwa/static_mem_pool.o: nvwa/static_mem_pool.cpp 
	${MKDIR} -p ${OBJECTDIR}/nvwa
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nvwa/static_mem_pool.o nvwa/static_mem_pool.cpp

${OBJECTDIR}/string_test.o: string_test.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/string_test.o string_test.cpp

${OBJECTDIR}/testdriver.o: testdriver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/testdriver.o testdriver.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppminiprojekti.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
