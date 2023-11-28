#include <iostream>
#include <filesystem>
#include <dirent.h>

namespace fs = std::filesystem;

// Function to list the directory content
void listDirectoryContents(const char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        std::cerr << "Error opening directory" << std::endl;
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        std::cout << entry->d_name << std::endl;
    }

    closedir(dir);
}

// Function to create the directory
void createDirectory(const std::string &path)
{
    if (!fs::create_directory(path))
    {
        std::cerr << "Failed to create directory: " << path << std::endl;
    }
    else
    {
        std::cout << "Directory created successfully: " << path << std::endl;
    }
}

// function to copy the files
void copyFile(const std::string &source, const std::string &destination)
{
    try
    {
        fs::copy(source, destination);
        std::cout << "File copied successfully" << std::endl;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "File copy failed: " << e.what() << std::endl;
    }
}

// Fucntion to move the files
void moveFile(const std::string &source, const std::string &destination)
{
    try
    {
        fs::rename(source, destination);
        std::cout << "File moved successfully" << std::endl;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "File move failed: " << e.what() << std::endl;
    }
}

int main()
{
    int choice;
    std::string path, source, destination;

    std::cout << "1. Create Directory\n2. List Directory Contents\n3. Copy File\n4. Move File\nEnter your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        std::cout << "Enter directory path to create: ";
        std::cin >> path;
        createDirectory(path);
        break;
    case 2:
        std::cout << "Enter directory path to list contents: ";
        std::cin >> path;
        listDirectoryContents(path.c_str());
        break;
    case 3:
        std::cout << "Enter source file path to copy: ";
        std::cin >> source;
        std::cout << "Enter destination file path: ";
        std::cin >> destination;
        copyFile(source, destination);
        break;
    case 4:
        std::cout << "Enter source file path to move: ";
        std::cin >> source;
        std::cout << "Enter destination file path: ";
        std::cin >> destination;
        moveFile(source, destination);
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
    }

    return 0;
}
