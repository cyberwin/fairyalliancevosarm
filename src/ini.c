/* inih -- simple .INI file parser

inih is released under the New BSD license (see LICENSE.txt). Go to the project
home page for more info:
https://github.com/benhoyt/inih
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "ini.h"

#define MAX_SECTION 50
#define MAX_NAME 50

/* Strip whitespace chars off end of given string, in place. Return s. */
static char* rstrip(char* s)
{
    char* p = s + strlen(s);
    while (p > s && isspace((unsigned char)(*--p)))
        *p = '\0';
    return s;
}

/* Return pointer to first non-whitespace char in given string. */
static char* lskip(const char* s)
{
    while (*s && isspace((unsigned char)(*s)))
        s++;
    return (char*)s;
}

/* Return pointer to first char (of chars) or inline comment in given string,
   or pointer to null at end of string if neither found. Inline comment must
   be prefixed by a whitespace character to register as a comment. */
static char* find_chars_or_comment(const char* s, const char* chars)
{
    int was_whitespace = 0;
    while (*s) {
        if (was_whitespace && (*s == ';' || *s == '#')) {
            return (char*)s;
        }
        if (strchr(chars, *s)) {
            return (char*)s;
        }
        was_whitespace = isspace((unsigned char)(*s));
        s++;
    }
    return (char*)s;
}

/* Version of strncpy that ensures dest (size bytes) is null-terminated. */
static char* strncpy0(char* dest, const char* src, size_t size)
{
    strncpy(dest, src, size);
    dest[size - 1] = '\0';
    return dest;
}

/* Parse given INI-style file. May have [section]s, name=value pairs
   (whitespace stripped), and comments starting with ';' or '#' (inline
   comments are allowed if prefixed by whitespace). Section is "" if name=value
   pair parsed before any section heading. name:value pairs are also supported
   as a concession to Python's configparser.

   For each name=value pair parsed, call handler function with given user
   pointer, section name, name, and value. Handler should return nonzero on
   success, zero on error.

   Returns 0 on success, line number of first error on parse error (doesn't
   stop on first error), -1 on file open error, or -2 on memory allocation
   error (only when INI_USE_STACK is zero).
*/
int ini_parse(const char* filename,
              int (*handler)(void*, const char*, const char*, const char*),
              void* user)
{
    FILE* file;
    char line[INI_MAX_LINE];
    char section[MAX_SECTION] = "";
    char prev_name[MAX_NAME] = "";

    char* start;
    char* end;
    char* name;
    char* value;
    int lineno = 0;
    int error = 0;

    /* Check for NULL handler */
    if (!handler) {
        return -3;
    }

    file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    while (fgets(line, INI_MAX_LINE, file) != NULL) {
        lineno++;

        start = line;
        start = lskip(rstrip(start));

        if (*start == ';' || *start == '#') {
            /* Per Python configparser, allow both ; and # comments at start of line */
            continue;
        }

        if (*start == '[') {
            /* A section line */
            end = find_chars_or_comment(start + 1, "]");
            if (*end == ']') {
                *end = '\0';
                strncpy0(section, start + 1, sizeof(section));
                *prev_name = '\0';
            } else if (!error) {
                /* No ']' found on section line */
                error = lineno;
            }
            continue;
        }

        if (*start == '\0') {
            /* Empty line */
            continue;
        }

        /* Not a comment, section, or empty line: parse name=value pair */
        end = find_chars_or_comment(start, "=:");
        if (*end == '=' || *end == ':') {
            *end = '\0';
            name = rstrip(start);
            value = lskip(end + 1);
            end = find_chars_or_comment(value, NULL);
            if (*end) {
                *end = '\0';
            }
            rstrip(value);

            /* Valid name=value pair found */
            strncpy0(prev_name, name, sizeof(prev_name));
            if (!handler(user, section, name, value) && !error) {
                error = lineno;
            }
        } else if (!error) {
            /* No '=' or ':' found on name=value line */
            error = lineno;
        }
    }

    fclose(file);

    return error;
}
