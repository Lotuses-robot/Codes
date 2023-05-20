//============================================================================  
// Name : debug.cpp  
// Author : boyce  
// Version : 1.0  
// Copyright : pku  
// Description : Hello World in C++, Ansi-style  
//============================================================================  
#include <cstdio>
#define DBG_PRINTF(fmt, args...) { printf("<%d> ", __LINE__); printf(fmt, ##args); }
int main() {  
    char str[]="Hello World";  
    DBG_PRINTF("%s\n", str);
    return 0;  
}  