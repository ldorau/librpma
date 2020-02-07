#
# Copyright 2018-2019, Intel Corporation
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

add_check_whitespace(man ${CMAKE_CURRENT_SOURCE_DIR}/*.md)

include(FindDoxygen)

if(DOXYGEN_FOUND AND DOXYGEN_DOT_FOUND)
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/librpma.Doxyfile.in"
		       "${CMAKE_CURRENT_BINARY_DIR}/librpma.Doxyfile" @ONLY)

	add_custom_target(doc-doxygen ALL ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/librpma.Doxyfile"
			  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cpp_html/ DESTINATION ${CMAKE_INSTALL_DOCDIR})
elseif(NOT DOXYGEN_FOUND)
	message(WARNING "Doxygen not found - doxygen documentation will not be generated")
else()
	message(WARNING "Dot tool not found - doxygen documentation will not be generated")
endif()

add_custom_target(doc-man ALL
	BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/librpma.7
	COMMENT "Building librpma.7"
	COMMAND ${CMAKE_SOURCE_DIR}/utils/md2man/md2man.sh
		${CMAKE_CURRENT_SOURCE_DIR}/librpma.7.md
		${CMAKE_SOURCE_DIR}/utils/md2man/default.man
		${CMAKE_CURRENT_BINARY_DIR}/librpma.7
	)
