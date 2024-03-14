#pragma once
#include<stdio.h>

#define GETFILENAME(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x

#define CONSOLE_RED "\033[1;31;40m"      //red
#define CONSOLE_GREEN "\033[1;32;40m"	   //green
#define CONSOLE_YELLOW "\033[0;33;40m"		   //yellow
#define CONSOLE_DEFAULT "\033[0m"		       //default
#define CONSOLE_HGREEN	"\033[1;40;32m"
#define trace(format,...) printf("[" CONSOLE_HGREEN " client " CONSOLE_DEFAULT "]" format,##__VA_ARGS__)
#define error(format,...) printf(CONSOLE_RED"[ client ]" format CONSOLE_DEFAULT,##__VA_ARGS__)
#define warnning(format,...) printf("[" CONSOLE_YELLOW " client " CONSOLE_DEFAULT "]" format,##__VA_ARGS__)
#define print(format,...) printf("[ client ]" format"",##__VA_ARGS__)


#define trace_tf(format,...) printf("[" CONSOLE_HGREEN " client " CONSOLE_DEFAULT "][%s|%s|File:%s|Line:%d]" format,__DATE__,__TIME__,GetFImeName(__FILE__),__LINE__,##__VA_ARGS__)
#define error_tf(format,...) printf(CONSOLE_RED"[ client ][%s|%s|File:%s|Line:%d]" format CONSOLE_DEFAULT,__DATE__,__TIME__,__FILE__,__LINE__,##__VA_ARGS__)
#define warnning_tf(format,...) printf("[" CONSOLE_YELLOW " client " CONSOLE_DEFAULT "][%s|%s|File:%s|Line:%d]" format,__DATE__,__TIME__,__FILE__,__LINE__,##__VA_ARGS__)
#define print_tf(format,...) printf("[ client ][File:%s|Line:%d]" format"",GetFImeName(__FILE__),__LINE__,##__VA_ARGS__)


#define sys_trace(format,...) printf("[\033[1;32;40m core \033[0m]" format,##__VA_ARGS__)
#define sys_error(format,...) printf("\033[1;31;40m[ core ]" format"\033[0m",##__VA_ARGS__)
#define sys_warnning(format,...) printf("\033[0;33;40m[ core ]" format"\033[0m",##__VA_ARGS__)
#define sys_print(format,...) printf("[ core ]" format,##__VA_ARGS__)

#define sys_trace_tf(format,...) printf("[\033[1;32;40m core \033[0m][%s|%s|File:%s|Line:%d]" format,__DATE__,__TIME__,__FILE__,__LINE__,##__VA_ARGS__)
#define sys_error_tf(format,...) printf("\033[1;31;40m[ core ][%s|%s|File:%s|Line:%d]" format"\033[0m",__DATE__,__TIME__,__FILE__,__LINE__,##__VA_ARGS__)
#define sys_warnning_tf(format,...) printf("\033[0;33;40m[ core ][%s|%s|File:%s|Line:%d]" format"\033[0m",__DATE__,__TIME__,__FILE__,__LINE__,##__VA_ARGS__)
#define sys_print_tf(format,...) printf("[ core ][File:%s|Line:%d]" format,__FILE__,__LINE__,##__VA_ARGS__)