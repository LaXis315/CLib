#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

//parameter
bool lor = 0;

//metodi
Tree *mk_tree(void);
Node *mk_node(int key);
void del_node_by_key(int key);
void del_node_by_pointer(Node *node);
void del_head();
void preoreder_tr(const Tree *tree);
void postorder_tr(const Tree *tree);
void inorder_tr(const Tree *tree);




//struttura della lista
typedef struct data Data; //necessario definirlo

typedef struct Node Node;
struct Node{
	Node *parent;
	Node * left_child,right_child;
	int key;
	Data dati;
};


typedef struct{  //testa che punta alla radice dell' albero e la sua grandezza
	int size;
	Node *root;  //puntatore alla radice
} Tree;

/*****************************************************************/
//inizializzazione 

Tree *mk_tree(void){

	Tree *tree_head = (Tree*) malloc(sizeof(Tree));
	tree_head->size = 0;
	tree_head->root = NULL;
	return tree_head;

}

Node *mk_node(int key){
	Node *node = (Node*) malloc(sizeof(Node));
	node -> parent = NULL;
	node -> left_child = NULL;
	node -> right_child = NULL;
	node -> key = key;
	return node;
}


//Liberazione di memoria

void del_node_by_key(int key){
	Node* node = find(int key);
	del_node_by_pointer(node);
}

static void bidirectional_p(Node *node){ //make the pointers of a node bidirectional (the parent and childs points at him)
	if(lor)
		node->parent->left_child = node;
	else
		node->parent->right_child = node;

	node->left_child->parent = node;
	node->right_child->parent = node;
}

static void switch_nodes(Node *node1, Node *node2){
	Node cpynode1;
	cpynode1.left_child = node1->left_child;
	cpynode1.right_child = node1->right_child		
	cpynode1.parent = node1->parent;
	
	node1 -> left_child = node2->left_child;
	node1 -> right_child = node2->right_child;
	node1 -> parent = node2->parent;

	node2 -> left_child = cpyleaf.left_child;
	node2 -> right_child = cpyleaf.right_child;
	node2 -> parent = cpyleaf.parent;	

	bidirectional_p(node1);
	bidirectional_p(node2);
}

void del_node_by_pointer(Node *node){
	if(node->left_child != NULL && node->right_child != NULL){  //se ho due figli, scambio il nodo con una foglia specifica
		Node *leaf;
		if(lor){
			leaf = node->right_child;
			while(leaf->left_child)
				leaf = leaf->left_child;
		}
		else{
			leaf = node->right_child;
			while(leaf->right_child)
				leaf = leaf->right_child;
		}

		switch_nodes(leaf, node);
	}
	
	Node *parent = node -> parent;

	Node *child;
	child = (node->left_child == NULL ? node->right_child : node->left_child);

	if(node->key <= parent->key)
		parent->left_child = child;
	else
		parent->right_child = child;

	free(node);
}

void del_tree(Tree *tree){


}

