#include "bin_tree.h"
#include <stdio.h>


typedef struct Data Data;
struct Data{
	int age;
	char nome[10];
	int height;
};

void make_data(Data *d, int age, char *nome, int height){
	d->age = age;
	strcpy(d->nome, nome);
	d->height = height;
}

void show_data(Node *node){
	Data d;
	if(!get_data(node, &d))
		return;

	printf("Eta: %d\n", d.age);
	printf("Nome: %s\n", d.nome);
	printf("Altezza: %d\n\n\n", d.height);
}


int main (){
	size_t size = sizeof(Data);
	Data d;
	make_data(&d, 54, "Franco", 310);

	Node *root = mk_node_w_data(3, &d, size);
	


	/*aggiungo i nodi assegnando anche i valori*/
	make_data(&d, 10, "Mario", 100);
	add_node_w_data(root, 21, &d, size);
	add_node(root, 10);
	add_node(root,11);
	make_data(&d, 22, "Luigi", -100);
	add_node_w_data(root, 23, &d, size);
	add_node(root,2);

	/*calcolo quanti nodi ci sono*/
	printf("Ci sono ben %d nodi\n", num_nodi(root));

	/*stampo le key dei nodi nei vari traversal*/
	printf("\n\nPost Order Traversal:\n");
	postorder_tr(root, stampa_key);
	printf("\n\nPre Order Traversal\n");
	preorder_tr(root, stampa_key);
	printf("\n\nIn Order Traversal\n");
	inorder_tr(root, stampa_key);
	printf("\n\n");

	/*stampo i dati in preordine*/
	preorder_tr(root, show_data);

	del_tree(root);
	return 0;
	
}