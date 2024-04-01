# HuffMan
Huffman Coding Implementation in C
Usage: your_program [OPTIONS]

Compress text files' size using the Huffman algorithm. By default, it operates in the current directory.

Options:
  -c, --compress [FILE]  Compress the specified text file. If no option is provided, do the same.
  -d, --decode [FILE]    Decode a compressed file using the specified output.bin and table.txt files.
  -h, --help             Display this help message.

Description:
  If you want to compress a file's size, use the -c option along with the file path or leave it empty with no option. The program will create two files: table.txt (Huffman algorithm table) and output.bin (compressed file).
  To decode a compressed file, provide the -d option along with the output.bin and table.txt file paths. The program will create one file: original.txt (it has the original file without decoding)

Example:
  Compress file.txt:
    your_program file.txt -c 

  Decode compressed file:
    your_program output.bin table.txt -d 
