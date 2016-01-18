/*通过管道，检测指定程序，若该应用打开的数量超过一定时，随机pid关闭
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int execmd(char *,char *);//反回多少个进程，第一个字符串是系统指令，第二个字符串保存字符信息
void kill_exe(char *);//杀掉指定程序
int main(void){
	int pr;
	int i=0;
	char CMDin[30]={"tasklist"};//通过tasklist命令查看进程
	char CMDout[40960]={0};//指定程序的进程记录
	//char clearn_buff[]={0};
	int check_exe=0;//检测进程的次数，超过一定数量会自动休眠
	while(1){
		pr = execmd(CMDin,CMDout);
		//printf("%s \n",CMDout);
		if(pr > 3){
			kill_exe(CMDout);
			check_exe=0;
		}
		++check_exe;
		if(check_exe > 50){
			sleep(10);
			check_exe=0;
		}
		
		CMDout[0]='\0';
		//strcpy(CMDout,clearn_buff);
		
	}
	
	return 0;
}
int execmd(char * in,char * out){
	char buffer[78]={0};
	int num=0;
	int i;
	FILE * pipe;
	pipe = _popen(in,"r");
	if(!pipe){
		return 0;
	}
	
	while(!feof(pipe)){
		if(fgets(buffer,78,pipe)){
			if(strstr(buffer,"notepad.exe")){
				++num;
				strcat(out,buffer);
			}
		}
		
	}
	return num;
}
void kill_exe(char * list){
	int pid[20]={0};
	int i = 0;
	time_t t;
	int k=0;
	char do_kill[1024];
	srand((unsigned int)time(&t));
	while(*list != '\0'){
		sscanf(list,"%*s %d ",&pid[i]);
		list += 78;
		++i;
	}
	k = rand()%i;
	sprintf(do_kill,"taskkill /F /PID %d",pid[k]);
	
	//printf("%s %d\n",do_kill,k);
	system(do_kill);
}
