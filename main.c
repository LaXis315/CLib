#include "bin_tree.h"
#include <stdio.h>


int main (){
	
	Tree *tree = mk_tree();

	assign_data(add_node(tree, 21), (Data){10, "Morbid", 33});
	add_node(tree, 10);
	add_node(tree,11);
	assign_data(add_node(tree,23), (Data){55, "Manuelito", -12});


	postorder_tr(tree->root, *stampa_key);
	printf("La radice ha eta: %d",tree->root->data->age);


	
	del_tree(tree);
	return 0;
	
}