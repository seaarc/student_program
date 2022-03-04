#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>
#define MAX 100     // 최대 학생 수
#define SUBJECT 3   // 과목 수

// 구조체 정의
typedef struct STUDENT_INFO{
    char name[10];
    int id;
    int gender;
    int kor;
    int eng;
    int math;
    int total;
    double avg;
    char grade;
}STUDENT;

// 함수 프로토타입
void input_info(STUDENT *mem);
void output_info(STUDENT *mem, int count);
char calculate_grade(STUDENT *mem, double avg);
void sub_avg(STUDENT *mem, int headcount, int subcount);
void search_info(STUDENT *mem);
void edit_info(STUDENT *mem);
void delete_info(STUDENT *mem);
void insert_info(STUDENT *mem);
void sort_info(STUDENT *mem);

// 입력받을 학생 수 변수
int headcount = 0;
int subcount = 0;

int main()
{
    STUDENT mem[MAX];
    int cnt_flag = 0;
    int flag = 0;
    int select = 0;

    // 학생 수 설정
    while(!cnt_flag){
    printf("전체 학생 수(100명 이하): ");
    scanf("%d", &headcount);
        if(headcount<=MAX){
            cnt_flag = 1;
        }
    }

    subcount = headcount;

    // 성적 프로그램 메뉴 출력
    while(!flag){
        getchar();
        getchar();
        system("cls");
        printf("1: 학생 정보 입력 (자동)\t");
        printf("2: 학생 성적 출력\t");
        printf("3: 학생 검색\n");
        printf("4: 학생 정보 삽입 (수동)\t");
        printf("5: 학생 성적 수정\t");
        printf("6: 학생 정보 삭제\n");
        printf("7: 총점을 기준으로 정렬\t\t");
        printf("0: 종료\n");

        printf("메뉴 선택: ");
        scanf("%d", &select);

        switch(select){
            case 1:
                input_info(mem);
                printf("입력을 완료했습니다."); break;
            case 2:
                output_info(mem, headcount);
                printf("=============================================================\n");
                sub_avg(mem, headcount, subcount);
                printf("출력을 완료했습니다."); break;
            case 3:
                search_info(mem);
                break;
            case 4:
                insert_info(mem);
                printf("삽입을 완료했습니다."); break;
            case 5:
                edit_info(mem);
                break;
            case 6:
                delete_info(mem);
                break;
            case 7:
                sort_info(mem);
                printf("정렬을 완료했습니다."); break;
            case 0:
                flag = 1; printf("종료합니다"); break;
        }
    }

    return 0;
}

// 학생 정보 자동 입력 함수 정의
void input_info(STUDENT *mem)
{
    for(int i=0; i<headcount; i++){
        //이름 입력
        mem[i].name[0] = rand()%26 + 'A';
        mem[i].name[1] = rand()%26 + 'A';
        mem[i].name[2] = rand()%26 + 'A';
        mem[i].name[3] = NULL;

        // 학번, 성별 입력
        mem[i].id = rand()%10000;
        mem[i].gender = rand()%2;

        // 점수 입력
        mem[i].kor = rand()%101;
        mem[i].eng = rand()%101;
        mem[i].math = rand()%101;

        // 성적 계산
        mem[i].total = mem[i].kor + mem[i].eng + mem[i].math;
        mem[i].avg = mem[i].total / (double)SUBJECT;
        mem[i].grade = calculate_grade(mem, mem[i].avg);
    }
    return;
}

// 성적 출력 함수 정의
void output_info(STUDENT *mem, int count)
{
    printf("     이름 학번 성별  국어  영어  수학\t총점\t평균\t등급 \n");

    for(int i=0; i<count; i++){
        printf("%2d %5s %5d %3s %5d %5d %5d %7d %7.1lf %7c \n",
               i+1, mem[i].name, mem[i].id, ((mem[i].gender==0)?"여":"남"),
               mem[i].kor, mem[i].eng, mem[i].math, mem[i].total, mem[i].avg, mem[i].grade);
    }

    return;
}

// 등급 산정 함수 정의
char calculate_grade(STUDENT *mem, double avg)
{
    char grade = 0;
    if(avg>=90){
        grade = 'A';
    }else if(avg>=80){
        grade = 'B';
    }else if(avg>=70){
        grade = 'C';
    }else if(avg>60){
        grade = 'D';
    }else{
        grade = 'F';
    }
    return grade;
}

// 과목별 평균 함수 정의
void sub_avg(STUDENT *mem, int headcount, int subcount)
{
    int kor_total = 0;
    int eng_total = 0;
    int math_total = 0;
    double kor_avg = 0.0;
    double eng_avg = 0.0;
    double math_avg = 0.0;

    for(int i=0; i<headcount; i++){
            kor_total += mem[i].kor;
            eng_total += mem[i].eng;
            math_total += mem[i].math;
        }

    kor_avg = kor_total / (double)subcount;
    eng_avg = eng_total / (double)subcount;
    math_avg = math_total / (double)subcount;

    printf("국어 평균: %10.2lf \n", kor_avg);
    printf("영어 평균: %10.2lf \n", eng_avg);
    printf("수학 평균: %10.2lf \n", math_avg);

    return;
}


