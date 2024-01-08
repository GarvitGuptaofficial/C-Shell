#ifndef __PEEK_H
#define __PEEK_H
#include <dirent.h>
void information_about_file(struct dirent * dir_info,char *dir_path);
int hidden_filter(const struct dirent * q);
void peek(char*argument,int condition);

#endif