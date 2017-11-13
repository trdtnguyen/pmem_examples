#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>
#include "layout.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("usage: %s file-name\n", argv[0]);
		return 1;
	}
	//create the pool file with the filename is the first arg
	PMEMobjpool *pop = pmemobj_create(argv[1], LAYOUT_NAME, PMEMOBJ_MIN_POOL, 0666);
	if (pop == NULL) {
		perror("pmemobj_create");
		return 1;
	}

	//request root object and transfer it to direct pointer
	PMEMoid root = pmemobj_root(pop, sizeof (struct my_root));
	struct my_root *rootp = pmemobj_direct(root);

	//read max 9 bytes to the temp buffer
	char buf[MAX_BUF_LEN] = {0};
	if(scanf("%9s", buf) == EOF) {
		fprintf(stderr, "EOF\n");
		return 1;
	}

	//make length and buf persistent
//	rootp->len = strlen(buf);
//	pmemobj_persist(pop, &rootp->len, sizeof (rootp->len));
//	pmemobj_memcpy_persist(pop, rootp->buf, buf, rootp->len);

	TX_BEGIN(pop) {
		pmemobj_tx_add_range(root, 0, sizeof (struct my_root)); 
		//after add_range we can use normal system call to access the persistent memory
		memcpy(rootp->buf, buf, strlen(buf));
	} TX_END

	pmemobj_close(pop);
	return 0;
}
