import java.util.*;


import java.util.ArrayList;
import java.util.List;

// Class representing a directory
class Directory {
    String name;
    List<File> files;
    List<Directory> subdirectories;

    public Directory(String name) {
        this.name = name;
        this.files = new ArrayList<>();
        this.subdirectories = new ArrayList<>();
    }

    // Method to add a file to the directory
    public void addFile(File file) {
        files.add(file);
    }

    // Method to add a subdirectory to the directory
    public void addSubdirectory(Directory directory) {
        subdirectories.add(directory);
    }

    // Method to remove a file from the directory
    public void removeFile(File file) {
        files.remove(file);
    }

    // Method to remove a subdirectory from the directory
    public void removeSubdirectory(Directory directory) {
        subdirectories.remove(directory);
    }

    @Override
    public String toString() {
        return name;
    }
}

// Class representing a file
class File {
    String name;

    public File(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }
}


public class QuestionFour {

    static Scanner scanner = new Scanner(System.in);
    static Map<String, List<File>> twoLevelDirectory = new HashMap<>();
    static Map<String, Directory> hierarchicalDirectory = new HashMap<>();
    static Directory rootDirectory = new Directory("Root");

    public static void main(String[] args) {
        boolean exit = false;

        while (!exit) {
            System.out.println("\nChoose File Organization Technique:");
            System.out.println("1. Single Level Directory");
            System.out.println("2. Two Level Directory");
            System.out.println("3. Hierarchical Directory");
            System.out.println("4. Exit");

            int choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    simulateSingleLevelDirectory();
                    break;
                case 2:
                    simulateTwoLevelDirectory();
                    break;
                case 3:
                    simulateHierarchicalDirectory();
                    break;
                case 4:
                    exit = true;
                    System.out.println("Exiting program...");
                    break;
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        }
    }

    static void simulateSingleLevelDirectory() {
        List<File> singleLevelDirectory = new ArrayList<>();

        while (true) {
            System.out.println("\nSingle Level Directory Menu:");
            System.out.println("1. Create File");
            System.out.println("2. Delete File");
            System.out.println("3. Display Files");
            System.out.println("4. Back to Main Menu");

            int choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    System.out.print("Enter file name: ");
                    String fileName = scanner.next();
                    singleLevelDirectory.add(new File(fileName));
                    System.out.println("File created successfully.");
                    break;
                case 2:
                    System.out.print("Enter file name to delete: ");
                    String deleteFileName = scanner.next();
                    File fileToDelete = singleLevelDirectory.stream()
                                                            .filter(file -> file.name.equals(deleteFileName))
                                                            .findFirst().orElse(null);
                    if (fileToDelete != null) {
                        singleLevelDirectory.remove(fileToDelete);
                        System.out.println("File deleted successfully.");
                    } else {
                        System.out.println("File not found.");
                    }
                    break;
                case 3:
                    System.out.println("Files in Single Level Directory:");
                    singleLevelDirectory.forEach(System.out::println);
                    break;
                case 4:
                    return;
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        }
    }

