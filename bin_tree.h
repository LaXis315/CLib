#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/*struttura della lista************************************************/
typedef struct Data Data;
struct Data{
		int age;
		char nome[10];
		int height;
};


typedef struct Node Node;
struct Node{
	Node *parent;
	Node *left_child, *right_child;
	int key;
	Data *data;
};

/*global parameters****************************************************/
bool lor = 0;

/*function pointers****************************************************/
typedef void (*node_handler_t) (Node * node);

/*metodi***************************************************************/
Tree *mk_tree(void);
Node *mk_node(int key);
void assign_data(Node *node, Data cluster_dati);
Node *add_node(Node *root, int key);
void del_node_by_key(Node *root, int key);
void del_node_by_pointer(Node *node);
void del_tree(Node *root);
Node *find(Node *root, int key);
Data *get_data(Node *node);
Data *get_data_by_key(Node *root, int key);
void postorder_tr(Node *root, node_handler_t function);
void preorder_tr(Node *root, node_handler_t function);
void inorder_tr(Node *root, node_handler_t function);
void print_node_key(const Node* node);

/*inizializzazione*****************************************************/

Node *mk_node(int key){
	Node *node = (Node*) malloc(sizeof(Node));
	if(!node)
		return NULL;
	node -> parent = NULL;
	node -> left_child = NULL;
	node -> right_child = NULL;
	node -> data = NULL;
	node -> key = key;
	return node;
}

void assign_data(Node *node, Data cluster_dati){
	node->data = malloc(sizeof(Data));
	if(data == NULL)
		return;
	*(node->data) = cluster_dati;
}

/*Incremento************************************************************/

Node *add_node(Node *root, int key){
	Node **walk = &root;

	while(*walk){
		
		(*walk)->parent = *walk; //aggiorno all'ultimo genitore conosciuto
		if(key <= (*walk)->key){ //i nodi con stessa chiave vengono messi a sinistra del genitore
			walk = &((*walk)->left_child);//pointer magic
		}
		else{
			walk = &((*walk)->right_child);//pointer magic
		}
	}

	*walk = mk_node(key);

	return *walk;
}


/*Liberazione di memoria**********************************************************/

void del_node_by_key(Node *root, int key){
	Node* node = find(root, key);
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
	if(node == NULL)
		return;
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

	free(node->data);
	free(node);
}

static void del_leaf(Node *node){ //usare solo in del_tree()
	//printf("Cancellazione nodo con key: %d\n", node->key);
	if(node->key <= node->parent->key)
		node->parent->left_child = NULL;
	else
		node->parent->right_child = NULL;
	
	free(node->data);
	free(node);
}

void del_tree(Node *root){
	node_handler_t deleter = del_leaf;

	/*scollego il padre se esiste*/
	if(root->parent != NULL)
		if(root->key <= root->parent->key)
			root->parent->left_child = NULL;
		else
			root->parent->right_child = NULL;

	postorder_tr(tree->root, deleter);
}

/*Traversal, finder, and get data*************************************************************************/

Node *find(Node *root, int key){

	while(root->key != key){
		if(key <= root->key)
			root = root->left_child;
		else
			root = root->right_child;

		if(root == NULL)
			break;
	}

	return root;
}

Data *get_data(Node *node){
	return node->data;
}

Data *get_data_by_key(Tree *tree, int key){
	Node *node = find(tree, key);
	if(!node)
		return NULL;

	return get_data(node);

}

void postorder_tr(Node *root, node_handler_t function){
	if(root->left_child != NULL)
		postorder_tr(root->left_child, function);
	if(root->right_child != NULL)
		postorder_tr(root->right_child, function);

	function(root); //eseguo dopo
}

void preorder_tr(Node *root, node_handler_t function){
	function(root); //eseguo subito

	if(root->left_child != NULL)
		preorder_tr(root->left_child, function);
	if(root->right_child != NULL)
		preorder_tr(root->right_child, function);
}

void inorder_tr(Node *root, node_handler_t function){
	
	if(root->left_child != NULL)
		inorder_tr(root->left_child, function);

	function(root); //eseguo in mezzo

	if(root->right_child != NULL)
		inorder_tr(root->right_child, function);

}


/*Informazioni sull'albero e i nodi***************************************************************************/

void stampa_key(Node *node){
	printf("Key: %d\n",node->key);
}

int num_nodi(Node *root){
	if(root)
		return 0;
	int n = 1;
	n += num_nodi(root->left_child);
	n += num_nodi(root->right_child);
	return n;
}

Node *find_root(Node *node){
	while(!node->parent)
		node = node->parent;
	return node;
}

Node *rightmost_node(Node *node){
	while(!node->right_child)
		node = node->right_child;
	return node;
}

Node *leftmost_node(Node *node){
	while(!node->left_child)
		node = node->left_child;
	return node;
}

int min_key(Node *node){
	return leftmost_node(node)->key;
}

int max_key(Node *node){
	return rightmost_node(node)->key;
}

