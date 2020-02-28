#
# Copyright 2020, Intel Corporation
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in
#       the documentation and/or other materials provided with the
#       distribution.
#
#     * Neither the name of the copyright holder nor the names of its
#       contributors may be used to endorse or promote products derived
#       from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

project(rpma C)

add_cppstyle(src
	${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/common/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_check_whitespace(src
	${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/common/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

set(SOURCES
	common/alloc.c
	common/os_posix.c
	common/os_thread_posix.c
	common/out.c
	common/ravl.c
	common/util.c
	common/util_posix.c
	config.c
	connection.c
	dispatcher.c
	librpma.c
	memory.c
	msg.c
	rma.c
	rpma.c
	rpma_utils.c
	zone.c)

add_library(rpma SHARED ${SOURCES})

target_include_directories(rpma PRIVATE . include common)

target_link_libraries(rpma PRIVATE
	${LIBPMEM_LIBRARIES}
	${LIBIBVERBS_LIBRARIES}
	${LIBRDMACM_LIBRARIES}
	-Wl,--version-script=${CMAKE_SOURCE_DIR}/src/librpma.map)

set(RPMA_PUBLIC_HEADERS
	include/librpma.h
	include/base.h
	include/msg.h
	include/rma.h)

set_target_properties(rpma PROPERTIES
	SOVERSION 0
	PUBLIC_HEADER "${RPMA_PUBLIC_HEADERS}")

target_compile_definitions(rpma PRIVATE SRCVERSION="${SRCVERSION}")

if(VALGRIND_FOUND)
	target_include_directories(rpma PRIVATE src/valgrind)
	# Enable librpma valgrind annotations
	target_compile_options(rpma PRIVATE -DLIBRPMA_VG_ENABLED=1)
endif()

install(TARGETS rpma
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
