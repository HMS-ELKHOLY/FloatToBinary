#include <stdio.h>
#include <stdlib.h>
//#include <cmath>
/*
Author : Hussien Mostafa Said EL-kholy
Date : 7/4/2019 13:18
*/
//contains the same binary data
typedef union container
{float ieee_754;
int binary_decimal;
}f_i;
void Float_binary(char  *c ,float f)
{
//printf("|||||||  %f  +  ",f);

f_i contains;

contains.ieee_754=f;
int sign=(contains.binary_decimal&0x80000000)==0x80000000;

contains.binary_decimal=contains.binary_decimal&0x7fffffff;
//
//printf("|||---||||  %d  +  ",contains.binary_decimal);
for (int i=31; i>=0;i--)
{//add 48 to convert to ASCII
*(c+i)=(contains.binary_decimal&0x7fffffff)%2+48;
contains.binary_decimal=contains.binary_decimal/2;

}
if (sign==1)
*(c+0)='1';
*(c+32)='_';
*(c+33)='\0';
//terimnate ASCII
}
int main()
{
char c[34];
f_i special [4];
special[0].binary_decimal=0x7f800000;//+inf
special[1].binary_decimal=0xff800000;//-inf
special[2].binary_decimal=0x7f800000;//NAN
special[3].binary_decimal=0xffc00000;//NAN
special[4].binary_decimal=0x0;//0
FILE * fp =fopen("SPECIAL_CASES.txt","w") ;

for(int i=0;i<5;i++)
{

    for(int j=0;j<5;j++)
    {
        Float_binary(c,special[i].ieee_754);
        fputs(c,fp);
        Float_binary(c,special[j].ieee_754);
        fputs(c,fp);
        Float_binary(c,special[i].ieee_754+special[j].ieee_754);
        fputs(c,fp);
        fputs("\n",fp);
    }
}
fclose(fp);
fp =fopen("SPECIAL_CASES_WITH_RANDOM.txt","w") ;
srand(RAND_MAX);
for(int i=0;i<5;i++)
{

    for(int j=0;j<100;j++)
    {
        f_i random ;
        random.binary_decimal=(unsigned int)((rand() & 0x7fff) | ((rand() & 0x7fff) << 15))%0x7FFFFF;
        Float_binary(c,random.ieee_754);
        printf("_%x %f  %x_\n",random.binary_decimal,random.ieee_754,RAND_MAX);
        fputs(c,fp);
        Float_binary(c,special[i].ieee_754);
        fputs(c,fp);
        Float_binary(c,special[i].ieee_754+random.ieee_754);
        fputs(c,fp);
        fputs("\n",fp);
    }
}
fclose(fp);

int flag=1;
printf("%s","enter flag");
scanf("%d",&flag);
if (flag==1){
fp=fopen("CustomInput.txt","w") ;
float f,f2;

do
{

    printf("first num :");
    scanf("%f",&f);
    printf("second num :");
    scanf("%f",&f2);
    Float_binary(c,f);
    fputs(c,fp);
    printf("F1 :  %s  +  ",c);
    Float_binary(c,f2);
    fputs(c,fp);


    printf("F2 :  %s  =  ",c);
    Float_binary(c,f2+f);
    fputs(c,fp);
    printf(" result  %s  \n\n  ",c);
    printf("flag :");
    scanf("%d",&flag);
    fputs("___\n",fp);

}
while(flag==1);
fclose(fp);

}    return 0;
}
