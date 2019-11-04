#include <unistd.h>
#include <stdio.h>

#define my_stack_push 335
#define my_stack_pop 336

int quit_sig = 1;//프로그램을 종료시키기 위한 flag
char op_val[102];//스텍에 어떤 기능을 수행할 것인지 입력을 받는 배열을 선언

int main(void) {
	printf("This is your stack user application utilizing system call.\n");
	while(quit_sig){//단순한 하드코드 입력이 아닌 사용자 스스로 원하는 값을 지속적으로 push/pop할 수 있게끔 구현 
		printf("Please enter the number of following operation: 1. Push  2. Pop  3. Quit\n");
		printf("operation number: ");
		scanf("%s", op_val); //선택한 기능의 번호를 입력
		fflush(stdin);
		if(op_val[0] == '1' && op_val[1] == '\0'){//1을 입력받을 경우는 push system call을 호출
			printf("Push: ");
			int val;
			scanf("%d", &val);
			syscall(my_stack_push, val);
		}else if(op_val[0] == '2' && op_val[1] == '\0'){//2을 입력받을 경우는 pop system call을 호출
			int pop_val = syscall(my_stack_pop);
			if(pop_val == -2147483648){
				printf("Stack Underflow\n");
				return 0;			
			}
			printf("Pop: %d\n", pop_val);//POP한 값을 출력
		}else if(op_val[0] == '3' && op_val[1] == '\0'){//3을 입력받을 경우는 프로그램 종료
			quit_sig = 0;
		}

	}
	return 0;
}

