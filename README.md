# Word Frecuency Counter

Overview:
This program can take multiple files from 3 different sources (STDIN, environment variables, and argument variables) as inputs. It takes these text files and and
puts every word it finds in the file into a binary search tree, if that word is already in the BST, than it increments the count of how often the word was found
throughout the files. After every file has been scanned, the program writes all the words in alphabetical order and the number of times the word has shown up into
a text (.txt) file called output.txt. 


Implementation: 
To get a word from the file I would first open the file. After I would read character by character to see if the character was an alphabet character
or not. If it was I would concat it to a string. I would ddo this until I came across a cahracter that was not an alphabetic character.
When this happended I would take the string that was made, which had the word in it, and I would either increment count or addd it to the BST. 
After this happend I would reset the string to an empty string, and repeat this cycle until the whole file was read. 
I did this for all input methods(STDIN, environment variables, argument variables).

To handle the word I would first call incrementWord() which would increment the word if it was foundd in the BST and return 1, but if the wordd was not found it would return 0. If it return 0, then I would add the word to the BST as it wasn't in the BST already. 

After adding all the wordds to the BST, I made an output file called output.txt.
I made this file write only and truncated it so it would be overwritten everytime the program was run. 
To ouput the BST into the output.txt file I would go through all the BSTs in a for loop and use inorder traverasal 
on each BST, so that it would write inorder. I would write every node's word and count into the output.txt file. 
After I wrote to the file I freed all the words andd BSTs that were malloced from the program. 
After this an output.txt file would be made with all the words and their respective counts in it.
