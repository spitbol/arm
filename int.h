# copyright 1987-2012 robert b. k. dewar and mark emmer.

# copyright 2012-2015 david shields
#
# this file is part of macro spitbol.
#
#     macro spitbol is free software: you can redistribute it and/or modify
#     it under the terms of the gnu general public license as published by
#     the free software foundation, either version 2 of the license, or
#     (at your option) any later version.
#
#     macro spitbol is distributed in the hope that it will be useful,
#     but without any warranty; without even the implied warranty of
#     merchantability or fitness for a particular purpose.  see the
#     gnu general public license for more details.
#
#     you should have received a copy of the gnu general public license
#     along with macro spitbol.	 if not, see <http://www.gnu.org/licenses/>.

	.code	32
#	.intel_syntax

#	results are usually returned in r0; real results in r0:r1

#	w0 -> r0  wa -> r2  wb -> r3  wc -> r4
#	xl -> r5 xr -> r6 sp => r13

#	r11 is grame pointer; 
#	r12 is procedure entry temporary workspace
#	r14 is link register, return address at function exit

#	%define m_char	byte	@ reference to byte in memory
#	%define d_char	db	@ define value of byte

#	%define m_word	qword
#	%define d_word	dq

#	%define m_real	qword	@ reference to floating point value in memory
#	%define d_real	dq	@ define value for floating point

# use  name .req reg   @ create alias for register 'reg'  with name 'name'

	w0	.req	r0
	wa	.req	r2
	wb	.req	r3
	wc	.req	r4
	xl	.req	r5
	xr	.req	r6
	xs	.req	r??

#	%define log_cfp_b 2
#	%define log_cfp_c 2

#	%define d_real	dq
#	%define cfp_c_val	8
#	%define log_cfp_c 2
#	%define cfp_m_	4294967295:1
	
#	%define	cfp_n_	32

#	%define	lods_w	lodsq
#	%define	lods_b	lodsb
#	%define movs_b	movsb
#	%define movs_w	movsq
#	%define stos_b	stosb
#	%define	stos_w	stosq
#	%define	cmps_b	cmpsb

#	%define	cdq	cqo	@ sign extend (64 bits)

#	flags
#	%define	flag_of	0x80
#	%define	flag_cf	0x01
#	%define	flag_ca	0x40
