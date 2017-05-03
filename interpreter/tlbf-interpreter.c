#include "tlbf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    int showHelp = 1;
    char* filename = 0;

    tlbfLangFlags flags;
    
    for(int i = 0; i < argc; ++i)
    {
	int skip = 1;
	if(argv[i][0] == '-')
	{
	    if(argv[i][1] != '-')
	    {
		// single dash, this should be a list of short flags
		int len = strlen(argv[i])-1;
		for(int j = 1; j < len; ++j)
		{
		    switch(argv[i][j])
		    {
		    case 'h':
			showHelp = 1;
			break;


			// language options
		    case 'O': // Ook
			flags |= TLBF_LANG_OOK;
			break;
		    default:
			showHelp = 1;
		    }
		}
	    }
	    else
	    {
		// double dash long flag
		if(strcmp(&argv[i][2], "ook") == 0)
		{
		    flags |= TLBF_LANG_OOK;
		}
	    }
	    
	    continue;
	}
	filename = argv[i];
	showHelp = 0;
    }

    if((flags & TLBF_LANG_MASK) == 0)
    {
	flags |= TLBF_LANG_BF;
    }
    
    if(showHelp)
    {
    }
    else
    {
//	char* filename = argv[1];
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
		tlbfSetLangFlags(ctx, flags);
		tlbfSetProgram(ctx, progbuf);
		tlbfRun(ctx);
		tlbfTerminateContext(&ctx);
	    }
	    free(progbuf);
	}
    }
    return 0;
}
