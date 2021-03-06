/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if(q == NULL)
	return NULL;
    /* What if malloc returned NULL? */
    q->head = q->rear = NULL;
    q->count = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements? */
    /* Free queue structure */
    if(q == NULL)
	return;
    while(q->head)
    {
	q->rear = q->head->next;
        free(q->head);
	q->head = q->rear;
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if(q == NULL)
	return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = (list_ele_t*)malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
    if(newh == NULL)
    {
	return false;
    }
    newh->value = v;
    newh->next = q->head;
    q->head = newh;
    if(q->rear == NULL)
	q->rear = q->head;
    q->count += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL)
        return false;
    list_ele_t *p = (list_ele_t*)malloc(sizeof(list_ele_t));
    if(p == NULL)
	return false;
    p->value = v;
    p->next = NULL;
    if(q->rear != NULL)
    {
	q->rear->next = p;
	q->rear = p;
    }
    else
    {
	q->head = p;
	q->rear = p;
    }
    q->count += 1;
    return true;

}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    /* You need to fix up this code. */
    if(q == NULL || q->head == NULL)
	return false;

    list_ele_t *old = q->head, *new = q->head->next;

    if(vp!=NULL)
    {
       *vp = old->value;
    }

    q->head = new;
    
    q->count -= 1;
    free(old);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q == NULL || q->head == NULL)
	return 0;

    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->count;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if(q==NULL || q->head == NULL)
	return;
    /* You need to write the code for this function */
    list_ele_t *oldhead = q->head, *oldrear = q->rear;

    list_ele_t *pre = q->head;
    list_ele_t *cur = pre->next;
    list_ele_t *next = NULL;
    q->rear = q->head;
    q->rear->next = NULL;
    while(cur != NULL)
    {
	next = cur->next;
	cur->next = pre;
	pre = cur;
	cur = next;
    }
    
    q->head = oldrear;
    q->rear = oldhead;
}

