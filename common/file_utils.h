#ifndef __FILE_UTILS__
#define __FILE_UTILS__

void *fileUtils_file_contents(const char *filename, int *length);
void *fileUtils_read_tga(const char *filename, int *width, int *height);

// Return the directory given a path
char* fileUtils_dir_name(char* path);

#endif
