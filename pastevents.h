#ifndef __PAST_H
#define __PAST_H
int compare_str(const char *str1, const char *str2);
void store_comm(char** ptr);
void show_pastevents(char ** ptr);
void delete();
void store(char* command,char**ptr);
void  passevents_execute(int index,char**ptr,Queue q);
void format_change(char**ptr);

#endif