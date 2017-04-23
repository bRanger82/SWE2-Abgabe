
struct SList
{
    void * Data;
    struct SList *Next;
    struct SList *Prev;
}; typedef struct SList SLIST;

struct SList_Header
{
    int Len;
    SLIST *First, *Last;
}; typedef struct SList_Header SLIST_HEADER;

extern SLIST_HEADER *createSList(void);
extern SLIST *insertFirst(SLIST_HEADER*,void *);
extern SLIST *insertLast(SLIST_HEADER*,void*);
extern void *deleteFirst(SLIST_HEADER*);
extern void *deleteLast(SLIST_HEADER*);
extern void pr_SList(SLIST_HEADER*);
extern void rm_SList(SLIST_HEADER*);
extern void *get_entrySList(SLIST_HEADER*,int);
