
int echo_main(int argc, char *argv[]) {
    // Write your code here
    // Do not write a main() function. Instead, deal with echo_main() as the main function of your program.
    if( argc < 2 ){
        /*
        fprintf(stderr, "echo_main: echo_main word1 [word2 .....]\n");
        exit(-1);
        */
        printf("\n");
    }
    int i =0;
    for(i = 1 ; i < argc ; i++){
        printf("%s%s", argv[i], (i != argc-1)?" ":"\n");
    }
    return 0;
}
