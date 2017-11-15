#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libpmemobj.h>

#include "rect.h"


int perimeter_calc(const TOID(struct my_rectangle) rect) {
	return D_RO(rect)->w * D_RO(rect)->h;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: %s file_name width height \n", argv[0]);
		return 1;
	}
	
	PMEMobjpool *pop = pmemobj_create(argv[1],
			POBJ_LAYOUT_NAME(rect_lay), PMEMOBJ_MIN_POOL, 0666);
	if (pop == NULL){
		perror("pmemobj_create");
		return 1;
	}

	TOID(struct my_root) root = POBJ_ROOT(pop, struct my_root);

	TX_BEGIN (pop) {
		TX_ADD(root);
		//declare and assign
		TOID(struct my_rectangle) rect = TX_NEW(struct my_rectangle);
		D_RW(rect)->w = atoi(argv[2]);
		D_RW(rect)->h = atoi(argv[3]);
		D_RW(root)->rect = rect;
	} TX_END

	int p = perimeter_calc(D_RO(root)->rect);
	// busy work 
	printf("perimeter is: %d\n",p);
	
	return 0;
}
