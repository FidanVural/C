#include <stdio.h>

int main(){
	int s,d;
	scanf("%d\n%d",&s,&d);
	
	char arr[32][20];
	strcpy(arr[0], "blah");
	strcpy(arr[1], "one");
	strcpy(arr[2], "two");
	strcpy(arr[3], "three");
	strcpy(arr[4], "four");
	strcpy(arr[5], "five");
	strcpy(arr[6], "six");
	strcpy(arr[7], "seven");
	strcpy(arr[8], "eight");
	strcpy(arr[9], "nine");
	strcpy(arr[10], "ten");
	strcpy(arr[11], "eleven");
	strcpy(arr[12], "twelve");
	strcpy(arr[13], "thirteen");
	strcpy(arr[14], "fourteen");
	strcpy(arr[15], "fifteen");
	strcpy(arr[16], "sixteen");
	strcpy(arr[17], "seventeen");
	strcpy(arr[18], "eighteen");
	strcpy(arr[19], "nineteen");
	strcpy(arr[20], "twenty");
	strcpy(arr[21], "twenty one");
	strcpy(arr[22], "twenty two");
	strcpy(arr[23], "twenty three");
	strcpy(arr[24], "twenty four");
	strcpy(arr[25], "twenty five");
	strcpy(arr[26], "twenty six");
	strcpy(arr[27], "twenty seven");
	strcpy(arr[28], "twenty eight");
	strcpy(arr[29], "twenty nine");
	
	if(d==0){
		printf("%s o' clock",arr[s]);
	}
	else if(d==1){
		printf("%s minute past %s",arr[d],arr[s]);
	}
	else if(d<=29 && d>1 && d!=15){
		printf("%s minutes past %s",arr[d],arr[s]);
	}
	else if(d==15){
		printf("quarter past %s",arr[s]);
	}
	else if(d==30){
		printf("half past %s",arr[s]);
	}
	else if(d==45){
		printf("quarter to %s",arr[s+1]);
	}
	else if(d>30 && d<60 && d!=45){
		printf("%s minutes to %s",arr[60-d],arr[s+1]);
	}
}
