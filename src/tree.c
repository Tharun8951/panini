#include "tree.h"
Node* root; 

Node* init_root(){
    Node *root = (Node*)malloc(sizeof(Node));
    (*root).tag = (TagRoot | TagNode);
    (*root).up = (Tree*)&root;
    (*root).left = 0;
    (*root).right = 0;
    strncpy((char*)(*root).path, "/", sizeof((*root).path)-1);
    (*root).path[sizeof((*root).path) - 1] = '\0';

    return root;
}

Node* create_node(Node* parent, int8 *path){
    Node *n;
    int16 n_size;
    assert(parent);

    n_size = sizeof(Node);
    n = (Node*)malloc((int)n_size);
    memset(n, 0, n_size);
    (*parent).left = n;

    (*n).tag = TagNode;
    (*n).up = (Tree*)parent;
    strncpy((char*)(*n).path, (char*)path, sizeof((*n).path));
    (*n).path[sizeof((*n).path) - 1] = '\0';
    return n;
}

Leaf* find_last_linear(Node* parent){
    Leaf* l;
    errno = NoError;
    assert(parent);

    if(!(*parent).right) reterr(NoError);

    for(l = (*parent).right; (*l).right; l = (*l).right)
    assert(l);
    return l;
}

Leaf* create_leaf(Node* parent, int8 *key, int8 *value, int16 count){
    Leaf *l, *new;
    int16 size;

    assert(parent);
    l = find_last_linear(parent);
    size = sizeof(Leaf);
    new = (Leaf*)malloc(size);
    assert(new);

    if(!l) (*parent).right = new;
    else (*l).right = new;

    memset(new, 0, size);

    strncpy((char*)(*new).key, (char*)key, sizeof((*new).key));
    (*new).key[sizeof((*new).key)-1] = '\0';
    (*new).tag = TagLeaf;
    (*new).left = (!l) ? (Tree*)parent : (Tree*)l;
    (*new).value = (int8*)malloc(count);
    assert((*new).value);
    strncpy((char*)(*new).value, (char*)value, count);
    (*new).size = count;
    return new;
}

int main(){
    root = init_root();
    printf("The address of root is: %p\n", (void*)root);

    Node* second = create_node((Node*)root, (int8*)"/Users");
    printf("The address of second is: %p\n", (void*)second);

    Node* third = create_node((Node*)second, (int8*)"/Users/tharun");
    printf("The address of third is: %p\n", (void*)third);

    Leaf *l1, *l2;
    int8 *key, *value1, *value2;
    int16 size1, size2;

    key = (int8*)"Tharun";
    value1 = (int8*)"My name is tharun and i love programming in c";
    value2 = (int8*)"Im building a custom redis database";
    size1 = (int16)strlen((char*)value1);
    size2 = (int16)strlen((char*)value2);
    l1 = create_leaf(third, key, value1, size1);
    assert(l1);
    l2 = create_leaf(third, key, value2, size2);

    printf("%p\t%p\n", (void*)l1, (void*)l2);
    printf("%s\t%s\n%s\t%s\n", (*l1).key, (*l1).value, (*l2).key, (*l2).value);
    free(second);
    free(root);
    free(l1);
    return 0;
}