#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE 40


// 문자열로 입력받은 정수를 int 형으로 변환 - 오른쪽 정렬
void encode(char *num_str, int *num){
    for(int i=strlen(num_str) - 1, j=SIZE; i>=0; i--, j--){
      num[j - 1] = num_str[i] - '0';
    }
}

// 문자열로 입력받은 정수를 int 형으로 변환 - 왼쪽 정렬(나눗셈)
void encode_left(char* s, int num[]) {
  for (int i = 0; i < strlen(s); ++i) {
    num[i] = s[i] - '0';
  }
}


int comp(char *num1_str, char* num2_str){
    int num1_len = strlen(num1_str), num2_len = strlen(num2_str);
    if(num1_len != num2_len) return num1_len > num2_len;
    for(int i=0; i<num1_len; i++){
        if(num1_str[i] != num2_str[i]) return num1_str[i] > num2_str[i];
    }
    return 1;
}

// Result 크기 - SIZE + 1
void result(int *num){
  int idx, start_point;
  for (idx = 0; idx < SIZE +1;idx++){
    if(num[idx]){
      start_point = idx;
      break;
    }
      
  }

  for (; idx < SIZE+1;idx++){
    if((SIZE+1-idx)%3==0 && idx != start_point){
      printf(",");
    }
    printf("%d", num[idx]);
  }
  printf("\n");
}


// Result 크기  - SIZE * 2 
void result_multi(int *num){
  int idx,start_point;
  for (idx = 0; idx < SIZE *2;idx++){
    if(num[idx]){
      start_point = idx;
      break;
    }
  }
  for (; idx < SIZE * 2-1;idx++){
    if((SIZE *2 -1-idx)%3==0&& idx != start_point){
      printf(",");
    }
    printf("%d", num[idx]);
    
  }
    
  printf("\n");
}

void sum(int *num1, int *num2){
  int sum[SIZE+1] = {0};

  for(int i=SIZE; i>0; i--){
    sum[i] += num1[i-1] + num2[i-1];

    // 올림수 처리
    if(sum[i] >= 10){
      sum[i-1]++;
      sum[i] -= 10;
    }
  }
  result(sum);
}

void sub(int *num1, int *num2){
  int sub[SIZE+1] = {0};

  for(int i=SIZE; i>0; i--){
    sub[i] -= num1[i-1] - num2[i-1];

    if(sub[i] < 0){
      sub[i-1]--;
      sub[i] += 10;
    }    
  }

  result(sub);
} 

void multi(int *num1, int *num2) {
    int multi[SIZE*2] = { 0 };
    for (int i = SIZE-1; i >=0; i--) {
        for (int j = 0; j < SIZE; j++) {
            multi[i + j] += num1[i] * num2[j];
        }
    }
 
    
    for (int i = SIZE*2-1; i > 0; i--) {
        multi[i - 1] += multi[i] / 10;
        multi[i] %= 10;
    }
    result_multi(multi);
}

int minus(int *num1, int *num2, int len) {
  for (int i = 0; i < len; ++i) {
    if (num1[i] > num2[i]) break;
    if (num1[i] < num2[i]) return 0;
  }
  for (int i = len - 1; i >= 0; --i) {
    num1[i] -= num2[i];
    if (num1[i] < 0){
      num1[i] += 10;
      num1[i - 1]--;
    }
  }
  return 1;
}


void div(int *num1, int num1_len, int *num2, int num2_len) {
  int div[SIZE] = { 0 }, idx;
  for (idx = 0; idx <= num1_len - num2_len; ++idx) {
    while (minus(num1 + idx, num2, num2_len)) div[idx]++;
    num1[idx + 1] += num1[idx] * 10;
  }
  if (div[0]) printf("%d", div[0]);
  for (idx = 1; idx <= num1_len - num2_len; idx++){
    if((num1_len-num2_len-idx+1)%3==0){
      printf(",");
    }
    printf("%d", div[idx]);
  } 
    printf("\n");
}


int main(void){
  char num1_str[SIZE];
  char num2_str[SIZE];
  int num1[SIZE] = {0};
  int num2[SIZE] = {0};
  int op;




  printf("-----------Calculator-----------\n");
  printf("Plus\t(1)\n");
  printf("Minus\t(2)\n");
  printf("Multi\t(3)\n");
  printf("Divide\t(4)\n");
  printf("Exit\t(0)\n");
  printf("--------------------------------\n");
  printf("Input Operator : ");
  scanf("%d", &op);

  if(!(op>=0 && op <=4)){
    printf("Operator Error\n\n");
  }
  else{
    printf("NUM1 : ");
    scanf(" %s", &num1_str);
    printf("NUM2 : ");
    scanf("%s", &num2_str);
    printf("--------------------------------\n");
    printf("Result : ");
    clock_t start = clock();
    switch(op){
      // 덧셈
      case 1:
        encode(num1_str, num1);
        encode(num2_str, num2);
        sum(num1, num2);
        break;

      // 뺄셈
      case 2:
        encode(num1_str, num1);
        encode(num2_str, num2);
        if(comp(num1_str,num2_str)){
          
          sub(num2, num1);
        }
        else{
          printf("-");
          sub(num1, num2);
        }
        break;
      // 곱셈
      case 3:
        encode(num1_str, num1);
        encode(num2_str, num2);
        multi(num1, num2);
        break;
      
      // 나눗셈
      case 4:
        encode_left(num1_str, num1);
        encode_left(num2_str, num2);

        if(comp(num1_str,num2_str)){
          div(num1, strlen(num1_str),num2,strlen(num2_str));
        }
        else{
          printf("0\n");
        }
        break;
        
        
    }
    clock_t end = clock();
    printf("Time : %lf\n\n", (double)((end - start)/CLOCKS_PER_SEC));
  }
  
  return 0;
}