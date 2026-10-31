// CS609_Assignment1_TextFileAnalyzer
#include <windows.h>
#include <iostream>
#include <string>

int main() {
    std::string filePath;
    
    // 2. Ask the user to enter the path of a text file
    std::cout << "Enter the path of the text file: ";
    std::getline(std::cin, filePath);
    
    
    
    
    // 3. Use CreateFile() to open the specified file in read-only mode
    HANDLE hFile = CreateFileA(
        filePath.c_str(),          // File path
        GENERIC_READ,              // Read-only access
        FILE_SHARE_READ,           // Share read access
        NULL,                      // Default security
        OPEN_EXISTING,             // Open only if it exists
        FILE_ATTRIBUTE_NORMAL,     // Normal file attributes
        NULL                       // No template file
    );
    
    // 8. If the specified file cannot be opened, display a suitable error message
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open the file. Please check the path. (Error Code: " 
                  << GetLastError() << ")" << std::endl;
        return 1;
    }
    
    // Get the handle to the standard output (console) to use with WriteFile
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to get console handle." << std::endl;
        CloseHandle(hFile);
        return 1;
    }
    
    
    const DWORD BUFFER_SIZE = 1024; // Buffer for reading in chunks
    char buffer[BUFFER_SIZE];
    DWORD bytesRead = 0;
    DWORD bytesWritten = 0;
    DWORD totalBytesRead = 0;
    
    std::cout << "\nFile Contents:\n";
    // 4. Read the file using ReadFile() in a loop to handle large files
    while (ReadFile(hFile, buffer, BUFFER_SIZE, &bytesRead, NULL) && bytesRead > 0) {
    	// 6. Calculate total number of bytes read
    	totalBytesRead += bytesRead;
    	// 5. Display the contents of the file on the console as they are read
        WriteFile(hConsole, buffer, bytesRead, &bytesWritten, NULL);
	}
	
	std::cout << "\n\nTotal Bytes Read: " << totalBytesRead << std::endl;
	// 7. Close its handle using CloseHandle()
	CloseHandle(hFile);
    
    return 0;
}
