#ifndef HEADERS_H_
#define HEADERS_H_
#include<string.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include<math.h>
#include "prompt.h"
#include <sys/stat.h>
#include<pwd.h>
#include "peek.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include "proclore.h"
#include "warp.h"
#include "seek.h"
#include "queue.h"
#include <signal.h>
#include "run.h"
#include "foreandback.h"
#include "pastevents.h"
extern char curr_dir[300];
extern char initial_dir[300];
extern char file_path[350];
extern char prev_dir[300];
extern char promptprocess[304];
extern int prevdir_condition;
extern int comm_count;
#endif