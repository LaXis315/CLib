L'header bin_tree.h è un header sviluppato per permettere lo sviluppo di alberi binari e il loro accesso.

La struttura di un albero binario fatta da questo header è: struct Tree (raccolta di info sull'albero e puntatore alla radice)  -----> root ------> left_child or right_child ------> left_child or right_child ----> .....

Tree {int size (numero nodi), Node* root (puntatore a nodo)}
Node {int key (chiave che decide la posizione del nodo nell'albero), Node *left_child, *right_child (figli del nodo), Node *parent (puntatore al genitore), Data *data (puntatore ai dati del nodo, questi possono essere cambiati indipendentemente)}

metodi:

Tree *mk_tree() : creazione di un albero (strutta con metadati e puntatore a root), viene restituito il puntatore alla struttura Tree.

Node *mk_node(int key) : creazione di un nodo con allocazione di memoria e assegnazione del valore key, viene restituito il puntatore a nodo (NULL il resto).

void assign_data(Node *node, Data cluster_dati) : vengono assegnati i dati (secondo lo struct data al nodo scelto).

Node *add_node(Tree* tree, int key) : viene aggiunto un nodo, con chiave key, secondo il metodo di costruizione alberi binari. Viene restituito il puntatore al nodo.

void del_node_by_key(Tree *tree, int key) : Si cerca il nodo secondo la sua key e viene cancellato invocando del_node_by_pointer.

void del_node_by_pointer(Node *node) : cancellazione del nodo liberando spazio. Il nodo viene cancellato mantenendo le regole di costruizione dell'albero, perciò la posizione degli altri nodi potrebbe essere variata (alcune scelte sono date dal valore della variabile globale "lor").

void del_head() : vengono cancellati tutti i nodi seguendo il percorso del postorder traversal e ad ogni nodo incontrato questo viene cancellato con una funzione "cancella foglie" (più veloce delle precedenti). Questo può essere fatto perchè cancellando ogni nodo nel postorder, ogni fogli che si incontra sarà un foglia.

Node *find(Tree *tree, int key) viene cercato nell'albero il nodo con la chiave key usando la ricerca binaria. Se non esiste viene restituito NULL.

Data *get_data(Node *node) Viene restituito il puntatore ai dati del nodo.

Data *get_data_by_key(Tree *tree, int key) viene restituito il puntatore ai dati del nodo con chiave key.

void preorder_tr(Node *root, node_handler_t function) : Preorder Traversal con attivazione della funzione function ad ogni nodo nell'ordine specifico.

void postorder_tr(Node *root, node_handler_t function) : Postorder Traversal con attivazione della funzione function ad ogni nodo nell'ordine specifico.

void inorder_tr(Node *root, node_handler_t function) : Inorder Traversal con attivazione della funzione function ad ogni nodo nell'ordine specifico.

void print_node_key(const Node* node); : funzione da usare nei traversal, stampa la key di un nodo
