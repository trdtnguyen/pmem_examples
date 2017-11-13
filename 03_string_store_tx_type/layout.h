
#define MAX_BUF_LEN 10 /* maximum length of our buffer */

//you can name the layout as "string_store" or other name
POBJ_LAYOUT_BEGIN(string_store);
	//link the layout name with your struct
	POBJ_LAYOUT_ROOT(string_store, struct my_root);
POBJ_LAYOUT_END(string_store)

struct my_root {
		char buf[MAX_BUF_LEN];
};
