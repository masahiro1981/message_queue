#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define QNAME "/testq"
//#define QNAME "$SNAP_DATA/testq"
//#define QNAME "/home/masahiro/hiroq"
int main(){
	int cnt = 0;
	int ret;
	char str[100];
	char *buff;
	mqd_t q;

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 1024;
	attr.mq_curmsgs = 0;

	mode_t omask;
	omask = umask(0);
	q = mq_open(QNAME, (O_WRONLY | O_CREAT), 0777, &attr);
	umask(omask);

	if ( q == -1 ){
		printf("[ERROR]%d: %s\n", errno, strerror(errno));
        printf("%s", QNAME);
		return 1;
	}
	while(1){
		sprintf(str ,"%d", cnt++);
		buff = (char *)calloc(strlen(str) + 1, sizeof(char));
		strcpy( buff, str );
		printf("%s\n", buff);

		ret = mq_send( q, buff , strlen(buff) , 0);
		if ( ret == -1	) {
			printf("[ERROR]%d: %s\n", errno, strerror(errno));
			return 1;
		}

		free(buff);
		sleep(1);
	}
}
