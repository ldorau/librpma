/*
 * Copyright 2020, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * rpma_config.c -- rpma_config unittest
 */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../src/common/fault_injection.h"
#include "../src/config.h"
#include "../src/include/base.h"
#include "unittest.h"

#define RPMA_MSG_SIZE 50
#define RPMA_QUEUE_LENGTH 5
#define RPMA_VALID_FLAGS 1

/*
 * rpma_cfg_create_and_delete_valid - test rpma_config allocation
 */
static void
rpma_cfg_create_and_delete_valid()
{
	struct rpma_config *cfg;

	int ret = rpma_config_new(&cfg);
	assert(ret == 0);
	assert(cfg != NULL);

	ret = rpma_config_delete(&cfg);
	assert(ret == 0);
	assert(cfg == NULL);
}

/*
 * test_cfg_alloc_enomem - test rpma_config allocation with error injection
 */
static int
test_alloc_cfg_enomem()
{
	struct rpma_config *cfg;
	if (!common_fault_injection_enabled()) {
		return 0;
	}
	common_inject_fault_at(PMEM_MALLOC, 1, "rpma_config_new");

	int ret = rpma_config_new(&cfg);

	assert(ret == -ENOMEM);
	assert(cfg == NULL);
	return 0;
}

/*
 * test_config_set_null_addr - test setting NULL IP address
 */
static void
test_config_set_null_addr()
{
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_addr(cfg, NULL);
	assert(ret == -1);
}

/*
 * test_config_set_addr - test setting valid IP address
 */
static void
test_config_set_addr()
{
	char *addr = "127.0.0.1";
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_addr(cfg, addr);
	assert(ret == 0);
	assert(strcmp(cfg->addr, addr) == 0);
}

/*
 * test_config_set_null_service - test setting NULL service
 */
static void
test_config_set_null_service()
{
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_service(cfg, NULL);
	assert(ret == -1);
}

/*
 * test_config_set_addr - test setting valid service
 */
static void
test_config_set_service()
{
	char *service = "2345";
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_service(cfg, service);
	assert(ret == 0);
	assert(strcmp(cfg->service, service) == 0);
}

/*
 * test_config_set_msg_size - test setting message size
 */
static void
test_config_set_msg_size()
{
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_msg_size(cfg, RPMA_MSG_SIZE);
	assert(ret == 0);
	assert(cfg->msg_size == RPMA_MSG_SIZE);
}

/*
 * test_config_set_send_queue_length - test setting send queue length
 */
static void
test_config_set_send_queue_length()
{
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_send_queue_length(cfg, RPMA_QUEUE_LENGTH);
	assert(ret == 0);
	assert(cfg->send_queue_length == RPMA_QUEUE_LENGTH);
}

/*
 * test_config_set_recv_queue_length - test setting receive queue length
 */
static void
test_config_set_recv_queue_length()
{
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_recv_queue_length(cfg, RPMA_QUEUE_LENGTH);
	assert(ret == 0);
	assert(cfg->recv_queue_length == RPMA_QUEUE_LENGTH);
}

/*
 * test_config_set_queue_alloc_funcs - test setting alloc functions
 */
static void
test_config_set_queue_alloc_funcs()
{
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_queue_alloc_funcs(cfg, malloc, free);
	assert(ret == 0);
	assert(cfg->malloc == malloc);
	assert(cfg->free == free);
}

/*
 * test_config_set_valid_flag - test setting valid flag
 */
static void
test_config_set_valid_flag()
{
	struct rpma_config *cfg;
	rpma_config_new(&cfg);

	int ret = rpma_config_set_flags(cfg, RPMA_VALID_FLAGS);
	assert(ret == 0);
	assert(cfg->flags == RPMA_VALID_FLAGS);
}

int
main(int argc, char **argv)
{
	rpma_cfg_create_and_delete_valid();
	test_alloc_cfg_enomem();
	test_config_set_null_addr();
	test_config_set_addr();
	test_config_set_null_service();
	test_config_set_service();
	test_config_set_msg_size();
	test_config_set_send_queue_length();
	test_config_set_recv_queue_length();
	test_config_set_queue_alloc_funcs();
	test_config_set_valid_flag();
}
