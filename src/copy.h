#ifndef COPY_H
#define COPY_H

#include <stdio.h>

int copy_file(const char *source, const char *destination);
int copy_directory(const char *source, const char *destination);
int copy_readme(const char *dest);
int copy_release_notes(const char *dest);
int copy_post(const char *dest);
int copy_file_to_file(const char *src_full_path, const char *dest_full_path);

#endif // COPY_H
