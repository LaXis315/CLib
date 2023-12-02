#include <malloc.h>
#include <math.h>
//struttura della lista

typedef struct node{  //nodi collegabili con il successivo e precendente
	struct node *parent;
	int n_childrens;
	struct node **childrens;
	int key;
	char *nome;

} Node;


typedef struct head{  //testa che punta alla radice dell' albero e la sua grandezza
	int size;
	Node *root;  //puntatore alla radice
} Head;


//Metodi per inizializzare, incrementare, cercare, rimuovere

Head *mk_head();
int head_size(Head *tree);
Node *mk_node(int key);
Node *rec_get(Node *root, int key);
void incr_list(Head *tree);
int del_node(Head *tree, int key);
int del_head(Head *tree);




Head *mk_head(int root_key){

	Head *head = (Head*) malloc(sizeof(Head));
	head->size = 1;
	head->root = mk_node(root_key);
	return head;

}

Node *mk_node(Node* parent,int key){
	Node *node = (Node*) malloc(sizeof(Node));
	node -> parent = parent;
	node -> childrens = (Node *) malloc(0);
	node -> key = key;
	return node;
}

/******************************************************************/

int head_size(Head *tree){
	return tree -> size;
}

Node *rec_get(Node *root, int key){
	if(node->key == key)
		return node;
	int n_child;	
	else if(n_child = root->n_childrens){
		for(int i = 0; i < n_child; i++){
			Node *n = rec_get(root->childrens[i]);
			if(n != NULL)
				return n;
		}
	}
	return NULL;
}

void assign_new_childrens(Node *dest,int n_childrens_to_add, Node **new_childrens){
	int n = (dest -> n_childrens) += n_childrens_to_add;
	//rialloco i vecchi nodi
	dest->childrens = (Node *) realloc(dest->childrens,size_of(Node*)*n);
	//aggiungo alla fine i nuovi
	*((dest->childrens)+n-n_childrens_to_add) = new_childrens;
}


Node *add_child(Head *tree, Node *dest, int key){

	if(dest == NULL)
		add_child(tree, tree->root, key);
	assign_new_childrens(dest,1,&mk_node(key));
	tree -> size++;

	return dest->childrens[dest->n_children-1];
}

void deassign_children(Node *dest, Node *child){
	int n = dest->n_childrens;
	int child_position;
	for(int i=0; i<n; i++){
		if(dest->childrens[i] == child)
			child_postion = i;
	}

	n--;
	Node *new_list = (Node *) malloc(sizeof(Node*)*n);
	for(int i=0; i<n; i++){
		if(i >= child_position){
			new_list[i]=dest->childrens[i+1]
			continue;		
		}
		new_list[i]=dest->childrens[i];
	}
	dest->childrens = new_list;
	dest->n_childrens = n;
}

static int del_node(Head *tree, Node *node){
	if(node->parent == null){
		return -1;
	}
	deassign_children(node->parent, node);
	if(node->n_childrens == 0)
		
	else{
		assign_new_childrens(parent, node->n_childrens, node->childrens);
	}
	free(node->childrens);
	free(node);
	tree->size--;

	return 0;
}

static int del_root(Head *tree){
	Node *root = tree->root;
	//sfrutto la funzionalità che, alla cancellazione di un nodo i figli vengano dati al padre
	//quindi cancellando un figlio della radice, questa si prende tutti i figli
	//quindi iteriamo la cancellazione dei figli fino al loro esaurimento

	while(!(root->n_childrens))
		del_node(tree,root->childrens[0]);
	free(root);
	return 0;
}


static int del_head(Head *tree){
	Node *root = tree->root;
	del_root(tree);
	free(tree);
	return 0;
}
