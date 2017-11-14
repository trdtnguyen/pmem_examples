#include <libpmemobj.h>

#define MAX_BUF_LEN 10 /* maximum length of our buffer */

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


int perimeter_calc(const TOID(struct my_rectangle) rect);
