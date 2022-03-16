// Simulate LRU replacement of page frames

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// represent an entry in a simple inverted page table

typedef struct ipt_entry {
    int virtual_page;        // == -1 if physical page free
    int last_access_time;
} ipt_entry_t;

void lru(int n_physical_pages, int n_virtual_pages);
void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt);
int least_used_recently(int n_physical_pages, struct ipt_entry *ipt);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    lru(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


void lru(int n_physical_pages, int n_virtual_pages) {
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
          n_physical_pages, n_virtual_pages);
    struct ipt_entry *ipt = malloc(n_physical_pages * sizeof *ipt);
    assert(ipt);

    for (int i = 0; i < n_physical_pages; i++) {
        ipt[i].virtual_page = -1;
        ipt[i].last_access_time = -1;
    }

    int virtual_page;
    for (int access_time = 0; scanf("%d", &virtual_page) == 1; access_time++) {
        assert(virtual_page >= 0 && virtual_page < n_virtual_pages);
        access_page(virtual_page, access_time, n_physical_pages, ipt);
    }
}

void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt) {
    int accessed = 0;
    int i = 0;
    while(i < n_physical_pages) {
        if (ipt[i].virtual_page == virtual_page) {
            ipt[i].last_access_time = access_time;
            printf("Time %d: virtual page %d -> physical page %d\n", access_time, virtual_page, i);
            accessed = 1;
            break;
        } 
        else if(ipt[i].virtual_page == -1) {
            ipt[i].virtual_page = virtual_page;
            ipt[i].last_access_time = access_time;
            printf("Time %d: virtual page %d loaded to physical page %d\n", access_time, virtual_page, i);
            accessed = 1;
            break;
        }
        i++;
    }
    if(accessed == 0) {
        int evicted_physical_page = least_used_recently(n_physical_pages, ipt);
        int old_virtual_page = ipt[evicted_physical_page].virtual_page;
        ipt[evicted_physical_page].virtual_page = virtual_page;
        ipt[evicted_physical_page].last_access_time = access_time;
        printf("Time %d: virtual page %d  - virtual page %d evicted - loaded to physical page %d\n", access_time, virtual_page, old_virtual_page, evicted_physical_page);
        accessed = 1;
    }
}

int least_used_recently(int n_physical_pages, struct ipt_entry *ipt) {
    int time = ipt[0].last_access_time;
    int physical = 0;
    int i = 1;
    while(i < n_physical_pages) {
        if(ipt[i].last_access_time < time) {
            time = ipt[i].last_access_time;
            physical = i;
        }
        i++;
    }

    return physical;
}