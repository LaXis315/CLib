#include <malloc.h>
#include <math.h>

//metodi extra
int modulo(int pos, int size){
	double y = -(double)pos/size;  // formula dalla matematica modulare: (size+pos)/size > x >= pos/size
	return pos += size*ceil(y);
}

//struttura della lista

typedef struct node{  //nodi collegabili con il successivo e precendente
	struct node *next;
	struct node *prev;
	int pos;
	char *nome;

} Node;


typedef struct head{  //testa che segna l'inizio della lista e la sua grandezza
	int size;
	Node *top;  //puntatore al primo nodo
} Head;


//Metodi per inizializzare, incrementare, cercare, rimuovere

Head *mk_head();
int head_size(Head *list);
Node *mk_node(int last_pos);
Node *get(Head *list, int posizioni);
void incr_list(Head *list);
int del_node(Head *list, int pos);
int del_head(Head *list);




Head *mk_head(){

	Head *head = (Head*) malloc(sizeof(Head));
	head->size = 0;
	return head;

}

Node *mk_node(int last_pos){
	Node *node = (Node*) malloc(sizeof(Node));
	node -> pos = last_pos+1;
	return node;
}

/******************************************************************/

int head_size(Head *list){
	return list -> size;
}

Node *get(Head *list, int posizioni){
	Node *node1 = list -> top;
	int size = list->size;

	if(size == 0)
		incr_list(list);

	if(posizioni < 0 || size <= posizioni){
		posizioni = modulo(posizioni, size);
	}

	for(int i = 0; i < posizioni; i++){ //faccio un get di n posizioni
		node1 = node1 -> next;
	}
	return node1;
}


void incr_list(Head *list){

	int size = list -> size;

	if(size == 0){
		Node *node = mk_node(-1);
		list -> top = node;
		//collegato a se stesso
		node -> next = node;
		node -> prev = node;
	}
	else{
		Node *lst_node = get(list,size-1);
		Node *new_lst_node = lst_node -> next = mk_node(size-1);
		//riallacciamo l' ultimo nodo al primo (top)
		new_lst_node -> next = list -> top;
		list -> top -> prev = new_lst_node;
		//allacciamento al penultimo nodo
		new_lst_node -> prev = lst_node;
	}

	(list -> size)++;
}


int del_node(Head *list, int pos){

	int size = list->size;
	if(size == 0)
		return -1; //errore, non esistono nodi

	if(pos < 0 || size <= pos){
		pos = modulo(pos, size);
	}

	Node *node = get(list,pos);

	node -> next -> prev = node -> prev;
	//list -> next -> prev = node -> prev;  equivalente al precedente
	node -> prev -> next = node -> next;

	free(node);

	(list -> size)--;

	return 0;
}

int del_head(Head *list){
	int size = list->size;

	if(size > 0){ //liberiamo spazio occupato dai nodi se esistono
		Node *node = list -> top;
		for(int i = 0; i < size; i++){
			Node *mom = node->next;
			free(node);
			node = mom;
		}
	}

	free(list);

	return 0;
}



/* Descriviamo il comportamento dei metodi:

1) mk_head: funzione che crea un head per una nuova lista, ritorna il puntatore all' head

2) mk_node: funzione che crea un nodo, non deve essere utilizzato dall' utente, ma viene usato dalla 
   funzione incr_list, ritorna un puntatore al nodo;

3) incr_list: funzione che ottiene un nodo da mk_node e lo aggiunge all'insieme di nodi della lista.
   si occupa degli allacciamenti

4) get : cerca nella lista il nodo alla posizione richiesta (se la posizione non esiste, viene calcolato il modulo)
   se non esistono nodi (size == 0), viene creato un nodo tramite la funzione incr_list;

5) del_node : cancella un nodo alla posizione scelta liberando la memoria e riallacciando i puntatori
   se non esistono nodi, viene dato return -1 che e un errore. 

6) del_head: cancella tutta la lista assieme ai nodi liberando la memoria

7) head_size : funzione che ritorna il numero di nodi nella lista

*/