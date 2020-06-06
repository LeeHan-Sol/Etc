#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVERSIZE 1

int input_types(const char *, char *, char *, int);
void display(const char *);

int main()
{
	char * template = (char *)malloc(sizeof(char) * 1024);
	memset(template, 0x00, sizeof(template));
	
	char * input_buffer = (char *)malloc(sizeof(char) * 1024);
	memset(input_buffer, 0x00, sizeof(input_buffer));

	for(;;)
	{
		int i = 1;
		fprintf(stdout, "\n담을 자료형");
		fprintf(stdout, "\n%d. char", i++);
		fprintf(stdout, "\n%d. int", i++);
		fprintf(stdout, "\n%d. double", i++);
		fprintf(stdout, "\n%d. string", i++);
		fprintf(stdout, "\n%d. 출력", i++);
		fprintf(stdout, "\n%d. 나가기", i++);
		fputs("\n>> ", stdout);

		fgets(input_buffer, sizeof(input_buffer) - 1, stdin);
		input_buffer[strlen(input_buffer) - 1] = 0x00;

		if(strcmp(input_buffer, "1") == 0)
		{
			int size = 1;
			if(input_types("\n문자를 입력해주세요", input_buffer, template, size) != 0)
			{
				memset(input_buffer, 0x00, strlen(input_buffer));
				continue;
			}
		}
		else if(strcmp(input_buffer, "2") == 0)
		{
			int size = 4;
			if(input_types("\n정수를 입력해주세요.", input_buffer, template, size) != 0)
			{
				memset(input_buffer, 0x00, strlen(input_buffer));
				continue;
			}
		}
		else if(strcmp(input_buffer, "3") == 0)
		{
			int size = 8;
			if(input_types("\n실수를 입력해주세요.", input_buffer, template, size) != 0)
			{
				memset(input_buffer, 0x00, strlen(input_buffer));
				continue;
			}
		}
		else if(strcmp(input_buffer, "4") == 0)
		{
			int size = -1;
			if(input_types("\n문자열을 입력해주세요.", input_buffer, template, size) != 0)
			{
				memset(input_buffer, 0x00, strlen(input_buffer));
				continue;
			}
		}
		else if(strcmp(input_buffer, "5") == 0)
		{
			display(template);
			continue;
		}
		else if(strcmp(input_buffer, "6") == 0)
		{
			fprintf(stdout, "\n프로그램을 종료합니다.\n");
			
			break;
		}
		else
		{
			fprintf(stdout, "\n다시 입력해주세요.");
			continue;
		}
		
		fputs("\n입력되었습니다.\n", stdout);
//fprintf(stdout, "result : %s\n", template);
	}

	free(input_buffer);
	free(template);

	return 0;
}

int input_types(const char * print_string, char * input_buffer, char * template, int size)
{
	fputs(print_string, stdout);
	fputs("\n>> ", stdout);

	memset(input_buffer, 0x00, strlen(input_buffer));
	fgets(input_buffer, 1023, stdin);
	input_buffer[strlen(input_buffer) - 1] = 0x00;
	
	if(size == 1 && strlen(input_buffer) != size) 
	{
		fprintf(stdout, "\n입력이 형식에 맞지 않습니다.\n");
		return OVERSIZE;
	}
	else if(size == 4 && strlen(input_buffer) > 9)
	{
		if(strlen(input_buffer) == 11 && strncmp(input_buffer, "-", 1) == 0 && strcmp((input_buffer + 1), "2147483648") > 0)
		{
			fprintf(stdout, "\n입력이 형식에 맞지 않습니다.\n");
			return OVERSIZE;
		}
		else if(strcmp(input_buffer, "2147483647") > 0)
		{
			fprintf(stdout, "\n입력이 형식에 맞지 않습니다.\n");
			return OVERSIZE;
		}
	}

	for(int i = 0; i < 1024; i++)
	{
		char temp = *(template + i);
fprintf(stdout, "i, temp : %d, %c\n", i, temp);

		if(temp == 0x00)
		{
			if(size == 1)
			{
				*(template + i) = 'c';
				*((char *)(template + (i + 1))) = *((char *)input_buffer);
				break;
			}
			else if(size == 4)
			{
				*(template + i) = 'i';
				*((int *)(template + (i + 1))) = atoi(input_buffer);
				break;
			}
			else if(size == 8)
			{
				*(template + i) = 'd';
				*((double *)(template + (i + 1))) = atof(input_buffer);
				break;
			}
			else if(size == -1)
			{
				*(template + i) = '-';
				strcat(template + (i + 1), input_buffer);
				break;
			}
		}
		else
		{
			if(temp == 'c')
			{
				i += 1;
			}
			else if(temp == 'i')
			{
				i += 4;
			}
			else if(temp == 'd')
			{
				i += 8;
			}
			else if(temp == '-')
			{
				i += strlen(template + i);
			}
		}
	}

	return 0;
}

void display(const char * template)
{
	if(*template == 0x00)
	{
		fputs("\n출력이 없어요...\n\n", stdout);
		return ;
	}

	fputs("\n", stdout);
	for(int i = 0;;)
	{
		char temp = *(template + i);
//fprintf(stdout, "i, temp : %d, %c\n", i, temp);
		if(temp == 0x00)
			break;

		if(temp == 'c')
		{
			fprintf(stdout, "문자 : %c\n", *((char *)(template + (++i))));
			i += 1;
		}
		else if(temp == 'i')
		{
			fprintf(stdout, "정수 : %d\n", *((int *)(template + (++i))));
			i += 4;
		}
		else if(temp == 'd')
		{
			fprintf(stdout, "실수 : %f\n", *((double *)(template + (++i))));
			i += 8;
		}
		else if(temp == '-')
		{
			fprintf(stdout, "문자열 : %s\n", ((char *)(template + (++i))));
			i += strlen(template + i) + 1;
		}
	}

	return ;
}
