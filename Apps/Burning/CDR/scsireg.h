/* @(#)scsireg.h	1.24 00/11/07 Copyright 1987 J. Schilling */
/*
 *	usefull definitions for dealing with CCS SCSI - devices
 *
 *	Copyright (c) 1987 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_SCG_SCSIREG_H
#define	_SCG_SCSIREG_H
#include "types.h"
#include "ecma_167.h"

#ifdef	__cplusplus
extern "C" {
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct	 {
	Ucbit	type		: 5;	/*  0 */
	Ucbit	qualifier	: 3;	/*  0 */

	Ucbit	type_modifier	: 7;	/*  1 */
	Ucbit	removable	: 1;	/*  1 */

	Ucbit	ansi_version	: 3;	/*  2 */
	Ucbit	ecma_version	: 3;	/*  2 */
	Ucbit	iso_version	: 2;	/*  2 */

	Ucbit	data_format	: 4;	/*  3 */
	Ucbit	res3_54		: 2;	/*  3 */
	Ucbit	termiop		: 1;	/*  3 */
	Ucbit	aenc		: 1;	/*  3 */

	Ucbit	add_len		: 8;	/*  4 */
	Ucbit	sense_len	: 8;	/*  5 */ /* only Emulex ??? */
	Ucbit	res2		: 8;	/*  6 */

	Ucbit	softreset	: 1;	/*  7 */
	Ucbit	cmdque		: 1;
	Ucbit	res7_2		: 1;
	Ucbit	linked		: 1;
	Ucbit	sync		: 1;
	Ucbit	wbus16		: 1;
	Ucbit	wbus32		: 1;
	Ucbit	reladr		: 1;	/*  7 */

	char	vendor_info[8];		/*  8 */
	char	prod_ident[16];		/* 16 */
	char	prod_revision[4];	/* 32 */
#ifdef	comment
	char	vendor_uniq[20];	/* 36 */
	char	reserved[40];		/* 56 */
#endif
}scsi_inquiry;					/* 96 */

#else					/* Motorola byteorder */

typedef struct	 {
	Ucbit	qualifier	: 3;	/*  0 */
	Ucbit	type		: 5;	/*  0 */

	Ucbit	removable	: 1;	/*  1 */
	Ucbit	type_modifier	: 7;	/*  1 */

	Ucbit	iso_version	: 2;	/*  2 */
	Ucbit	ecma_version	: 3;
	Ucbit	ansi_version	: 3;	/*  2 */

	Ucbit	aenc		: 1;	/*  3 */
	Ucbit	termiop		: 1;
	Ucbit	res3_54		: 2;
	Ucbit	data_format	: 4;	/*  3 */

	Ucbit	add_len		: 8;	/*  4 */
	Ucbit	sense_len	: 8;	/*  5 */ /* only Emulex ??? */
	Ucbit	res2		: 8;	/*  6 */
	Ucbit	reladr		: 1;	/*  7 */
	Ucbit	wbus32		: 1;
	Ucbit	wbus16		: 1;
	Ucbit	sync		: 1;
	Ucbit	linked		: 1;
	Ucbit	res7_2		: 1;
	Ucbit	cmdque		: 1;
	Ucbit	softreset	: 1;
	char	vendor_info[8];		/*  8 */
	char	prod_ident[16];		/* 16 */
	char	prod_revision[4];	/* 32 */
#ifdef	comment
	char	vendor_uniq[20];	/* 36 */
	char	reserved[40];		/* 56 */
#endif
}scsi_inquiry;					/* 96 */
#endif

/* Peripheral Device Qualifier */

#define	INQ_DEV_PRESENT	0x00		/* Physical device present */
#define	INQ_DEV_NOTPR	0x01		/* Physical device not present */
#define	INQ_DEV_RES	0x02		/* Reserved */
#define	INQ_DEV_NOTSUP	0x03		/* Logical unit not supported */

/* Peripheral Device Type */

#define	INQ_DASD	0x00		/* Direct-access device (disk) */
#define	INQ_SEQD	0x01		/* Sequential-access device (tape) */
#define	INQ_PRTD	0x02 		/* Printer device */
#define	INQ_PROCD	0x03 		/* Processor device */
#define	INQ_OPTD	0x04		/* Write once device (optical disk) */
#define	INQ_WORM	0x04		/* Write once device (optical disk) */
#define	INQ_ROMD	0x05		/* CD-ROM device */
#define	INQ_SCAN	0x06		/* Scanner device */
#define	INQ_OMEM	0x07		/* Optical Memory device */
#define	INQ_JUKE	0x08		/* Medium Changer device (jukebox) */
#define	INQ_COMM	0x09		/* Communications device */
#define	INQ_IT8_1	0x0A		/* IT8 */
#define	INQ_IT8_2	0x0B		/* IT8 */
#define	INQ_STARR	0x0C		/* Storage array device */
#define	INQ_ENCL	0x0D		/* Enclosure services device */
#define	INQ_NODEV	0x1F		/* Unknown or no device */
#define	INQ_NOTPR	0x1F		/* Logical unit not present (SCSI-1) */

typedef struct  {
	Uchar	dataLen[2];
	Uchar	res1;
	Uchar	res2;
}cd_atip_header;
#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {
	Ucbit	ref_speed	: 3;	/* Reference speed		*/
	Ucbit	res4_3		: 1;	/* Reserved			*/
	Ucbit	ind_wr_power: 3;	/* Indicative tgt writing power	*/
	Ucbit	res4_7		: 1;	/* Reserved (must be "1")	*/
	Ucbit	res5_05		: 6;	/* Reserved			*/
	Ucbit	uru			: 1;	/* Disk is for unrestricted use	*/
	Ucbit	res5_7		: 1;	/* Reserved (must be "0")	*/
	Ucbit	a3_v		: 1;	/* A 3 Values valid		*/
	Ucbit	a2_v		: 1;	/* A 2 Values valid		*/
	Ucbit	a1_v		: 1;	/* A 1 Values valid		*/
	Ucbit	sub_type	: 3;	/* Disc sub type		*/
	Ucbit	erasable	: 1;	/* Disk is erasable		*/
	Ucbit	res6_7		: 1;	/* Reserved (must be "1")	*/
	Ucbit	res3		: 8;
	Uchar	lead_in[4];			/* Lead in time			*/
	Uchar	lead_out[4];		/* Lead out time		*/
	Uchar	res15;				/* Reserved			*/
	Ucbit	clv_high	: 4;	/* Highes usable CLV recording speed */
	Ucbit	clv_low		: 3;	/* Lowest usable CLV recording speed */
	Ucbit	res16_7		: 1;	/* Reserved (must be "0")	*/
	Ucbit	res17_0		: 1;	/* Reserved			*/
	Ucbit	tgt_y_pow	: 3;	/* Tgt y val of the power mod fun */
	Ucbit	power_mult	: 3;	/* Power multiplication factor	*/
	Ucbit	res17_7		: 1;	/* Reserved (must be "0")	*/
	Ucbit	res_18_30	: 4;	/* Reserved			*/
	Ucbit	rerase_pwr_ratio: 3;	/* Recommended erase/write power*/
	Ucbit	res18_7		: 1;	/* Reserved (must be "1")	*/
	Uchar	res19;			/* Reserved			*/
	Uchar	a2[3];			/* A 2 Values			*/
	Uchar	res23;			/* Reserved			*/
	Uchar	a3[3];			/* A 3 Vaules			*/
	Uchar	res27;			/* Reserved			*/
}cd_atip_desc;
#else				/* Motorola bitorder */

