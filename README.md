# ADS-CP-SEM-III-
Implementation of Huffman Encoding and Decoding Algorithm for File Compresssion

The Huffman File Encoding and Decoding project 
addresses the need for efficient text file compression and 
decompression. Text data often takes up a significant amount 
of storage space and transmission bandwidth. The goal of this 
project is to implement Huffman coding, a well-known 
compression technique, to reduce the size of text files while 
ensuring lossless data recovery during the decompression 
process.

## How to run 

1. Create a text file(here i have created rishi1.txt) and write some text inside it.
2. Now compile both the **encode.c** and decode.c files
3. Run encode.c file - put the input as filename.txt ( here rishi1.txt)
4. After executing the encode.c file it will output two separate files in the same directory with **filename.txt.huffman** and **filename.table** extensions.
5. Now use the **decode.c** file to decode or decompress any **.huffman** and **.table** file. These two files are mandatory. The decoded file will be saved in a directory with extension **.decoded**
