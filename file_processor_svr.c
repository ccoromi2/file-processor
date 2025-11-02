// file_processor_svr.c
// --------------------------------------------
// 프로세스 협력 파일 처리기 - 서버 프로그램
// 클라이언트로부터 한 줄씩 문자열을 받아서
// 지정된 모드(count, upper, lower, reverse)에 맞게 처리 후 결과를 전송한다.
// --------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_C2S "fifo_c2s" // Client → Server
#define FIFO_S2C "fifo_s2c" // Server → Client
#define BUF_SIZE 1024

// 문자열 뒤집기 함수
void reverse_str(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// 단어 수 계산 함수
int count_words(char *str) {
    int count = 0, in_word = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int main() {
    int fd_read, fd_write;
    char buf[BUF_SIZE];
    char mode[20];
    int line_num = 0;

    // FIFO 생성 (이미 존재하면 무시)
    mkfifo(FIFO_C2S, 0666);
    mkfifo(FIFO_S2C, 0666);

    // FIFO 열기
    fd_read = open(FIFO_C2S, O_RDONLY);
    fd_write = open(FIFO_S2C, O_WRONLY);

    // 첫 번째 메시지로 모드(mode) 수신
    read(fd_read, mode, sizeof(mode));

    while (1) {
        memset(buf, 0, sizeof(buf));
        read(fd_read, buf, sizeof(buf));

        // 클라이언트가 "END"를 보내면 종료
        if (strncmp(buf, "END", 3) == 0) {
            printf("서버 종료\n");
            break;
        }

        line_num++;
        printf("%d번째 줄 처리 중...\n", line_num);

        // 개행 제거
        buf[strcspn(buf, "\n")] = '\0';

        char result[BUF_SIZE] = {0};

        // 모드별 처리
        if (strcmp(mode, "count") == 0) {
            int chars = strlen(buf);
            int words = count_words(buf);
            sprintf(result, "Line %d: %d chars, %d words", line_num, chars, words);
        } 
        else if (strcmp(mode, "upper") == 0) {
            for (int i = 0; buf[i]; i++) buf[i] = toupper(buf[i]);
            sprintf(result, "Line %d: %s", line_num, buf);
        } 
        else if (strcmp(mode, "lower") == 0) {
            for (int i = 0; buf[i]; i++) buf[i] = tolower(buf[i]);
            sprintf(result, "Line %d: %s", line_num, buf);
        } 
        else if (strcmp(mode, "reverse") == 0) {
            reverse_str(buf);
            sprintf(result, "Line %d: %s", line_num, buf);
        } 
        else {
            sprintf(result, "Unknown mode: %s", mode);
        }

        // 결과 전송
        write(fd_write, result, strlen(result) + 1);
    }

    close(fd_read);
    close(fd_write);
    unlink(FIFO_C2S);
    unlink(FIFO_S2C);

    return 0;
}
// file_processor_svr.c
// --------------------------------------------
// 프로세스 협력 파일 처리기 - 서버 프로그램
// 클라이언트로부터 한 줄씩 문자열을 받아서
// 지정된 모드(count, upper, lower, reverse)에 맞게 처리 후 결과를 전송한다.
// --------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_C2S "fifo_c2s" // Client → Server
#define FIFO_S2C "fifo_s2c" // Server → Client
#define BUF_SIZE 1024

// 문자열 뒤집기 함수
void reverse_str(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// 단어 수 계산 함수
int count_words(char *str) {
    int count = 0, in_word = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int main() {
    int fd_read, fd_write;
    char buf[BUF_SIZE];
    char mode[20];
    int line_num = 0;

    // FIFO 생성 (이미 존재하면 무시)
    mkfifo(FIFO_C2S, 0666);
    mkfifo(FIFO_S2C, 0666);

    // FIFO 열기
    fd_read = open(FIFO_C2S, O_RDONLY);
    fd_write = open(FIFO_S2C, O_WRONLY);

    // 첫 번째 메시지로 모드(mode) 수신
    read(fd_read, mode, sizeof(mode));

    while (1) {
        memset(buf, 0, sizeof(buf));
        read(fd_read, buf, sizeof(buf));

        // 클라이언트가 "END"를 보내면 종료
        if (strncmp(buf, "END", 3) == 0) {
            printf("서버 종료\n");
            break;
        }

        line_num++;
        printf("%d번째 줄 처리 중...\n", line_num);

        // 개행 제거
        buf[strcspn(buf, "\n")] = '\0';

        char result[BUF_SIZE] = {0};

        // 모드별 처리
        if (strcmp(mode, "count") == 0) {
            int chars = strlen(buf);
            int words = count_words(buf);
            sprintf(result, "Line %d: %d chars, %d words", line_num, chars, words);
        } 
        else if (strcmp(mode, "upper") == 0) {
            for (int i = 0; buf[i]; i++) buf[i] = toupper(buf[i]);
            sprintf(result, "Line %d: %s", line_num, buf);
        } 
        else if (strcmp(mode, "lower") == 0) {
            for (int i = 0; buf[i]; i++) buf[i] = tolower(buf[i]);
            sprintf(result, "Line %d: %s", line_num, buf);
        } 
        else if (strcmp(mode, "reverse") == 0) {
            reverse_str(buf);
            sprintf(result, "Line %d: %s", line_num, buf);
        } 
        else {
            sprintf(result, "Unknown mode: %s", mode);
        }

        // 결과 전송
        write(fd_write, result, strlen(result) + 1);
    }

    close(fd_read);
    close(fd_write);
    unlink(FIFO_C2S);
    unlink(FIFO_S2C);

    return 0;
}