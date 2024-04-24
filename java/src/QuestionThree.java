import java.util.*;

class Page {
    int pageNumber;
    int frameNumber;

    public Page(int pageNumber, int frameNumber) {
        this.pageNumber = pageNumber;
        this.frameNumber = frameNumber;
    }
}

public class QuestionThree {

    static Scanner scanner = new Scanner(System.in);

    static void simulatePaging(int totalFrames, int frameSize, int totalPages, int pageSize) {
        List<Page> pageTable = new ArrayList<>();

        // Initialize page table
        for (int i = 0; i < totalPages; i++) {
            pageTable.add(new Page(i, -1)); // Initially, no page is in memory (-1 represents not in memory)
        }

        // Simulate page allocation and replacement (for demonstration, using FIFO algorithm)
        Queue<Integer> frameQueue = new LinkedList<>();
        int pageFaults = 0;

        System.out.println("Page\tFrame\tPage Table");
        for (int i = 0; i < totalPages; i++) {
            int pageIndex = i / pageSize;
            if (!frameQueue.contains(pageIndex)) {
                pageFaults++;
                if (frameQueue.size() >= totalFrames) {
                    int removedPageIndex = frameQueue.poll();
                    pageTable.get(removedPageIndex * pageSize).frameNumber = -1; // Remove page from memory
                }
                frameQueue.add(pageIndex);
                pageTable.get(i).frameNumber = pageIndex;
            }

            System.out.println(i + "\t" + pageIndex + "\t" + pageTable);
        }

        System.out.println("Total Page Faults: " + pageFaults);
    }

    public static void main(String[] args) {
        System.out.print("Enter total number of frames in physical memory: ");
        int totalFrames = scanner.nextInt();

        System.out.print("Enter size of each frame: ");
        int frameSize = scanner.nextInt();

        System.out.print("Enter total number of pages in virtual memory: ");
        int totalPages = scanner.nextInt();

        System.out.print("Enter size of each page: ");
        int pageSize = scanner.nextInt();

        simulatePaging(totalFrames, frameSize, totalPages, pageSize);

        scanner.close();
    }
}
