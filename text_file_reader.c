#include "text_file_reader.h"

int main(void)
{
	int fd = open("filterFile.txt", O_RDONLY);
	
	// read line by line and store text strings in an array.
	char filter_entries[MAX_FILTER_ENTRY][MAX_FILTER_ENTRY_SIZE];
	//std::memset(filter_entries,0,MAX_FILTER_ENTRY*MAX_FILTER_ENTRY_SIZE*sizeof(char));
	int entry = 0;
	int c = 0;
	if ( fd >= 0)
	{
		char rdbuf[1];
		rdbuf[0] = 0;
		
		int cnt = read(fd, rdbuf, 1);
		while (cnt>0)
		{
			if ( rdbuf[0] != '\n' )
			{
				if ( c < MAX_FILTER_ENTRY_SIZE-1 )
				{
					filter_entries[entry][c] = rdbuf[0];
					c++;
					//std::cout << rdbuf[0] << std::endl;
				}
				else
				{
					filter_entries[entry][c] = 0; // terminator
				}
			}
			else
			{
				if (c > 0)
				{
					//std::cout << "terminating string" << std::endl;
					filter_entries[entry][c] = 0; // terminator
					entry++;
					c = 0;
				}
				if ( entry >= MAX_FILTER_ENTRY ) 
				{
					break;
				}
			}
			cnt = read(fd, rdbuf, 1);
		}
	close(fd);
	}
	else
	{
		std::cout << "File not found." << std::endl;	
	}
	
	std::cout << "entry="<< entry << std::endl;
	
	for( int i = entry-1; i >= 0; i-- )
	{
		std::cout <<  filter_entries[i] << std::endl;
		//printf( "%s \n",filter_entries[i]);
		if ( NULL != strstr(filter_entries[i],"not") )
		{
			std::cout <<  "   strstr FOUND " << std::endl;
		}
	}
	
	return 0;	
}
