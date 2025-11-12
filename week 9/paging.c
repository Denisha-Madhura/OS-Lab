#include <stdio.h>
#include <stdlib.h>

int main() {
    int physical_mem_size, logical_mem_size, frame_size, page_size;
    printf("Enter physical memory size (KB): ");
    scanf("%d", &physical_mem_size);
    printf("Enter frame size (KB): ");
    scanf("%d", &frame_size);
    printf("Enter logical memory size (KB): ");
    scanf("%d", &logical_mem_size);
    printf("Enter page size (KB): ");
    scanf("%d", &page_size);

    int num_frames = (physical_mem_size * 1024) / (frame_size * 1024);
    int num_pages = (logical_mem_size * 1024) / (page_size * 1024);

    printf("Number of frames in physical memory: %d\n", num_frames);
    printf("Number of pages in logical memory: %d\n", num_pages);

    int *page_table = malloc(num_pages * sizeof(int));
    printf("Enter page table (frame number for each page):\n");
    for (int i = 0; i < num_pages; i++) {
        printf("Page %d -> Frame #: ", i);
        scanf("%d", &page_table[i]);
        if (page_table[i] >= num_frames || page_table[i] < 0) {
            printf("Invalid frame number. Must be between 0 and %d\n", num_frames - 1);
            i--;
        }
    }

    int logical_addresses[] = {25, 46, 62, 10, 68};
    int num_addresses = sizeof(logical_addresses) / sizeof(logical_addresses[0]);
    int offset_bits = 0;
    int temp = page_size * 1024;
    while (temp > 1) {
        temp >>= 1;
        offset_bits++;
    }
    int offset_mask = (1 << offset_bits) - 1;

    printf("\nMapping logical addresses to physical addresses:\n");
    for (int i = 0; i < num_addresses; i++) {
        int logical_address = logical_addresses[i] * 1024;  // convert KB to bytes for address
        int page_number = logical_address >> offset_bits;
        int offset = logical_address & offset_mask;
        if (page_number >= num_pages) {
            printf("Logical address %dKB -> invalid (page number out of range)\n", logical_addresses[i]);
            continue;
        }
        int frame_number = page_table[page_number];
        int physical_address = (frame_number << offset_bits) | offset;
        printf("Logical address %dKB -> Physical address %d bytes\n", logical_addresses[i], physical_address);
    }

    free(page_table);
    return 0;
}

