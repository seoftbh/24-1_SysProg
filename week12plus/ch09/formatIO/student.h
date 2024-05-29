/* 상수 정의 */
#define MAX 24           // 이름 필드의 최대 문자수 지정
#define START_ID 1401001 // 학생 레코드의 위치 지정에 사용되는 시작 학번

/* student 구조체 정의 */
struct student
{
    char name[MAX]; // 이름
    int id;         // 학번
    int score;      // 점수
};