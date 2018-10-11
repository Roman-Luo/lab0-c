/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    /* Hint - 2-layer malloc */
    if (q!=NULL){
        q->head = NULL;
        return q;
    }
    else
        return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q!=NULL){
        list_ele_t *node = q->head;
        if (node!=NULL){
            list_ele_t *pre;
            /* free nodes through the leading of next pointer*/ 
            while (node->next!=NULL){
                node->value = NULL;
                pre = node;
                node = node->next;
                free(pre);
            }
            free(q);
            return;
        }
        else {
            free(q);
            return;
        }
    }
    else
        return;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    /* Don't forget to allocate space for the string and copy it */
    if (q!=NULL){
        list_ele_t *newh;
        newh = (list_ele_t *)malloc(sizeof(list_ele_t));
        if (newh != NULL){
            if (q->head !=NULL){
                newh->next = q->head;
                newh->value = strdup(s);
                q->head = newh;
                return true;
            }
            else {
                newh->next = NULL;
                newh->value = strdup(s);
                q->head = newh;
                return true;
            }
        }
    /* What if either call to malloc returns NULL? */
        else
            return false;
    }
    else
        return false;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if (q != NULL){
    /* Create a new tail element */
        list_ele_t *newt = (list_ele_t *)malloc(sizeof(list_ele_t));
        if (newt != NULL){
            newt->value = strdup(s);
            newt->next = NULL;
    /* Insert the newt to tail of queue */
    /* Hint: No chance to write a recursive fn here, iterative only */
            list_ele_t *oldt;  // old tail
            oldt = q->head;
            while (oldt->next != NULL) {
                oldt = oldt->next;
            }
            oldt->next = newt;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
/* Hint: *sp is a ready pointer somewhere in the memory */
/* Notice: the precedence of using free to remove the element */

bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q != NULL){
        if (q->head!=NULL){
    /* Copy string value from element to *sp */
            list_ele_t *oldele = q->head;
            const char *str = oldele->value;
    /* Remove element */
            q->head = oldele->next;
            free(oldele);
            if (str!=NULL){
                memcpy(sp, str, bufsize-1);//Jser's Ch Pointer
                *(sp + bufsize - 1)='\0';
//                sp = strndup(str,bufsize-1);
//                free(str); // error: free unallocated space?
            }
//            else
//                free(str);
    /* Remove element */
//            q->head = oldele->next;
//            free(oldele);
            
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q!=NULL){
        list_ele_t *node = q->head;
        int count = 0;
        if (node!=NULL){
            while (node->next != NULL)
            {
                count++;
                node = node->next;
            }
                return count+1;
        }
        else
            return count;
    }   
    else
        return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q != NULL){
        list_ele_t *node, *pre;
        node = q->head;
        if (node!=NULL){
            pre = q->head;
            while (node->next != NULL) {
                node = node->next;
                node->next = pre;
                pre = node;
            }
            q->head->next = NULL;
            q->head = node;
        }
    }
    else
        return;
}
