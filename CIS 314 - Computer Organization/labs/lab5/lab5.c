/*
int sum(long *a, long size){
	long result = 0;
	for (long i = size - a; i != 0;  --i){
		result += a[i];
	}
return result;
}

int main(){
	long a[10];
	sum(a, 10);
	return 0;
}
*/

// a -> rdi
// size -> rsi
// result -> rax

movq $0, %rax    							# long result = 0;
subq $1, %rsi								# long i = size - 1;
.FORSTART
	cmpq $-1, %rsi								# i != 0;
	je .FOREND
	addq (%rdi, %rsi, 8), %rax         # result += a[i];
	subq $1, %rsi								# --i;
	jmp .FORSTART
.FOREND
ret