typedef struct  {
	Ucbit	res4_7		: 1;	/* Reserved (must be "1")	*/
	Ucbit	ind_wr_power	: 3;	/* Indicative tgt writing power	*/
	Ucbit	res4_3		: 1;	/* Reserved			*/
	Ucbit	ref_speed	: 3;	/* Reference speed		*/
	Ucbit	res5_7		: 1;	/* Reserved (must be "0")	*/
	Ucbit	uru		: 1;	/* Disk is for unrestricted use	*/
	Ucbit	res5_05		: 6;	/* Reserved			*/
	Ucbit	res6_7		: 1;	/* Reserved (must be "1")	*/
	Ucbit	erasable	: 1;	/* Disk is erasable		*/
	Ucbit	sub_type	: 3;	/* Disc sub type		*/
	Ucbit	a1_v		: 1;	/* A 1 Values valid		*/
	Ucbit	a2_v		: 1;	/* A 2 Values valid		*/
	Ucbit	a3_v		: 1;	/* A 3 Values valid		*/
	Ucbit				: 8;
	Uchar	lead_in[4];		/* Lead in time			*/
	Uchar	lead_out[4];		/* Lead out time		*/
	Uchar	res15;			/* Reserved			*/
	Ucbit	res16_7		: 1;	/* Reserved (must be "0")	*/
	Ucbit	clv_low		: 3;	/* Lowest usable CLV recording speed */
	Ucbit	clv_high	: 4;	/* Highes usable CLV recording speed */
	Ucbit	res17_7		: 1;	/* Reserved (must be "0")	*/
	Ucbit	power_mult	: 3;	/* Power multiplication factor	*/
	Ucbit	tgt_y_pow	: 3;	/* Tgt y val of the power mod fun */
	Ucbit	res17_0		: 1;	/* Reserved			*/
	Ucbit	res18_7		: 1;	/* Reserved (must be "1")	*/
	Ucbit	rerase_pwr_ratio: 3;	/* Recommended erase/write power*/
	Ucbit	res_18_30	: 4;	/* Reserved			*/
	Uchar	res19;			/* Reserved			*/
	Uchar	a2[3];			/* A 2 Values			*/
	Uchar	res23;			/* Reserved			*/
	Uchar	a3[3];			/* A 3 Vaules			*/
	Uchar	res27;			/* Reserved			*/
}cd_atip_desc;

#endif

typedef struct {
	cd_atip_header	header;
	cd_atip_desc		desc;
}cd_atip;


typedef struct  {
	Uchar	dataLen[2];
	Uchar	firstSession;
	Uchar	lastSession;
}cd_toc_header;

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct {
	Uchar	res1;
	Ucbit	ctrl		: 4;
	Ucbit	adr			: 4;
	Uchar	firstTrack;
	Uchar	res2;
	Uchar	lba[4];
}cd_toc_00;

#else					/* Motorola byteorder */

typedef struct  {
	Uchar	res1;
	Ucbit	adr			: 4;
	Ucbit	ctrl		: 4;
	Uchar	firstTrack;
	Uchar	res2;
	int		lba;
}cd_toc_00;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {
	Uchar	res0;
	Ucbit	ctrl		: 4;
	Ucbit	adr			: 4;
	Uchar	TNO;
	Uchar	point;
	Uchar	min;
	Uchar	sec;
	Uchar	frame;
	Uchar	zero;
	Uchar	pmin;
	Uchar	psec;
	Uchar	pframe;	
}cd_PMA_desc;

#else					/* Motorola byteorder */

typedef struct cd_PMA_desc {
	Uchar	res0;
	Ucbit	adr			: 4;
	Ucbit	ctrl		: 4;
	Uchar	TNO;
	Uchar	point;
	Uchar	min;
	Uchar	sec;
	Uchar	frame;
	Uchar	zero;
	Uchar	pmin;
	Uchar	psec;
	Uchar	pframe;	
}cd_PMA_desc;
#endif

typedef struct {
	cd_atip_header	header;
	cd_PMA_desc		desc;
}cd_pma;

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {
	Ucbit	sense_data_len	: 8;
	Uchar	medium_type;
	Ucbit	res2		: 4;
	Ucbit	cache		: 1;
	Ucbit	res		: 2;
	Ucbit	write_prot	: 1;
	Uchar	blockdesc_len;
}scsi_mode_header;

#else					/* Motorola byteorder */

typedef struct{
	Ucbit	sense_data_len	: 8;
	Uchar	medium_type;
	Ucbit	write_prot	: 1;
	Ucbit	res		: 2;
	Ucbit	cache		: 1;
	Ucbit	res2		: 4;
	Uchar	blockdesc_len;
}scsi_mode_header;
#endif

typedef struct  {
	Ucbit	sense_data_len	: 8;
	Uchar	medium_type;
	Ucbit	res2		: 8;
	Uchar	blockdesc_len;
}scsi_modesel_header;

typedef struct {
	Uchar	density;
	Uchar	nlblock[3];
	Ucbit	res		: 8;
	Uchar	lblen[3];
}scsi_mode_blockdesc;

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {
	Uchar	listformat;
	Uchar	ncyl[2];
	Uchar	nhead;
	Uchar	start_red_wcurrent[2];
	Uchar	start_precomp[2];
	Uchar	landing_zone;
	Uchar	step_rate;
	Ucbit			: 2;
	Ucbit	hard_sec	: 1;
	Ucbit	fixed_media	: 1;
	Ucbit			: 4;
	Uchar	sect_per_trk;
}acb_mode_data;

#else					/* Motorola byteorder */

typedef struct {
	Uchar	listformat;
	Uchar	ncyl[2];
	Uchar	nhead;
	Uchar	start_red_wcurrent[2];
	Uchar	start_precomp[2];
	Uchar	landing_zone;
	Uchar	step_rate;
	Ucbit			: 4;
	Ucbit	fixed_media	: 1;
	Ucbit	hard_sec	: 1;
	Ucbit			: 2;
	Uchar	sect_per_trk;
}acb_mode_data;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {
	Ucbit	p_code		: 6;
	Ucbit	res			: 1;
	Ucbit	parsave		: 1;
	Uchar	p_len;
}scsi_mode_page_header;

/*
 * This is a hack that allows mode pages without
 * any further bitfileds to be defined bitorder independent.
 */
#define	MP_P_CODE			\
	Ucbit	p_code		: 6;	\
	Ucbit	p_res		: 1;	\
	Ucbit	parsave		: 1

#else					/* Motorola byteorder */

typedef struct{
	Ucbit	parsave		: 1;
	Ucbit	res		: 1;
	Ucbit	p_code		: 6;
	Uchar	p_len;
} scsi_mode_page_header ;

/*
 * This is a hack that allows mode pages without
 * any further bitfileds to be defined bitorder independent.
 */
#define	MP_P_CODE			\
	Ucbit	parsave		: 1;	\
	Ucbit	p_res		: 1;	\
	Ucbit	p_code		: 6

