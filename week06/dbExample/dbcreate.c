#include <stdio.h>   // 표준 입출력 함수
#include <stdlib.h>  // 표준 라이브러리 함수 - 메모리 할당, 프로그램 종료(exit)
#include <unistd.h>  // UNIX 표준 API
#include <fcntl.h>   // 파일 제어 관련 함수 - open, close 등
#include "student.h"

/* 학생 정보를 입력받아 데이터베이스 파일에 저장 */
int main(int argc, char *argv[])  // argc: 인자 수, argv: 인자 값 배열
{
    int fd;  // 파일 디스크립터 저장할 변수
    struct student record;  // student 구조체 인스턴스

    /* 인자값 검사 */
    if (argc < 2)  // 명령줄 인자가 부족한 경우
    {
        fprintf(stderr, "사용법 : %s 파일명\n", argv[0]);  // 표준 에러 스트림에 사용방법 출력함
        exit(1);  // 프로그램 종료 및 종료 코드 1 반환
    }
    /* 파일 열기 */
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1)  // 쓰기 전용, 새로 생성, 독점 접근 모드로 열고, fd 값으로 검사
    {
        perror(argv[1]);  // 파일 열기 실패한 경우 에러메시지 출력
        exit(2);  // 프로그램 종료 및 종료 코드 2 반환
    }

    printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");  // 열 정보를 화면에 출력 (지정된 크기, 왼쪽 정렬)

    /* 데이터 입력 및 파일 쓰기 */
    while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3)  // 입력 받기 - 정상 입력되면, 반복해서 입력 받음
    {
        lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);  // 파일 포인터 위치 이동
        write(fd, (char *)&record, sizeof(record));  // 파일에 student 구조체 기록
    }

    close(fd);  // 파일 디스크립터 닫기
    exit(0);    // 프로그램 정상 종료
}