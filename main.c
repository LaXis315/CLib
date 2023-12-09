#include "bin_tree.h"
#include <stdio.h>

int main (){
	
	Node *root = mk_node();

	assign_data(add_node(root, 21), (struct Data){10, "Morbid", 33});
	add_node(root, 10);
	add_node(root,11);
	assign_data(add_node(root,23), (struct Data){55, "Manuelito", -12});
	add_node(root,2);


	printf("\n\nPost Order Traversal:\n");
	postorder_tr(root, *stampa_key);
	printf("\n\nPre Order Traversal\n");
	preorder_tr(root, *stampa_key);
	printf("\n\nIn Order Traversal\n");
	inorder_tr(root, *stampa_key);
	printf("\n\n");

	printf("La radice ha eta: %d\n\n",get_data_by_key(root,21)->age);
	printf("La radice ha nome: %s\n\n",get_data_by_key(root,21)->nome);
	printf("La 10 ha eta: %d\n\n",get_data_by_key(root,10)->age);

	//non accettabili
	//printf("La 4 ha eta: %d\n\n",get_data_by_key(root,4)->age); 
	//printf("La 4 ha eta: %d\n\n",get_data_by_key(root,23)->height);

	printf("Ci sono ben %d nodi\n", num_nodi(root));
	
	
	del_tree(tree);
	return 0;
	
}