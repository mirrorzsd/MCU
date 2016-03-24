//qw 编码的正负
//as V的正负
//zx B的正负
//编码规则：
//1.以1开头且第一个1的编码为-1
//2.所有1以+1，-1交替编码
//3.若连续4个0，则第四个0为V，V的正负与上一个V的符号相反，且与上一个编码后的1符号相同
//4.优先满足于上一个V相反的规则，若与上一个编码后1符号冲突，则第一个0编码为B，B与上一个编码后的1符号相反
//5.B与编码后的1同地位
#include <stdio.h>
/*
typedef struct Node
{
	char code = 'a';
	int index; 
	struct Node *prior;
	struct Node *next;
}Node,*pNode;
*/

char code[] = "1000010000110000000011k";
char curCode,preV,pre1;
int zeroCount = 0;


void HDB3encode(char *code);

int main(void)
{
	int i = 0;
	//gets(code);
	//printf("\nInput finished!%s",code);
	HDB3encode(code);
	i = 0;
	printf("HDB3 = %s",code);
	scanf("%d",i);
	return 0;
}

void HDB3encode(char *code)
{
	int i = 0;
	while(code[i] != 'k')
	{
		curCode = code[i];
		if(curCode == '0')
		{
			zeroCount += 1;
			if(zeroCount == 4)
			{
				zeroCount = 0;
				if(!preV)
				{
					if(pre1 == 'q')
					{
						curCode = preV = 'a';
					}
					if(pre1 == 'w')
					{
						curCode = preV = 's';
					}
				}
				else if(preV == 'a' && pre1 == 'q')
				{
					preV = curCode = 's';
					code[i-3] = 'x';
					pre1 = 'w';
				}
				else if(preV == 'a' && pre1 == 'w')
				{
					preV = curCode = 's';
				}
				else if(preV == 's' && pre1 == 'q')
				{
					preV = curCode = 'a';
				}
				else if(preV == 's' && pre1 == 'w')
				{
					preV = curCode = 'a';
					code[i-3] = 'z';
					pre1 = 'q';
				}
			}
		}
		if(curCode == '1')
		{
			if(!pre1)
			{
				curCode = pre1 = 'w';
			}
			else if(pre1 == 'q')
			{
				pre1 = curCode = 'w';
			}
			else if(pre1 == 'w')
			{
				pre1 = curCode = 'q';
			}
		}
		//printf("\n%c",curCode);
		code[i] = curCode;
		i++;
	}
}