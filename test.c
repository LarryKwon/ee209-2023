#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <dirent.h>
#include<string.h>
#include <error.h>

void _execv(const char *path, char *const argv[]) {
    int ret;
    pid_t pid;

    pid = fork();
    if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }
    if (pid == 0) {
        ret = execv(path, argv);
        print("%d\n",ret)
        if (ret == -1) { perror("execv"); exit(EXIT_FAILURE); }
    }
    waitpid(-1, NULL, 0);
}

int main() {

    DIR *dir;
    struct dirent *ent;
    dir = opendir("./tests/input");
    int i = 1;
    if(dir != NULL){
        while((ent = readdir(dir))!= NULL){
            char* fileName = ent->d_name;
            char inputPath[256] = "./tests/input/";
            char outputPath[256] = "./tests/output/";
            char outputFileNo[20];
            sprintf(outputFileNo, "output%d.txt" ,i);
            strcat(inputPath, fileName);
            strcat(outputPath,outputFileNo);
            printf("\n[*] ./wc209 < %s > %s\n",inputPath, outputPath);
            char *argv[] = {"./wc209"," < ", inputPath, " > " , outputPath,NULL};
            _execv("./wc209",argv);
            i++;
        }
        closedir(dir);
    }else{
        perror("");
        return EXIT_FAILURE;
    }
    return 0;

}