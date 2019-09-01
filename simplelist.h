/*
 * Author: alcubierre-drive
 * Original source: http://github.com/alcubierre-drive/libsimplelist
 * License: GNU GENERAL PUBLIC LICENSE -- Version 3
 */

#ifndef LIBSIMPLELIST_H
#define LIBSIMPLELIST_H

#ifdef __cplusplus
extern "C" {
#endif

struct slist_node;

struct slist_node {
    struct slist_node* next;
    struct slist_node* prev;
    void* content;
    size_t content_size;
};

typedef struct slist_node slist_node;

slist_node* slist_init( void* content, size_t content_size );
slist_node* slist_append( slist_node* HEAD_END, void* content, size_t content_size );
slist_node* slist_prepend( slist_node* HEAD_BEGIN, void* content, size_t content_size );
slist_node* slist_insert_after( slist_node* POSITION, void* content, size_t content_size );
slist_node* slist_insert_before( slist_node* POSITION, void* content, size_t content_size );
void slist_destroy( slist_node* HEAD_BEGIN, slist_node* HEAD_END );
void slist_access_forward( slist_node* HEAD, int count, void** content, size_t* content_size );
void slist_access_backward( slist_node* HEAD, int count, void** content, size_t* content_size );

#ifdef __cplusplus
}
#endif

#endif // LIBSIMPLELIST_H

/*
#include "simplelist.h"

int main() {
    int x = 1;
    slist_node* HEAD_BEGIN = slist_init(&x,sizeof(int));
    slist_node* HEAD = HEAD_BEGIN;
    for (int i=0; i<10; ++i) {
        int y = rand();
        HEAD = slist_append(HEAD,&y,sizeof(int));
        // and here is is the mighty segfault for y...
    }
    void* data; size_t count;
    slist_access_forward( HEAD_BEGIN, 5, &data, &count );
    slist_destroy( NULL, HEAD );
}
*/
