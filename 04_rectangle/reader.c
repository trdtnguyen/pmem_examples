#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>

#include "rect.h"

int main(int argc, char *argv[]) {
	int w, h;

	if (argc != 2) {
		printf("usage: %s file-name\n", argv[0]);
		return 1;
	}

	//PMEMobjpool *pop = pmemobj_open(argv[1], LAYOUT_NAME);
	PMEMobjpool *pop = pmemobj_open(argv[1], POBJ_LAYOUT_NAME(rect_lay));
	if (pop == NULL){
		perror("pmemobj_open");
		return 1;
	}
	
	TOID(struct my_root) root = POBJ_ROOT(pop, struct my_root);	

	w = D_RO(D_RO(root)->rect)->w;
	h = D_RO(D_RO(root)->rect)->h;

	printf("w is %d h is %d\n", w, h);

	pmemobj_close(pop);

	return 0;
		
}
