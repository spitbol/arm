/*
Copyright 1987-2012 Robert B. K. Dewar and Mark Emmer.
Copyright 2012-2017 David Shields
*/

/*
/   optfile( varname, result )
/
/   optfile() looks for other, optional ways to supply a filename to
/   the INPUT/OUTPUT functions.  Varname is an SCBLK containing the string
/   used as an alias for the file name, and result is an SCBLK that will
/   receive the aliased name.
/
/   optfile() looks in two places for the alias.  First, if the alias is
/   a numeric string, it looks in the cfiles table to see if it was specified
/   on the command line.  If not found there, it looks in the environment block.
/
/   Parameters:
/	varname	 pointer to SCBLK containing alias
/	result   pointer to SCBLK that will receive any name found
/   Returns:
/       0  - success, result contains name
/	-1 - failure
/   Side Effects:
/	none
*/

#include "port.h"

int optfile( varname, result )

struct	scblk	*varname, *result;

{
    word	i, j, n;
    register char *p, *q;

    // try to convert alias to an integer
    i = 0;
    n = scnint( varname->str, varname->len, &i);
    if (i == varname->len)		// Consume all characters?
    {
        for (j = 0; j <= maxf; j++)
        {
            if (cfiles[j].filenum == n)
            {
                p = cfiles[j].fileptr;
                q = result->str;
                while ((*q++ = *p++) != 0)
                    ;
                result->len = q - result->str - 1;
                return 0;
            }
        }
    }

    // didn't find it on the command line.  Check environment
    return rdenv( varname, result );
}