#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Error recovery Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Ucbit	term_on_rec_err	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	en_early_corr	: 1;
	Ucbit	read_continuous	: 1;
	Ucbit	tranfer_block	: 1;
	Ucbit	en_auto_reall_r	: 1;
	Ucbit	en_auto_reall_w	: 1;	/* Byte 2 */
	Uchar	rd_retry_count;		/* Byte 3 */
	Uchar	correction_span;
	char	head_offset_count;
	char	data_strobe_offset;
	Uchar	res;
	Uchar	wr_retry_count;
	Uchar	res_tape[2];
	Uchar	recov_timelim[2];
}scsi_mode_page_01;

#else					/* Motorola byteorder */

typedef struct  {		/* Error recovery Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	en_auto_reall_w	: 1;	/* Byte 2 */
	Ucbit	en_auto_reall_r	: 1;
	Ucbit	tranfer_block	: 1;
	Ucbit	read_continuous	: 1;
	Ucbit	en_early_corr	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	term_on_rec_err	: 1;
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Uchar	rd_retry_count;		/* Byte 3 */
	Uchar	correction_span;
	char	head_offset_count;
	char	data_strobe_offset;
	Uchar	res;
	Uchar	wr_retry_count;
	Uchar	res_tape[2];
	Uchar	recov_timelim[2];
}scsi_mode_page_01;
#endif


#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Device dis/re connect Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 16 Bytes */
	Uchar	buf_full_ratio;
	Uchar	buf_empt_ratio;
	Uchar	bus_inact_limit[2];
	Uchar	disc_time_limit[2];
	Uchar	conn_time_limit[2];
	Uchar	max_burst_size[2];	/* Start SCSI-2 */
	Ucbit	data_tr_dis_ctl	: 2;
	Ucbit			: 6;
	Uchar	res[3];
}scsi_mode_page_02;

#else					/* Motorola byteorder */

typedef struct {		/* Device dis/re connect Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 16 Bytes */
	Uchar	buf_full_ratio;
	Uchar	buf_empt_ratio;
	Uchar	bus_inact_limit[2];
	Uchar	disc_time_limit[2];
	Uchar	conn_time_limit[2];
	Uchar	max_burst_size[2];	/* Start SCSI-2 */
	Ucbit			: 6;
	Ucbit	data_tr_dis_ctl	: 2;
	Uchar	res[3];
}scsi_mode_page_02;
#endif

#define	DTDC_DATADONE	0x01		/*
					 * Target may not disconnect once
					 * data transfer is started until
					 * all data successfully transferred.
					 */

#define	DTDC_CMDDONE	0x03		/*
					 * Target may not disconnect once
					 * data transfer is started until
					 * command completed.
					 */


#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Direct access format Paramters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	trk_per_zone[2];
	Uchar	alt_sec_per_zone[2];
	Uchar	alt_trk_per_zone[2];
	Uchar	alt_trk_per_vol[2];
	Uchar	sect_per_trk[2];
	Uchar	bytes_per_phys_sect[2];
	Uchar	interleave[2];
	Uchar	trk_skew[2];
	Uchar	cyl_skew[2];
	Ucbit			: 3;
	Ucbit	inhibit_save	: 1;
	Ucbit	fmt_by_surface	: 1;
	Ucbit	removable	: 1;
	Ucbit	hard_sec	: 1;
	Ucbit	soft_sec	: 1;
	Uchar	res[3];
}scsi_mode_page_03;

#else					/* Motorola byteorder */

typedef struct {		/* Direct access format Paramters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	trk_per_zone[2];
	Uchar	alt_sec_per_zone[2];
	Uchar	alt_trk_per_zone[2];
	Uchar	alt_trk_per_vol[2];
	Uchar	sect_per_trk[2];
	Uchar	bytes_per_phys_sect[2];
	Uchar	interleave[2];
	Uchar	trk_skew[2];
	Uchar	cyl_skew[2];
	Ucbit	soft_sec	: 1;
	Ucbit	hard_sec	: 1;
	Ucbit	removable	: 1;
	Ucbit	fmt_by_surface	: 1;
	Ucbit	inhibit_save	: 1;
	Ucbit			: 3;
	Uchar	res[3];
}scsi_mode_page_03;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Rigid disk Geometry Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	ncyl[3];
	Uchar	nhead;
	Uchar	start_precomp[3];
	Uchar	start_red_wcurrent[3];
	Uchar	step_rate[2];
	Uchar	landing_zone[3];
	Ucbit	rot_pos_locking	: 2;	/* Start SCSI-2 */
	Ucbit			: 6;	/* Start SCSI-2 */
	Uchar	rotational_off;
	Uchar	res1;
	Uchar	rotation_rate[2];
	Uchar	res2[2];
}scsi_mode_page_04;

#else					/* Motorola byteorder */

typedef struct  {		/* Rigid disk Geometry Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	ncyl[3];
	Uchar	nhead;
	Uchar	start_precomp[3];
	Uchar	start_red_wcurrent[3];
	Uchar	step_rate[2];
	Uchar	landing_zone[3];
	Ucbit			: 6;	/* Start SCSI-2 */
	Ucbit	rot_pos_locking	: 2;	/* Start SCSI-2 */
	Uchar	rotational_off;
	Uchar	res1;
	Uchar	rotation_rate[2];
	Uchar	res2[2];
}scsi_mode_page_04;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Flexible disk Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x1E = 32 Bytes */
	Uchar	transfer_rate[2];
	Uchar	nhead;
	Uchar	sect_per_trk;
	Uchar	bytes_per_phys_sect[2];
	Uchar	ncyl[2];
	Uchar	start_precomp[2];
	Uchar	start_red_wcurrent[2];
	Uchar	step_rate[2];
	Uchar	step_pulse_width;
	Uchar	head_settle_delay[2];
	Uchar	motor_on_delay;
	Uchar	motor_off_delay;
	Ucbit	spc		: 4;
	Ucbit			: 4;
	Ucbit			: 5;
	Ucbit	mo		: 1;
	Ucbit	ssn		: 1;
	Ucbit	trdy		: 1;
	Uchar	write_compensation;
	Uchar	head_load_delay;
	Uchar	head_unload_delay;
	Ucbit	pin_2_use	: 4;
	Ucbit	pin_34_use	: 4;
	Ucbit	pin_1_use	: 4;
	Ucbit	pin_4_use	: 4;
	Uchar	rotation_rate[2];
	Uchar	res[2];
}scsi_mode_page_05;

#else					/* Motorola byteorder */

typedef struct  {		/* Flexible disk Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x1E = 32 Bytes */
	Uchar	transfer_rate[2];
	Uchar	nhead;
	Uchar	sect_per_trk;
	Uchar	bytes_per_phys_sect[2];
	Uchar	ncyl[2];
	Uchar	start_precomp[2];
	Uchar	start_red_wcurrent[2];
	Uchar	step_rate[2];
	Uchar	step_pulse_width;
	Uchar	head_settle_delay[2];
	Uchar	motor_on_delay;
	Uchar	motor_off_delay;
	Ucbit	trdy		: 1;
	Ucbit	ssn		: 1;
	Ucbit	mo		: 1;
	Ucbit			: 5;
	Ucbit			: 4;
	Ucbit	spc		: 4;
	Uchar	write_compensation;
	Uchar	head_load_delay;
	Uchar	head_unload_delay;
	Ucbit	pin_34_use	: 4;
	Ucbit	pin_2_use	: 4;
	Ucbit	pin_4_use	: 4;
	Ucbit	pin_1_use	: 4;
	Uchar	rotation_rate[2];
	Uchar	res[2];
}scsi_mode_page_05;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Verify Error recovery */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Ucbit	term_on_rec_err	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	en_early_corr	: 1;
	Ucbit	res		: 4;	/* Byte 2 */
	Uchar	ve_retry_count;		/* Byte 3 */
	Uchar	ve_correction_span;
	char	res2[5];		/* Byte 5 */
	Uchar	ve_recov_timelim[2];	/* Byte 10 */
}scsi_mode_page_07;

