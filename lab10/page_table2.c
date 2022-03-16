#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct n_virtual_page {
    int virtual_page;
    int last_access_time;
    int physical_page;
} n_virtual_page;

int least_used_recently(int n_virtual, struct n_virtual_page *ipt, int max_time);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    int time = 0;
    char line[10];
    int physical = atoi(argv[1]);
    int physical_counter = 0;
    int virtual = atoi(argv[2]);
    struct n_virtual_page *vir_page = malloc(virtual * sizeof *vir_page);
    for (int i = 0; i < virtual; i++) {
        vir_page[i].virtual_page = -1;
        vir_page[i].last_access_time = -1;
        vir_page[i].physical_page = -1;
    }

    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n", physical, virtual);
    while(fgets(line, 10, stdin)){
        char *temp = &line[2];
        int page = atoi(temp);
        char action = line[0];
        
        if(action == 'r'){
            if(vir_page[page].virtual_page == -1){
                printf("Time %d: virtual page %d  - read access - illegal\n", time, page);
                vir_page[page].last_access_time = time;
            }
            else{
                if(vir_page[page].physical_page != -1){
                    printf("Time %d: virtual page %d  - read access - at physical page %d\n", time, page, vir_page[page].physical_page);
                    vir_page[page].last_access_time = time;
                }
                else if(vir_page[page].physical_page == -1 && physical_counter != physical){
                    printf("Time %d: virtual page %d  - read access - loaded to physical page %d\n",time, page, physical_counter);
                    vir_page[page].physical_page = physical_counter;
                    physical_counter++;
                    vir_page[page].last_access_time = time;
                }
                else if(vir_page[page].physical_page == -1 && physical_counter == physical){
                    int temp1 = least_used_recently(virtual, vir_page, time);
                    printf("Time %d: virtual page %d  - read access - virtual page %d evicted - loaded to physical page %d\n", time, page, temp1, vir_page[temp1].physical_page);
                    vir_page[page].physical_page = vir_page[temp1].physical_page;
                    vir_page[temp1].physical_page = -1;
                    vir_page[page].last_access_time = time;
                }
            }
        }
        else if(action == 'w'){
            if(vir_page[page].virtual_page == -1 || vir_page[page].virtual_page == 0){
                printf("Time %d: virtual page %d  - write access - illegal\n", time, page);
                vir_page[page].last_access_time = time;
            }
            else{
                if(vir_page[page].physical_page != -1){
                    printf("Time %d: virtual page %d  - write access - at physical page %d\n", time, page, vir_page[page].physical_page);
                    vir_page[page].last_access_time = time;
                }
                else if(vir_page[page].physical_page == -1 && physical_counter != physical){
                    printf("Time %d: virtual page %d  - write access - loaded to physical page %d\n",time, page, physical_counter);
                    vir_page[page].physical_page = physical_counter;
                    physical_counter++;
                    vir_page[page].last_access_time = time;
                }
                else if(vir_page[page].physical_page == -1 && physical_counter == physical){
                    int temp1 = least_used_recently(virtual, vir_page, time);
                    printf("Time %d: virtual page %d  - write access - virtual page %d evicted - loaded to physical page %d\n", time, page, temp1, vir_page[temp1].physical_page);
                    vir_page[page].physical_page = vir_page[temp1].physical_page;
                    vir_page[temp1].physical_page = -1;
                    vir_page[page].last_access_time = time;
                }
            }
        }
        else if(action == 'W'){
            printf("Time %d: virtual page %d mapped read-write\n", time, page);
            if(vir_page[page].virtual_page == -1){
                vir_page[page].last_access_time = time;
                vir_page[page].virtual_page += 2;
            }
            else if(vir_page[page].virtual_page == 0){
                vir_page[page].last_access_time = time;
                vir_page[page].virtual_page += 1;
            }
            else if(vir_page[page].virtual_page == 1){
                vir_page[page].last_access_time = time;
            }
        }
        else if(action == 'R'){
            printf("Time %d: virtual page %d mapped read-only\n", time, page);
            if(vir_page[page].virtual_page == -1){
                vir_page[page].last_access_time = time;
                vir_page[page].virtual_page += 1;
            }
            else if(vir_page[page].virtual_page == 0){
                vir_page[page].last_access_time = time;
            }
            else if(vir_page[page].virtual_page == 1){
                vir_page[page].last_access_time = time;
            }
        }   
        else if(action == 'U'){
            if(vir_page[page].physical_page == -1){
                printf("Time %d: virtual page %d unmapped\n", time, page);
                vir_page[page].last_access_time = time;
                vir_page[page].virtual_page = -1;
            }
            else{
                printf("Time %d: virtual page %d unmapped - physical page %d now free\n", time, page, vir_page[page].physical_page);
                vir_page[page].last_access_time = time;
                vir_page[page].physical_page = -1;
                vir_page[page].virtual_page = -1;
            }
        }
        time++;
    }
    return 0;
}

int least_used_recently(int n_virtual, struct n_virtual_page *ipt, int max_time){
    int time = max_time;
    int physical = 0;
    int i = 0;
    while(i < n_virtual) {
        if(ipt[i].last_access_time < time && ipt[i].last_access_time != -1 && ipt[i].physical_page != -1) {
            time = ipt[i].last_access_time;
            physical = i;
        }
        i++;
    }

    return physical;
}