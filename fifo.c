#include <stdio.h>

int main() {
    int frames, pages;

    printf("Enter the number of pages: ");
    scanf("%d", &pages);

    int arr[pages];

    printf("Enter the page reference string: ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    int Frames[frames];
    for (int i = 0; i < frames; i++) {
        Frames[i] = -1;
    }

    int pointer = 0;
    int faults = 0;

    for (int i = 0; i < pages; i++) {
        int page = arr[i];
        int found = 0;

        // Check if page is already present (hit)
        for (int j = 0; j < frames; j++) {
            if (Frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            Frames[pointer] = page;
            pointer = (pointer + 1) % frames;
            faults++;

            printf("Page %d caused a page fault.\nFrames: ", page);
            for (int k = 0; k < frames; k++) {
                if (Frames[k] != -1)
                    printf("%d ", Frames[k]);
                else
                    printf("- ");
            }
            printf("\n");
        } else {
            printf("Page %d hit. Frames unchanged.\n", page);
        }
    }

    int hits = pages - faults;
    float hit_ratio = (float)hits / pages;
    float miss_ratio = (float)faults / pages;

    printf("\nTotal Page Faults = %d", faults);
    printf("\nTotal Page Hits = %d", hits);
    printf("\nHit Ratio = %.2f", hit_ratio);
    printf("\nMiss Ratio = %.2f\n", miss_ratio);

    return 0;
}


