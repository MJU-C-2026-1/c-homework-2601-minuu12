/* 파일이름 : main.c
   작 성 자 : 60222530 최민우
   하 는 일 : 시나리오 계획 및 코드 작성 (4차 과제 - 배열 및 포인터 적용)
*/
#include <stdio.h>

float g_health_data[5];
char g_gender;
float g_bmr;
int g_is_data_exist = 0;

void input_health_data();
float calculate_bmi(float height, float weight);
void calculate_bmr_tdee(char gender, float height, float weight, float ex_time);
void print_report_with_pointer(float arr[]); //배열을 매개변수 형태로 전달받는 함수 정의

int main()
{
  int choice;
  for (int i=0; i<5; i++) {
    g_health_data[i] = 0.0;
  }
  while(1) {
    printf("\n===[V4.0] 배열&포인터 기반 건강 분석 시스템 ====\n");
    printf("1. 건강 데이터 입력 (성별/키/몸무게/운동시간)\n");
    printf("2. 건강 지수 계산 (BMI/BMR/TDEE 계산)\n");
    printf("3. 건강 분석 결과 리포트 및 가이드 조회\n");
    printf("4. 프로그램 종료\n");
    printf("===========================================\n");
    printf("원하는 메뉴를 입력하세요: ");
    scanf("%d", &choice);

    if (choice == 1) {
      input_health_data();
    }
    else if (choice == 2) {
      if (g_is_data_exist == 0) {
        printf("\n[알림] 먼저 1번 메뉴에서 건강 데이터를 입력하세요.\n");
      }
      else { 
        g_health_data[3] = calculate_bmi(g_health_data[0], g_health_data[1]);
        calculate_bmr_tdee(g_gender, g_health_data[0], g_health_data[1], g_health_data[2]);
        printf("\n[연산 완료] 모든 건강 지수 계산이 완료됐습니다.\n");
      }
    } 
    else if (choice == 3) {
      if (g_is_data_exist == 0) {
        printf("\n[알림] 먼저 1번 메뉴에서 건강 데이터를 입력하세요.\n");
      }
      else if(g_health_data[3] == 0.0) {
        printf("\n[알림] 먼저 2번 메뉴에서 건강 지수 연산을 진행해 주세요.\n");
      }
      else { 
        print_report_with_pointer(g_health_data);
      }
    } 
    else if (choice == 4) {
      printf("\n프로그램을 종료합니다.\n");
      break;
    } 
    else { 
      printf("\n[오류] 잘못된 입력입니다. 올바른 메뉴 번호를 선택해 주세요.\n");
    }
  }  
  return 0;
}

void input_health_data() {
  printf("\n--- [데이터 입력] ---\n");
  printf("성별 입력(M/F): ");
  scanf(" %c", &g_gender);

  printf("키(cm) 입력 : ");
  scanf("%f", &g_health_data[0]);

  printf("몸무게(kg) 입력: ");
  scanf("%f", &g_health_data[1]);

  printf("하루 운동 시간 (예: 1시간 30분 = 1.5): ");
  scanf("%f", &g_health_data[2]);

  g_is_data_exist = 1;
  g_health_data[3] = 0.0;

  printf("[완료] 데이터가 성공적으로 배열에 저장되었습니다. \n");
}

float calculate_bmi(float height, float weight) {
  float bmi_result;
  bmi_result = weight / ((height/100.0) * (height/100.0));
  return bmi_result;
}

void calculate_bmr_tdee(char gender, float height, float weight, float ex_time) {
  if (gender == 'M' || gender == 'm') {
    g_bmr = (10.0 * weight) + (6.25 * height) - 120.0;
  }
  else if (gender == 'F' || gender == 'f') {
    g_bmr = (10.0 * weight) + (6.25 * height) - 286.0;
  }
  else {
    printf("[주의] 성별 입력이 올바르지 않아 기본(남성) BMR로 계산됩니다.\n");
    g_bmr = (10.0 * weight) + (6.25 * height) - 120.0;
  }
  g_health_data[4] = g_bmr * (1.2 + (ex_time * 0.1));
}

void print_report_with_pointer(float arr[]) {
  printf("\n========================================\n");
  printf("        [ 건강 분석 결과 리포트 ]        \n");
  printf("========================================\n");

  printf("[시스템 로그] arr[i] 방식으로 원본 배열 데이터 순회 조회:\n");
  for(int i = 0; i<5; i++)  {
     switch(i) {
        case 0: printf("  ▶ 등록된 신장(키)    : %.1f cm\n", arr[i]); break;
        case 1: printf("  ▶ 등록된 체중(몸무게): %.1f kg\n", arr[i]); break;
        case 2: printf("  ▶ 일일 평균 운동 시간: %.1f 시간\n", arr[i]); break;
        case 3: printf("  ▶ 체질량지수 (BMI)   : %.2f\n", arr[i]); break;
        case 4: printf("  ▶ 총 에너지 소비(TDEE): %.2f kcal\n", arr[i]); break;
     }
  }   
  printf("----------------------------------------\n");
  printf("[입력 정보] 성별: %c | 키: %.1fcm | 몸무게: %.1fkg\n", g_gender, *(arr + 0), *(arr + 1));
  printf("[활동 데이터] 하루 %.1f시간 운동 실천 중\n", *(arr + 2));
  printf("----------------------------------------\n");

  float current_bmi = *(arr + 3);
  float current_tdee = *(arr + 4);

  if (current_bmi < 18.5) {
    printf("현재 체형 상태는 '저체중'입니다.\n");
    printf("[관리 팁] 충분한 영양 섭취와 근력 운동이 필요합니다.\n");
  }
  else if (current_bmi < 23.0) {
    printf("현재 체형 상태는 '정상'입니다.\n");
    printf("[관리 팁] 꾸준한 운동으로 지금의 상태를 유지하세요.\n");
  }
  else if (current_bmi < 25.0) { 
    printf("현재 체형 상태는 '과체중'입니다.\n");  
    printf("[관리 팁] 유산소 운동과 식단 조절을 병행해 보세요.\n");
  }
  else {
    printf("현재 체형 상태는 '비만'입니다.\n");
    printf("[관리 팁] 체계적인 감량 계획과 식단이 필요합니다.\n");
  }
  printf("----------------------------------------\n");
  printf("1.체질량지수(BMI): %.2f\n", current_bmi);
  printf("2.기초 대사량(BMR): %.2f kcal\n", g_bmr);  
  printf("3.에너지 소비 데이터(TDEE): %.2f kcal\n", current_tdee);
  printf("----------------------------------------\n");

  printf("      [ TDEE 기반 맞춤형 식단 가이드 ]   \n");
  printf("----------------------------------------\n");
  printf("▶ 현재 체중 유지 목적: 하루 %.0f kcal 섭취\n", current_tdee);
  printf("▶ 건강한 다이어트 목적: 하루 %.0f kcal 섭취(-500kcal 제한)\n", current_tdee - 500.0);
  printf("▶ 벌크업 및 체중 증량: 하루 %.0f kcal 섭취(+300kcal 추가)\n", current_tdee + 300.0);
  printf("========================================\n");
}

