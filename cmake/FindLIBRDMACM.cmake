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

message(STATUS "Looking for librdmacm ...")

find_library(LIBRDMACM_LIBRARY
	NAMES librdmacm.so librdmacm.so.1
	PATHS /usr/lib64 /usr/lib)

find_path(LIBRDMACM_INCLUDE_DIR
	NAMES rdma_cma.h
	PATHS /usr/include/rdma)

set(LIBRDMACM_LIBRARIES ${LIBRDMACM_LIBRARY})
set(LIBRDMACM_INCLUDE_DIRS ${LIBRDMACM_INCLUDE_DIR})

set(MSG_NOT_FOUND "librdmacm NOT found (set CMAKE_PREFIX_PATH to point the location)")
if(NOT (LIBRDMACM_LIBRARY AND LIBRDMACM_INCLUDE_DIR))
	if(LIBRDMACM_FIND_REQUIRED)
		message(FATAL_ERROR ${MSG_NOT_FOUND})
	else()
		message(WARNING ${MSG_NOT_FOUND})
	endif()
else()
	message(STATUS "  Found librdmacm library: ${LIBRDMACM_LIBRARY}")
	message(STATUS "  Found librdmacm include directory: ${LIBRDMACM_INCLUDE_DIR}")
endif()

mark_as_advanced(LIBRDMACM_LIBRARY LIBRDMACM_INCLUDE_DIR)
