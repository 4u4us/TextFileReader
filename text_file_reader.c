#include "text_file_reader.h"

char filter_entries[MAX_FILTER_ENTRY][MAX_FILTER_ENTRY_SIZE];
std::string filterFilename("filterFile.txt");


void loadFilter()
{
	int fd = open(filterFilename.c_str(), O_RDONLY);
	// read line by line and store text strings in an array.
	std::memset(filter_entries,0,MAX_FILTER_ENTRY*MAX_FILTER_ENTRY_SIZE*sizeof(char));
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
		std::cout << "Filter File not found." << std::endl;	
	}
	
	std::cout << "num of entries found="<< entry << std::endl;	
}

bool applyFilterTo(const char* input)
{
	for( int i = 0 ; i < MAX_FILTER_ENTRY && (strlen(filter_entries[i])>0); i++ )
	{
		std::cout <<  filter_entries[i] << std::endl;
		if ( NULL != strstr(input, filter_entries[i]) )
		{
			std::cout <<  "   strstr " << filter_entries[i] << " FOUND in " << input << std::endl;
			return true;
		}
	}	
	return false;
}

int main(void)
{
	loadFilter();
    std::cout <<  "____________" << std::endl;
	std::string input_a("/data/not/applied/more/myapp.exe");
	bool ret_a = applyFilterTo(input_a.c_str());
	std::cout <<  "____________" << std::endl;
	std::string input_b("/data/not/valid/more/myapp.exe");
	bool ret_b = applyFilterTo(input_b.c_str());
	std::cout <<  "____________" << std::endl;

	
	return 0;	
}
