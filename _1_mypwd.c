#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUFF_LEN 512U

int pwd_main() {
    // Write your code here
    // Do not write a main() function. Instead, deal with pwd_main() as the main function of your program.
    //char cwd_buff [BUFF_LEN] = {0};
    /*
    
    #include <unistd.h>

       char *getcwd(size_t size;
                    char buf[size], size_t size);
       char *get_current_dir_name(void);

       [[deprecated]] char *getwd(char buf[PATH_MAX]);
        The getcwd() function copies an absolute pathname of the current
       working directory to the array pointed to by buf, which is of
       length size.

       If the length of the absolute pathname of the current working
       directory, including the terminating null byte, exceeds size
       bytes, NULL is returned, and errno is set to ERANGE; an
       application should check for this error, and allocate a larger
       buffer if necessary.

       As an extension to the POSIX.1-2001 standard, glibc's getcwd()
       allocates the buffer dynamically using malloc(3) if buf is NULL.
       In this case, the allocated buffer has the length size unless size
       is zero, when buf is allocated as big as necessary.  The caller
       should free(3) the returned buffer.

       get_current_dir_name() will malloc(3) an array big enough to hold
       the absolute pathname of the current working directory.  If the
       environment variable PWD is set, and its value is correct, then
       that value will be returned.  The caller should free(3) the
       returned buffer.
    */
    char *cwd_str = get_current_dir_name();
    if(cwd_str == NULL){
        perror("get_current_dir_name: ");
        fprintf(stderr, "Errno: %d\n", errno);
    }
    else{
        printf("%s\n", cwd_str);
        free(cwd_str);
    }
    
    return 0;
}
