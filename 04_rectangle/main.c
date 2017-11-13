#include <stdio.h>
#include <string.h>
#include <libpmemobj.h>

//#include "rect.h"

struct my_rectangle;
struct my_root;

//TOID_DECLARE(struct my_rectangle);


struct my_rectangle {
		int w;
		int h;
};


//you can name the layout as "string_store" or other name
POBJ_LAYOUT_BEGIN(rect_lay);
	//link the layout name with your struct
	POBJ_LAYOUT_ROOT(rect_lay, struct my_root);
	POBJ_LAYOUT_TOID(rect_lay, struct my_rectangle);
//	POBJ_LAYOUT_TOID(rect_lay, TOID( struct my_rectangle));
POBJ_LAYOUT_END(rect_lay)

struct my_root {
	TOID(struct my_rectangle) rect;
};

int perimeter_calc(const TOID(struct my_rectangle) rect) {
	return D_RO(rect)->w * D_RO(rect)->h;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s width height \n", argv[0]);
		return 1;
	}

	PMEMobjpool *pop = pmemobj_create("ptemp",
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
		D_RW(rect)->w = 3;
		D_RW(rect)->h = 4;
		D_RW(root)->rect = rect;
	} TX_END

	int p = perimeter_calc(D_RO(root)->rect);
	// busy work 
	
	return 0;
}
