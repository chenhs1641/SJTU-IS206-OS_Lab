#include<stdio.h>
#include<stdlib.h>
#define SIZE 1024

struct map{
    unsigned m_size;
    char *m_addr;
    struct map *next, *prior;
}*ptr;
char *begin_addr, *end_addr;

void linit() {
    ptr = malloc(sizeof(ptr));
    ptr->m_size = SIZE;
    ptr->m_addr = malloc(SIZE);
    ptr->prior = ptr;
    ptr->next = ptr;
    begin_addr = ptr->m_addr;
    end_addr = ptr->m_addr + ptr->m_size;
    printf("Memory init succeed!\n");
    printf("The begin address of the memory is %u.\n", begin_addr);
    printf("The end address of the memory is %u.\n", end_addr);
}

char *lmalloc(unsigned size) {
    if (size == 0) {
        printf("Error! No memory need to alloc!\n");
        return NULL;
    }
    if (!ptr) {
        printf("Error! Memory not enough!\n");
        return NULL;
    }
    struct map *begin = ptr;
    do {
        if (ptr->m_size >= size) {
            char *a = ptr->m_addr;
            ptr->m_size -= size;
            ptr->m_addr += size;
            if (ptr->m_size == 0) {
                struct map *del = ptr;
                if (ptr->next == ptr)
                    ptr = NULL;
                else {
                    ptr->prior->next = ptr->next;
                    ptr->next->prior = ptr->prior;
                    ptr = ptr->next;
                }
                free(del);
            }
            return a;
        }
        ptr = ptr->next;
    } while (ptr != begin);
    printf("Error! Memory not enough!\n");
    return NULL;
}

void lfree(unsigned size, char *addr) {
    if (addr < begin_addr || addr + size > end_addr) {
        printf("Error! No such address!\n");
        return;
    }
    while (1) {
        if (!ptr) {
            ptr = malloc(sizeof(ptr));
            ptr->m_size = size;
            ptr->m_addr = addr;
            ptr->prior = ptr;
            ptr->next = ptr;
            return;
        }
        else if (ptr->next->m_addr <= ptr->m_addr) {                //下一块空闲区又从头开始
            if (ptr->m_addr <= addr) {                              //释放位于最后空闲块以后的占用内存其中一块
                if (ptr->m_addr + ptr->m_size >= addr) {            //刚好连在一起
                    if (ptr->m_addr + ptr->m_size < addr + size) {
                        ptr->m_size = addr - ptr->m_addr + size;
                    }
                    return;
                }
                else {                                              //新增一块空闲区
                    struct map *new = malloc(sizeof(new));
                    new->m_size = size;
                    new->m_addr = addr;
                    new->prior = ptr;
                    new->next = ptr->next;
                    ptr->next->prior = new;
                    ptr->next = new;
                    ptr = new;
                    return;
                }
            }
            else if (ptr->next->m_addr > addr) {                    //释放位于最前空闲块以前的占用内存其中一块
                if (ptr->next->m_addr > addr + size) {              //新增一块空闲区
                    struct map *new = malloc(sizeof(new));
                    new->m_size = size;
                    new->m_addr = addr;
                    new->prior = ptr;
                    new->next = ptr->next;
                    ptr->next->prior = new;
                    ptr->next = new;
                    ptr = new;
                    return;
                }
                else {                                              //刚好连在一起
                    ptr->next->m_size = ptr->next->m_addr - addr + ptr->next->m_size;
                    ptr->next->m_addr = addr;
                    ptr = ptr->next;
                    while (ptr->next->m_addr <= addr + size) {      //如果一连释放了很多块
                        if (ptr->next->m_addr <= ptr->m_addr) {     //如果再下一块又从头开始
                            if (ptr->m_addr + ptr->m_size < addr + size) {
                                ptr->m_size = addr - ptr->m_addr + size;
                            }
                            break;
                        }
                        ptr->m_size = ptr->next->m_addr - ptr->m_addr + ptr->next->m_size;
                        struct map *del = ptr->next;
                        ptr->next->next->prior = ptr;
                        ptr->next = ptr->next->next;
                        free(del);
                    }
                    return;
                }
            }
            else ptr = ptr->next;
        }
        else {                                                      //下一块空闲区正常往后
            if (ptr->m_addr <= addr && ptr->next->m_addr > addr) {
                if (ptr->m_addr + ptr->m_size >= addr) {
                    if (ptr->next->m_addr > addr + size) {          //当前块连，下一块断开
                        if (ptr->m_addr + ptr->m_size < addr + size) {
                            ptr->m_size = addr - ptr->m_addr + size;
                        }
                        return;
                    }
                    else {                                          //当前块和后面的块都连在一起
                        while (ptr->next->m_addr <= addr + size) {  //如果一连释放了很多块
                            if (ptr->next->m_addr <= ptr->m_addr) { //如果再下一块又从头开始
                                if (ptr->m_addr + ptr->m_size < addr + size) {
                                    ptr->m_size = addr - ptr->m_addr + size;
                                }
                                break;
                            }
                            ptr->m_size = ptr->next->m_addr - ptr->m_addr + ptr->next->m_size;
                            struct map *del = ptr->next;
                            ptr->next->next->prior = ptr;
                            ptr->next = ptr->next->next;
                            free(del);
                        }
                        return;
                    }
                }
                else if (ptr->m_addr + ptr->m_size < addr) {
                    if (ptr->next->m_addr > addr + size) {          //不和前后相连，新建一块空闲区
                        struct map *new = malloc(sizeof(new));
                        new->m_size = size;
                        new->m_addr = addr;
                        new->prior = ptr;
                        new->next = ptr->next;
                        ptr->next->prior = new;
                        ptr->next = new;
                        ptr = new;
                        return;
                    }
                    else {                                          //只和后面的块连在一起
                        ptr->next->m_size = ptr->next->m_addr - addr + ptr->next->m_size;
                        ptr->next->m_addr = addr;
                        ptr = ptr->next;
                        while (ptr->next->m_addr <= addr + size) {  //如果一连释放了很多块
                            if (ptr->next->m_addr <= ptr->m_addr) { //如果再下一块又从头开始
                                if (ptr->m_addr + ptr->m_size < addr + size) {
                                    ptr->m_size = addr - ptr->m_addr + size;
                                }
                                break;
                            }
                            ptr->m_size = ptr->next->m_addr - ptr->m_addr + ptr->next->m_size;
                            struct map *del = ptr->next;
                            ptr->next->next->prior = ptr;
                            ptr->next = ptr->next->next;
                            free(del);
                        }
                        return;
                    }
                }
            }
            else ptr = ptr->next;
        }
    }
}

void lprint() {
    if (!ptr) {
        printf("Now there is no free memory.\n");
        return;
    }
    struct map *begin = ptr;
    printf("Now the free momory blocks are:\n");
    do {
        printf("Address:%u, Size:%u\n", ptr->m_addr, ptr->m_size);
        ptr = ptr->next;
    } while (ptr != begin);
}

int main() {
    linit();
    char c, *ans, *addr;
    unsigned size;
    while (1) {
        do {
            c = getchar();
        } while (c == '\n' || c == '\t' || c == '\r' || c == ' ');
        if (c == 'm') {
            scanf("%u", &size);
            ans = lmalloc(size);
            if (ans) printf("%u\n", ans);
            lprint();
        }
        else if (c == 'f') {
            scanf("%u%u", &size, &addr);
            lfree(size, addr);
            lprint();
        }
        else if (c == 'q') {
            printf("Program succefully run.\n");
            break;
        }
        else {
            printf("Error! Wrong instrument!\n");
        }
    }
}
