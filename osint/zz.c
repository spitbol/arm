/*
Copyright 1987-2012 Robert B. K. Dewar and Mark Emmer.
Copyright 2012-2017 David Shields
*/

#ifdef z_trace

#include "port.h"

#include <stdio.h>


extern uword compsp;
extern uword osisp;

uword save_xl;
uword save_xr;
uword save_xs;
uword save_wa;
uword save_wb;
uword save_wc;
uword save_w0;
uword save_cp;
double save_ra;
uword zz_zz;
uword zz_ln;

uword last_xl;
uword last_xr;
uword last_xs;
uword last_wa;
uword last_wb;
uword last_wc;
uword last_w0;
uword last_cp;
double last_ra;

uword zz_calls = 0;
uword zz_hundred = 0;

uword zz_off;
uword zz_id=0;
uword zz_last = 0;
char * zz_de;
extern long c_aaa;
extern long w_yyy;
long off_c_aaa;
long off_w_yyy;
char * AT_DESC;
extern char at1_0;
void prtnl() {
	fprintf(stderr,"\n");
}
void prtreal(double val) {
	fprintf(stderr, " %8.3g ", val);
}

void prtval(long reg) {
//	if (reg > 32 && reg < 127 ) {
//		fprintf(stderr," '%c' %4d ", reg, reg);
//	}
//	else if (reg >= 0 && reg < 300000) {
	if (reg >= 0 && reg < 100000) {
		fprintf(stderr," %8ld ", reg);
	}
	else if ( reg >= off_c_aaa && reg <= off_w_yyy) {
		fprintf(stderr," Z%ld ", reg);
	}
	else {
		fprintf(stderr," %8lxx", reg & 0xffffffff);
//		fprintf(stderr," ---------", reg);
	}
}
void prtregr(char * name, double val) {
	prtreal(val);
	fprintf(stderr," %s",name);
}

void prtreg(char * name, long val) {
	prtval(val);
	fprintf(stderr," %s",name);
}
void prtdif(char* name, long old, long new, long listed)
{
	// print old and new values of named register
	fprintf(stderr,"%s:", name);
	prtval(old); fprintf(stderr," -> "); prtval(new);
	prtnl();
}

void prtdifr(char* name, double old, double new, long listed)
{
	// print old and new values of named register
	fprintf(stderr,"%s:", name);
	prtreal(old); fprintf(stderr," -> "); prtreal(new);
	prtnl();
}
extern long c_aaa;
extern long w_yyy;

long off_c_aaa;
long off_w_yyy;


void zz_init() {
//	off_c_aaa = &c_aaa;
//	off_w_yyy = &w_yyy;
//	fprintf(stderr, "off_c_aaa %ld\n", &c_aaa);
//	fprintf(stderr, "off_w_yyy %ld\n", &w_yyy);
}

char * zz_charp;

void zz_str() {
// print memory block pointed to by save_cp as string.
// print up to 20 characters, or until find non-printable character.
	char * cp;
	cp = zz_charp;
	int i;
	fprintf(stderr,"zz_str  ");
	for (i = 0;i<20;i++) {
		char c = *cp++;
		if (c>=32 && c <= 126) fprintf(stderr,"%c",c);
		else break;
	}
	fprintf(stderr,"\n");
}

