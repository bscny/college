typedef struct Potato tPotato;
typedef struct PotatoBall tPotatoBall;
typedef struct PotatoProducer tPotatoProducer;

tPotato *produce_outside(tPotatoProducer *producer);
void print_outside_Potato(tPotato **p_potato_ptr);
tPotatoBall *fry_oitside(tPotato **p_potato_ptr);
void print_outside_PotatoBALL(tPotatoBall **p_potatoball_ptr);
void dtor_outside(tPotatoBall **p_potatoball_ptr);

struct Potato{
	tPotatoProducer *producer;
	int weight;
	int magical;
	char effect[32];
	void (*print)(struct Potato **p_potato_ptr);
	tPotatoBall* (*fry)(struct Potato **p_potato_ptr);
};

struct PotatoBall{
	tPotatoProducer *producer;
	int weight;
	int magical;
	char effect[32];
	void (*print)(struct PotatoBall **p_potatoball_ptr);
	void (*dtor)(struct PotatoBall **p_potatoball_ptr);
};

struct PotatoProducer{
	char name[20];
	int magical;
	tPotato* (*produce)(struct PotatoProducer *producer);
};

//init-----------
void init_potato_producer(tPotatoProducer *producer, const char *name, int magical){
	strcpy(producer->name , name);
	producer->magical = magical;
	producer->produce = produce_outside; //member func produce_outside defined
}
//init------------


//setting member func-----------------------

//member func of produce
tPotato *produce_outside(tPotatoProducer *producer){
	tPotato *potato_ptr;

	potato_ptr = malloc(1*sizeof(tPotato));
	potato_ptr->producer = producer;
	potato_ptr->weight = (rand()%1000)+1;
	potato_ptr->magical = producer->magical;
	strcpy(potato_ptr->effect , "slowness");
	potato_ptr->print = print_outside_Potato; //member func print_outside_Potato defined
	potato_ptr->fry = fry_oitside; //member func fry_outside defined

	return potato_ptr;
}

//member func of print
void print_outside_Potato(tPotato **p_potato_ptr){
	tPotato *potato_ptr = *p_potato_ptr;
	
	if(potato_ptr->magical == 0){ //no magic
		printf("Potato:\n");
		printf("  producer: %s\n", potato_ptr->producer->name);
		printf("  weight: %d\n", potato_ptr->weight);
	}else{
		printf("Magical Potato:\n");
		printf("  producer: %s\n", potato_ptr->producer->name);
		printf("  weight: %d\n", potato_ptr->weight);
		printf("  effect: %s\n", potato_ptr->effect);
	}
}

//member func of fry
tPotatoBall *fry_oitside(tPotato **p_potato_ptr){
	tPotato *potato_ptr = *p_potato_ptr;
	tPotatoBall *potatoball_ptr;

	potatoball_ptr = malloc(1*sizeof(tPotatoBall));
	potatoball_ptr->producer = potato_ptr->producer;
	potatoball_ptr->weight = potato_ptr->weight;
	potatoball_ptr->magical = potato_ptr->magical;
	strcpy(potatoball_ptr->effect , potato_ptr->effect);
	potatoball_ptr->print = print_outside_PotatoBALL; //member func produce_outside_PotatoBall defined
	potatoball_ptr->dtor = dtor_outside; //member func dtor_outside defined

	free(potato_ptr); //delete the potato
	p_potato_ptr = NULL;

	return potatoball_ptr;
}

//member func of print ball
void print_outside_PotatoBALL(tPotatoBall **p_potatoball_ptr){
	tPotatoBall *potatoball_ptr = *p_potatoball_ptr;
	
	if(potatoball_ptr->magical == 0){ //no magic
		printf("Potato Ball:\n");
		printf("  producer: %s\n", potatoball_ptr->producer->name);
		printf("  weight: %d\n", potatoball_ptr->weight);
	}else{
		printf("Magical Potato Ball:\n");
		printf("  producer: %s\n", potatoball_ptr->producer->name);
		printf("  weight: %d\n", potatoball_ptr->weight);
		printf("  effect: %s\n", potatoball_ptr->effect);
	}
}

//member func of dtor
void dtor_outside(tPotatoBall **p_potatoball_ptr){
	free(*p_potatoball_ptr);
	p_potatoball_ptr = NULL;
}
