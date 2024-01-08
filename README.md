PART A:-

# Description

1. 'headers.h' is the main header main including all libraries and extern statements used to make variables access to all files.

2.  'commandstore.txt' file is used to store previously entered commands.

3. 'ter_val.c' contains variables:-
        
        (1) curr_dir: stores address of current directory wrt home directory(~).
        
        (2) prev_dir: contains address of previous directory wrt homedirecctory(~).
        
        (3) file_path: contains path of 'commandstore.txt' wrt system.
        
        (4) promptprocess: conatins process to be shown on prompt.
        
        (5) initial_dir:  conatins code's directory address wrt system.
        
        (6) prevdir_condition: a flag to check whether any other directory is accessed or not.
        
        (7) comm_count: To store number of commands entered mod 15.

4.  MAIN.C FILE:-
         
        (1) Data structures such as Queue , 2D char array(use to store previous commands) are initialised inside it.
        
        (2) It takes input , then checks in queue whether a background has completed or not, then passes the entered command to 'runcommand' func present in 'run.c'.

5. RUN.C FILE:-
        
        (1) Input string is first tokenised and then first checks whether the command is foreground or background and then checks whether it is user defined command or not and output accordingly.
        
        (2) If a command is not user defined command then it is passed 'fore_back' func which is present in 'foreandback.c' file which executes it on the basis of foreground or background process.

6. QUEUE.C:- It contains functions related to queue like standard push and pop          function  , 'find_delete' which deletes an queue node(linked list implementation) which matches a specific id.

7. FOREANDBACK.C FILE:-
         
        (1) Contains a function 'fore_back' which takes command and a condition 'back_cond' whether it is foreground or background and execute accordinly.
        
        (2) It forks the process use 'execvp' in child process if command entered is
        foreground then use 'waitpid' to wait for child process and if backgorund then do not wait for child process.
        
        (3) Stores pid of backgorund process alonmg with command in queue.
       
        (4) Calculates time of foregorund process execution.

8. PASTEVENTS FILE :-

        Functions conatined:-

        (1) store_comm: use to count number of commands present in 'commandstore.txt'file and store in comm_count.
        
        (2) compare_str: compares two strings on the basis of characters except space and tab,returns 1 if true.
        
        (3) show_pastevents: Prints commands stored in 2D array ptr in which previous commands were stored.
        
        (4) delete: deletes the content of file 'commadstore.txt' by opening file in write mode.
         
        (5) store: Used to store command in file and ptr array.
         
        (6) passevents_execute: Used to execute pastevent stored in 2D arr.
        
        (7) format_change: Used to update file with commands stored in 2D arr ptr.

9. PEEK.C:-
        Function conatined:-

        (1)information_about_file:Prints information about file like ls command stat function and its macros.

        (2)hidden_filter: filter function used by scandir to filter files on the basis whether first character is . or not(i.e for hidden files).

        (3)peek: Used to print information by files and directory like ls commad using scandir.

10. PROCLORE.C:-
        Function conatined:-

        (1)process: searches for a process directory status file in proc with given pid and then prints information regarding process.

11. PROMPT.C:-
        Function conatined:-
        
        (1)prompt: prints prompt by using curr_dir to print current directory relative to ~, username,sysname,process which take more than 2 sec.

12. SEEK.C:-
        Function conatined:-

        (1)check_names:Used to match file name with search name given.

        (2)give_relpath:Gives rel path of dir A wrt dir B.

        (3)search_seek_count: count number of files and directory matching with search name and store path of matched file.

        (4)search_seek: Used to implement seek i.e print rel path of matched files when -e flag is not used.

        (5)seek: Used to check for condition whether -e flag is used or not and then call functions accordingly.

13. WARP.C:-
        Function conatined:-

        (1)convertdir_to_original:Used to convert rel path od dir to absolute path wrt system.

        (2)covert_to_prompt:Used to convert dir to wrt to ~ to print in prompt.

        (3)change_dir:Used to change dir using chdir and update prev_dir and curr_dir.

        (4)warp_func:Used to call above functions accordingly and chack for OLDPWD is set or not.




# Assumptions

1. Assuming the directory in which all code is present as home directory.

2. If you are giving path before code's home directory then  give absolute path wrt to root and for relative .. . and etc works.

3. If you are giving absolute path for files after or in code directory then give it relative to home directory like ~/something , for relative it is fine.

4. If in seek suppose flags -f -e is passed and more than one filename match is found then it will just print file path relative to directory given same for -d -e.

5. For flags if more than two flags are given then it will be valid if there is a space between them.

6. For foreground process taking more than 2 sec ,it will be showned in prompt but on accepting next command that foreground process command will be removed from prompt.

7. For directory before code's directory prompt will show absolute path wrt to system and will print absolute path wrt to sysytem in warp command.

8. At many places perror is not used instead a printf statement is used to denote error.

9. Not implemented exit command and storing it.

