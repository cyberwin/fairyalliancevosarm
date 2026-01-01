#ifndef __INI_H__
#define __INI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifndef INI_HANDLER_LINENO
#define INI_HANDLER_LINENO 0
#endif

#ifndef INI_MAX_LINE
#define INI_MAX_LINE 200
#endif

typedef int (*ini_handler)(void* user, const char* section,
                          const char* name, const char* value);

int ini_parse(const char* filename, ini_handler handler, void* user);
int ini_parse_file(FILE* file, ini_handler handler, void* user);

#ifdef __cplusplus
}
#endif

#endif // __INI_H__