extern uword _rc_;
void zz() {

	char *p;
	int changed = 0;
	int listed = 0;

	zz_calls++;
//	if (zz_calls < 2000)	return;	// bypass initial code
	if (zz_calls > 50000) return;
/*
	return;
 	zz_calls++;

	if (zz_calls == 100 ) {
	zz_hundred++;
	printf("%\d\n",zz_hundred);
	zz_calls = 0;
	}
	return;
*/
	// print registers that have changed since last statement

	// see if any have changed.
	if (save_xl != last_xl)  changed += 1;
	if (save_xr != last_xr)  changed += 1;
//	if (save_xs != last_xs)  changed += 1;
//	if (save_cp != last_cp)  changed += 1;
	if (save_wa != last_wa)  changed += 1;
	if (save_wb != last_wb)  changed += 1;
	if (save_wc != last_wc)  changed += 1;
	if (save_w0 != last_w0)  changed += 1;
	if (save_ra != last_ra)  changed += 1;
  changed = 0; // bypass printout
	if (changed) {
/* marked changed Minimal registers with "!" to make it easy to search
   backward for last statement that changed a register. */
		prtnl();
		if (save_xl != last_xl)
			{ prtdif("XL.esi", last_xl, save_xl, listed); listed += 1; }
		if (save_xr != last_xr)
			{ prtdif("XR.edi", last_xr, save_xr, listed); listed += 1; }
//		if (save_xs != last_xs)
//			{ prtdif("XS.esp", last_xs, save_xs, listed); listed += 1; }
//		if (save_cp != last_cp)
//			{ prtdif("CP.ebp", last_cp, save_cp, listed); listed += 1; }
		if (save_w0 != last_w0)
			{ prtdif("W0.eax", last_w0, save_w0, listed); listed += 1; }
		if (save_wa != last_wa)
			{ prtdif("WA.ecx", last_wa, save_wa, listed); listed += 1; }
		if (save_wb != last_wb)
			{ prtdif("WB.ebx", last_wb, save_wb, listed); listed += 1; }
		if (save_wc != last_wc)
			{ prtdif("WC.edx", last_wc, save_wc, listed); listed += 1; }
		if (save_ra != last_ra)
			{ prtdifr("RA    ", last_ra, save_ra, listed); listed += 1; }
		prtnl();
	}

//	if (zz_calls % 3 == 1) {
//	if (zz_calls>0) {
	int prtregs=1;
	 prtregs=0;
	 prtregs=1;

if (prtregs) {

		// print register values before the statement was executed
		prtreg("XL.esi", save_xl);
		prtreg("XR.edi", save_xr);
		prtregr("RA    ",save_ra);
//		prtreg("XS.esp", save_xs);
		// cp is last on line, so don't print it zero
//		if (save_cp) prtreg("cp.ebp", save_cp);
		fprintf(stderr, "\n");
		prtreg("W0.eax", save_w0);
		prtreg("WA.ecx", save_wa);
		prtreg("WB.ebx", save_wb);
		prtreg("WC.edx", save_wc);
		fprintf(stderr, "\n");
}
//	}
	// display instruction pointer and description of current statement.
	if (zz_zz != zz_last) {
//	fprintf(stderr, "\n%8xx %s\n", zz_ip, p);
//	fprintf(stderr, "zzz %d %d %d %s\n",zz_calls, zz_id, zz_zz,zz_de);
//	fprintf(stderr, "zzz %d %s\n",_rc_,zz_de);
//	fprintf(stderr, "\n    %6d  %s\n",zz_calls,zz_de);
	fprintf(stderr, "\n  %s\n",zz_de);
	}
	zz_last = zz_zz;

	// save current register contents.
	last_xl = save_xl; last_xr = save_xr; last_xs = save_xs; last_cp = save_cp;

	last_wa = save_wa; last_wb = save_wb; last_wc = save_wc; last_w0 = save_w0;

}
void zz_0() {
	fprintf(stderr, "zz_0\n");
}
void zz_1() {
	fprintf(stderr, "zz_1\n");
}
void zz_2() {
	fprintf(stderr, "zz_2\n");
}
void zz_3() {
	fprintf(stderr, "zz_3\n");
}
void zz_4() {
	fprintf(stderr, "zz_4\n");
}
uword zz_arg;
void zz_num() {
	fprintf(stderr, "zz_num\t%x\n",(unsigned int) zz_arg);
}
int zz_num_id;
int zz_sys_id;
int zz_sys_calls=0;
void zz_sys() {
	zz_sys_calls++;
	fprintf(stderr, "zz_sys %d %d\n",zz_sys_calls,zz_sys_id);
}
	extern double REAV1;
void zz_ra() {
	fprintf(stderr,"zz_ra %e\n",reg_ra);
}
#endif
