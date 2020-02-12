#
# Copyright 2018-2020, Intel Corporation
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

include(ctest_helpers.cmake)

add_cppstyle(tests-common
	${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/common/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/check_is_pmem/*.[ch])

add_check_whitespace(tests-common
	${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/common/*.[ch]
	${CMAKE_CURRENT_SOURCE_DIR}/check_is_pmem/*.[ch])

add_check_whitespace(tests-cmake
	${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)

if(MSVC_VERSION)
	add_flag(-W3)

	# disable warning C4996 - disable checking iterators
	add_flag(-D_SCL_SECURE_NO_WARNINGS)

	# disable warning C4996 - disable deprecation of getenv and strcpy functions
	add_flag(-D_CRT_SECURE_NO_WARNINGS)

	# fix C1128 raised for some test binaries
	add_flag(-bigobj)
else()
	add_flag(-Wall)
endif()

add_flag(-Wpointer-arith)
add_flag(-Wunused-macros)
add_flag(-Wsign-conversion)
add_flag(-Wsign-compare)
add_flag(-Wunreachable-code-return)
add_flag(-Wmissing-variable-declarations)
add_flag(-fno-common)

add_flag(-ggdb DEBUG)
add_flag(-DDEBUG DEBUG)

add_flag("-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2" RELEASE)

if(USE_ASAN)
       add_sanitizer_flag(address)
endif()
if(USE_UBSAN)
       add_sanitizer_flag(undefined)
endif()

if(COVERAGE)
       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -coverage")
endif()

find_packages()
find_gdb()

add_library(test_backtrace STATIC test_backtrace.c)
if(LIBUNWIND_FOUND)
	target_compile_definitions(test_backtrace PUBLIC USE_LIBUNWIND=1)
endif()

add_library(valgrind_internal STATIC valgrind_internal.c)

add_executable(check_is_pmem check_is_pmem/check_is_pmem.c)
target_link_libraries(check_is_pmem ${LIBPMEM_LIBRARIES})

build_test(template-test template-test/template-test.c)
add_test_generic(NAME template-test CASE 0 TRACERS none)
add_test_generic(NAME template-test CASE 1 TRACERS none)
add_test_generic(NAME template-test CASE 2 TRACERS none)
add_test_generic(NAME template-test CASE 3 TRACERS none)
add_test_generic(NAME template-test CASE 4 TRACERS none)
add_test_generic(NAME template-test CASE 5 TRACERS none)

set(RPMA_CONFIG_SOURCES
	rpma_config/rpma_config.c
	../src/config.c
	../src/common/alloc.c
	../src/common/os_posix.c
	../src/common/os_thread_posix.c
	../src/common/out.c
	../src/common/util.c
	../src/common/util_posix.c)

build_test(rpma_config ${RPMA_CONFIG_SOURCES})
target_link_directories(rpma_config PRIVATE ${LIBRPMA_LIBRARY_DIRS})
target_compile_definitions(rpma_config PRIVATE SRCVERSION="${SRCVERSION}")
target_include_directories(rpma_config PRIVATE ${LIBRPMA_INCLUDE_DIRS} ../src/include ../src/common)
target_link_libraries(rpma_config rpma ${LIBRPMEM_LIBRARIES})
add_test_generic(NAME rpma_config CASE 0 TRACERS none)

