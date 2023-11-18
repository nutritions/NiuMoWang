#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>

typedef struct info_arr
{
	pid_t pid_kel[128];
	char name_kel[1024];
	unsigned long long run_time_kel[128];
	long state_kel[128];
} info_arr;

int split_string(char *string, char *sep, char **string_clips)
{

	char string_dup[1024];
	string_clips[0] = strtok(string, sep);
	int clip_num = 0;

	do
	{
		char *head, *tail;
		head = string_clips[clip_num];
		tail = head + strlen(string_clips[clip_num]) - 1;
		while (*head == ' ' && head != tail)
			head++;
		while (*tail == ' ' && tail != head)
			tail--;
		*(tail + 1) = '\0';
		string_clips[clip_num] = head;
		clip_num++;
	} while (string_clips[clip_num] = strtok(NULL, sep));
	return clip_num;
}

int main()
{
	info_arr userInfo;
	int i = 0, j = 0, cnt;
	int pid_out[128];
	long state_out[128];
	char *name_out[128];
	double CPU_out[128];
	double runtime_out[128];
	unsigned long long runtime_old[128];



	while (1)
	{
		syscall(332, &cnt);
		syscall(333, userInfo.pid_kel, userInfo.name_kel, userInfo.state_kel, userInfo.run_time_kel);
		//处理name_out
		int split_out = split_string(userInfo.name_kel, ";", name_out);
		for (i = 0; i < cnt; i++)
		{
			//处理state_out
			if (!userInfo.state_kel[i])
				state_out[i] = 1;
			else
				state_out[i] = 0;
			//处理pid_put
			pid_out[i] = userInfo.pid_kel[i];
			//处理runtime_out
			runtime_out[i] = (((double)(userInfo.run_time_kel[i])) / 1000000000);
			//处理CPU_out
            		CPU_out[i] = (((double)(userInfo.run_time_kel[i] - runtime_old[i])) / 10000000);
            		runtime_old[i] = userInfo.run_time_kel[i];
			
			
		}

		// 冒泡排序

		for (i = 0; i < cnt; i++)
		{
			for (j = 0; j < cnt - i - 1; j++)
			{
				if (CPU_out[j] < CPU_out[j + 1])
				{
					char *name_temp = name_out[j + 1];
					long state_temp = state_out[j + 1];
					double CPU_temp = CPU_out[j + 1];
					pid_t pid_temp = pid_out[j + 1];
					double runtime_temp = runtime_out[j + 1];

					name_out[j + 1] = name_out[j];
					state_out[j + 1] = state_out[j];
					CPU_out[j + 1] = CPU_out[j];
					pid_out[j + 1] = pid_out[j];
					runtime_out[j + 1] = runtime_out[j];

					name_out[j] = name_temp;
					state_out[j] = state_temp;
					CPU_out[j] = CPU_temp;
					pid_out[j] = pid_temp;
					runtime_out[j] = runtime_temp;
				}
			}
		}

		printf("PID\t\t    COMM\t\t   ISRUNNING\t CPU%%\t\tRUNTIME\n");
		for (i = 0; i < 20; i++)
			printf("%-5d\t%*s\t%12ld\t   %10.5f%%\t\t%7.5f\n", pid_out[i], 16, name_out[i], state_out[i], CPU_out[i], runtime_out[i]);

		sleep(1);
		system("clear");
	}
}