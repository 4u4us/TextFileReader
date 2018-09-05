#include "text_file_reader.h"

char filter_entries[MAX_FILTER_ENTRY][MAX_FILTER_ENTRY_SIZE];
std::string filterFilename("filterFile.txt");

std::map<int, std::string> mapOfFiles;

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
	
	std::cout << "num of entries found in filter = "<< entry << std::endl;	
}

bool applyFilterTo(const char* input)
{
	//for( int i = 0 ; i < MAX_FILTER_ENTRY && (strlen(filter_entries[i])>0); i++ )
	//{
	//	std::cout <<  filter_entries[i] << "::" << strlen(filter_entries[i]) << std::endl;
	//}
	//std::cout <<  "\n _______ \n" << std::endl;
	for( int i = MAX_FILTER_ENTRY-1 ; i >= 0; i-- )
	{
		std::cout <<  filter_entries[i] << "::" << strlen(filter_entries[i]) << std::endl;
		if ( strlen(filter_entries[i])>0 )
		{
			//std::cout <<  filter_entries[i] << std::endl;
			if ( NULL != strstr(input, filter_entries[i]) )
			{
				std::cout <<  "   strstr " << filter_entries[i] << " FOUND in " << input << std::endl;
				return true;
			}
		}
	}	
	return false;
}

bool getFilenameBasedOnFileDescriptor(int a_fd, std::string& a_filename, bool doErase)
{
	bool ret = false; // default not found
	a_filename = "";
	std::map<int, std::string>::iterator it;
	it = mapOfFiles.find(a_fd);
	if (it != mapOfFiles.end())
	{
		ret = true;
		std::cout <<  "   Found from map " << it->second.c_str() << std::endl;
		a_filename = it->second;
		if (true==doErase)
		{
			std::cout <<  "       Erasing from map " << it->second.c_str() << std::endl;
			mapOfFiles.erase (it);
		}
	}
	return ret;
}

int main(void)
{
	loadFilter();
	
	// Init a map of files with simulated file descriptor.
	mapOfFiles[2] = "/data/not/valid/more/my2app.exe";
	mapOfFiles[12] = "/data/not/vvalid/more/myapp";
	mapOfFiles[100] = "/data/valid/more/my3app.exe";
	mapOfFiles[3] = "/data/not/applied/more/myapp.exe";
	
	std::cout <<  "Num of elements in mapOfFiles: " << mapOfFiles.size() << std::endl;
	
    std::cout <<  "____________" << std::endl;
   	std::string input_a(""); 
    getFilenameBasedOnFileDescriptor(3, input_a, false);
	bool ret_a = applyFilterTo(input_a.c_str());
	std::cout <<  "____________" << std::endl;
	std::string input_b("");
	getFilenameBasedOnFileDescriptor(12, input_b, false);
	bool ret_b = applyFilterTo(input_b.c_str());
	std::cout <<  "____________" << std::endl;
	
	// remove from map the files that were not used.
	getFilenameBasedOnFileDescriptor(2, input_b, true);
	getFilenameBasedOnFileDescriptor(100, input_b, true);
	
	std::cout <<  "Num of elements in mapOfFiles: " << mapOfFiles.size() << std::endl;

	return 0;	
}
