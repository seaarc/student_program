#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>
#define MAX 100     // �ִ� �л� ��
#define SUBJECT 3   // ���� ��

// ����ü ����
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

// �Լ� ������Ÿ��
void input_info(STUDENT *mem);
void output_info(STUDENT *mem, int count);
char calculate_grade(STUDENT *mem, double avg);
void sub_avg(STUDENT *mem, int headcount, int subcount);
void search_info(STUDENT *mem);
void edit_info(STUDENT *mem);
void delete_info(STUDENT *mem);
void insert_info(STUDENT *mem);
void sort_info(STUDENT *mem);

// �Է¹��� �л� �� ����
int headcount = 0;
int subcount = 0;

int main()
{
    STUDENT mem[MAX];
    int cnt_flag = 0;
    int flag = 0;
    int select = 0;

    // �л� �� ����
    while(!cnt_flag){
    printf("��ü �л� ��(100�� ����): ");
    scanf("%d", &headcount);
        if(headcount<=MAX){
            cnt_flag = 1;
        }
    }

    subcount = headcount;

    // ���� ���α׷� �޴� ���
    while(!flag){
        getchar();
        getchar();
        system("cls");
        printf("1: �л� ���� �Է� (�ڵ�)\t");
        printf("2: �л� ���� ���\t");
        printf("3: �л� �˻�\n");
        printf("4: �л� ���� ���� (����)\t");
        printf("5: �л� ���� ����\t");
        printf("6: �л� ���� ����\n");
        printf("7: ������ �������� ����\t\t");
        printf("0: ����\n");

        printf("�޴� ����: ");
        scanf("%d", &select);

        switch(select){
            case 1:
                input_info(mem);
                printf("�Է��� �Ϸ��߽��ϴ�."); break;
            case 2:
                output_info(mem, headcount);
                printf("=============================================================\n");
                sub_avg(mem, headcount, subcount);
                printf("����� �Ϸ��߽��ϴ�."); break;
            case 3:
                search_info(mem);
                break;
            case 4:
                insert_info(mem);
                printf("������ �Ϸ��߽��ϴ�."); break;
            case 5:
                edit_info(mem);
                break;
            case 6:
                delete_info(mem);
                break;
            case 7:
                sort_info(mem);
                printf("������ �Ϸ��߽��ϴ�."); break;
            case 0:
                flag = 1; printf("�����մϴ�"); break;
        }
    }

    return 0;
}

// �л� ���� �ڵ� �Է� �Լ� ����
void input_info(STUDENT *mem)
{
    for(int i=0; i<headcount; i++){
        //�̸� �Է�
        mem[i].name[0] = rand()%26 + 'A';
        mem[i].name[1] = rand()%26 + 'A';
        mem[i].name[2] = rand()%26 + 'A';
        mem[i].name[3] = NULL;

        // �й�, ���� �Է�
        mem[i].id = rand()%10000;
        mem[i].gender = rand()%2;

        // ���� �Է�
        mem[i].kor = rand()%101;
        mem[i].eng = rand()%101;
        mem[i].math = rand()%101;

        // ���� ���
        mem[i].total = mem[i].kor + mem[i].eng + mem[i].math;
        mem[i].avg = mem[i].total / (double)SUBJECT;
        mem[i].grade = calculate_grade(mem, mem[i].avg);
    }
    return;
}

// ���� ��� �Լ� ����
void output_info(STUDENT *mem, int count)
{
    printf("     �̸� �й� ����  ����  ����  ����\t����\t���\t��� \n");

    for(int i=0; i<count; i++){
        printf("%2d %5s %5d %3s %5d %5d %5d %7d %7.1lf %7c \n",
               i+1, mem[i].name, mem[i].id, ((mem[i].gender==0)?"��":"��"),
               mem[i].kor, mem[i].eng, mem[i].math, mem[i].total, mem[i].avg, mem[i].grade);
    }

    return;
}

// ��� ���� �Լ� ����
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

// ���� ��� �Լ� ����
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

    printf("���� ���: %10.2lf \n", kor_avg);
    printf("���� ���: %10.2lf \n", eng_avg);
    printf("���� ���: %10.2lf \n", math_avg);

    return;
}