#else					/* Motorola byteorder */

typedef struct  {		/* Verify Error recovery */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	res		: 4;	/* Byte 2 */
	Ucbit	en_early_corr	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	term_on_rec_err	: 1;
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Uchar	ve_retry_count;		/* Byte 3 */
	Uchar	ve_correction_span;
	char	res2[5];		/* Byte 5 */
	Uchar	ve_recov_timelim[2];	/* Byte 10 */
}scsi_mode_page_07;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	disa_rd_cache	: 1;	/* Byte 2 */
	Ucbit	muliple_fact	: 1;
	Ucbit	en_wt_cache	: 1;
	Ucbit	res		: 5;	/* Byte 2 */
	Ucbit	wt_ret_pri	: 4;	/* Byte 3 */
	Ucbit	demand_rd_ret_pri: 4;	/* Byte 3 */
	Uchar	disa_pref_tr_len[2];	/* Byte 4 */
	Uchar	min_pref[2];		/* Byte 6 */
	Uchar	max_pref[2];		/* Byte 8 */
	Uchar	max_pref_ceiling[2];	/* Byte 10 */
}scsi_mode_page_08;

#else					/* Motorola byteorder */

typedef struct  {		/* Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	res		: 5;	/* Byte 2 */
	Ucbit	en_wt_cache	: 1;
	Ucbit	muliple_fact	: 1;
	Ucbit	disa_rd_cache	: 1;	/* Byte 2 */
	Ucbit	demand_rd_ret_pri: 4;	/* Byte 3 */
	Ucbit	wt_ret_pri	: 4;
	Uchar	disa_pref_tr_len[2];	/* Byte 4 */
	Uchar	min_pref[2];		/* Byte 6 */
	Uchar	max_pref[2];		/* Byte 8 */
	Uchar	max_pref_ceiling[2];	/* Byte 10 */
}scsi_mode_page_08;
#endif

typedef struct  {		/* Peripheral device Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* >= 0x06 = 8 Bytes */
	Uchar	interface_id[2];	/* Byte 2 */
	Uchar	res[4];			/* Byte 4 */
	Uchar	vendor_specific[1];	/* Byte 8 */
}scsi_mode_page_09;

#define	PDEV_SCSI	0x0000		/* scsi interface */
#define	PDEV_SMD	0x0001		/* SMD interface */
#define	PDEV_ESDI	0x0002		/* ESDI interface */
#define	PDEV_IPI2	0x0003		/* IPI-2 interface */
#define	PDEV_IPI3	0x0004		/* IPI-3 interface */

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Common device Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Ucbit	rep_log_exeption: 1;	/* Byte 2 */
	Ucbit	res		: 7;	/* Byte 2 */
	Ucbit	dis_queuing	: 1;	/* Byte 3 */
	Ucbit	queuing_err_man	: 1;
	Ucbit	res2		: 2;
	Ucbit	queue_alg_mod	: 4;	/* Byte 3 */
	Ucbit	EAENP		: 1;	/* Byte 4 */
	Ucbit	UAENP		: 1;
	Ucbit	RAENP		: 1;
	Ucbit	res3		: 4;
	Ucbit	en_ext_cont_all	: 1;	/* Byte 4 */
	Ucbit	res4		: 8;
	Uchar	ready_aen_hold_per[2];	/* Byte 6 */
}scsi_mode_page_0A;

#else					/* Motorola byteorder */

typedef struct  {		/* Common device Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Ucbit	res		: 7;	/* Byte 2 */
	Ucbit	rep_log_exeption: 1;	/* Byte 2 */
	Ucbit	queue_alg_mod	: 4;	/* Byte 3 */
	Ucbit	res2		: 2;
	Ucbit	queuing_err_man	: 1;
	Ucbit	dis_queuing	: 1;	/* Byte 3 */
	Ucbit	en_ext_cont_all	: 1;	/* Byte 4 */
	Ucbit	res3		: 4;
	Ucbit	RAENP		: 1;
	Ucbit	UAENP		: 1;
	Ucbit	EAENP		: 1;	/* Byte 4 */
	Ucbit	res4		: 8;
	Uchar	ready_aen_hold_per[2];	/* Byte 6 */
}scsi_mode_page_0A;
#endif

#define	CTRL_QMOD_RESTRICT	0x0
#define	CTRL_QMOD_UNRESTRICT	0x1


typedef struct  {		/* Medium Types Supported Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Uchar	res[2];			/* Byte 2 */
	Uchar	medium_one_supp;	/* Byte 4 */
	Uchar	medium_two_supp;	/* Byte 5 */
	Uchar	medium_three_supp;	/* Byte 6 */
	Uchar	medium_four_supp;	/* Byte 7 */
}scsi_mode_page_0B;

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Notch & Partition Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Ucbit	res		: 6;	/* Byte 2 */
	Ucbit	logical_notch	: 1;
	Ucbit	notched_drive	: 1;	/* Byte 2 */
	Uchar	res2;			/* Byte 3 */
	Uchar	max_notches[2];		/* Byte 4  */
	Uchar	active_notch[2];	/* Byte 6  */
	Uchar	starting_boundary[4];	/* Byte 8  */
	Uchar	ending_boundary[4];	/* Byte 12 */
	Uchar	pages_notched[8];	/* Byte 16 */
}scsi_mode_page_0C;

#else					/* Motorola byteorder */

typedef struct  {		/* Notch & Partition Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Ucbit	notched_drive	: 1;	/* Byte 2 */
	Ucbit	logical_notch	: 1;
	Ucbit	res		: 6;	/* Byte 2 */
	Uchar	res2;			/* Byte 3 */
	Uchar	max_notches[2];		/* Byte 4  */
	Uchar	active_notch[2];	/* Byte 6  */
	Uchar	starting_boundary[4];	/* Byte 8  */
	Uchar	ending_boundary[4];	/* Byte 12 */
	Uchar	pages_notched[8];	/* Byte 16 */
}scsi_mode_page_0C;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* CD-ROM Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Uchar	res;			/* Byte 2 */
	Ucbit	inact_timer_mult: 4;	/* Byte 3 */
	Ucbit	res2		: 4;	/* Byte 3 */
	Uchar	s_un_per_m_un[2];	/* Byte 4  */
	Uchar	f_un_per_s_un[2];	/* Byte 6  */
}scsi_mode_page_0D;

#else					/* Motorola byteorder */

typedef struct  {		/* CD-ROM Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Uchar	res;			/* Byte 2 */
	Ucbit	res2		: 4;	/* Byte 3 */
	Ucbit	inact_timer_mult: 4;	/* Byte 3 */
	Uchar	s_un_per_m_un[2];	/* Byte 4  */
	Uchar	f_un_per_s_un[2];	/* Byte 6  */
}scsi_mode_page_0D;
#endif

