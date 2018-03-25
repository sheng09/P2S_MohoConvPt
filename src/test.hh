#include <cstdlib>
#include <cstdio>

#ifndef __TEST__
#define __TEST__


#ifdef DEBUG
//#define INFO(fmt) "[DPRINT...][%s %d]" fmt "\n"
//#define DPRINT(fmt, args...) fprintf(stderr, INFO(fmt), __FILE__, __LINE__, ##args); 
#define DPRINT(fmt, args...) fprintf(stderr, "[DPRINT...][%s %d] " fmt "\n", __FILE__, __LINE__, ##args); 

#else
#define DPRINT(fmt, ...)  
#endif

#endif
