#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define true	0
#define false	1
 
 
int Deal_String(char *t, char *s)    //内存统计法，适用于字符多的情况下，字符少也行
{
	clock_t begin, end;
    	double cost;
	begin = clock();
	char *ss = s, *tt = t;
	int flag = false;
	int lengt = strlen(tt);
	int lengs = strlen(ss);
	if(lengt != lengs)
		return false;
	char *tram = malloc(128 * sizeof(char));
	char *sram = malloc(128 * sizeof(char));
	memset(tram, 0, (128 * sizeof(char)));
	memset(sram, 0, (128 * sizeof(char)));
	for(int i = 0; i < lengt; i++)
	{
		tram[*tt]++;
		sram[*ss]++;
		#if DEBUG
		printf("tram[%d]=%d,sram[%d]=%d\n", *tt, tram[*tt], *ss, sram[*ss]);
		#endif
		tt++;
		ss++;
	}
	if(memcmp(tram, sram , (128 * sizeof(char))))
		flag = false;
	else
 		flag = true;
	free(tram);
	free(sram);
	end = clock();
    	cost = (double)(end - begin)/CLOCKS_PER_SEC;
    	printf("Time cost is: %lf secs\n", cost);
	return flag;
}
 
 
 
int datcmp(void *a, void *b)
{
	return (*(char *)a > *(char *)b) ? 1 : -1;
}
 
 
int Deal_Str_Sort(char *t, char *s)    //排序统计法，适用于字符少的情况，排序直接调用C接口
{
	clock_t begin, end;
    	double cost;
	begin = clock();
 
	char *ss = s, *tt = t;
	int flag = false;
	int lengt = strlen(tt);
	int lengs = strlen(ss);
	if(lengt != lengs)
		return false;
	char *tram = malloc(lengt * sizeof(char));
	char *sram = malloc(lengt * sizeof(char));
	memset(tram, 0, (lengt * sizeof(char)));
	memset(sram, 0, (lengt * sizeof(char)));
	memcpy(tram, tt, lengt);
	memcpy(sram, ss, lengt);
	qsort(tram, lengt, sizeof(char), datcmp);
	qsort(sram, lengt, sizeof(char), datcmp);
	#if DEBUG
	printf("T is:%s S is:%s\n", tram, sram);
	#endif
	if(!strncmp(tram, sram, lengt))
		flag = true;
	free(tram);
	free(sram);
	end = clock();
    	cost = (double)(end - begin)/CLOCKS_PER_SEC;
    	printf("Time cost is: %lf secs\n", cost);
	return flag;
		
}
 
 
 
int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("Param Input Error!\n");
		exit(1);
	}
	char *t = argv[1], *s = argv[2];
	printf("T is %s,S is %s,method is %s\n", t, s, argv[3]);
	if(!strcmp(argv[3], "memory"))
	{
		if(Deal_String(t, s))
			printf("Is False\n");
		else
			printf("Is True\n");
		return 0;
	}
	if(!strcmp(argv[3], "sort"))
	{
		if(Deal_Str_Sort(t, s))
			printf("Is False\n");
		else
			printf("Is True\n");
		return 0;
	}
	printf("Method Input Error !\n");
	return 1;
}
