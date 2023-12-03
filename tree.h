#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

//struttura della lista

typedef struct Node Node;
struct Node{  //nodi collegabili con il successivo e precendente
	Node *parent;
	int n_childrens;
	Node **childrens;
	int key;
	char *nome;
};


typedef struct{  //testa che punta alla radice dell' albero e la sua grandezza
	int size;
	Node *root;  //puntatore alla radice
} Tree;


//Metodi per inizializzare, incrementare, cercare, rimuovere
Node *mk_node(int key);




Tree *mk_tree(int root_key){

	Tree *tree_head = (Tree*) malloc(sizeof(Tree));
	tree_head->size = 1;
	tree_head->root = mk_node(root_key);
	return tree_head;

}

Node *mk_node(int key){
	Node *node = (Node*) malloc(sizeof(Node));
	node -> parent = NULL;
	node -> childrens = (Node **) malloc(0);
	node -> key = key;
	return node;
}

/******************************************************************/

int tree_size(Tree *tree){
	return tree -> size;
}

Node *rec_get(Node *root, int key){
	int n_child;
	if(root->key == key)
		return root;	
	else if(n_child = root->n_childrens){
		for(int i = 0; i < n_child; i++){
			Node *n = rec_get(root->childrens[i], key);
			if(n != NULL)
				return n;
		}
	}
	return NULL;
}

void assign_new_childrens(Node *dest,int n_childrens_to_add, Node **new_childrens){
	int n = (dest -> n_childrens) + n_childrens_to_add;
	//rialloco i vecchi nodi
	dest->childrens = (Node **) realloc(dest->childrens,((sizeof(Node *))*n));
	//aggiungo alla fine i nuovi
	for(int i = dest->n_childrens; i < n; i++)
		*(dest->childrens)[i] = *new_childrens[i-(dest->n_childrens)];
	
	//aggiorno il numero di figli
	dest->n_childrens += n_childrens_to_add;
}


Node *add_child(Tree *tree, Node *dest, int key){

	if(dest == NULL)
		add_child(tree, tree->root, key);
	Node *new_child = mk_node(key);
	new_child -> parent = dest;
	assign_new_childrens(dest,1,&new_child);
	tree -> size++;

	return dest->childrens[dest->n_childrens-1];
}

void deassign_children(Node *dest, Node *child){
	int n = dest->n_childrens;
	int child_position;
	for(int i=0; i<n; i++){
		if(dest->childrens[i] == child)
			child_position = i;
	}

	n--;
	Node **new_list = (Node **) malloc(sizeof(Node*)*n);
	for(int i=0; i<n; i++){
		if(i >= child_position){
			new_list[i]= dest->childrens[i+1];
			continue;		
		}
		new_list[i]=dest->childrens[i];
	}
	dest->childrens = new_list;
	dest->n_childrens = n;
}

static int del_node(Tree *tree, Node *node){
	if(node->parent == NULL){
		return -1;
	}
	deassign_children(node->parent, node);
	if(node->n_childrens != 0){
		assign_new_childrens(node->parent, node->n_childrens, node->childrens);
	}
	
	free(node->childrens);
	free(node);
	tree->size--;

	return 0;
}

static int del_root(Tree *tree){
	Node *root = tree->root;
	//sfrutto la funzionalità che, alla cancellazione di un nodo i figli vengano dati al padre
	//quindi cancellando un figlio della radice, questa si prende tutti i figli
	//quindi iteriamo la cancellazione dei figli fino al loro esaurimento

	while(root->n_childrens)
		del_node(tree,root->childrens[0]);
	free(root);
	return 0;
}


static int del_tree(Tree *tree){
	Node *root = tree->root;
	del_root(tree);
	free(tree);
	return 0;
}
