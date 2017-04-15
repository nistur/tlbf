#include "tlbf.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argc > 1)
    {
	char* filename = argv[1];
	FILE* fp = fopen(filename, "r");
	char* progbuf = 0;
	if(fp)
	{
	    fseek(fp, 0l, SEEK_END);
	    long p = ftell(fp);
	    rewind(fp);
	    
	    progbuf = (char*)malloc(p);
	    
	    fread(progbuf, 1, p, fp);
	    
	    fclose(fp);
	}

	if(progbuf)
	{
	    tlbfContext* ctx = 0;
	    tlbfInitContext(&ctx);
	    if(ctx)
	    {
		tlbfSetProgram(ctx, progbuf);
		tlbfRun(ctx);
		tlbfTerminateContext(&ctx);
	    }
	    free(progbuf);
	}
    }
    return 0;
}