// 학생 검색 함수 정의
void search_info(STUDENT *mem)
{
    char name[10] = {0, };
    int find_flag = 0;

    printf("검색할 학생의 이름(대소문자 구분 X): ");
    scanf("%s", name);

    // 일치하는 이름이 있는지 문자열 비교
    for(int i=0; i<headcount; i++){
        if(!strnicmp(mem[i].name, name, 3)){
            output_info(&mem[i], 1);
            find_flag = 1;
        }
    }
    // 일치하는 이름이 없을 경우
    if(!find_flag){
        printf("정보를 찾을 수 없습니다.\n");
    }

    return;
}

// 성적 수정 함수 정의
void edit_info(STUDENT *mem)
{
    char name[10] = {0, };
    int find_flag = 0;

    printf("수정할 학생의 이름(대소문자 구분 X): ");
    scanf("%s", name);

    // 문자열을 비교하여 일치하는 이름이 있을 경우 수정 입력
    for(int i=0; i<headcount; i++){
        if(!strnicmp(mem[i].name, name, 3)){

            printf("국어 점수: ");
            scanf("%d", &mem[i].kor);
            printf("영어 점수: ");
            scanf("%d", &mem[i].eng);
            printf("수학 점수: ");
            scanf("%d", &mem[i].math);

            mem[i].total = mem[i].kor + mem[i].eng + mem[i].math;
            mem[i].avg = mem[i].total / (double)SUBJECT;
            mem[i].grade = calculate_grade(mem, mem[i].avg);

            output_info(mem, headcount);

            find_flag = 1;
        }
    }

    if(!find_flag){
        printf("정보를 찾을 수 없습니다.\n");
    }else{
        printf("\n수정이 완료되었습니다.\n");
    }

    return;
}

// 학생 정보 삭제 함수 정의
void delete_info(STUDENT *mem)
{
    char name[10] = {0, };
    int find_flag = 0;

    printf("삭제할 학생의 이름(대소문자 구분 X): ");
    scanf("%s", name);

    // 문자열을 비교하여 일치하는 이름이 있을 경우 정보 0
    for(int i=0; i<headcount; i++){
        if(!strnicmp(mem[i].name, name, 3)){
            strcpy(mem[i].name, "");
            mem[i].id = 0;
            mem[i].gender = 0;
            mem[i].kor = 0;
            mem[i].eng = 0;
            mem[i].math = 0;
            mem[i].total = 0;
            mem[i].avg = 0.0;
            mem[i].grade = 0;

            find_flag = 1;
        }
    }

    if(!find_flag){
        printf("정보를 찾을 수 없습니다.\n");
    }else{
        printf("삭제가 완료되었습니다.\n");
        subcount--;
        // 학생이 정말로 삭제되는 것이 아니라 0으로 표현될 뿐이기 때문에, 제대로 된 과목 평균을 구하기 위해 따로 과목 수-1
    }

    return;
}

// 학생 정보 삽입 함수 정의
void insert_info(STUDENT *mem)
{
    // 학생을 새로 추가 가능한지 확인
    if(headcount+1>=MAX){
        printf("더 이상 입력이 불가능합니다.");
    }else{
        headcount++;
        subcount++;
    }

    // 새 학생 입력
    printf("이름: ");
    scanf("%s", &mem[headcount-1].name[0]);
    printf("학번: ");
    scanf("%d", &mem[headcount-1].id);
    printf("성별(0=여성, 1=남성): ");
    scanf("%d", &mem[headcount-1].gender);
    printf("한국어 점수: ");
    scanf("%d", &mem[headcount-1].kor);
    printf("영어 점수: ");
    scanf("%d", &mem[headcount-1].eng);
    printf("수학 점수: ");
    scanf("%d", &mem[headcount-1].math);

    // 계산
    mem[headcount-1].total = mem[headcount-1].kor + mem[headcount-1].eng + mem[headcount-1].math;
    mem[headcount-1].avg = mem[headcount-1].total / (double)SUBJECT;
    mem[headcount-1].grade = calculate_grade(mem, mem[headcount-1].avg);

    return;
}

// 학생 정렬 함수 정의
void sort_info(STUDENT *mem)
{
    STUDENT buffer_mem;     // 선택 정렬 시 담아둘 빈 구조체
    int sort = 0;
    int i, j = 0;

    // 원본 구조체 복사
    STUDENT copy_mem[headcount];
    for(i=0; i<headcount; i++){
        memcpy(&copy_mem[i], &mem[i], sizeof(mem[i]));
    }

    printf("오름차순(0), 내림차순(1) 선택: ");
    scanf("%d", &sort);

    // 오름차순
    if(sort==0){
        for(i=0; i<headcount-1; i++){
            for(j=i+1; j<headcount; j++){
                if(copy_mem[i].total > copy_mem[j].total){
                    memcpy(&buffer_mem, &copy_mem[i], sizeof(buffer_mem));
                    memcpy(&copy_mem[i], &copy_mem[j], sizeof(buffer_mem));
                    memcpy(&copy_mem[j], &buffer_mem, sizeof(buffer_mem));
                }
            }
        }
    }else{
    // 내림차순
        for(i=0; i<headcount-1; i++){
            for(j=i+1; j<headcount; j++){
                if(copy_mem[i].total < copy_mem[j].total){
                    memcpy(&buffer_mem, &copy_mem[i], sizeof(buffer_mem));
                    memcpy(&copy_mem[i], &copy_mem[j], sizeof(buffer_mem));
                    memcpy(&copy_mem[j], &buffer_mem, sizeof(buffer_mem));
                }
            }
        }
    }

    output_info(copy_mem, headcount);

    return;
}