typedef struct  {		/* Sony Format Mode Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Uchar	format_mode;
	Uchar	format_type;
#define	num_bands	user_band_size	/* Gilt bei Type 1 */
	Uchar	user_band_size[4];	/* Gilt bei Type 0 */
	Uchar	spare_band_size[2];
	Uchar	res[2];
}sony_mode_page_20;

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* Toshiba Speed Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x01 = 3 Bytes */
	Ucbit	speed		: 1;
	Ucbit	res		: 7;
}toshiba_mode_page_20;

#else					/* Motorola byteorder */

typedef struct  {		/* Toshiba Speed Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x01 = 3 Bytes */
	Ucbit	res		: 7;
	Ucbit	speed		: 1;
}toshiba_mode_page_20;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct  {		/* CCS Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 14 Bytes */

	Ucbit	cache_table_size: 4;	/* Byte 3 */
	Ucbit	cache_en	: 1;
	Ucbit	res2		: 1;
	Ucbit	wr_index_en	: 1;
	Ucbit	res		: 1;	/* Byte 3 */
	Uchar	threshold;		/* Byte 4 Prefetch threshold */
	Uchar	max_prefetch;		/* Byte 5 Max. prefetch */
	Uchar	max_multiplier;		/* Byte 6 Max. prefetch multiplier */
	Uchar	min_prefetch;		/* Byte 7 Min. prefetch */
	Uchar	min_multiplier;		/* Byte 8 Min. prefetch multiplier */
	Uchar	res3[8];		/* Byte 9 */
}ccs_mode_page_38;

#else					/* Motorola byteorder */

typedef struct  {		/* CCS Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 14 Bytes */

	Ucbit	res		: 1;	/* Byte 3 */
	Ucbit	wr_index_en	: 1;
	Ucbit	res2		: 1;
	Ucbit	cache_en	: 1;
	Ucbit	cache_table_size: 4;	/* Byte 3 */
	Uchar	threshold;		/* Byte 4 Prefetch threshold */
	Uchar	max_prefetch;		/* Byte 5 Max. prefetch */
	Uchar	max_multiplier;		/* Byte 6 Max. prefetch multiplier */
	Uchar	min_prefetch;		/* Byte 7 Min. prefetch */
	Uchar	min_multiplier;		/* Byte 8 Min. prefetch multiplier */
	Uchar	res3[8];		/* Byte 9 */
}ccs_mode_page_38;
#endif

#if defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */


typedef struct
{
	Uchar	fileNumber;
	Uchar	channelNumber;
	Uchar	subMode;
	Uchar	coding;
}sub_header;



typedef struct {		/* write parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x32 = 50 Bytes */
	Ucbit	write_type	: 4;	/* Session write type (PACKET/TAO...)*/
	Ucbit	test_write	: 1;	/* Do not actually write data	     */
	Ucbit	ls_v		: 1;
	Ucbit	BUFE		: 1;
	Ucbit	res_2		: 1;
	Ucbit	track_mode	: 4;	/* Track mode (Q-sub control nibble) */
	Ucbit	copy		: 1;	/* 1st higher gen of copy prot track ~*/
	Ucbit	fp		: 1;	/* Fixed packed (if in packet mode)  */
	Ucbit	multi_session	: 2;	/* Multi session write type	     */
	Ucbit	dbtype		: 4;	/* Data block type		     */
	Ucbit	res_4		: 4;	/* Reserved			     */
	Uchar	link_size;		/* link size			     */
	Uchar	res_6;			/* Reserved			     */
	Ucbit	host_appl_code	: 6;	/* Host application code of disk     */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Uchar	session_format;		/* Session format (DA/CDI/XA)	     */
	Uchar	res_9;			/* Reserved			     */
	Uchar	packet_size[4];		/* # of user datablocks/fixed packet */
	Uchar	audio_pause_len[2];	/* # of blocks where index is zero   */
	Uchar	media_cat_number[16];	/* Media catalog Number (MCN)	     */
	Uchar	ISRC[16];		/* ISRC for this track		     */
	sub_header	sub_h;
	Uchar	vendor_uniq[4];
}cd_mode_page_05;

#else				/* Motorola byteorder */

typedef struct  {		/* write parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x32 = 50 Bytes */
	Ucbit	res_2		: 1;
	Ucbit	BUFE		: 1;
	Ucbit	ls_v		: 1;
	Ucbit	test_write	: 1;	/* Do not actually write data	     */
	Ucbit	write_type	: 4;	/* Session write type (PACKET/TAO...)*/
	Ucbit	multi_session	: 2;	/* Multi session write type	     */
	Ucbit	fp		: 1;	/* Fixed packed (if in packet mode)  */
	Ucbit	copy		: 1;	/* 1st higher gen of copy prot track */
	Ucbit	track_mode	: 4;	/* Track mode (Q-sub control nibble) */
	Ucbit	res_4		: 4;	/* Reserved			     */
	Ucbit	dbtype		: 4;	/* Data block type		     */
	Uchar	link_size;		/* link size			     */
	Uchar	res_6;			/* Reserved			     */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Ucbit	host_appl_code	: 6;	/* Host application code of disk     */
	Uchar	session_format;		/* Session format (DA/CDI/XA)	     */
	Uchar	res_9;			/* Reserved			     */
	Uchar	packet_size[4];		/* # of user datablocks/fixed packet */
	Uchar	audio_pause_len[2];	/* # of blocks where index is zero   */
	Uchar	media_cat_number[16];	/* Media catalog Number (MCN)	     */
	Uchar	ISRC[16];		/* ISRC for this track		     */
	Uchar	sub_header[4];
	Uchar	vendor_uniq[4];
}cd_mode_page_05;

#endif

