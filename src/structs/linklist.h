#ifndef __HLIB_STRUCTS_LINKLIST
#define __HLIB_STRUCTS_LINKLIST

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../helpers/calloc.h"
#include "../symbols.h"
#include "bool.h"

struct LinkList
{
  void *value;
  struct LinkList *next;
};

struct LinkList *LinkListUnshift(struct LinkList *head, ...)
{
  void *value;
  va_list argv;
  struct LinkList *curr;
  struct LinkList *prev;
  struct LinkList *new_head = HLIB_CALLOC(struct LinkList);

  va_start(argv, head);
  for (prev = new_head; (value = va_arg(argv, void *)) != ENDARG; prev = curr)
  {
    prev->next = curr = HLIB_CALLOC(struct LinkList);
    curr->value = value, curr->next = NULL;
  }
  va_end(argv);

  prev->next = head;
  head = new_head->next;
  free(new_head);

  return head;
}

void LinkListFree(struct LinkList **head)
{
  if (head == NULL || *head == NULL)
    return;

  struct LinkList *next;
  struct LinkList *curr = *head;
  while (curr != NULL)
  {
    next = curr->next;
    free(curr);
    curr = next;
  }

  *head = NULL;
}

void LinkListFreeN(struct LinkList **head, ...)
{
  va_list argv;
  LinkListFree(head);
  va_start(argv, head);
  while ((head = va_arg(argv, struct LinkList **)) != ENDARG)
    LinkListFree(head);
  va_end(argv);
}

void LinkListFreeEach(
    struct LinkList **head, void (*callback)(void *value, int index, struct LinkList *curr))
{
  if (head == NULL || *head == NULL)
    return;

  struct LinkList *next;
  struct LinkList *curr = *head;

  for (int index = 0; curr != NULL; index++)
  {
    next = curr->next;
    callback(curr->value, index, curr);
    free(curr);
    curr = next;
  }

  *head = NULL;
}

void LinkListFreeValue(struct LinkList **head)
{
  if (head == NULL || *head == NULL)
    return;

  struct LinkList *next;
  struct LinkList *curr = *head;
  while (curr != NULL)
  {
    next = curr->next;
    if (curr->value != NULL)
      free(curr->value);
    free(curr);
    curr = next;
  }

  *head = NULL;
}

struct LinkList *LinkListPush(struct LinkList *head, ...)
{
  va_list argv;
  va_start(argv, head);

  struct LinkList *curr = head;
  void *value = va_arg(argv, void *);

  if (value == ENDARG)
    return head;

  if (head == NULL)
    curr = head = HLIB_CALLOC(struct LinkList);
  else
  {
    while (curr->next != NULL)
      curr = curr->next;
    curr = curr->next = HLIB_CALLOC(struct LinkList);
  }

  for (curr->value = value, curr->next = NULL; (value = va_arg(argv, void *)) != ENDARG;)
  {
    curr = curr->next = HLIB_CALLOC(struct LinkList);
    curr->value = value, curr->next = NULL;
  }
  va_end(argv);

  return head;
}

int LinkListLength(struct LinkList *head)
{
  int length = 0;
  for (; head != NULL; length++)
    head = head->next;
  return length;
}

struct LinkList *LinkListSlice(struct LinkList *head, int start, int end)
{
  struct LinkList *curr;
  struct LinkList *new_head = NULL;

  if (start < 0 && end < 0 && start >= end)
    return new_head;

  if (start < 0 || end < 0)
  {
    int length = LinkListLength(head);
    start += start < 0 ? length : 0, end += end < 0 ? length : 0;
    start = start < 0 ? 0 : start, end = end < 0 ? 0 : end;
  }

  if (start >= end)
    return new_head;

  int count = end - start;

  while (start-- && head != NULL)
    head = head->next;

  for (curr = new_head = HLIB_CALLOC(struct LinkList); head != NULL && count--; head = head->next)
    (curr = curr->next = HLIB_CALLOC(struct LinkList))->value = head->value;

  head = new_head->next;
  free(new_head);

  return head;
}

struct LinkList *LinkListLocate(struct LinkList *head, int index)
{
  if (index < 0)
    return NULL;

  while (head != NULL && index--)
    head = head->next;

  return head;
}

void *LinkListGetter(struct LinkList *head, int index)
{
  head = LinkListLocate(head, index);
  return head == NULL ? NULL : head->value;
}

struct LinkList *LinkListCopyHead(struct LinkList *head)
{
  struct LinkList *new_head = HLIB_CALLOC(struct LinkList);
  *new_head = *head;
  return new_head;
}

struct LinkList *LinkListConcat(struct LinkList *head, ...)
{
  va_list argv;
  struct LinkList *curr = head;
  struct LinkList *new_head = head;

  va_start(argv, head);
  while (new_head == NULL && (curr = va_arg(argv, struct LinkList *)) != ENDARG)
    new_head = curr;

  if (new_head == NULL)
    return new_head;

  for (curr = new_head = LinkListCopyHead(curr); true;)
  {
    for (head = curr->next; head != NULL; head = head->next)
      (curr = curr->next = HLIB_CALLOC(struct LinkList))->value = head->value;

    head = va_arg(argv, struct LinkList *);
    if (head == ENDARG)
      break;
    if (head == NULL)
      continue;
    curr = curr->next = LinkListCopyHead(head);
  }
  va_end(argv);

  return new_head;
}

struct LinkList *LinkListFind(
    struct LinkList *head, bool (*find)(void *value, int index, struct LinkList *head))
{
  struct LinkList *curr = head;

  for (int index = 0; curr != NULL; index++, curr = curr->next)
    if (find(curr->value, index, head))
      return curr;

  return NULL;
}

bool LinkListSome(
    struct LinkList *head, bool (*find)(void *value, int index, struct LinkList *head))
{
  struct LinkList *curr = head;

  for (int index = 0; curr != NULL; index++, curr = curr->next)
    if (find(curr->value, index, head))
      return true;

  return false;
}

struct LinkList *LinkListMap(
    struct LinkList *head, void *(*mapping)(void *value, int index, struct LinkList *head))
{
  if (head == NULL)
    return NULL;

  struct LinkList *curr_new = HLIB_CALLOC(struct LinkList);
  struct LinkList *curr_old = head;
  struct LinkList *new_head = curr_new;

  for (int index = 0; true; index++)
  {
    curr_new->value = mapping(curr_old->value, index, head);
    if ((curr_old = curr_old->next) == NULL)
      break;
    curr_new = curr_new->next = HLIB_CALLOC(struct LinkList);
  }

  return new_head;
}

void LinkListForeach(
    struct LinkList *head, void (*callback)(void *value, int index, struct LinkList *head))
{
  struct LinkList *curr = head;

  for (int index = 0; curr != NULL; index++, curr = curr->next)
    callback(curr->value, index, head);
}

void *LinkListReduce(
    struct LinkList *head,
    void *(*callback)(void *memo, void *value, int index, struct LinkList *head),
    void *memo)
{
  struct LinkList *curr = head;

  for (int index = 0; curr != NULL; index++, curr = curr->next)
    memo = callback(memo, curr->value, index, head);

  return memo;
}

#endif /* __HLIB_STRUCTS_LINKLIST */
