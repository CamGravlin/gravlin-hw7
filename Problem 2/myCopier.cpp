/*
*   This program takes one file to read and a second file to write to. Takes
*   both as a command line argument. The first file is read and copied to the
*   second file.
*   Example Invocation: ./myCopier file1 file2
*
*/

#include <iostream>
#include <fstream>
#include <string>
// std::cerr used like as std::out, but only used to print out error messages

int main(int argc, char* argv[]) {
  if (argc != 3) { // Checks if proper number of arguments are entered
      std::cerr << "Usage: " << argv[0] << " <input file> <output file>" <<
      std::endl;
  return 1;
  }

  std::ifstream inputFile(argv[1]); // Opens input file for reading
  if (!inputFile) {
    std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
  return 1;
  }

  std::ofstream outputFile(argv[2]); // Opens output file for writing
  if (!outputFile) {
    std::cerr << "Error: Could not open file " << argv[2] << std::endl;
    inputFile.close();
  return 1;
  }
  
  std::string line; // Copies contents line by line
  while (std::getline(inputFile, line)) {
    outputFile << line << std::endl;
  }

  // Closes both files
  inputFile.close();
  outputFile.close();

  std::cout << "File successfully copied!" << std::endl;

return 0;
}
