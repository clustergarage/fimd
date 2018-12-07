/**
 * MIT License
 *
 * Copyright (c) 2018 ClusterGarage
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __ARGUS_NOTIFY__
#define __ARGUS_NOTIFY__

#include <limits.h>
#include <signal.h>
#include <sys/inotify.h>

#include "argusutil.h"

#define ARGUSNOTIFY_KILL SIGKILL

static const size_t INOTIFY_READ_BUF_LEN = (100 * (sizeof(struct inotify_event) + NAME_MAX + 1));

struct arguswatch_event {
    struct arguswatch *watch;
    uint32_t event_mask;
    const char *path_name, *file_name;
    bool is_dir;
};

static int reinitialize(struct arguswatch *watch);
static size_t process_next_inotify_event(struct arguswatch *watch, const char *buf, size_t len, bool first,
    void (*logfn)(struct arguswatch_event *));
static int process_inotify_events(struct arguswatch *watch, void (*logfn)(struct arguswatch_event *));
int start_inotify_watcher(char *name, int pid, int sid, char *nodename, char *podname, unsigned int pathc, char *paths[],
    unsigned int ignorec, char *ignores[], uint32_t mask, bool onlydir, bool recursive, int maxdepth, int processevtfd,
    char *tags, char *logformat, void (*logfn)(struct arguswatch_event *));
void send_watcher_kill_signal(int processfd);

#endif