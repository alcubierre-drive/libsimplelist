#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "simplelist.h"

/* LICENSE: SEE HEADER */

static void slist_assign( slist_node* element, void* content, size_t content_size ) {
    element->content = malloc(sizeof(content_size));
    element->content_size = content_size;
    memcpy(element->content,content,content_size);
}

static void slist_free( slist_node* element ) {
    free(element->content);
    element->content = NULL;
    element->content_size = 0;
}

slist_node* slist_init( void* content, size_t content_size ) {
    slist_node* result = malloc(sizeof(slist_node));
    slist_assign(result,content,content_size);
    result->prev = NULL;
    result->next = NULL;
    return result;
}

slist_node* slist_append( slist_node* HEAD_END, void* content, size_t content_size ) {
    slist_node* element = slist_init(content,content_size);
    HEAD_END->next = element;
    element->prev = HEAD_END;
    element->next = NULL;
    return element;
}

slist_node* slist_prepend( slist_node* HEAD_BEGIN, void* content, size_t content_size ) {
    slist_node* element = slist_init(content,content_size);
    HEAD_BEGIN->prev = element;
    element->next = HEAD_BEGIN;
    element->prev = NULL;
    return element;
}

slist_node* slist_insert_after( slist_node* POSITION, void* content, size_t content_size ) {
    slist_node* element = slist_init(content,content_size);
    element->next = POSITION->next;
    element->prev = POSITION;
    POSITION->next = element;
    return element;
}

slist_node* slist_insert_before( slist_node* POSITION, void* content, size_t content_size ) {
    slist_node* element = slist_init(content,content_size);
    element->prev = POSITION->prev;
    element->next = POSITION;
    POSITION->prev = element;
    return element;
}

void slist_destroy( slist_node* HEAD_BEGIN, slist_node* HEAD_END ) {
    assert((HEAD_BEGIN == NULL) ^ (HEAD_END == NULL));
    if (HEAD_END != NULL) {
        // backward
        while (HEAD_END != NULL) {
            slist_node* prev = HEAD_END->prev;
            slist_free(HEAD_END);
            free(HEAD_END);
            HEAD_END = prev;
        }
    }
    if (HEAD_BEGIN != NULL) {
        // forward
        while (HEAD_BEGIN!= NULL) {
            slist_node* next = HEAD_BEGIN->next;
            slist_free(HEAD_BEGIN);
            free(HEAD_BEGIN);
            HEAD_BEGIN = next;
        }
    }
}

void slist_access_forward( slist_node* HEAD, int count, void** content, size_t* content_size ) {
    for (int i=0; i<count; ++i) {
        HEAD = HEAD->next;
    }
    *content = HEAD->content;
    *content_size = HEAD->content_size;
}

void slist_access_backward( slist_node* HEAD, int count, void** content, size_t* content_size ) {
    for (int i=0; i<count; ++i) {
        HEAD = HEAD->prev;
    }
    *content = HEAD->content;
    *content_size = HEAD->content_size;
}
