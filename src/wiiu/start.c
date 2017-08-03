#include <wiiu/service/coreinit.h>

int main(int, char**);
int _start(void){
	return main(0, (char**)0);
}

void __eabi(void){}
