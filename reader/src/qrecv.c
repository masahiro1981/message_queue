#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


//#define QNAME "/home/masahiro/testq"
//#define QNAME "$SNAP_DATA/testq"
#define QNAME "/testq"
int main(){
	mqd_t q;
	struct mq_attr attr;
	char *buff;
	ssize_t n;
	int i;

	q = mq_open(QNAME, O_RDONLY);
	if ( q == -1 ){
		printf("[ERROR]%d: %s\n", errno, strerror(errno));
		printf("%s",QNAME);
        return 1;
	}

	while(1){
		mq_getattr( q ,&attr );
        printf("attr.mq_msgsize* %ld",attr.mq_msgsize);
		buff = (char *)malloc(attr.mq_msgsize);
		n = mq_receive( q, buff, attr.mq_msgsize, NULL);
		if ( n == -1	) {
			printf("[ERROR]%d: %s\n", errno, strerror(errno));
			return 1;
		}

		for (i = 0; i < n; i++) putchar(buff[i]);
		putchar('\n');
		fflush(stdout);
		free(buff);
	}
}
