#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int portno = 9997;
char* host = "127.0.0.1";

int main(int argc, char *argv[]){
    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[256];
    char name[100];
    char age[100];
    char job[100];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("couldnt open socket");
        exit(-1);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, host, &serv_addr.sin_addr) <=0){
        perror("invalid host");
        exit(-1);
    }
    
    serv_addr.sin_port = htons(portno);
    
    if(connect(sockfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        perror("couldn't connect");
        exit(-1);
    }
    printf("Hello welcome to the server! What would you like to do?\n\na)Enter information\n\nb)Close the Server\n\nc)Find out information\n");
    fgets(buffer, 100, stdin);
    n = write(sockfd, buffer, 255);
    if(strcmp(buffer, "a\n") ==0){
        while(1){
            printf("What information would you like to enter?\n\na)Name\n\nb)Age\n\nc)Job\n\nd)Date of Birth\n\ne)Exit\n\n");
            fgets(buffer, 100, stdin);
            n = write(sockfd, buffer, 255);
            if(strcmp(buffer, "a\n")==0){
                printf("enter your name: ");
                bzero(buffer, 256);
                fgets(buffer, 100, stdin);
                n = write(sockfd, buffer, 255);
            }
            if(strcmp(buffer, "b\n")==0){
                printf("enter your age: ");
                bzero(buffer, 256);
                fgets(buffer, 100, stdin);
                n = write(sockfd, buffer, 255);
            }
            if(strcmp(buffer, "c\n")==0){
                printf("enter your job: ");
                bzero(buffer, 256);
                fgets(buffer, 100, stdin);
                n = write(sockfd, buffer, 255);
            }
            if(strcmp(buffer, "d\n")==0){
                printf("enter your DOB: ");
                bzero(buffer, 256);
                fgets(buffer, 100, stdin);
                n = write(sockfd, buffer, 255);
            }
            if(strcmp(buffer, "e\n")==0){
                bzero(buffer, 256);
                break;
                
            }
            if(n < 0){
                perror("couldn't write data to socket");
                }
            if(n < 0){
                perror("couldn't read from socket socket");
                }

            }
            bzero(buffer, 256);
        }
    if(strcmp(buffer, "b\n") == 0){
        bzero(buffer, 256);
    }
    if(strcmp(buffer, "c\n") == 0){
        printf("What information would you like to see?\n\na)All information\n\nb)Names\n\nc)Ages\n\nd)Jobs\n\ne)Birthdates\n");
        fgets(buffer, 100, stdin);
        n = write(sockfd, buffer, 255);
        if(strcmp(buffer, "a\n") == 0){
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            printf("\nPersonal Information: \n");
            printf("%s", buffer);
        }
        if(strcmp(buffer, "b\n") == 0){
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            printf("\nNames: \n\n");
            printf("%s", buffer);
        }
        if(strcmp(buffer, "c\n") == 0){
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            printf("\nAges: \n\n");
            printf("%s", buffer);
        }
        if(strcmp(buffer, "d\n") == 0){
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            printf("\nJobs: \n\n");
            printf("%s", buffer);
        }
        if(strcmp(buffer, "e\n") == 0){
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            printf("\nBirthdates: \n\n");
            printf("%s", buffer);
        }
    }
    close(sockfd);
    return 0;
}