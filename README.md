# 학생 성적 관리 프로그램

학생의 성적을 입·출력하고, 이름으로 검색, 학생 정보 수정, 학생 정보 삭제 및 학생 정보를 총점순 정렬할 수 있는 프로그램   

## Environment
Codeblocks 20.3.0.0   
GNU GCC Complier

## Descripton
> 함수 목록

|기능|함수명|
|------|---|
|학생 정보 자동 입력|input_info|
|학생 성적 및 과목별 평균 출력|output_info|
|등급 계산 함수|calculate_grade|
|과목별 평균 계산 함수|sub_avg|
|학생 검색|search_info|
|학생 정보 수동 삽입|insert_info|
|학생 성적 수정|edit_info|
|학생 정보 삭제|delete_info|
|총점 기준 학생 정렬|sort_info|   
<br>

> #### 학생 정보 자동 입력
rand 함수 사용하여 학생 정보 입력
    
    for(int i=0; i<headcount; i++){
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
        }
<br>

> #### 학생 검색, 학생 정보 수정, 학생 정보 삭제
strnicmp(const char *s1, const char *s2, size) 사용하여 문자열 비교 - 입력한 이름과 찾는 이름이 일치할 경우 검색 결과 출력/정보 수정

    for(int i=0; i<headcount; i++){
        if(!strnicmp(mem[i].name, name, 3)){
            output_info(&mem[i], 1);
            find_flag = 1;
        }
    }
    if(!find_flag){
        printf("정보를 찾을 수 없습니다.\n");
    }
<br>

> #### 학생 정보 삭제
완전히 삭제하는 대신 0으로 뜨도록 처리
strnicmp를 사용하여 문자열을 비교한 후, strcpy(char *dest, const char *src) 사용하여 기존 배열에 새로운 정보 덮어씌우기

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
<br>

> #### 학생 정보 추가 입력
최대값을 넘지는 않는지 확인한 후, 넘지 않는다면 처음 입력한 학생 정원을 추가로 늘림

    if(headcount+1>=MAX){
        printf("더 이상 입력이 불가능합니다.");
    }else{
        headcount++;
    }
<br>

> #### 학생 정렬
- 원본은 남겨 두고 따로 정렬 : 원본 구조체의 사본으로 정렬 실행
- buffer_mem라는 빈 구조체 사용
- memcpy(void *dest, const void *src, sizeof()) 사용하여 선택 정렬
<br>

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
<br>

> #### 과목별 평균
문제 요인
1. 학생을 삭제할 경우 데이터를 아예 없애는 대신 0으로 표시하는 방식
2. 정보가 누락되어선 안 되므로 headcount(학생 수)에 변동을 줄 수 없음
3. 과목별 평균을 구할 때 headcount로 총점을 나눌 시 원하는 값이 구해지지 않는 문제가 발생   

<br>

    if(!find_flag){
        printf("정보를 찾을 수 없습니다.\n");
    }else{
        printf("삭제가 완료되었습니다.\n");
        subcnt--;
    }
    
→ 해결을 위해 과목 수 headcount와 동일한 초기값을 받는 subcnt 변수를 따로 만들고, delete_info 함수가 작동할 때 과목 수가 줄도록 만듦

<pre>
kor_avg = kor_total / (double)subcnt;
eng_avg = eng_total / (double)subcnt;
math_avg = math_total / (double)subcnt;
</pre>
→ sub_avg 함수에서 subcnt로 과목별 평균 계산