#if defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct {		/* CD Cap / mech status */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x14 = 20 Bytes */
	Ucbit	cd_r_read	: 1;	/* Reads CD-R  media		     */
	Ucbit	cd_rw_read	: 1;	/* Reads CD-RW media		     */
	Ucbit	method2		: 1;	/* Reads fixed packet method2 media  */
	Ucbit	dvd_rom_read	: 1;	/* Reads DVD ROM media		     */
	Ucbit	dvd_r_read	: 1;	/* Reads DVD-R media		     */
	Ucbit	dvd_ram_read	: 1;	/* Reads DVD-RAM media		     */
	Ucbit	res_2_67	: 2;	/* Reserved			     */
	Ucbit	cd_r_write	: 1;	/* Supports writing CD-R  media	     */
	Ucbit	cd_rw_write	: 1;	/* Supports writing CD-RW media	     */
	Ucbit	test_write	: 1;	/* Supports emulation write	     */
	Ucbit	res_3_3		: 1;	/* Reserved			     */
	Ucbit	dvd_r_write	: 1;	/* Supports writing DVD-R media	     */
	Ucbit	dvd_ram_write	: 1;	/* Supports writing DVD-RAM media    */
	Ucbit	res_3_67	: 2;	/* Reserved			     */
	Ucbit	audio_play	: 1;	/* Supports Audio play operation     */
	Ucbit	composite	: 1;	/* Deliveres composite A/V stream    */
	Ucbit	digital_port_2	: 1;	/* Supports digital output on port 2 */
	Ucbit	digital_port_1	: 1;	/* Supports digital output on port 1 */
	Ucbit	mode_2_form_1	: 1;	/* Reads Mode-2 form 1 media (XA)    */
	Ucbit	mode_2_form_2	: 1;	/* Reads Mode-2 form 2 media	     */
	Ucbit	multi_session	: 1;	/* Reads multi-session media	     */
	Ucbit	res_4		: 1;	/* Reserved			     */
	Ucbit	cd_da_supported	: 1;	/* Reads audio data with READ CD cmd */
	Ucbit	cd_da_accurate	: 1;	/* READ CD data stream is accurate   */
	Ucbit	rw_supported	: 1;	/* Reads R-W sub channel information */
	Ucbit	rw_deint_corr	: 1;	/* Reads de-interleved R-W sub chan  */
	Ucbit	c2_pointers	: 1;	/* Supports C2 error pointers	     */
	Ucbit	ISRC		: 1;	/* Reads ISRC information	     */
	Ucbit	UPC		: 1;	/* Reads media catalog number (UPC)  */
	Ucbit	read_bar_code	: 1;	/* Supports reading bar codes	     */
	Ucbit	lock		: 1;	/* PREVENT/ALLOW may lock media	     */
	Ucbit	lock_state	: 1;	/* Lock state 0=unlocked 1=locked    */
	Ucbit	prevent_jumper	: 1;	/* State of prev/allow jumper 0=pres */
	Ucbit	eject		: 1;	/* Ejects disc/cartr with STOP LoEj  */
	Ucbit	res_6_4		: 1;	/* Reserved			     */
	Ucbit	loading_type	: 3;	/* Loading mechanism type	     */
	Ucbit	sep_chan_vol	: 1;	/* Vol controls each channel separat */
	Ucbit	sep_chan_mute	: 1;	/* Mute controls each channel separat*/
	Ucbit	disk_present_rep: 1;	/* Changer supports disk present rep */
	Ucbit	sw_slot_sel	: 1;	/* Load empty slot in changer	     */
	Ucbit	side_change	: 1;	/* Side change capable		     */
	Ucbit	pw_in_lead_in	: 1;	/* Reads raw P-W sucode from lead in */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Uchar	max_read_speed[2];	/* Max. read speed in KB/s	     */
	Uchar	num_vol_levels[2];	/* # of supported volume levels	     */
	Uchar	buffer_size[2];		/* Buffer size for the data in KB    */
	Uchar	cur_read_speed[2];	/* Current read speed in KB/s	     */
	Uchar	res_16;			/* Reserved			     */
	Ucbit	res_17_0	: 1;	/* Reserved			     */
	Ucbit	BCK		: 1;	/* Data valid on falling edge of BCK */
	Ucbit	RCK		: 1;	/* Set: HIGH high LRCK=left channel  */
	Ucbit	LSBF		: 1;	/* Set: LSB first Clear: MSB first   */
	Ucbit	length		: 2;	/* 0=32BCKs 1=16BCKs 2=24BCKs 3=24I2c*/
	Ucbit	res_17		: 2;	/* Reserved			     */
	Uchar	max_write_speed[2];	/* Max. write speed supported in KB/s*/
	Uchar	cur_write_speed[2];	/* Current write speed in KB/s	     */
}cd_mode_page_2A;

#else				/* Motorola byteorder */

typedef struct  {		/* CD Cap / mech status */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x14 = 20 Bytes */
	Ucbit	res_2_67	: 2;	/* Reserved			     */
	Ucbit	dvd_ram_read	: 1;	/* Reads DVD-RAM media		     */
	Ucbit	dvd_r_read	: 1;	/* Reads DVD-R media		     */
	Ucbit	dvd_rom_read	: 1;	/* Reads DVD ROM media		     */
	Ucbit	method2		: 1;	/* Reads fixed packet method2 media  */
	Ucbit	cd_rw_read	: 1;	/* Reads CD-RW media		     */
	Ucbit	cd_r_read	: 1;	/* Reads CD-R  media		     */
	Ucbit	res_3_67	: 2;	/* Reserved			     */
	Ucbit	dvd_ram_write	: 1;	/* Supports writing DVD-RAM media    */
	Ucbit	dvd_r_write	: 1;	/* Supports writing DVD-R media	     */
	Ucbit	res_3_3		: 1;	/* Reserved			     */
	Ucbit	test_write	: 1;	/* Supports emulation write	     */
	Ucbit	cd_rw_write	: 1;	/* Supports writing CD-RW media	     */
	Ucbit	cd_r_write	: 1;	/* Supports writing CD-R  media	     */
	Ucbit	res_4		: 1;	/* Reserved			     */
	Ucbit	multi_session	: 1;	/* Reads multi-session media	     */
	Ucbit	mode_2_form_2	: 1;	/* Reads Mode-2 form 2 media	     */
	Ucbit	mode_2_form_1	: 1;	/* Reads Mode-2 form 1 media (XA)    */
	Ucbit	digital_port_1	: 1;	/* Supports digital output on port 1 */
	Ucbit	digital_port_2	: 1;	/* Supports digital output on port 2 */
	Ucbit	composite	: 1;	/* Deliveres composite A/V stream    */
	Ucbit	audio_play	: 1;	/* Supports Audio play operation     */
	Ucbit	read_bar_code	: 1;	/* Supports reading bar codes	     */
	Ucbit	UPC		: 1;	/* Reads media catalog number (UPC)  */
	Ucbit	ISRC		: 1;	/* Reads ISRC information	     */
	Ucbit	c2_pointers	: 1;	/* Supports C2 error pointers	     */
	Ucbit	rw_deint_corr	: 1;	/* Reads de-interleved R-W sub chan  */
	Ucbit	rw_supported	: 1;	/* Reads R-W sub channel information */
	Ucbit	cd_da_accurate	: 1;	/* READ CD data stream is accurate   */
	Ucbit	cd_da_supported	: 1;	/* Reads audio data with READ CD cmd */
	Ucbit	loading_type	: 3;	/* Loading mechanism type	     */
	Ucbit	res_6_4		: 1;	/* Reserved			     */
	Ucbit	eject		: 1;	/* Ejects disc/cartr with STOP LoEj  */
	Ucbit	prevent_jumper	: 1;	/* State of prev/allow jumper 0=pres */
	Ucbit	lock_state	: 1;	/* Lock state 0=unlocked 1=locked    */
	Ucbit	lock		: 1;	/* PREVENT/ALLOW may lock media	     */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Ucbit	pw_in_lead_in	: 1;	/* Reads raw P-W sucode from lead in */
	Ucbit	side_change	: 1;	/* Side change capable		     */
	Ucbit	sw_slot_sel	: 1;	/* Load empty slot in changer	     */
	Ucbit	disk_present_rep: 1;	/* Changer supports disk present rep */
	Ucbit	sep_chan_mute	: 1;	/* Mute controls each channel separat*/
	Ucbit	sep_chan_vol	: 1;	/* Vol controls each channel separat */
	Uchar	max_read_speed[2];	/* Max. read speed in KB/s	     */
	Uchar	num_vol_levels[2];	/* # of supported volume levels	     */
	Uchar	buffer_size[2];		/* Buffer size for the data in KB    */
	Uchar	cur_read_speed[2];	/* Current read speed in KB/s	     */
	Uchar	res_16;			/* Reserved			     */
	Ucbit	res_17		: 2;	/* Reserved			     */
	Ucbit	length		: 2;	/* 0=32BCKs 1=16BCKs 2=24BCKs 3=24I2c*/
	Ucbit	LSBF		: 1;	/* Set: LSB first Clear: MSB first   */
	Ucbit	RCK		: 1;	/* Set: HIGH high LRCK=left channel  */
	Ucbit	BCK		: 1;	/* Data valid on falling edge of BCK */
	Ucbit	res_17_0	: 1;	/* Reserved			     */
	Uchar	max_write_speed[2];	/* Max. write speed supported in KB/s*/
	Uchar	cur_write_speed[2];	/* Current write speed in KB/s	     */
}cd_mode_page_2A;

