#ifndef __SEEK_H
#define __SEEK_H
void search_e(char*search,char*path,int flag_cond,char* ori_path);
void search_seek_count(char*search,char*path,int*file_count,int*dir_count,char*copy_path );
void search_seek(char*search,char*path,int flag_cond,char* ori_path);
void seek(char*search,char*target_dir,int flag_cond);
#endif