//page replacement

#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int frames[MAX_FRAMES];  // Array representing frames
int pageRequests[MAX_PAGES];  // Array representing page requests
int pageFaults = 0;  // Counter for page faults
int front = 0;  // Front of the queue (oldest page)
int rear = 0;  // Rear of the queue (newest page)
int count = 0;  // Number of pages currently in frames

// Function to initialize frames to -1 (indicating empty)
void initializeFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }
}

// Function to check if a page is present in the frames
int isPagePresent(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

// Function to display frames
void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d ", frames[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

// Function to simulate page replacement using FIFO algorithm
void pageReplacementFIFO(int n) {
    initializeFrames();

    for (int i = 0; i < n; i++) {
        printf("Page request #%d: ", i + 1);
        scanf("%d", &pageRequests[i]);

        if (!isPagePresent(pageRequests[i])) {
            // Page fault occurs
            pageFaults++;

            // If frames are full, replace the oldest page using FIFO
            if (count == MAX_FRAMES) {
                // Replace the page at the front of the queue
                frames[front] = pageRequests[i];
                front = (front + 1) % MAX_FRAMES;
            } else {
                // There is space in the frames, add the page at the rear
                frames[rear] = pageRequests[i];
                rear = (rear + 1) % MAX_FRAMES;
                count++;
            }

            printf("Page %d is not present in frames. Page %d added to frames.\n", pageRequests[i], pageRequests[i]);
        } else {
            printf("Page %d is already present in frames.\n", pageRequests[i]);
        }

        printf("Current frames: ");
        displayFrames();
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n;

    printf("Enter the number of page requests: ");
    scanf("%d", &n);

    printf("Enter the page requests (pages numbered from 0 to 9):\n");
    pageReplacementFIFO(n);

    return 0;
}