    static void simulateTwoLevelDirectory() {
        while (true) {
            System.out.println("\nTwo Level Directory Menu:");
            System.out.println("1. Create Directory");
            System.out.println("2. Create File");
            System.out.println("3. Delete File");
            System.out.println("4. Display Files");
            System.out.println("5. Back to Main Menu");

            int choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    System.out.print("Enter directory name: ");
                    String directoryName = scanner.next();
                    twoLevelDirectory.put(directoryName, new ArrayList<>());
                    System.out.println("Directory created successfully.");
                    break;
                case 2:
                    System.out.print("Enter directory name: ");
                    String dirName = scanner.next();
                    if (!twoLevelDirectory.containsKey(dirName)) {
                        System.out.println("Directory not found.");
                        break;
                    }
                    System.out.print("Enter file name: ");
                    String fileName = scanner.next();
                    twoLevelDirectory.get(dirName).add(new File(fileName));
                    System.out.println("File created successfully.");
                    break;
                case 3:
                    System.out.print("Enter directory name: ");
                    String delDirName = scanner.next();
                    if (!twoLevelDirectory.containsKey(delDirName)) {
                        System.out.println("Directory not found.");
                        break;
                    }
                    System.out.print("Enter file name to delete: ");
                    String deleteFileName = scanner.next();
                    List<File> files = twoLevelDirectory.get(delDirName);
                    File fileToDelete = files.stream().filter(file -> file.name.equals(deleteFileName)).findFirst().orElse(null);
                    if (fileToDelete != null) {
                        files.remove(fileToDelete);
                        System.out.println("File deleted successfully.");
                    } else {
                        System.out.println("File not found.");
                    }
                    break;
                case 4:
                    System.out.println("Files in Two Level Directory:");
                    twoLevelDirectory.forEach((dir, fileList) -> {
                        System.out.println("Directory: " + dir);
                        fileList.forEach(System.out::println);
                    });
                    break;
                case 5:
                    return;
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        }
    }

    static void simulateHierarchicalDirectory() {
        while (true) {
            System.out.println("\nHierarchical Directory Menu:");
            System.out.println("1. Create Directory");
            System.out.println("2. Create File");
            System.out.println("3. Delete File");
            System.out.println("4. Display Files");
            System.out.println("5. Back to Main Menu");

            int choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    System.out.print("Enter directory path (e.g., /dir1/dir2): ");
                    String path = scanner.next();
                    createDirectory(path);
                    break;
                case 2:
                    System.out.print("Enter directory path (e.g., /dir1/dir2): ");
                    String filePath = scanner.next();
                    Directory directory = getDirectory(filePath);
                    if (directory == null) {
                        System.out.println("Directory not found.");
                        break;
                    }
                    System.out.print("Enter file name: ");
                    String fileName = scanner.next();
                    directory.addFile(new File(fileName));
                    System.out.println("File created successfully.");
                    break;
                case 3:
                    System.out.print("Enter file path (e.g., /dir1/dir2/file.txt): ");
                    String fileToDeletePath = scanner.next();
                    Directory fileDir = getDirectory(fileToDeletePath);
                    if (fileDir == null) {
                        System.out.println("File not found.");
                        break;
                    }
                    String deleteFileName = fileToDeletePath.substring(fileToDeletePath.lastIndexOf('/') + 1);
                    File fileToDelete = fileDir.files.stream().filter(file -> file.name.equals(deleteFileName)).findFirst().orElse(null);
                    if (fileToDelete != null) {
                        fileDir.removeFile(fileToDelete);
                        System.out.println("File deleted successfully.");
                    } else {
                        System.out.println("File not found.");
                    }
                    break;
                case 4:
                    System.out.println("Files in Hierarchical Directory:");
                    displayHierarchicalDirectory(rootDirectory, 0);
                    break;
                case 5:
                    return;
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        }
    }

    static void createDirectory(String path) {
        String[] directories = path.split("/");
        Directory currentDir = rootDirectory;
        for (String directory : directories) {
            if (!directory.isEmpty()) {
                if (!currentDir.files.stream().anyMatch(file -> file.name.equals(directory))) {
                    Directory newDir = new Directory(directory);
                    currentDir.addFile(newDir);
                    hierarchicalDirectory.put(path, newDir);
                }
                currentDir = hierarchicalDirectory.get(path);
            }
        }
    }

    static Directory getDirectory(String path) {
        return hierarchicalDirectory.get(path);
    }

    static void displayHierarchicalDirectory(Directory directory, int level) {
        if (directory != null) {
            StringBuilder indent = new StringBuilder();
            for (int i = 0; i < level; i++) {
                indent.append("  ");
            }
            System.out.println(indent + directory.name);
            for (File file : directory.files) {
                System.out.println(indent + "  " + file.name);
            }
            for (File file : directory.files) {
                if (file instanceof Directory) {
                    displayHierarchicalDirectory((Directory) file, level + 1);
                }
            }
        }
    }
}
