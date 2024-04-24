import java.util.*;

class File {
    int id;
    int size;
    int[] blocks;

    public File(int id, int size, int[] blocks) {
        this.id = id;
        this.size = size;
        this.blocks = blocks;
    }
}

public class QuestionTwo {

    static Scanner scanner = new Scanner(System.in);

    static void sequentialAllocation(int[] disk, List<File> files) {
        for (File file : files) {
            int startBlock = -1;
            for (int i = 0; i < disk.length; i++) {
                if (disk[i] == 0) {
                    if (startBlock == -1) {
                        startBlock = i;
                    }
                    file.blocks[i - startBlock] = 1;
                    disk[i] = 1;
                }
            }
        }
    }

    static void indexedAllocation(int[] disk, List<File> files) {
        for (File file : files) {
            int indexBlock = -1;
            for (int i = 0; i < disk.length; i++) {
                if (disk[i] == 0) {
                    indexBlock = i;
                    disk[i] = 1;
                    break;
                }
            }
            if (indexBlock == -1) {
                System.out.println("No space left for index block!");
                return;
            }

            for (int i = 0; i < file.size; i++) {
                int block = -1;
                for (int j = 0; j < disk.length; j++) {
                    if (disk[j] == 0) {
                        block = j;
                        disk[j] = 1;
                        break;
                    }
                }
                if (block == -1) {
                    System.out.println("No space left for file blocks!");
                    return;
                }
                file.blocks[i] = block;
            }
            file.blocks[0] = indexBlock;
        }
    }

    static void linkedAllocation(int[] disk, List<File> files) {
        for (File file : files) {
            int startBlock = -1;
            for (int i = 0; i < disk.length; i++) {
                if (disk[i] == 0) {
                    startBlock = i;
                    disk[i] = 1;
                    break;
                }
            }
            if (startBlock == -1) {
                System.out.println("No space left for start block!");
                return;
            }

            int currentBlock = startBlock;
            for (int i = 0; i < file.size; i++) {
                int nextBlock = -1;
                for (int j = currentBlock + 1; j < disk.length; j++) {
                    if (disk[j] == 0) {
                        nextBlock = j;
                        disk[j] = 1;
                        break;
                    }
                }
                if (nextBlock == -1) {
                    System.out.println("No space left for file blocks!");
                    return;
                }
                file.blocks[i] = nextBlock;
                currentBlock = nextBlock;
            }
        }
    }

    static void printDiskStatus(int[] disk) {
        System.out.println("Disk Status:");
        for (int i = 0; i < disk.length; i++) {
            System.out.print(disk[i] + " ");
            if ((i + 1) % 10 == 0) {
                System.out.println();
            }
        }
        System.out.println();
    }

    static void printFiles(List<File> files) {
        System.out.println("File Allocation Details:");
        for (File file : files) {
            System.out.println("File ID: " + file.id);
            System.out.println("File Blocks: " + Arrays.toString(file.blocks));
        }
    }

    public static void main(String[] args) {
        System.out.print("Enter the total number of blocks in disk: ");
        int totalBlocks = scanner.nextInt();

        int[] disk = new int[totalBlocks];

        System.out.print("Enter the number of files: ");
        int numFiles = scanner.nextInt();

        List<File> files = new ArrayList<>();

        for (int i = 0; i < numFiles; i++) {
            System.out.print("Enter size of file " + (i + 1) + ": ");
            int size = scanner.nextInt();
            int[] blocks = new int[size];
            files.add(new File(i + 1, size, blocks));
        }

        System.out.println("\nSequential Allocation:");
        sequentialAllocation(disk, new ArrayList<>(files));
        printDiskStatus(disk);
        printFiles(new ArrayList<>(files));

        // Reset disk
        Arrays.fill(disk, 0);

        System.out.println("\nIndexed Allocation:");
        indexedAllocation(disk, new ArrayList<>(files));
        printDiskStatus(disk);
        printFiles(new ArrayList<>(files));

        // Reset disk
        Arrays.fill(disk, 0);

        System.out.println("\nLinked Allocation:");
        linkedAllocation(disk, new ArrayList<>(files));
        printDiskStatus(disk);
        printFiles(new ArrayList<>(files));

        scanner.close();
    }
}
