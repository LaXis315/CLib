#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/*struttura della lista************************************************/
typedef struct{
	char name[20];
	int age;
} Data;

typedef struct Node Node;
struct Node{
	Node *parent;
	Node *left_child, *right_child;
	int key;
	Data dati;
};

typedef struct{  //testa che punta alla radice dell' albero e la sua grandezza
	int size;
	Node *root;  //puntatore alla radice
} Tree;

/*global parameters****************************************************/
bool lor = 0;

/*function pointers****************************************************/
typedef void (*node_handler_t) (Node * node);

/*metodi***************************************************************/
Tree *mk_tree(void);
Node *mk_node(int key);
void add_node(Tree* tree, int key);
void del_node_by_key(Tree *tree, int key);
void del_node_by_pointer(Node *node);
void del_head();
Node *find(Tree *tree, int key);
void preoreder_tr(Node *root, node_handler_t function);
void postorder_tr(Node *root, node_handler_t function);
void inorder_tr(Node *root, node_handler_t function);
void print_node_key(const Node* node);

/*inizializzazione*****************************************************/
 

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

/*Incremento************************************************************/

void add_node(Tree *tree, int key){
	Node *node = mk_node(key);
	if(tree->root == NULL){
		tree->root = node;
		return;
	}

	Node **walk = &(tree->root);

	while(*walk){ 
		if(key <= (*walk)->key) //i nodi con stessa chiave vengono messi a sinistra del genitore
			walk = &((*walk)->left_child);//pointer magic
		else
			walk = &((*walk)->right_child);//pointer magic
	}

	*walk = node;
}


/*Liberazione di memoria**********************************************************/

void del_node_by_key(Tree *tree, int key){
	Node* node = find(tree, key);
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
	cpynode1.right_child = node1->right_child;		
	cpynode1.parent = node1->parent;
	
	node1 -> left_child = node2->left_child;
	node1 -> right_child = node2->right_child;
	node1 -> parent = node2->parent;

	node2 -> left_child = cpynode1.left_child;
	node2 -> right_child = cpynode1.right_child;
	node2 -> parent = cpynode1.parent;	

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

static void del_leaf(Node *node){ //usare solo se il nodo non ha figli
	if(node->left_child == NULL || node->right_child == NULL)
		return;
	if(node->key <= node->parent->key)
		node->parent->left_child = NULL;
	else
		node->parent->right_child = NULL;
	free(node);
}

void del_tree(Tree *tree){
	node_handler_t deleter = del_leaf;
	postorder_tr(tree->root, deleter);
	free(tree);
}

/*Traversal and finder*******************************************************************************/

Node *find(Tree *tree, int key){
	Node *walk = tree->root;

	while(walk != NULL || walk->key != key){
		if(key <= walk->key)
			walk = walk->left_child;
		else
			walk = walk->right_child;
	}

	return walk;
}

void postorder_tr(Node *root, node_handler_t function){
	if(root->left_child != NULL)
		postorder_tr(root->left_child, function);
	if(root->right_child != NULL)
		postorder_tr(root->right_child, function);

	function(root);
}




/*Stampa key nodo***************************************************************************/

void stampa_key(Node *node){
	printf("Key: %d\n",node->key);
}

