#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define CP_BUF_SIZE 256U

int cp_main(int argc, char *argv[]) {
    // Write your code here
    // Do not write a main() function. Instead, deal with cp_main() as the main function of your program.
    int ret = 0;
    char cp_buf [CP_BUF_SIZE];
    int read_size = 0; int  write_size = 0;
    
    if(argc != 3){
        fprintf(stderr,"Usage: cp src dest\n");
        ret = -1;
        exit(ret);
    }
    
    
    int fd_src, fd_dest;
    if( (fd_src = open(argv[1], O_RDONLY)) < 0   ){
        perror("open: Could not open src file ");
        fprintf(stderr, "errno = %d\n", errno);
        ret = -2;
        goto __ret;
    }
    if( (fd_dest = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644 )) < 0   ){
        perror("open: Could not open dest file ");
        fprintf(stderr, "errno = %d\n", errno);
        ret = -3 ; 
        goto close_src;
    }
    

    while( (read_size =  read(fd_src, cp_buf, CP_BUF_SIZE)) > 0 ){
        if( (write_size =  write(fd_dest, cp_buf, read_size)) !=  read_size ){
            perror("write: Could not write \"read_size\" byte to dest file ");
            fprintf(stderr, "errno = %d\n", errno);

            ret = -4;
            goto close_dest;
        }
    }
    if(read_size < 0 ){
            perror("read: Could not read ant bytes from src file ");
            fprintf(stderr, "errno = %d\n", errno);
            ret = -5;
            goto close_dest;        
    }
    
    
/* Cleanup labels */    
close_dest: 
    close(fd_dest);
close_src: 
    close(fd_src);
__ret:    
    return ret;
}


int mv_main(int argc, char *argv[]) {
    // Write your code here
    // Do not write a main() function. Instead, deal with mv_main() as the main function of your program.
    int ret = 0;
    char mv_buf[CP_BUF_SIZE];
    int fd_src, fd_dest;

    int read_size, write_size;

    if(argc != 3){
        fprintf(stderr,"Usage: mv src dest\n");
        ret = -1;
        exit(ret);
    }

    /* Try a rename for dest file in the same filesystem */
    if( (ret = rename(argv[1], argv[2])) >= 0 ){
        /* renaming/moving in same filesystem under same mount point was successfull */
        goto __ret; /* No need to unlink here */
    }
    else{
        perror("rename error: ");
        fprintf(stderr, "errno = %d\n", errno);
        if( errno == EXDEV ){
            switch((ret = cp_main(argc, argv))){ /* Fallback mechanism */
                case 0: /* Nothing */
                case -1: /* Dead code as this case already handled in mv_main() above */
                    (void)0 ; break;
                default: goto __ret;
            }
        }
    }
    /* remove the old name from the file system */
    if(ret == 0){
        if( (ret = unlink(argv[1])) < 0  ){
            perror("unlink error: ");
            fprintf(stderr, "errno = %d\n", errno);
        }
    }
__ret:
    return ret;
}
