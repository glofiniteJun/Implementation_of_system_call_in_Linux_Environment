//my_stack_syscall.c is cuztomized system call simulating stack data structure
//2013210063 Gi Jun Moon
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/linkage.h>

#define MAXSIZE 102

#define bool int
#define true 1
#define false 0

int stack[MAXSIZE]; //사이즈 102의 스텍을 선언
int top = -1; //stack의 top을 -1로 설정
int i; //포문을 위한 변수 i를 선언
int pop_val; //pop을 통해서 반환되는 값을 담는 변수 선언

bool overlap_check(int val){//스텍에 담겨 있는 모든 int값을 traverse하여 해당 값이 이미 존재한다면 false, 존재하지 않는다면 true를 리턴하는 함수
	for(i=top; i>=0;i--){
			if(stack[i] == val){
				printk("\nOVERLAP ERROR: the number already exist in the stack\n\n");
				return false;
		}
	}
	return true;
}

void print_stack(bool is_push, int val){ //스텍의 상태를 pop과 push연산에 따라 출력해주는 함수
	if(is_push)
		printk("\n Push %d \n", val);
	else
		printk("\n Pop %d \n", val);
	printk("Stack Top ----------\n");
	for(i = top; i>=0; i--){
		printk("%d\n", stack[i]);
	}
	printk("Stack Bottom -------\n");
}

SYSCALL_DEFINE1(oslab_push,int,val){//DEFINE뒤에 1을 넣어 input 인자가 1개인 oslab_push system call을 구현
	if(top >= MAXSIZE - 1){//스텍 오버플로우에 대한 처리
		printk("\n STACK OVERFLOW \n\n");
		return 0;
	}else if(!overlap_check(val)){//중복된 값이 들어왔을 때의 처리
		return 0;
	}else{
		stack[++top] = val;//stack의 push 연산으로 stack의 top에 해당 int값을 할당
		print_stack(1, val);//stack의 상태를 출력
		return 0;		
	}
}

SYSCALL_DEFINE0(oslab_pop){//DEFINE뒤에 0을 넣어 input 인자가 0개인 oslab_pop system call을 구현
	if (top < 0) {
        printk("\n STACK UNDERFLOW \n\n");//스텍 언더플로우에 대한 처리
        return -2147483648; //언더플로우 시 int의 최저 값을 리턴
    }
    pop_val = stack[top--];//stack의 pop 연산으로 stack의 top에 해당 int값을 제거
    print_stack(0, pop_val);//stack의 상태를 출력
    return pop_val;//pop한 값을 리턴
}
