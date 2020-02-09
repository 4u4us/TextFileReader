# TextFileReader
Text file reader in C

Added use of systemtap
Get functions that can be probed:
stap -L 'process("/home/$USER/mygit/TextFileReader/text-file-reader").function("*").call'
