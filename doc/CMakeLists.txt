#
# Copyright 2019-2020, Intel Corporation
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

add_check_whitespace(man
	${CMAKE_CURRENT_SOURCE_DIR}/*.md)

find_program(PANDOC NAMES pandoc)
if(PANDOC)
	# convert md files to manpage format
	add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/man/librpma.7
		MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/doc/librpma.7.md
		COMMAND ${CMAKE_SOURCE_DIR}/utils/md2man/md2man.sh
			${CMAKE_SOURCE_DIR}/doc/librpma.7.md
			${CMAKE_SOURCE_DIR}/utils/md2man/default.man
			${CMAKE_BINARY_DIR}/man/librpma.7
			${VERSION})
	add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/man/rpma_config_new.3
		MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/doc/rpma_config_new.3.md
		COMMAND ${CMAKE_SOURCE_DIR}/utils/md2man/md2man.sh
			${CMAKE_SOURCE_DIR}/doc/rpma_config_new.3.md
			${CMAKE_SOURCE_DIR}/utils/md2man/default.man
			${CMAKE_BINARY_DIR}/man/rpma_config_new.3
			${VERSION})
	add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/man/rpma_domain_new.3
		MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/doc/rpma_domain_new.3.md
		COMMAND ${CMAKE_SOURCE_DIR}/utils/md2man/md2man.sh
			${CMAKE_SOURCE_DIR}/doc/rpma_domain_new.3.md
			${CMAKE_SOURCE_DIR}/utils/md2man/default.man
			${CMAKE_BINARY_DIR}/man/rpma_domain_new.3
			${VERSION})
	add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/man/rpmem_persist.3
		MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/doc/rpmem_persist.3.md
		COMMAND ${CMAKE_SOURCE_DIR}/utils/md2man/md2man.sh
			${CMAKE_SOURCE_DIR}/doc/rpmem_persist.3.md
			${CMAKE_SOURCE_DIR}/utils/md2man/default.man
			${CMAKE_BINARY_DIR}/man/rpmem_persist.3
			${VERSION})

	# install manpages
	install(FILES ${CMAKE_BINARY_DIR}/man/librpma.7
		DESTINATION ${CMAKE_INSTALL_MANDIR}/man7)
	install(FILES ${CMAKE_BINARY_DIR}/man/rpma_config_new.3
		DESTINATION ${CMAKE_INSTALL_MANDIR}/man3)
	install(FILES ${CMAKE_BINARY_DIR}/man/rpma_domain_new.3
		DESTINATION ${CMAKE_INSTALL_MANDIR}/man3)
	install(FILES ${CMAKE_BINARY_DIR}/man/rpmem_persist.3
		DESTINATION ${CMAKE_INSTALL_MANDIR}/man3)
else()
	message(WARNING "pandoc not found - man pages will not be generated")
endif()

include(FindDoxygen)
if(DOXYGEN_FOUND AND DOXYGEN_DOT_FOUND)
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/librpma.Doxyfile.in"
		"${CMAKE_CURRENT_BINARY_DIR}/librpma.Doxyfile" @ONLY)
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cpp_html/ DESTINATION ${CMAKE_INSTALL_DOCDIR})
elseif(NOT DOXYGEN_FOUND)
	message(WARNING "Doxygen not found - Doxygen documentation will not be generated")
else()
	message(WARNING "Dot tool not found - Doxygen documentation will not be generated")
endif()

if(PANDOC AND DOXYGEN_FOUND AND DOXYGEN_DOT_FOUND)
	add_custom_target(doc ALL
		${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/librpma.Doxyfile"
		DEPENDS ${CMAKE_BINARY_DIR}/man/librpma.7
		DEPENDS ${CMAKE_BINARY_DIR}/man/rpma_config_new.3
		DEPENDS ${CMAKE_BINARY_DIR}/man/rpma_domain_new.3
		DEPENDS ${CMAKE_BINARY_DIR}/man/rpmem_persist.3
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
elseif(PANDOC)
	add_custom_target(doc ALL
		DEPENDS ${CMAKE_BINARY_DIR}/man/librpma.7
		DEPENDS ${CMAKE_BINARY_DIR}/man/rpma_config_new.3
		DEPENDS ${CMAKE_BINARY_DIR}/man/rpma_domain_new.3
		DEPENDS ${CMAKE_BINARY_DIR}/man/rpmem_persist.3
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
elseif(DOXYGEN_FOUND AND DOXYGEN_DOT_FOUND)
	add_custom_target(doc ALL
		${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/librpma.Doxyfile"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()
