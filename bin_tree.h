#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/*struttura della lista************************************************/
// typedef struct Data Data;
// struct Data{
// 	int age;
// 	char nome[10];
// 	int height;
// };


typedef struct Node Node;
struct Node{
	Node *parent;
	Node *left_child, *right_child;
	int key;
	void *data;
	size_t size; //size block of data
};

/*global parameters****************************************************/
bool lor = 0;

/*function pointers****************************************************/
typedef void (*node_handler_t) (Node * node);

/*metodi***************************************************************/
Node *mk_node(int key);
bool assign_data(Node *node, void *cluster_dati, size_t size);
Node *mk_node_w_data(int key, void *cluster_dati, size_t size);
Node *add_node(Node *root, int key);
Node *add_node_w_data(Node *root, int key, void *cluster_dati, size_t size);

void del_node_by_key(Node *root, int key);
void del_node_by_pointer(Node *node);
void del_tree(Node *root);

Node *find(Node *root, int key);
bool get_data(Node *node, void *buffer);
bool get_data_by_key(Node *root, void *buffer, int key);
void postorder_tr(Node *root, node_handler_t function);
void preorder_tr(Node *root, node_handler_t function);
void inorder_tr(Node *root, node_handler_t function);
void print_node_key(const Node* node);

/*inizializzazione*****************************************************/

Node *mk_node(int key){
	Node *node = malloc(sizeof(Node));
	if(!node)
		return NULL;
	node -> parent = NULL;
	node -> left_child = NULL;
	node -> right_child = NULL;
	node -> data = NULL;
	node -> size = 0;
	node -> key = key;
	return node;
}

bool assign_data(Node *node, void *cluster_dati, size_t size){
	node->data = malloc(size);
	if(!node->data)
		return false;
	
	memcpy(node->data, cluster_dati, size);
	node->size = size;
	return true;
}

Node *mk_node_w_data(int key, void *cluster_dati, size_t size){
	Node *node = mk_node(key);
	assign_data(node, cluster_dati, size);
	return node;
}

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

Node *add_node_w_data(Node *root, int key, void *cluster_dati, size_t size){
	Node *node = add_node(root,key);
	assign_data(node, cluster_dati, size);
	return node;
}


/*Liberazione di memoria**********************************************************/

void del_node_by_key(Node *root, int key){
	Node* node = find(root, key);
	del_node_by_pointer(node);
}

static bool disconnect_parent(Node *node){
	Node *parent = node->parent;

	if(!parent)
		return false;

	Node *new_child = (!node->left_child ? node->right_child : node->left_child);

	if(node->key <= parent->key)
		parent->left_child = new_child;
	else
		parent->right_child = new_child;

	return true;

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
	
	disconnect_parent(node);

	free(node->data);
	free(node);
}

static void del_leaf(Node *node){ //usare solo in del_tree()
	disconnect_parent(node);
	
	free(node->data);
	free(node);
}

void del_tree(Node *root){
	node_handler_t deleter = del_leaf;
	postorder_tr(root, deleter);
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
	if(!root)
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

bool get_data(Node *node, void *buffer){
	if(!node->data)
		return false;
	memcpy(buffer, node->data, node->size);
	return true;
}

bool get_data_by_key(Node *root, void *buffer, int key){
	Node *node = find(root, key);
	if(!node)
		return false;
	
	return get_data(node, buffer);
}

