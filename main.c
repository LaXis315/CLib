#include "bin_tree.h"
#include <stdio.h>

int main (){
	
	Tree *tree = mk_tree();

	assign_data(add_node(tree, 21), (struct Data){10, "Morbid", 33});
	add_node(tree, 10);
	add_node(tree,11);
	assign_data(add_node(tree,23), (struct Data){55, "Manuelito", -12});
	add_node(tree,2);


	printf("\n\nPost Order Traversal:\n");
	postorder_tr(tree->root, *stampa_key);
	printf("\n\nPre Order Traversal\n");
	preorder_tr(tree->root, *stampa_key);
	printf("\n\nIn Order Traversal\n");
	inorder_tr(tree->root, *stampa_key);
	printf("\n\n");

	printf("La radice ha eta: %d\n\n",get_data_by_key(tree,21)->age);
	printf("La radice ha nome: %s\n\n",get_data_by_key(tree,21)->nome);
	printf("La 10 ha eta: %d\n\n",get_data_by_key(tree,10)->age);
	printf("La 4 ha eta: %d\n\n",get_data_by_key(tree,4)->age);
	printf("La 4 ha eta: %d\n\n",get_data_by_key(tree,23)->height);

	
	del_tree(tree);
	return 0;
	
}