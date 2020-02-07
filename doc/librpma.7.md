---
layout: manual
Content-Style: 'text/css'
title: _MP(LIBRPMA.7)
collection: rpma
header: LIBRPMA
...

[NAME](#name)<br />
[SYNOPSIS](#synopsis)<br />
[DESCRIPTION](#description)<br />

[comment]: <> (Copyright 2020, Intel Corporation)

[comment]: <> (Redistribution and use in source and binary forms, with or without)
[comment]: <> (modification, are permitted provided that the following conditions)
[comment]: <> (are met:)
[comment]: <> (    * Redistributions of source code must retain the above copyright)
[comment]: <> (      notice, this list of conditions and the following disclaimer.)
[comment]: <> (    * Redistributions in binary form must reproduce the above copyright)
[comment]: <> (      notice, this list of conditions and the following disclaimer in)
[comment]: <> (      the documentation and/or other materials provided with the)
[comment]: <> (      distribution.)
[comment]: <> (    * Neither the name of the copyright holder nor the names of its)
[comment]: <> (      contributors may be used to endorse or promote products derived)
[comment]: <> (      from this software without specific prior written permission.)

[comment]: <> (THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS)
[comment]: <> ("AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT)
[comment]: <> (LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR)
[comment]: <> (A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT)
[comment]: <> (OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,)
[comment]: <> (SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT)
[comment]: <> (LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,)
[comment]: <> (DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY)
[comment]: <> (THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT)
[comment]: <> ((INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE)
[comment]: <> (OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.)

# NAME #

**rpma** - ...

# SYNOPSIS #

```c
#include <librpma.h>

int rpma_open(void);

void rpma_close(void);

const char *rpma_errormsg(void);

```

# DESCRIPTION #

**librpma** is ...

`int rpma_open(void);`

:   Opens ...

`void rpma_close(void);`

:   Closes ...

`const char *rpma_errormsg(void);`

:   Retrieves a human-friendly description of the last error.

##### Errors #####

On an error, a machine-usable description is passed in `errno`. It may be:

+ **EINVAL** -- nonsensical/invalid parameter
+ **ENOMEM** -- out of DRAM
+ **EEXIST** -- (put) entry for that key already exists
+ **ENOENT** -- (evict, get) no entry for that key
+ **ESRCH** -- (evict) could not find an evictable entry
+ **EAGAIN** -- (evict) an entry was used and could not be evicted, please try again
+ **ENOSPC** -- (create, put) not enough space in the memory pool
