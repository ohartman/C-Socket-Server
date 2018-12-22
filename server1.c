#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int portno = 9997;

int main(int argc, char *argv[]) {
    char *exitcommand = "exit";
    int sockfd, newsockfd;
    unsigned int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n, i, x;
    char buffer[256];
    char name[256];
    char age[256];
    char job[256];
    char DOB[256];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <0){
        perror("couldn't open socket");
        exit(-1);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("binding failed");
        exit(-1);
    }
    listen(sockfd, 5);
    
    clilen = sizeof(cli_addr);
    x = 1;
    char *array[20];
    char runninglist[1000];
    strcat(runninglist, "\n ------------------------ \n");
    bzero(buffer, 256);
    while(1){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newsockfd < 0){
            perror("accept failed");
            exit(-1);
        }

        n = read(newsockfd, buffer, 255);
        if(strcmp(buffer, "a\n") == 0){
            while(x == 1){
                bzero(buffer, 256);
                n = read(newsockfd, buffer, 255);
                if(strcmp(buffer, "a\n") == 0){
                    bzero(buffer, 255);
                    n = read(newsockfd, buffer, 255);
                    strcat(name, buffer);
                }
                if(strcmp(buffer, "b\n") == 0){
                    bzero(buffer, 255);
                    n = read(newsockfd, buffer, 255);
                    strcat(age, buffer);
                }
                if(strcmp(buffer, "c\n") == 0){
                    bzero(buffer, 255);
                    n = read(newsockfd, buffer, 255);
                    strcat(job, buffer);
                }
                if(strcmp(buffer, "d\n") == 0){
                    bzero(buffer, 255);
                    n = read(newsockfd, buffer, 255);
                    strcat(DOB, buffer);
                }
                if(strcmp(buffer, "e\n") == 0){
                    bzero(buffer, 255);
                    n = read(newsockfd, buffer, 255);
                    break;
                }  
            }
        }
        if(strcmp(buffer, "b\n") == 0){
            close(newsockfd);
            close(sockfd);
            return 0;
            break;
        }
        if(strcmp(buffer, "c\n") == 0){
            n = read(newsockfd, buffer, 255);
            if(strcmp(buffer, "a\n") == 0){    
                bzero(buffer, 256);
                strcat(buffer, "\nNames: \n\n");
                strcat(buffer, name);
                strcat(buffer, "\n ------------------------ \n\n");
                strcat(buffer, "\nAges: \n\n");
                strcat(buffer, age);
                strcat(buffer, "\n ------------------------ \n\n");
                strcat(buffer, "\nJobs: \n\n");
                strcat(buffer, job);
                strcat(buffer, "\n ------------------------ \n\n");
                strcat(buffer, "\nBirthdates: \n\n");
                strcat(buffer, DOB);
                strcat(runninglist, buffer);
                strcat(runninglist, "\n ------------------------ \n\n");
                n = write(newsockfd, runninglist, n);
            }
            if(strcmp(buffer, "b\n") == 0){
                bzero(buffer, 256);
                strcat(buffer, name);
                n = write(newsockfd, buffer, n);
            }
            if(strcmp(buffer, "c\n") == 0){
                bzero(buffer, 256);
                strcat(buffer, age);
                n = write(newsockfd, buffer, n);
            }
            if(strcmp(buffer, "d\n") == 0){
                bzero(buffer, 256);
                strcat(buffer, job);
                n = write(newsockfd, buffer, n);
            }
            if(strcmp(buffer, "e\n") == 0){
                bzero(buffer, 256);
                strcat(buffer, DOB);
                n = write(newsockfd, buffer, n);
            }
        }
    }
}