// �л� �˻� �Լ� ����
void search_info(STUDENT *mem)
{
    char name[10] = {0, };
    int find_flag = 0;

    printf("�˻��� �л��� �̸�(��ҹ��� ���� X): ");
    scanf("%s", name);

    // ��ġ�ϴ� �̸��� �ִ��� ���ڿ� ��
    for(int i=0; i<headcount; i++){
        if(!strnicmp(mem[i].name, name, 3)){
            output_info(&mem[i], 1);
            find_flag = 1;
        }
    }
    // ��ġ�ϴ� �̸��� ���� ���
    if(!find_flag){
        printf("������ ã�� �� �����ϴ�.\n");
    }

    return;
}

// ���� ���� �Լ� ����
void edit_info(STUDENT *mem)
{
    char name[10] = {0, };
    int find_flag = 0;

    printf("������ �л��� �̸�(��ҹ��� ���� X): ");
    scanf("%s", name);

    // ���ڿ��� ���Ͽ� ��ġ�ϴ� �̸��� ���� ��� ���� �Է�
    for(int i=0; i<headcount; i++){
        if(!strnicmp(mem[i].name, name, 3)){

            printf("���� ����: ");
            scanf("%d", &mem[i].kor);
            printf("���� ����: ");
            scanf("%d", &mem[i].eng);
            printf("���� ����: ");
            scanf("%d", &mem[i].math);

            mem[i].total = mem[i].kor + mem[i].eng + mem[i].math;
            mem[i].avg = mem[i].total / (double)SUBJECT;
            mem[i].grade = calculate_grade(mem, mem[i].avg);

            output_info(mem, headcount);

            find_flag = 1;
        }
    }

    if(!find_flag){
        printf("������ ã�� �� �����ϴ�.\n");
    }else{
        printf("\n������ �Ϸ�Ǿ����ϴ�.\n");
    }

    return;
}

// �л� ���� ���� �Լ� ����
void delete_info(STUDENT *mem)
{
    char name[10] = {0, };
    int find_flag = 0;

    printf("������ �л��� �̸�(��ҹ��� ���� X): ");
    scanf("%s", name);

    // ���ڿ��� ���Ͽ� ��ġ�ϴ� �̸��� ���� ��� ���� 0
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
        printf("������ ã�� �� �����ϴ�.\n");
    }else{
        printf("������ �Ϸ�Ǿ����ϴ�.\n");
        subcount--;
        // �л��� ������ �����Ǵ� ���� �ƴ϶� 0���� ǥ���� ���̱� ������, ����� �� ���� ����� ���ϱ� ���� ���� ���� ��-1
    }

    return;
}

// �л� ���� ���� �Լ� ����
void insert_info(STUDENT *mem)
{
    // �л��� ���� �߰� �������� Ȯ��
    if(headcount+1>=MAX){
        printf("�� �̻� �Է��� �Ұ����մϴ�.");
    }else{
        headcount++;
        subcount++;
    }

    // �� �л� �Է�
    printf("�̸�: ");
    scanf("%s", &mem[headcount-1].name[0]);
    printf("�й�: ");
    scanf("%d", &mem[headcount-1].id);
    printf("����(0=����, 1=����): ");
    scanf("%d", &mem[headcount-1].gender);
    printf("�ѱ��� ����: ");
    scanf("%d", &mem[headcount-1].kor);
    printf("���� ����: ");
    scanf("%d", &mem[headcount-1].eng);
    printf("���� ����: ");
    scanf("%d", &mem[headcount-1].math);

    // ���
    mem[headcount-1].total = mem[headcount-1].kor + mem[headcount-1].eng + mem[headcount-1].math;
    mem[headcount-1].avg = mem[headcount-1].total / (double)SUBJECT;
    mem[headcount-1].grade = calculate_grade(mem, mem[headcount-1].avg);

    return;
}

// �л� ���� �Լ� ����
void sort_info(STUDENT *mem)
{
    STUDENT buffer_mem;     // ���� ���� �� ��Ƶ� �� ����ü
    int sort = 0;
    int i, j = 0;

    // ���� ����ü ����
    STUDENT copy_mem[headcount];
    for(i=0; i<headcount; i++){
        memcpy(&copy_mem[i], &mem[i], sizeof(mem[i]));
    }

    printf("��������(0), ��������(1) ����: ");
    scanf("%d", &sort);

    // ��������
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
    // ��������
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
