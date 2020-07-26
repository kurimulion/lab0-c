#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if(q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    /* Iteratively remove the head of the queue */
    while(q_remove_head(q, NULL, 0));
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if(newh && q) {
        newh->value = malloc(sizeof(*s));
        if(!newh->value) {
            return false;
        }
        strcpy(newh->value, s);
    }
    else {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if(q->size == 0) {
        q->tail = newh;
    }
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *tail = q->tail;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if(newt && q) {
        newt->value = malloc(sizeof(*s));
        if(!newt->value) {
            return false;
        }
        strcpy(newt->value, s);
        newt->next = NULL;
    }
    else {
        return false;
    }
    tail->next = newt;
    q->tail = newt;
    if(q->size == 0) {
        q->head = newt;
    }
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if(q && q->size != 0) {
        list_ele_t *oldh = q->head;
        q->head = q->head->next;
        q->size--;
        if(sp){
            strncpy(sp, oldh->value, bufsize - 1);
            sp[bufsize] = '\0';
        }
        free(oldh->value);
        free(oldh);
        return true;
    }
    else {
        return false;
    }
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if(q) {
        if(q->size == 0 || q->size == 1) {
            /* Return if queue is empty or size is 1 */
            return;
        }
        list_ele_t *prev = q->head, *curr = q->head->next, *next;
        q->tail = q->head;
        prev->next = NULL;
        while(curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        q->head = prev;
    }
    else {
        /* Return if queue is null */
        return;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if(q) {
        if(q->size == 0 || q->size == 1) {
            /* Return if queue is empty or size is 1 */
            return;
        }
        list_ele_t *curr = q->head, *next, *big;
        big = curr;
        /* The easiest sorting algorithm of all time: bubble sort */
        for(int i = 0; i < q->size; ++i) {
            for(int j = 0; j < q->size; ++j) {
                next = curr->next;
                /* Swap two nodes if current node is greater */
                if(strnatcasecmp(curr, next) > 0) {
                    curr->next = next->next;
                    next->next = curr;
                    if(j == 0) {
                        /* Change head if first pair gets swapped */
                        q->head = next;
                    }
                }
                /* No swap just move on if current node is lesser */
                else {
                    curr = next;
                }
            }
            if(i == 0) {
                q->tail = curr; 
            }
        }
    }
    else {
        /* Return if queue is null */
        return;
    }
}
