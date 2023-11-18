SYSCALL_DEFINE1(ps_counter, int __user *, num) {
	struct task_struct* task;
	int counter = 0, err;
	printk("[Syscall] ps_counter    [StuID] PB21111728\n");
	for_each_process(task) {
		counter ++;
	}
	err = copy_to_user(num, &counter, sizeof(int));
	return 0;
}

SYSCALL_DEFINE4(ps_info, pid_t  __user *, user_pid, char __user * , user_name,  long  __user *, user_state,unsigned long long  __user *, user_run_time) {
		
	struct task_struct* task;
	int i = 0, j = 0, k = 0, cnt = 0, err = 0;
	char name_kel[1024];
	pid_t pid_kel[128];
	long state_kel[128];
	unsigned long long run_time_kel[128];
	for(j = 0; j < 1024; j++) name_kel[j] = ' ';
	
	//print
	printk("[Syscall] ps_info    [StuID] PB21111728\n");
	
	//kernel cal
	for_each_process(task) {
		pid_kel[i] = task -> pid;
		state_kel[i]= task -> state;
		run_time_kel[i] = task -> se.sum_exec_runtime;
		for(k = 0; k < 16; k++) {
			if(task -> comm[k] != '\0') {
				name_kel[cnt + k] = task -> comm[k];
			}
			else {
				name_kel[cnt + k] = ';';
				cnt += k + 1;
				break;
			}
		}
		
		i++;
	}
	
	//to user
	err = copy_to_user(user_run_time, run_time_kel, sizeof(run_time_kel));
	err = copy_to_user(user_name, name_kel, sizeof(name_kel));
	err = copy_to_user(user_pid, pid_kel, sizeof(pid_kel));
	err = copy_to_user(user_state, state_kel, sizeof(state_kel));

	return 0;
}