#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char * GetFileType(struct stat * fileStat, char * access) {
    char * fileType;

    /* use bit mask for file type bit fields to find mode */
    if (S_ISDIR(fileStat->st_mode)){
        fileType = "Directory";
        access[0] = 'd';
    } else if (S_ISREG(fileStat->st_mode)) {
        fileType = "Regular File";
    } else if (S_ISCHR(fileStat->st_mode)) {
        fileType = "Character Device";
        access[0] = 'c';
    } else if (S_ISBLK(fileStat->st_mode)) {
        fileType = "Block Device";
        access[0] = 'b';
    } else if (S_ISFIFO(fileStat->st_mode)) {
        fileType = "FIFO";
        access[0] = 'p';
    } else if (S_ISLNK(fileStat->st_mode)) {
        fileType = "Symbolic Link";
        access[0] = 'l';
    } else {
        fileType = "Unknown";
    }
    return fileType;
}

void SetPermissions( char * perms, struct stat * fstat) {
    /* owner's permmissions */
    if (fstat->st_mode & S_IRUSR){
        perms[1] = 'r';
    }
    if (fstat->st_mode & S_IWUSR) {
        perms[2] = 'w';
    }
    if (fstat->st_mode & S_IXUSR) perms[3] = 'x';

    /* group's permissions */
    if (fstat->st_mode & S_IRGRP) perms[4] = 'r';
    if (fstat->st_mode & S_IWGRP) perms[5] = 'w';
    if (fstat->st_mode & S_IXGRP) perms[6] = 'x';

    /* everyone's permissions */
    if (fstat->st_mode & S_IROTH) perms[7] = 'r';
    if (fstat->st_mode & S_IWOTH) perms[8] = 'w';
    if (fstat->st_mode & S_IXOTH) perms[9] = 'x';
}

void ProcessFile(char * name) {
    struct stat * fileStat;
    char * fileType;
    char permissions[] =  "----------";

    fileStat = (struct stat *)malloc(sizeof(struct stat));
    lstat(name, fileStat);

    /* file name */
    fprintf(stdout, "File: '%s'\n",name);

    /* type */
    fileType = GetFileType(fileStat, permissions);
    fprintf(stdout, "Type: %s\n", fileType);

    /* size */
    fprintf(stdout, "Size: %d\n", (int)(fileStat->st_size));

    /* inode */
    fprintf(stdout, "Inode %d\n", (int)(fileStat->st_ino));

    /* links */
    fprintf(stdout, "Links: %d\n", (int)(fileStat->st_nlink));

    /* access */ 
    SetPermissions(permissions, fileStat);
    fprintf(stdout, "Access: %s\n", permissions);

}


int main(int argc, char ** argv) {
    int i = 1;

    while (i < argc) {
        ProcessFile(argv[i]);
        ++i;
   }
   
    return 1;
    

}

