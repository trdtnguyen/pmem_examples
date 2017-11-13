#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>

#include "layout.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: %s file-name\n", argv[0]);
		return 1;
	}

	//PMEMobjpool *pop = pmemobj_open(argv[1], LAYOUT_NAME);
	PMEMobjpool *pop = pmemobj_open(argv[1], POBJ_LAYOUT_NAME(string_store));
	if (pop == NULL){
		perror("pmemobj_open");
		return 1;
	}

	//Old version
//	PMEMoid root = pmemobj_root(pop, sizeof (struct my_root));
//	struct my_root *rootp = pmemobj_direct(root);
	
	TOID(struct my_root) root = POBJ_ROOT(pop, struct my_root);	

	//Old version
//	if (rootp->len == strlen(rootp->buf))
//		printf("%s\n", rootp->buf);

	printf("%s\n", D_RO(root)->buf);

	pmemobj_close(pop);

	return 0;
		
}
