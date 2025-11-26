#ifndef HEADERS_H_
#define HEADERS_H_
#include<string.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <signal.h>
#include<math.h>
#include "prompt.h"
#include <sys/stat.h>
#include<pwd.h>
#include "peek.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <ctype.h>
#include "proclore.h"
#include "neonate.h"
#include "man.h"
#include "kill.h"
#include "warp.h"
#include "seek.h"
#include "queue.h"
#include "fgandbg.h"
#include "activities.h"
#include "pipingcommand.h"
#include <signal.h>
#include "run.h"
#include "foreandback.h"
#include "pastevents.h"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"
extern char curr_dir[300];
extern char initial_dir[300];
extern char file_path[350];
extern char prev_dir[300];
extern char promptprocess[304];
extern int prevdir_condition;
extern int comm_count;
extern int ori_stdin_fd;
extern int ori_stdout_fd;
extern int foreground_running;
extern int store_comm_cond;
#endif