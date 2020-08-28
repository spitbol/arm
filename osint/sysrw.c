/*
Copyright 1987-2012 Robert B. K. Dewar and Mark Emmer.
Copyright 2012-2017 David Shields
*/

/*
/   zysrw - rewind file
/
/	Parameters
/	    WA - pointer to FCBLK or 0
/	    XR - pointer to SCBLK containing rewind argument
/	Returns:
/	    Nothing
/	Exits:
/	    1 - file doesn't exit
/	    2 - rewind not allowed on this device
/	    3 - I/O error
/
*/

#include "port.h"

int zysrw()
{
    register struct fcblk *fcb = WA (struct fcblk *);
    register struct ioblk *iob = ((struct ioblk *) (fcb->iob));

    // ensure the file is open
    if ( !(iob->flg1 & IO_OPN) )
        return EXIT_1;

    // see if this file can be LSEEK'ed
    if ( LSEEK(iob->fdn, (FILEPOS)0, 1) < (FILEPOS)0 )
        return EXIT_2;

    // seek to the beginning
    if (doset( iob, 0L, 0 ) == (FILEPOS)-1)
        return EXIT_3;

    return NORMAL_RETURN;
}
