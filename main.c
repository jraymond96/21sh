#include<unistd.h>
#define t int
#define l(i,n)(i==0||i==n-1)
void p(t a){write(1,&a,1);}void rush(t x,t y){for(t i=0;i<y;++i){for(t j=0;j<x;++j)p(l(i,y)?l(j,x)?'o':45:l(j,x)?'|':32);p(10);}}
