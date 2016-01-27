// This C program moves the a txt file to another location.
// (It actually just copies it and deletes the source file.)
// How to call from command line:
//		mv>Debug\mv.exe test.txt out.txt
// 2 parameters: src file and dest file.

#include <Windows.h>
#include <cstdio>

// Move function prototype.
void mv( const char * src, const char * dst );

int main( int argc, char * args[] ) 
{
	// Check if user send in correct parameters.
	if ( args[1] == nullptr || args[2] == nullptr )
	{
		printf( "Error: Please specify source and dest files!" );
		return 0;
	}
	
	// Call the move function.
	mv( args[1], args[2] );

	return 0;
}

// 2 parameters: source file and dest file.
void mv( const char * src, const char * dst )
{
	HANDLE srcfile;				// Points to source file.
	HANDLE dstfile;				// Points to dest file.
	DWORD numberOfBytesRead;	// The number of bytes actually read from input file.
	DWORD numberOfBytesWritten;	// The number of bytes actually written to input file.
	char buffer[20];			// Buffer to hold characters read from file.

	// Open up an existing file to read from.
	srcfile = CreateFileA( src, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	// If file does not exist, exit program.
	if( GetLastError() == ERROR_FILE_NOT_FOUND )
	{
		printf( "Error: Could not find file!" );
		return;
	}

	// Create a new file to hold output.
	dstfile = CreateFileA( dst, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Read data from input file and write it to output file.
	bool loop = true;
	while( loop )
	{
		// Read 20 bytes from infile, saving the actual numer of bytes read in numberOfBytesRead.
		ReadFile( srcfile, buffer, 20, &numberOfBytesRead, NULL );

		// If we've reached the end of input file, exit loop.
		if( numberOfBytesRead == 0 )
		{
			loop = false;
		}
		else 
		{
			// If bytes were read, write them to the output file.
			WriteFile( dstfile, buffer, numberOfBytesRead, &numberOfBytesWritten, NULL );
		}
	}

	// Close the files.
	CloseHandle( srcfile );
	CloseHandle( dstfile );

	// Delete the source file.
	DeleteFile( src );

	return;
}
