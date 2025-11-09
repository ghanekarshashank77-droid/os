#include <stdio.h>

#define MAX 10

int main()
{
    int frames[MAX];
    int pages[100], n, fcount;
    int i, j, k, faults = 0;
    
    printf("Enter the number of pages: \n");
    scanf("%d", &n);
    
    printf("Enter the page reference string: \n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter the number of frames: \n");
    scanf("%d", &fcount);
    
    for(i = 0; i < fcount; i++)
    {
        frames[i] = -1;
    }
    
    int RU[fcount];
    for(i = 0; i < fcount; i++) {
        RU[i] = -1;
    }
    
    for(i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;
        
        for(j = 0; j < fcount; j++)
        {
            if(frames[j] == page)
            {
                found = 1;
                RU[j] = i;
                break;
            }
        }
        
        if(!found)
        {
            faults++;
            int index = 0;
            int min_time = RU[0];
            
            for(k = 1; k < fcount; k++)
            {
                if(RU[k] < min_time)
                {
                    min_time = RU[k];
                    index = k;
                }
            }
            
            frames[index] = page;
            RU[index] = i;
        }
        
        printf("Frames after accessing page %d: ", page);
        for(j = 0; j < fcount; j++) {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    
    printf("Total Page Faults: %d\n", faults);
    
    return 0;
}

