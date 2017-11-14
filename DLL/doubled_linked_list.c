#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <inttypes.h>

#include <libpmemobj.h>

POBJ_LAYOUT_BEGIN(dll);
POBJ_LAYOUT_ROOT(dll, struct my_root);
POBJ_LAYOUT_TOID(dll, struct note);
POBJ_LAYOUT_END(dll);

static PMEMobjpool *pop;
static TOID(struct note) current_note;

struct note;
struct my_root;



struct note {
	time_t date_created;
	POBJ_LIST_ENTRY(struct note) notes;
	char msg[];
};


//the root will include the head 
struct my_root {
	POBJ_LIST_HEAD(linkedlist, struct note) head;	
};

//this function is called by note_add, do not call it directly
static int 
note_construct(PMEMobjpool *pop, void *ptr, void *arg) {
	struct note *n = (struct note*) ptr;
	char *msg = (char*) arg;

	pmemobj_memcpy_persist(pop, n->msg, msg, strlen(msg));

	time(&n->date_created); 
	pmemobj_persist(pop, &n->date_created, sizeof (time_t));

	return 0;
}

static void 
note_add(char* msg){
	TOID(struct my_root) root = POBJ_ROOT(pop, struct my_root);

	size_t nlen = strlen(msg);
	POBJ_LIST_INSERT_NEW_HEAD(pop, &D_RW(root)->head, notes,
			sizeof(struct note) + nlen,
			note_construct, msg);
}

static void
note_read_init() {
	TOID(struct my_root) root = POBJ_ROOT(pop, struct my_root);		

	current_note = POBJ_LIST_FIRST(&D_RO(root)->head);
}


static void
note_print(const TOID(struct note) n) {
	printf("Create at %s: \n %s \n", ctime(&D_RO(n)->date_created), 
		 D_RO(n)->msg);
}

static void
note_print_all() {
	TOID(struct my_root) root = POBJ_ROOT(pop, struct my_root);
	TOID(struct note) iter;
	POBJ_LIST_FOREACH(iter, &D_RO(root)->head, notes){
		note_print(iter);
	}
		
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s file_name list_size \n", argv[0]);
		return 1;
	}
	pop = NULL;	
	const char* path = argv[1];
	if( (pop = pmemobj_create(argv[1],
					POBJ_LAYOUT_NAME(dll),
					PMEMOBJ_MIN_POOL, 0666))==NULL){
		printf("fail to create pool\n");
		return 1;
	}
	note_add("TEST Message");

	note_read_init();
	//note_print(current_node);

	printf("End program\n");

	return 0;
}
