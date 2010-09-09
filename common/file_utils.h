#ifndef __FILE_UTILS__
#define __FILE_UTILS__

void *fileUtils_file_contents(const char *filename, GLint *length);
void *fileUtils_read_tga(const char *filename, int *width, int *height);

#endif