#endif

#define	LT_CADDY	0
#define	LT_TRAY		1
#define	LT_POP_UP	2
#define	LT_RES3		3
#define	LT_CHANGER_IND	4
#define	LT_CHANGER_CART	5
#define	LT_RES6		6
#define	LT_RES7		7


typedef struct  {
	scsi_mode_header		header;
	scsi_mode_blockdesc	blockdesc;
	union	pagex	{
		acb_mode_data		acb;
		scsi_mode_page_01	page1;
		scsi_mode_page_02	page2;
		scsi_mode_page_03	page3;
		scsi_mode_page_04	page4;
		scsi_mode_page_05	page5;
		scsi_mode_page_07	page7;
		scsi_mode_page_08	page8;
		scsi_mode_page_09	page9;
		scsi_mode_page_0A	pageA;
		scsi_mode_page_0B	pageB;
		scsi_mode_page_0C	pageC;
		scsi_mode_page_0D	pageD;
		sony_mode_page_20	sony20;
		toshiba_mode_page_20	toshiba20;
		ccs_mode_page_38		ccs38;
	} pagex;
}scsi_mode_data;

typedef struct  {
	int	c_baddr;		/* must convert byteorder!! */
	int	c_bsize;		/* must convert byteorder!! */
}scsi_capacity;

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct {
	Ucbit		: 8;
	Ucbit	format	: 3;
	Ucbit	gdl	: 1;
	Ucbit	mdl	: 1;
	Ucbit		: 3;
	Uchar	length[2];
}scsi_def_header;

#else					/* Motorola byteorder */

typedef struct  {
	Ucbit		: 8;
	Ucbit		: 3;
	Ucbit	mdl	: 1;
	Ucbit	gdl	: 1;
	Ucbit	format	: 3;
	Uchar	length[2];
}scsi_def_header;
#endif


#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct {
	Ucbit	res		: 8;	/* Adaptec 5500: 1 --> format track */
	Ucbit	vu		: 1;
	Ucbit			: 3;
	Ucbit	serr		: 1;	/* Stop on error		    */
	Ucbit	dcert		: 1;	/* Disable certification	    */
	Ucbit	dmdl		: 1;	/* Disable manufacturer defect list */
	Ucbit	enable		: 1;	/* Enable to use the next 3 bits    */
	Uchar	length[2];		/* Length of following list in bytes*/
}scsi_format_header;

#else					/* Motorola byteorder */

typedef struct  {
	Ucbit	res		: 8;	/* Adaptec 5500: 1 --> format track */
	Ucbit	enable		: 1;	/* Enable to use the next 3 bits    */
	Ucbit	dmdl		: 1;	/* Disable manufacturer defect list */
	Ucbit	dcert		: 1;	/* Disable certification	    */
	Ucbit	serr		: 1;	/* Stop on error		    */
	Ucbit			: 3;
	Ucbit	vu		: 1;
	Uchar	length[2];		/* Length of following list in bytes*/
}scsi_format_header;
#endif

typedef struct	 {
	Uchar	cyl[3];
	Uchar	head;
	Uchar	bfi[4];
}scsi_def_bfi;

typedef struct	 {
	Uchar	cyl[3];
	Uchar	head;
	Uchar	sec[4];
}scsi_def_phys;

typedef struct	 {
	scsi_def_header	hd;
	union {
		Uchar		list_block[1][4];
		scsi_def_bfi	list_bfi[1];
		scsi_def_phys	list_phys[1];
	} def_list;
}scsi_def_list;

typedef struct	 {
	scsi_format_header hd;
	union {
		Uchar		list_block[1][4];
		scsi_def_bfi	list_bfi[1];
		scsi_def_phys	list_phys[1];
	} def_list;
}scsi_format_data;

#define	def_block	def_list.list_block
#define	def_bfi		def_list.list_bfi
#define	def_phys	def_list.list_phys

#define	SC_DEF_BLOCK	0
#define	SC_DEF_BFI	4
#define	SC_DEF_PHYS	5
#define	SC_DEF_VU	6
#define	SC_DEF_RES	7

typedef struct	 {
	Uchar	cmd;
	Uchar	addr[4];
	Ucbit		: 8;
} scsi_send_diag_cmd;

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct {
	Uchar	cyl[2];
	Uchar	head;
	Uchar	sec;
	Ucbit		: 5;
	Ucbit	rp	: 1;
	Ucbit	sp	: 1;
	Ucbit	dt	: 1;
}scsi_sector_header;

#else					/* Motorola byteorder */

typedef struct	 {
	Uchar	cyl[2];
	Uchar	head;
	Uchar	sec;
	Ucbit	dt	: 1;
	Ucbit	sp	: 1;
	Ucbit	rp	: 1;
	Ucbit		: 5;
}scsi_sector_header;
#endif

typedef struct{
	Uchar	opc_speed[2];
	Uchar	opc_val[6];
} opc;


#if defined(_BIT_FIELDS_LTOH)	/* Intel bitorder */

typedef struct  {
	Uchar	data_len[2];		
	Uchar	track_number_LSB;	
	Uchar	session_number_LSB;	
	Uchar	reserved4;
	Ucbit	track_mode	: 4;	
	Ucbit	copy		: 1;	
	Ucbit	damage		: 1;
	Ucbit	res1		: 2;
	
	Ucbit	data_mode	: 4;	
	Ucbit	fp			: 1;	
	Ucbit	packet		: 1;
	Ucbit	blank		: 1;	
	Ucbit	RT			: 1;

	Ucbit	NWA_V		: 1;
	Ucbit	LRA_V		: 1;
	Ucbit	res2		: 6;	
	Uchar	track_start_addr[4];
	Uchar	next_writtable_addr[4];
	Uchar	free_blocks[4];
	Uchar	fixed_packet_size[4];
	Uchar	track_size[4];
	Uchar	last_record_addr[4];
	Uchar	track_number_MSB;
	Uchar	session_number_MSB;
	Uchar	reserved34[2];
}track_info;

#else				/* Motorola bitorder */

typedef struct  {
	Uchar	data_len[2];		
	Uchar	track_number_LSB;	
	Uchar	session_number_LSB;	
	Uchar	reserved4;
	Ucbit	res1		: 2;
	Ucbit	damage		: 1;
	Ucbit	copy		: 1;	
	Ucbit	track_mode	: 4;	
	
	Ucbit	RT			: 1;
	Ucbit	blank		: 1;	
	Ucbit	packet		: 1;
	Ucbit	fp			: 1;	
	Ucbit	data_mode	: 4;	
	
	Ucbit	res2		: 6;	
	Ucbit	LRA_V		: 1;
	Ucbit	NWA_V		: 1;

	Uchar	track_start_addr[4];
	Uchar	next_writtable_addr[4];
	Uchar	free_blocks[4];
	Uchar	fixed_packet_size[4];
	Uchar	last_record_addr[4];
	Uchar	track_number_MSB;
	Uchar	session_number_MSB;
	Uchar	reserved34[2];
} track_info;
#endif

