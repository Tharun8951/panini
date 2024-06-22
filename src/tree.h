#ifndef TREE_H_
#define TREE_H_
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#define TagRoot     1   /* 00 01 */
#define TagNode     2   /* 00 10 */
#define TagLeaf     4   /* 01 00 */

typedef void* Nullptr;
Nullptr nullptr = 0;

#define NoError 0
#define find_last(x)   find_last_linear(x)
#define reterr(x)  \
    do { \
        errno = (x); \
        return nullptr; \
    } while (0)
    


typedef unsigned int int32;
typedef unsigned short int16;
typedef unsigned char int8;
typedef unsigned char Tag;

typedef union u_tree Tree;
typedef struct s_node Node;
typedef struct s_leaf Leaf;

struct s_node{
    Tag tag;
    Tree *up;
    Node *left;
    Leaf *right;
    int8 path[256];
};

struct s_leaf{
    Tag tag;
    Tree *left;
    Leaf *right;
    int8 key[128];
    int8 *value;
    int16 size;
};

union u_tree{
    Node n;
    Leaf l;
};

#endif
