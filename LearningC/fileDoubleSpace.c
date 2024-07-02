/* Use File I/O
Command line arguments
Double Space input file to output file
Lou de Tarade
02/07/2024*/

#include <stdio.h>
#include <stdlib.h> //exit()


void print_file(FILE* fptr)
{
	int c;
	rewind(fptr);
	while ((c = getc(fptr)) != EOF)
		putc(c, stdout);
}

void double_space(FILE* ifp, FILE* ofp)
{
	int c;
	rewind(ifp);
	while ((c = getc(ifp)) != EOF)
	{
		putc(c, ofp);
		if (c == '\n')
			putc('\n', ofp);
	}
}

int main(int argc, char *argv[])
{
	FILE* ifp, * ofp;

	if (argc != 3)
	{
		printf("Need executable inputfile outputfile \n");
		exit(1);
	}

	ifp = fopen(argv[1], "r+");
	ofp = fopen(argv[2], "w+");

	printf("my %s file as read is \n\n", argv[1]);
	print_file(ifp);
	printf("\n\n");
	double_space(ifp, ofp);
	printf("my %s file double spaced is \n\n", argv[2]);
	print_file(ofp);
	printf("\n\n");

	fclose(ifp);
	fclose(ofp);

	return 0;
}