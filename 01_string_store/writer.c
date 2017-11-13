#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>
#include "layout.h"

int main(int argc, char* argv[]) {
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
	char buf[MAX_BUF_LEN];
	scanf("%9s", buf);

	//make length and buf persistent
	rootp->len = strlen(buf);
	pmemobj_persist(pop, &rootp->len, sizeof (rootp->len));
	pmemobj_memcpy_persist(pop, rootp->buf, buf, rootp->len);

	pmemobj_close(pop);
	return 0;
}