#if defined(_BIT_FIELDS_LTOH)	/* Intel bitorder */

typedef struct  {
	Uchar	data_len[2];		/* Data len without this info	*/
	Ucbit	disk_status	: 2;	/* Status of the disk		*/
	Ucbit	sess_status	: 2;	/* Status of last session	*/
	Ucbit	erasable	: 1;	/* Disk is erasable		*/
	Ucbit	res2		: 3;	/* Reserved			*/
	Uchar	first_track;		/* # of first track on disk	*/
	Uchar	numsess;		/* # of sessions		*/
	Uchar	first_track_ls;		/* First track in last sessaion	*/
	Uchar	last_track_ls;		/* Last track in last sessaion	*/
	Ucbit	res7_04		: 5;	/* Reserved			*/
	Ucbit	uru		: 1;	/* This is an unrestricted disk	*/
	Ucbit	dbc_v		: 1;	/* Disk bar code valid		*/
	Ucbit	did_v		: 1;	/* Disk id valid		*/
	Uchar	disk_type;		/* Disk type			*/
	Uchar	res9[3];		/* Reserved			*/
	Uchar	disk_id[4];		/* Disk identification		*/
	Uchar	last_lead_in[4];	/* Last session lead in time	*/
	Uchar	last_lead_out[4];	/* Last session lead out time	*/
	Uchar	disk_barcode[8];	/* Disk bar code		*/
	Uchar	res32;			/* Reserved			*/
	Uchar	num_opc_entries;	/* # of OPC table entries	*/
	opc		opc_table[1];		/* OPC table 			*/
}disk_info;

#else				/* Motorola bitorder */

typedef struct  {
	Uchar	data_len[2];		/* Data len without this info	*/
	Ucbit	res2		: 3;	/* Reserved			*/
	Ucbit	erasable	: 1;	/* Disk is erasable		*/
	Ucbit	sess_status	: 2;	/* Status of last session	*/
	Ucbit	disk_status	: 2;	/* Status of the disk		*/
	Uchar	first_track;		/* # of first track on disk	*/
	Uchar	numsess;		/* # of sessions		*/
	Uchar	first_track_ls;		/* First track in last sessaion	*/
	Uchar	last_track_ls;		/* Last track in last sessaion	*/
	Ucbit	did_v		: 1;	/* Disk id valid		*/
	Ucbit	dbc_v		: 1;	/* Disk bar code valid		*/
	Ucbit	uru		: 1;	/* This is an unrestricted disk	*/
	Ucbit	res7_04		: 5;	/* Reserved			*/
	Uchar	disk_type;		/* Disk type			*/
	Uchar	res9[3];		/* Reserved			*/
	Uchar	disk_id[4];		/* Disk identification		*/
	Uchar	last_lead_in[4];	/* Last session lead in time	*/
	Uchar	last_lead_out[4];	/* Last session lead out time	*/
	Uchar	disk_barcode[8];	/* Disk bar code		*/
	Uchar	res32;			/* Reserved			*/
	Uchar	num_opc_entries;	/* # of OPC table entries	*/
	opc		opc_table[1];		/* OPC table 			*/
}disk_info;
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

typedef struct{	/* scsi extended sense for error class 7 */
	/* byte 0 */
	Ucbit	type	: 7;	/* fixed at 0x70 */
	Ucbit	adr_val	: 1;	/* sense data is valid */
	/* byte 1 */
	Uchar	seg_num;	/* segment number, applies to copy cmd only */
	/* byte 2 */
	Ucbit	key	: 4;	/* sense key, see below */
	Ucbit		: 1;	/* reserved */
	Ucbit	ili	: 1;	/* incorrect length indicator */
	Ucbit	eom	: 1;	/* end of media */
	Ucbit	fil_mk	: 1;	/* file mark on device */
	/* bytes 3 through 7 */
	Uchar	info_1;		/* information byte 1 */
	Uchar	info_2;		/* information byte 2 */
	Uchar	info_3;		/* information byte 3 */
	Uchar	info_4;		/* information byte 4 */
	Uchar	add_len;	/* number of additional bytes */
	/* bytes 8 through 13, CCS additions */
	Uchar	optional_8;	/* CCS search and copy only */
	Uchar	optional_9;	/* CCS search and copy only */
	Uchar	optional_10;	/* CCS search and copy only */
	Uchar	optional_11;	/* CCS search and copy only */
	Uchar 	ASC;	/* sense code */
	Uchar	ASCQ;	/* sense code qualifier */
	Uchar	fru_code;	/* Field replacable unit code */
	Ucbit	bptr	: 3;	/* bit pointer for failure (if bpv) */
	Ucbit	bpv	: 1;	/* bit pointer is valid */
	Ucbit		: 2;
	Ucbit	cd	: 1;	/* pointers refer to command not data */
	Ucbit	sksv	: 1;	/* sense key specific valid */
	Uchar	field_ptr[2];	/* field pointer for failure */
	Uchar	add_info[2];	/* round up to 20 bytes */
} scsi_sense;

#else	/* Motorola byteorder */

typedef struct	 {	/* scsi extended sense for error class 7 */
	/* byte 0 */
	Ucbit	adr_val	: 1;	/* sense data is valid */
	Ucbit	type	: 7;	/* fixed at 0x70 */
	/* byte 1 */
	Uchar	seg_num;	/* segment number, applies to copy cmd only */
	/* byte 2 */
	Ucbit	fil_mk	: 1;	/* file mark on device */
	Ucbit	eom	: 1;	/* end of media */
	Ucbit	ili	: 1;	/* incorrect length indicator */
	Ucbit		: 1;	/* reserved */
	Ucbit	key	: 4;	/* sense key, see below */
	/* bytes 3 through 7 */
	Uchar	info_1;		/* information byte 1 */
	Uchar	info_2;		/* information byte 2 */
	Uchar	info_3;		/* information byte 3 */
	Uchar	info_4;		/* information byte 4 */
	Uchar	add_len;	/* number of additional bytes */
	/* bytes 8 through 13, CCS additions */
	Uchar	optional_8;	/* CCS search and copy only */
	Uchar	optional_9;	/* CCS search and copy only */
	Uchar	optional_10;	/* CCS search and copy only */
	Uchar	optional_11;	/* CCS search and copy only */
	Uchar 	ASC	/* sense code */
	Uchar	ASCQ;	/* sense code qualifier */
	Uchar	fru_code;	/* Field replacable unit code */
	Ucbit	sksv	: 1;	/* sense key specific valid */
	Ucbit	cd	: 1;	/* pointers refer to command not data */
	Ucbit		: 2;
	Ucbit	bpv	: 1;	/* bit pointer is valid */
	Ucbit	bptr	: 3;	/* bit pointer for failure (if bpv) */
	Uchar	field_ptr[2];	/* field pointer for failure */
	Uchar	add_info[2];	/* round up to 20 bytes */
}scsi_sense;
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCSIREG_H */
