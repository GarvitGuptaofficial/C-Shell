#include "headers.h"
char curr_dir[300]="~";
char prev_dir[300]="";
char file_path[350];
char promptprocess[304]="";
char initial_dir[300];
int prevdir_condition=0;
int foreground_running=0;
int ori_stdin_fd;
int ori_stdout_fd;
int comm_count=0;
int store_comm_cond=1;
// size_t size=4096;