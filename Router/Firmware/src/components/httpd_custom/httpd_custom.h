#ifndef HTTPD_CUSTOM_H_
#define HTTPD_CUSTOM_H_

/** Set this to 1 and provide the functions:
 * - "int fs_open_custom(struct fs_file *file, const char *name)"
 *    Called first for every opened file to allow opening files
 *    that are not included in fsdata(_custom).c
 * - "void fs_close_custom(struct fs_file *file)"
 *    Called to free resources allocated by fs_open_custom().
 */
// #define LWIP_HTTPD_CUSTOM_FILES       1

// int fs_open_custom(struct fs_file *file, const char *name);
// void fs_close_custom(struct fs_file *file);

#endif