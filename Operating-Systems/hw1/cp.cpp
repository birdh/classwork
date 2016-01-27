// This C program copies the contents of a txt file to another txt file.
// How to call from command line:
//		cp>Debug\cp.exe test.txt out.txt
// 2 parameters: input file and output file.

#include <Windows.h>
#include <cstdio>

// Copy function prototype.
void cp( const char * src, const char * dst );

int main( int argc, char * args[] ) 
{
	// Check if user send in correct parameters.
	if ( args[1] == nullptr || args[2] == nullptr )
	{
		printf( "Error: Please specify source and dest files!" );
		return 0;
	}
	
	// Call the copy function.
	cp( args[1], args[2] );

	return 0;
}

// 2 parameters: input file and output file.
void cp( const char * src, const char * dst )
{
	HANDLE infile;				// Points to input file.
	HANDLE outfile;				// Points to output file.
	DWORD numberOfBytesRead;	// The number of bytes actually read from input file.
	DWORD numberOfBytesWritten;	// The number of bytes actually written to input file.
	char buffer[20];			// Buffer to hold characters read from file.

	// Open up an existing file to read from.
	infile = CreateFileA( src, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	// If file does not exist, exit program.
	if( GetLastError() == ERROR_FILE_NOT_FOUND )
	{
		printf( "Error: Could not find file!" );
		return;
	}

	// Create a new file to hold output.
	outfile = CreateFileA( dst, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Read data from input file and write it to output file.
	bool loop = true;
	while( loop )
	{
		// Read 20 bytes from infile, saving the actual numer of bytes read in numberOfBytesRead.
		ReadFile( infile, buffer, 20, &numberOfBytesRead, NULL );

		// If we've reached the end of input file, exit loop.
		if( numberOfBytesRead == 0 )
		{
			loop = false;
		}
		else 
		{
			// If bytes were read, write them to the output file.
			WriteFile( outfile, buffer, numberOfBytesRead, &numberOfBytesWritten, NULL );
		}
	}

	return;
}
