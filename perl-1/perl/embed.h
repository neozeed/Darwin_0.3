/* !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!! 
   This file is built by embed.pl from global.sym, intrpvar.h,
   and thrdvar.h.  Any changes made here will be lost!
*/

/* (Doing namespace management portably in C is really gross.) */

/*  EMBED has no run-time penalty, but helps keep the Perl namespace
    from colliding with that used by other libraries pulled in
    by extensions or by embedding perl.  Allow a cc -DNO_EMBED
    override, however, to keep binary compatability with previous
    versions of perl.
*/
#ifndef NO_EMBED
#  define EMBED 1 
#endif

/* Hide global symbols? */

#ifdef EMBED

#define AMG_names		Perl_AMG_names
#define Error			Perl_Error
#define Gv_AMupdate		Perl_Gv_AMupdate
#define abs_amg			Perl_abs_amg
#define add_amg			Perl_add_amg
#define add_ass_amg		Perl_add_ass_amg
#define additem			Perl_additem
#define amagic_call		Perl_amagic_call
#define append_elem		Perl_append_elem
#define append_list		Perl_append_list
#define apply			Perl_apply
#define assertref		Perl_assertref
#define atan2_amg		Perl_atan2_amg
#define av_clear		Perl_av_clear
#define av_extend		Perl_av_extend
#define av_fake			Perl_av_fake
#define av_fetch		Perl_av_fetch
#define av_fill			Perl_av_fill
#define av_len			Perl_av_len
#define av_make			Perl_av_make
#define av_pop			Perl_av_pop
#define av_push			Perl_av_push
#define av_reify		Perl_av_reify
#define av_shift		Perl_av_shift
#define av_store		Perl_av_store
#define av_undef		Perl_av_undef
#define av_unshift		Perl_av_unshift
#define avhv_exists_ent		Perl_avhv_exists_ent
#define avhv_fetch_ent		Perl_avhv_fetch_ent
#define avhv_iternext		Perl_avhv_iternext
#define avhv_iterval		Perl_avhv_iterval
#define avhv_keys		Perl_avhv_keys
#define band_amg		Perl_band_amg
#define bind_match		Perl_bind_match
#define block_end		Perl_block_end
#define block_gimme		Perl_block_gimme
#define block_start		Perl_block_start
#define block_type		Perl_block_type
#define bool__amg		Perl_bool__amg
#define boot_core_UNIVERSAL	Perl_boot_core_UNIVERSAL
#define bor_amg			Perl_bor_amg
#define bset_obj_store		Perl_bset_obj_store
#define bxor_amg		Perl_bxor_amg
#define byterun			Perl_byterun
#define call_list		Perl_call_list
#define cando			Perl_cando
#define cast_ulong		Perl_cast_ulong
#define check			Perl_check
#define check_uni		Perl_check_uni
#define checkcomma		Perl_checkcomma
#define ck_aelem		Perl_ck_aelem
#define ck_anoncode		Perl_ck_anoncode
#define ck_bitop		Perl_ck_bitop
#define ck_concat		Perl_ck_concat
#define ck_delete		Perl_ck_delete
#define ck_eof			Perl_ck_eof
#define ck_eval			Perl_ck_eval
#define ck_exec			Perl_ck_exec
#define ck_exists		Perl_ck_exists
#define ck_ftst			Perl_ck_ftst
#define ck_fun			Perl_ck_fun
#define ck_fun_locale		Perl_ck_fun_locale
#define ck_glob			Perl_ck_glob
#define ck_grep			Perl_ck_grep
#define ck_gvconst		Perl_ck_gvconst
#define ck_index		Perl_ck_index
#define ck_lengthconst		Perl_ck_lengthconst
#define ck_lfun			Perl_ck_lfun
#define ck_listiob		Perl_ck_listiob
#define ck_match		Perl_ck_match
#define ck_null			Perl_ck_null
#define ck_repeat		Perl_ck_repeat
#define ck_require		Perl_ck_require
#define ck_retarget		Perl_ck_retarget
#define ck_rfun			Perl_ck_rfun
#define ck_rvconst		Perl_ck_rvconst
#define ck_scmp			Perl_ck_scmp
#define ck_select		Perl_ck_select
#define ck_shift		Perl_ck_shift
#define ck_sort			Perl_ck_sort
#define ck_spair		Perl_ck_spair
#define ck_split		Perl_ck_split
#define ck_subr			Perl_ck_subr
#define ck_svconst		Perl_ck_svconst
#define ck_trunc		Perl_ck_trunc
#define compl_amg		Perl_compl_amg
#define concat_amg		Perl_concat_amg
#define concat_ass_amg		Perl_concat_ass_amg
#define condpair_magic		Perl_condpair_magic
#define convert			Perl_convert
#define cos_amg			Perl_cos_amg
#define croak			Perl_croak
#define cv_ckproto		Perl_cv_ckproto
#define cv_clone		Perl_cv_clone
#define cv_const_sv		Perl_cv_const_sv
#define cv_undef		Perl_cv_undef
#define cx_dump			Perl_cx_dump
#define cxinc			Perl_cxinc
#define dc			Perl_dc
#define deb			Perl_deb
#define deb_growlevel		Perl_deb_growlevel
#define debop			Perl_debop
#define debprofdump		Perl_debprofdump
#define debstack		Perl_debstack
#define debstackptrs		Perl_debstackptrs
#define dec_amg			Perl_dec_amg
#define delimcpy		Perl_delimcpy
#define deprecate		Perl_deprecate
#define di			Perl_di
#define die			Perl_die
#define die_where		Perl_die_where
#define div_amg			Perl_div_amg
#define div_ass_amg		Perl_div_ass_amg
#define do_aexec		Perl_do_aexec
#define do_binmode		Perl_do_binmode
#define do_chomp		Perl_do_chomp
#define do_chop			Perl_do_chop
#define do_close		Perl_do_close
#define do_eof			Perl_do_eof
#define do_exec			Perl_do_exec
#define do_execfree		Perl_do_execfree
#define do_ipcctl		Perl_do_ipcctl
#define do_ipcget		Perl_do_ipcget
#define do_join			Perl_do_join
#define do_kv			Perl_do_kv
#define do_msgrcv		Perl_do_msgrcv
#define do_msgsnd		Perl_do_msgsnd
#define do_open			Perl_do_open
#define do_pipe			Perl_do_pipe
#define do_print		Perl_do_print
#define do_readline		Perl_do_readline
#define do_seek			Perl_do_seek
#define do_semop		Perl_do_semop
#define do_shmio		Perl_do_shmio
#define do_sprintf		Perl_do_sprintf
#define do_sysseek		Perl_do_sysseek
#define do_tell			Perl_do_tell
#define do_trans		Perl_do_trans
#define do_vecset		Perl_do_vecset
#define do_vop			Perl_do_vop
#define dofindlabel		Perl_dofindlabel
#define dopoptoeval		Perl_dopoptoeval
#define dounwind		Perl_dounwind
#define dowantarray		Perl_dowantarray
#define ds			Perl_ds
#define dump_all		Perl_dump_all
#define dump_eval		Perl_dump_eval
#define dump_fds		Perl_dump_fds
#define dump_form		Perl_dump_form
#define dump_gv			Perl_dump_gv
#define dump_mstats		Perl_dump_mstats
#define dump_op			Perl_dump_op
#define dump_packsubs		Perl_dump_packsubs
#define dump_pm			Perl_dump_pm
#define dump_sub		Perl_dump_sub
#define eq_amg			Perl_eq_amg
#define exp_amg			Perl_exp_amg
#define expectterm		Perl_expectterm
#define fallback_amg		Perl_fallback_amg
#define fbm_compile		Perl_fbm_compile
#define fbm_instr		Perl_fbm_instr
#define fetch_gv		Perl_fetch_gv
#define fetch_io		Perl_fetch_io
#define filter_add		Perl_filter_add
#define filter_del		Perl_filter_del
#define filter_read		Perl_filter_read
#define find_script		Perl_find_script
#define find_threadsv		Perl_find_threadsv
#define fold			Perl_fold
#define fold_constants		Perl_fold_constants
#define fold_locale		Perl_fold_locale
#define force_ident		Perl_force_ident
#define force_list		Perl_force_list
#define force_next		Perl_force_next
#define force_word		Perl_force_word
#define form			Perl_form
#define free_tmps		Perl_free_tmps
#define freq			Perl_freq
#define ge_amg			Perl_ge_amg
#define gen_constant_list	Perl_gen_constant_list
#define get_no_modify		Perl_get_no_modify
#define get_op_descs		Perl_get_op_descs
#define get_op_names		Perl_get_op_names
#define get_opargs		Perl_get_opargs
#define get_specialsv_list	Perl_get_specialsv_list
#define gp_free			Perl_gp_free
#define gp_ref			Perl_gp_ref
#define gt_amg			Perl_gt_amg
#define gv_AVadd		Perl_gv_AVadd
#define gv_HVadd		Perl_gv_HVadd
#define gv_IOadd		Perl_gv_IOadd
#define gv_autoload4		Perl_gv_autoload4
#define gv_check		Perl_gv_check
#define gv_efullname		Perl_gv_efullname
#define gv_efullname3		Perl_gv_efullname3
#define gv_fetchfile		Perl_gv_fetchfile
#define gv_fetchmeth		Perl_gv_fetchmeth
#define gv_fetchmethod		Perl_gv_fetchmethod
#define gv_fetchmethod_autoload	Perl_gv_fetchmethod_autoload
#define gv_fetchpv		Perl_gv_fetchpv
#define gv_fullname		Perl_gv_fullname
#define gv_fullname3		Perl_gv_fullname3
#define gv_init			Perl_gv_init
#define gv_stashpv		Perl_gv_stashpv
#define gv_stashpvn		Perl_gv_stashpvn
#define gv_stashsv		Perl_gv_stashsv
#define hv_clear		Perl_hv_clear
#define hv_delayfree_ent	Perl_hv_delayfree_ent
#define hv_delete		Perl_hv_delete
#define hv_delete_ent		Perl_hv_delete_ent
#define hv_exists		Perl_hv_exists
#define hv_exists_ent		Perl_hv_exists_ent
#define hv_fetch		Perl_hv_fetch
#define hv_fetch_ent		Perl_hv_fetch_ent
#define hv_free_ent		Perl_hv_free_ent
#define hv_iterinit		Perl_hv_iterinit
#define hv_iterkey		Perl_hv_iterkey
#define hv_iterkeysv		Perl_hv_iterkeysv
#define hv_iternext		Perl_hv_iternext
#define hv_iternextsv		Perl_hv_iternextsv
#define hv_iterval		Perl_hv_iterval
#define hv_ksplit		Perl_hv_ksplit
#define hv_magic		Perl_hv_magic
#define hv_stashpv		Perl_hv_stashpv
#define hv_store		Perl_hv_store
#define hv_store_ent		Perl_hv_store_ent
#define hv_undef		Perl_hv_undef
#define ibcmp			Perl_ibcmp
#define ibcmp_locale		Perl_ibcmp_locale
#define inc_amg			Perl_inc_amg
#define ingroup			Perl_ingroup
#define init_stacks		Perl_init_stacks
#define init_thread_intern	Perl_init_thread_intern
#define instr			Perl_instr
#define intro_my		Perl_intro_my
#define intuit_more		Perl_intuit_more
#define invert			Perl_invert
#define io_close		Perl_io_close
#define jmaybe			Perl_jmaybe
#define keyword			Perl_keyword
#define know_next		Perl_know_next
#define le_amg			Perl_le_amg
#define leave_scope		Perl_leave_scope
#define lex_end			Perl_lex_end
#define lex_start		Perl_lex_start
#define linklist		Perl_linklist
#define list			Perl_list
#define listkids		Perl_listkids
#define localize		Perl_localize
#define log_amg			Perl_log_amg
#define looks_like_number	Perl_looks_like_number
#define lshift_amg		Perl_lshift_amg
#define lshift_ass_amg		Perl_lshift_ass_amg
#define lt_amg			Perl_lt_amg
#define magic_clear_all_env	Perl_magic_clear_all_env
#define magic_clearenv		Perl_magic_clearenv
#define magic_clearpack		Perl_magic_clearpack
#define magic_clearsig		Perl_magic_clearsig
#define magic_existspack	Perl_magic_existspack
#define magic_freeregexp	Perl_magic_freeregexp
#define magic_get		Perl_magic_get
#define magic_getarylen		Perl_magic_getarylen
#define magic_getdefelem	Perl_magic_getdefelem
#define magic_getglob		Perl_magic_getglob
#define magic_getnkeys		Perl_magic_getnkeys
#define magic_getpack		Perl_magic_getpack
#define magic_getpos		Perl_magic_getpos
#define magic_getsig		Perl_magic_getsig
#define magic_getsubstr		Perl_magic_getsubstr
#define magic_gettaint		Perl_magic_gettaint
#define magic_getuvar		Perl_magic_getuvar
#define magic_getvec		Perl_magic_getvec
#define magic_len		Perl_magic_len
#define magic_mutexfree		Perl_magic_mutexfree
#define magic_nextpack		Perl_magic_nextpack
#define magic_set		Perl_magic_set
#define magic_set_all_env	Perl_magic_set_all_env
#define magic_setamagic		Perl_magic_setamagic
#define magic_setarylen		Perl_magic_setarylen
#define magic_setbm		Perl_magic_setbm
#define magic_setcollxfrm	Perl_magic_setcollxfrm
#define magic_setdbline		Perl_magic_setdbline
#define magic_setdefelem	Perl_magic_setdefelem
#define magic_setenv		Perl_magic_setenv
#define magic_setfm		Perl_magic_setfm
#define magic_setglob		Perl_magic_setglob
#define magic_setisa		Perl_magic_setisa
#define magic_setmglob		Perl_magic_setmglob
#define magic_setnkeys		Perl_magic_setnkeys
#define magic_setpack		Perl_magic_setpack
#define magic_setpos		Perl_magic_setpos
#define magic_setsig		Perl_magic_setsig
#define magic_setsubstr		Perl_magic_setsubstr
#define magic_settaint		Perl_magic_settaint
#define magic_setuvar		Perl_magic_setuvar
#define magic_setvec		Perl_magic_setvec
#define magic_sizepack		Perl_magic_sizepack
#define magic_wipepack		Perl_magic_wipepack
#define magicname		Perl_magicname
#define malloced_size		Perl_malloced_size
#define markstack_grow		Perl_markstack_grow
#define mem_collxfrm		Perl_mem_collxfrm
#define mess			Perl_mess
#define mg_clear		Perl_mg_clear
#define mg_copy			Perl_mg_copy
#define mg_find			Perl_mg_find
#define mg_free			Perl_mg_free
#define mg_get			Perl_mg_get
#define mg_length		Perl_mg_length
#define mg_magical		Perl_mg_magical
#define mg_set			Perl_mg_set
#define mg_size			Perl_mg_size
#define mod			Perl_mod
#define mod_amg			Perl_mod_amg
#define mod_ass_amg		Perl_mod_ass_amg
#define modkids			Perl_modkids
#define moreswitches		Perl_moreswitches
#define mstats			Perl_mstats
#define mult_amg		Perl_mult_amg
#define mult_ass_amg		Perl_mult_ass_amg
#define my			Perl_my
#define my_bcopy		Perl_my_bcopy
#define my_bzero		Perl_my_bzero
#define my_chsize		Perl_my_chsize
#define my_exit			Perl_my_exit
#define my_failure_exit		Perl_my_failure_exit
#define my_htonl		Perl_my_htonl
#define my_lstat		Perl_my_lstat
#define my_memcmp		Perl_my_memcmp
#define my_memset		Perl_my_memset
#define my_ntohl		Perl_my_ntohl
#define my_pclose		Perl_my_pclose
#define my_popen		Perl_my_popen
#define my_setenv		Perl_my_setenv
#define my_stat			Perl_my_stat
#define my_swap			Perl_my_swap
#define my_unexec		Perl_my_unexec
#define ncmp_amg		Perl_ncmp_amg
#define ne_amg			Perl_ne_amg
#define neg_amg			Perl_neg_amg
#define newANONHASH		Perl_newANONHASH
#define newANONLIST		Perl_newANONLIST
#define newANONSUB		Perl_newANONSUB
#define newASSIGNOP		Perl_newASSIGNOP
#define newAV			Perl_newAV
#define newAVREF		Perl_newAVREF
#define newBINOP		Perl_newBINOP
#define newCONDOP		Perl_newCONDOP
#define newCONSTSUB		Perl_newCONSTSUB
#define newCVREF		Perl_newCVREF
#define newFORM			Perl_newFORM
#define newFOROP		Perl_newFOROP
#define newGVOP			Perl_newGVOP
#define newGVREF		Perl_newGVREF
#define newGVgen		Perl_newGVgen
#define newHV			Perl_newHV
#define newHVREF		Perl_newHVREF
#define newHVhv			Perl_newHVhv
#define newIO			Perl_newIO
#define newLISTOP		Perl_newLISTOP
#define newLOGOP		Perl_newLOGOP
#define newLOOPEX		Perl_newLOOPEX
#define newLOOPOP		Perl_newLOOPOP
#define newNULLLIST		Perl_newNULLLIST
#define newOP			Perl_newOP
#define newPMOP			Perl_newPMOP
#define newPROG			Perl_newPROG
#define newPVOP			Perl_newPVOP
#define newRANGE		Perl_newRANGE
#define newRV			Perl_newRV
#define newRV_noinc		Perl_newRV_noinc
#define newSLICEOP		Perl_newSLICEOP
#define newSTATEOP		Perl_newSTATEOP
#define newSUB			Perl_newSUB
#define newSV			Perl_newSV
#define newSVOP			Perl_newSVOP
#define newSVREF		Perl_newSVREF
#define newSViv			Perl_newSViv
#define newSVnv			Perl_newSVnv
#define newSVpv			Perl_newSVpv
#define newSVpvf		Perl_newSVpvf
#define newSVpvn		Perl_newSVpvn
#define newSVrv			Perl_newSVrv
#define newSVsv			Perl_newSVsv
#define newUNOP			Perl_newUNOP
#define newWHILEOP		Perl_newWHILEOP
#define newXS			Perl_newXS
#define newXSUB			Perl_newXSUB
#define new_stackinfo		Perl_new_stackinfo
#define new_struct_thread	Perl_new_struct_thread
#define nextargv		Perl_nextargv
#define ninstr			Perl_ninstr
#define no_aelem		Perl_no_aelem
#define no_dir_func		Perl_no_dir_func
#define no_fh_allowed		Perl_no_fh_allowed
#define no_func			Perl_no_func
#define no_helem		Perl_no_helem
#define no_mem			Perl_no_mem
#define no_modify		Perl_no_modify
#define no_myglob		Perl_no_myglob
#define no_op			Perl_no_op
#define no_security		Perl_no_security
#define no_sock_func		Perl_no_sock_func
#define no_symref		Perl_no_symref
#define no_usym			Perl_no_usym
#define no_wrongref		Perl_no_wrongref
#define nointrp			Perl_nointrp
#define nomem			Perl_nomem
#define nomethod_amg		Perl_nomethod_amg
#define not_amg			Perl_not_amg
#define numer_amg		Perl_numer_amg
#define oopsAV			Perl_oopsAV
#define oopsCV			Perl_oopsCV
#define oopsHV			Perl_oopsHV
#define op_const_sv		Perl_op_const_sv
#define op_desc			Perl_op_desc
#define op_free			Perl_op_free
#define op_name			Perl_op_name
#define opargs			Perl_opargs
#define package			Perl_package
#define pad_alloc		Perl_pad_alloc
#define pad_allocmy		Perl_pad_allocmy
#define pad_findmy		Perl_pad_findmy
#define pad_free		Perl_pad_free
#define pad_leavemy		Perl_pad_leavemy
#define pad_reset		Perl_pad_reset
#define pad_sv			Perl_pad_sv
#define pad_swipe		Perl_pad_swipe
#define peep			Perl_peep
#define pidgone			Perl_pidgone
#define pmflag			Perl_pmflag
#define pmruntime		Perl_pmruntime
#define pmtrans			Perl_pmtrans
#define pop_return		Perl_pop_return
#define pop_scope		Perl_pop_scope
#define pow_amg			Perl_pow_amg
#define pow_ass_amg		Perl_pow_ass_amg
#define pp_aassign		Perl_pp_aassign
#define pp_abs			Perl_pp_abs
#define pp_accept		Perl_pp_accept
#define pp_add			Perl_pp_add
#define pp_aelem		Perl_pp_aelem
#define pp_aelemfast		Perl_pp_aelemfast
#define pp_alarm		Perl_pp_alarm
#define pp_and			Perl_pp_and
#define pp_andassign		Perl_pp_andassign
#define pp_anoncode		Perl_pp_anoncode
#define pp_anonhash		Perl_pp_anonhash
#define pp_anonlist		Perl_pp_anonlist
#define pp_aslice		Perl_pp_aslice
#define pp_atan2		Perl_pp_atan2
#define pp_av2arylen		Perl_pp_av2arylen
#define pp_backtick		Perl_pp_backtick
#define pp_bind			Perl_pp_bind
#define pp_binmode		Perl_pp_binmode
#define pp_bit_and		Perl_pp_bit_and
#define pp_bit_or		Perl_pp_bit_or
#define pp_bit_xor		Perl_pp_bit_xor
#define pp_bless		Perl_pp_bless
#define pp_caller		Perl_pp_caller
#define pp_chdir		Perl_pp_chdir
#define pp_chmod		Perl_pp_chmod
#define pp_chomp		Perl_pp_chomp
#define pp_chop			Perl_pp_chop
#define pp_chown		Perl_pp_chown
#define pp_chr			Perl_pp_chr
#define pp_chroot		Perl_pp_chroot
#define pp_close		Perl_pp_close
#define pp_closedir		Perl_pp_closedir
#define pp_complement		Perl_pp_complement
#define pp_concat		Perl_pp_concat
#define pp_cond_expr		Perl_pp_cond_expr
#define pp_connect		Perl_pp_connect
#define pp_const		Perl_pp_const
#define pp_cos			Perl_pp_cos
#define pp_crypt		Perl_pp_crypt
#define pp_cswitch		Perl_pp_cswitch
#define pp_dbmclose		Perl_pp_dbmclose
#define pp_dbmopen		Perl_pp_dbmopen
#define pp_dbstate		Perl_pp_dbstate
#define pp_defined		Perl_pp_defined
#define pp_delete		Perl_pp_delete
#define pp_die			Perl_pp_die
#define pp_divide		Perl_pp_divide
#define pp_dofile		Perl_pp_dofile
#define pp_dump			Perl_pp_dump
#define pp_each			Perl_pp_each
#define pp_egrent		Perl_pp_egrent
#define pp_ehostent		Perl_pp_ehostent
#define pp_enetent		Perl_pp_enetent
#define pp_enter		Perl_pp_enter
#define pp_entereval		Perl_pp_entereval
#define pp_enteriter		Perl_pp_enteriter
#define pp_enterloop		Perl_pp_enterloop
#define pp_entersub		Perl_pp_entersub
#define pp_entersubr		Perl_pp_entersubr
#define pp_entertry		Perl_pp_entertry
#define pp_enterwrite		Perl_pp_enterwrite
#define pp_eof			Perl_pp_eof
#define pp_eprotoent		Perl_pp_eprotoent
#define pp_epwent		Perl_pp_epwent
#define pp_eq			Perl_pp_eq
#define pp_eservent		Perl_pp_eservent
#define pp_evalonce		Perl_pp_evalonce
#define pp_exec			Perl_pp_exec
#define pp_exists		Perl_pp_exists
#define pp_exit			Perl_pp_exit
#define pp_exp			Perl_pp_exp
#define pp_fcntl		Perl_pp_fcntl
#define pp_fileno		Perl_pp_fileno
#define pp_flip			Perl_pp_flip
#define pp_flock		Perl_pp_flock
#define pp_flop			Perl_pp_flop
#define pp_fork			Perl_pp_fork
#define pp_formline		Perl_pp_formline
#define pp_ftatime		Perl_pp_ftatime
#define pp_ftbinary		Perl_pp_ftbinary
#define pp_ftblk		Perl_pp_ftblk
#define pp_ftchr		Perl_pp_ftchr
#define pp_ftctime		Perl_pp_ftctime
#define pp_ftdir		Perl_pp_ftdir
#define pp_fteexec		Perl_pp_fteexec
#define pp_fteowned		Perl_pp_fteowned
#define pp_fteread		Perl_pp_fteread
#define pp_ftewrite		Perl_pp_ftewrite
#define pp_ftfile		Perl_pp_ftfile
#define pp_ftis			Perl_pp_ftis
#define pp_ftlink		Perl_pp_ftlink
#define pp_ftmtime		Perl_pp_ftmtime
#define pp_ftpipe		Perl_pp_ftpipe
#define pp_ftrexec		Perl_pp_ftrexec
#define pp_ftrowned		Perl_pp_ftrowned
#define pp_ftrread		Perl_pp_ftrread
#define pp_ftrwrite		Perl_pp_ftrwrite
#define pp_ftsgid		Perl_pp_ftsgid
#define pp_ftsize		Perl_pp_ftsize
#define pp_ftsock		Perl_pp_ftsock
#define pp_ftsuid		Perl_pp_ftsuid
#define pp_ftsvtx		Perl_pp_ftsvtx
#define pp_fttext		Perl_pp_fttext
#define pp_fttty		Perl_pp_fttty
#define pp_ftzero		Perl_pp_ftzero
#define pp_ge			Perl_pp_ge
#define pp_gelem		Perl_pp_gelem
#define pp_getc			Perl_pp_getc
#define pp_getlogin		Perl_pp_getlogin
#define pp_getpeername		Perl_pp_getpeername
#define pp_getpgrp		Perl_pp_getpgrp
#define pp_getppid		Perl_pp_getppid
#define pp_getpriority		Perl_pp_getpriority
#define pp_getsockname		Perl_pp_getsockname
#define pp_ggrent		Perl_pp_ggrent
#define pp_ggrgid		Perl_pp_ggrgid
#define pp_ggrnam		Perl_pp_ggrnam
#define pp_ghbyaddr		Perl_pp_ghbyaddr
#define pp_ghbyname		Perl_pp_ghbyname
#define pp_ghostent		Perl_pp_ghostent
#define pp_glob			Perl_pp_glob
#define pp_gmtime		Perl_pp_gmtime
#define pp_gnbyaddr		Perl_pp_gnbyaddr
#define pp_gnbyname		Perl_pp_gnbyname
#define pp_gnetent		Perl_pp_gnetent
#define pp_goto			Perl_pp_goto
#define pp_gpbyname		Perl_pp_gpbyname
#define pp_gpbynumber		Perl_pp_gpbynumber
#define pp_gprotoent		Perl_pp_gprotoent
#define pp_gpwent		Perl_pp_gpwent
#define pp_gpwnam		Perl_pp_gpwnam
#define pp_gpwuid		Perl_pp_gpwuid
#define pp_grepstart		Perl_pp_grepstart
#define pp_grepwhile		Perl_pp_grepwhile
#define pp_gsbyname		Perl_pp_gsbyname
#define pp_gsbyport		Perl_pp_gsbyport
#define pp_gservent		Perl_pp_gservent
#define pp_gsockopt		Perl_pp_gsockopt
#define pp_gt			Perl_pp_gt
#define pp_gv			Perl_pp_gv
#define pp_gvsv			Perl_pp_gvsv
#define pp_helem		Perl_pp_helem
#define pp_hex			Perl_pp_hex
#define pp_hslice		Perl_pp_hslice
#define pp_i_add		Perl_pp_i_add
#define pp_i_divide		Perl_pp_i_divide
#define pp_i_eq			Perl_pp_i_eq
#define pp_i_ge			Perl_pp_i_ge
#define pp_i_gt			Perl_pp_i_gt
#define pp_i_le			Perl_pp_i_le
#define pp_i_lt			Perl_pp_i_lt
#define pp_i_modulo		Perl_pp_i_modulo
#define pp_i_multiply		Perl_pp_i_multiply
#define pp_i_ncmp		Perl_pp_i_ncmp
#define pp_i_ne			Perl_pp_i_ne
#define pp_i_negate		Perl_pp_i_negate
#define pp_i_subtract		Perl_pp_i_subtract
#define pp_index		Perl_pp_index
#define pp_int			Perl_pp_int
#define pp_interp		Perl_pp_interp
#define pp_ioctl		Perl_pp_ioctl
#define pp_iter			Perl_pp_iter
#define pp_join			Perl_pp_join
#define pp_keys			Perl_pp_keys
#define pp_kill			Perl_pp_kill
#define pp_last			Perl_pp_last
#define pp_lc			Perl_pp_lc
#define pp_lcfirst		Perl_pp_lcfirst
#define pp_le			Perl_pp_le
#define pp_leave		Perl_pp_leave
#define pp_leaveeval		Perl_pp_leaveeval
#define pp_leaveloop		Perl_pp_leaveloop
#define pp_leavesub		Perl_pp_leavesub
#define pp_leavetry		Perl_pp_leavetry
#define pp_leavewrite		Perl_pp_leavewrite
#define pp_left_shift		Perl_pp_left_shift
#define pp_length		Perl_pp_length
#define pp_lineseq		Perl_pp_lineseq
#define pp_link			Perl_pp_link
#define pp_list			Perl_pp_list
#define pp_listen		Perl_pp_listen
#define pp_localtime		Perl_pp_localtime
#define pp_lock			Perl_pp_lock
#define pp_log			Perl_pp_log
#define pp_lslice		Perl_pp_lslice
#define pp_lstat		Perl_pp_lstat
#define pp_lt			Perl_pp_lt
#define pp_map			Perl_pp_map
#define pp_mapstart		Perl_pp_mapstart
#define pp_mapwhile		Perl_pp_mapwhile
#define pp_match		Perl_pp_match
#define pp_method		Perl_pp_method
#define pp_mkdir		Perl_pp_mkdir
#define pp_modulo		Perl_pp_modulo
#define pp_msgctl		Perl_pp_msgctl
#define pp_msgget		Perl_pp_msgget
#define pp_msgrcv		Perl_pp_msgrcv
#define pp_msgsnd		Perl_pp_msgsnd
#define pp_multiply		Perl_pp_multiply
#define pp_ncmp			Perl_pp_ncmp
#define pp_ne			Perl_pp_ne
#define pp_negate		Perl_pp_negate
#define pp_next			Perl_pp_next
#define pp_nextstate		Perl_pp_nextstate
#define pp_not			Perl_pp_not
#define pp_nswitch		Perl_pp_nswitch
#define pp_null			Perl_pp_null
#define pp_oct			Perl_pp_oct
#define pp_open			Perl_pp_open
#define pp_open_dir		Perl_pp_open_dir
#define pp_or			Perl_pp_or
#define pp_orassign		Perl_pp_orassign
#define pp_ord			Perl_pp_ord
#define pp_pack			Perl_pp_pack
#define pp_padany		Perl_pp_padany
#define pp_padav		Perl_pp_padav
#define pp_padhv		Perl_pp_padhv
#define pp_padsv		Perl_pp_padsv
#define pp_pipe_op		Perl_pp_pipe_op
#define pp_pop			Perl_pp_pop
#define pp_pos			Perl_pp_pos
#define pp_postdec		Perl_pp_postdec
#define pp_postinc		Perl_pp_postinc
#define pp_pow			Perl_pp_pow
#define pp_predec		Perl_pp_predec
#define pp_preinc		Perl_pp_preinc
#define pp_print		Perl_pp_print
#define pp_prototype		Perl_pp_prototype
#define pp_prtf			Perl_pp_prtf
#define pp_push			Perl_pp_push
#define pp_pushmark		Perl_pp_pushmark
#define pp_pushre		Perl_pp_pushre
#define pp_qr			Perl_pp_qr
#define pp_quotemeta		Perl_pp_quotemeta
#define pp_rand			Perl_pp_rand
#define pp_range		Perl_pp_range
#define pp_rcatline		Perl_pp_rcatline
#define pp_read			Perl_pp_read
#define pp_readdir		Perl_pp_readdir
#define pp_readline		Perl_pp_readline
#define pp_readlink		Perl_pp_readlink
#define pp_recv			Perl_pp_recv
#define pp_redo			Perl_pp_redo
#define pp_ref			Perl_pp_ref
#define pp_refgen		Perl_pp_refgen
#define pp_regcmaybe		Perl_pp_regcmaybe
#define pp_regcomp		Perl_pp_regcomp
#define pp_regcreset		Perl_pp_regcreset
#define pp_rename		Perl_pp_rename
#define pp_repeat		Perl_pp_repeat
#define pp_require		Perl_pp_require
#define pp_reset		Perl_pp_reset
#define pp_return		Perl_pp_return
#define pp_reverse		Perl_pp_reverse
#define pp_rewinddir		Perl_pp_rewinddir
#define pp_right_shift		Perl_pp_right_shift
#define pp_rindex		Perl_pp_rindex
#define pp_rmdir		Perl_pp_rmdir
#define pp_rv2av		Perl_pp_rv2av
#define pp_rv2cv		Perl_pp_rv2cv
#define pp_rv2gv		Perl_pp_rv2gv
#define pp_rv2hv		Perl_pp_rv2hv
#define pp_rv2sv		Perl_pp_rv2sv
#define pp_sassign		Perl_pp_sassign
#define pp_scalar		Perl_pp_scalar
#define pp_schomp		Perl_pp_schomp
#define pp_schop		Perl_pp_schop
#define pp_scmp			Perl_pp_scmp
#define pp_scope		Perl_pp_scope
#define pp_seek			Perl_pp_seek
#define pp_seekdir		Perl_pp_seekdir
#define pp_select		Perl_pp_select
#define pp_semctl		Perl_pp_semctl
#define pp_semget		Perl_pp_semget
#define pp_semop		Perl_pp_semop
#define pp_send			Perl_pp_send
#define pp_seq			Perl_pp_seq
#define pp_setpgrp		Perl_pp_setpgrp
#define pp_setpriority		Perl_pp_setpriority
#define pp_sge			Perl_pp_sge
#define pp_sgrent		Perl_pp_sgrent
#define pp_sgt			Perl_pp_sgt
#define pp_shift		Perl_pp_shift
#define pp_shmctl		Perl_pp_shmctl
#define pp_shmget		Perl_pp_shmget
#define pp_shmread		Perl_pp_shmread
#define pp_shmwrite		Perl_pp_shmwrite
#define pp_shostent		Perl_pp_shostent
#define pp_shutdown		Perl_pp_shutdown
#define pp_sin			Perl_pp_sin
#define pp_sle			Perl_pp_sle
#define pp_sleep		Perl_pp_sleep
#define pp_slt			Perl_pp_slt
#define pp_sne			Perl_pp_sne
#define pp_snetent		Perl_pp_snetent
#define pp_socket		Perl_pp_socket
#define pp_sockpair		Perl_pp_sockpair
#define pp_sort			Perl_pp_sort
#define pp_splice		Perl_pp_splice
#define pp_split		Perl_pp_split
#define pp_sprintf		Perl_pp_sprintf
#define pp_sprotoent		Perl_pp_sprotoent
#define pp_spwent		Perl_pp_spwent
#define pp_sqrt			Perl_pp_sqrt
#define pp_srand		Perl_pp_srand
#define pp_srefgen		Perl_pp_srefgen
#define pp_sselect		Perl_pp_sselect
#define pp_sservent		Perl_pp_sservent
#define pp_ssockopt		Perl_pp_ssockopt
#define pp_stat			Perl_pp_stat
#define pp_stringify		Perl_pp_stringify
#define pp_stub			Perl_pp_stub
#define pp_study		Perl_pp_study
#define pp_subst		Perl_pp_subst
#define pp_substcont		Perl_pp_substcont
#define pp_substr		Perl_pp_substr
#define pp_subtract		Perl_pp_subtract
#define pp_symlink		Perl_pp_symlink
#define pp_syscall		Perl_pp_syscall
#define pp_sysopen		Perl_pp_sysopen
#define pp_sysread		Perl_pp_sysread
#define pp_sysseek		Perl_pp_sysseek
#define pp_system		Perl_pp_system
#define pp_syswrite		Perl_pp_syswrite
#define pp_tell			Perl_pp_tell
#define pp_telldir		Perl_pp_telldir
#define pp_threadsv		Perl_pp_threadsv
#define pp_tie			Perl_pp_tie
#define pp_tied			Perl_pp_tied
#define pp_time			Perl_pp_time
#define pp_tms			Perl_pp_tms
#define pp_trans		Perl_pp_trans
#define pp_truncate		Perl_pp_truncate
#define pp_uc			Perl_pp_uc
#define pp_ucfirst		Perl_pp_ucfirst
#define pp_umask		Perl_pp_umask
#define pp_undef		Perl_pp_undef
#define pp_unlink		Perl_pp_unlink
#define pp_unpack		Perl_pp_unpack
#define pp_unshift		Perl_pp_unshift
#define pp_unstack		Perl_pp_unstack
#define pp_untie		Perl_pp_untie
#define pp_utime		Perl_pp_utime
#define pp_values		Perl_pp_values
#define pp_vec			Perl_pp_vec
#define pp_wait			Perl_pp_wait
#define pp_waitpid		Perl_pp_waitpid
#define pp_wantarray		Perl_pp_wantarray
#define pp_warn			Perl_pp_warn
#define pp_xor			Perl_pp_xor
#define ppaddr			Perl_ppaddr
#define pregcomp		Perl_pregcomp
#define pregexec		Perl_pregexec
#define pregfree		Perl_pregfree
#define prepend_elem		Perl_prepend_elem
#define psig_name		Perl_psig_name
#define psig_ptr		Perl_psig_ptr
#define push_return		Perl_push_return
#define push_scope		Perl_push_scope
#define q			Perl_q
#define reall_srchlen		Perl_reall_srchlen
#define ref			Perl_ref
#define refkids			Perl_refkids
#define regdump			Perl_regdump
#define regexec_flags		Perl_regexec_flags
#define regkind			Perl_regkind
#define regnext			Perl_regnext
#define regprop			Perl_regprop
#define repeat_amg		Perl_repeat_amg
#define repeat_ass_amg		Perl_repeat_ass_amg
#define repeatcpy		Perl_repeatcpy
#define rninstr			Perl_rninstr
#define rshift_amg		Perl_rshift_amg
#define rshift_ass_amg		Perl_rshift_ass_amg
#define rsignal			Perl_rsignal
#define rsignal_restore		Perl_rsignal_restore
#define rsignal_save		Perl_rsignal_save
#define rsignal_state		Perl_rsignal_state
#define runops_debug		Perl_runops_debug
#define runops_standard		Perl_runops_standard
#define rxres_free		Perl_rxres_free
#define rxres_restore		Perl_rxres_restore
#define rxres_save		Perl_rxres_save
#define safecalloc		Perl_safecalloc
#define safefree		Perl_safefree
#define safemalloc		Perl_safemalloc
#define saferealloc		Perl_saferealloc
#define safexcalloc		Perl_safexcalloc
#define safexfree		Perl_safexfree
#define safexmalloc		Perl_safexmalloc
#define safexrealloc		Perl_safexrealloc
#define same_dirent		Perl_same_dirent
#define save_I16		Perl_save_I16
#define save_I32		Perl_save_I32
#define save_aelem		Perl_save_aelem
#define save_aptr		Perl_save_aptr
#define save_ary		Perl_save_ary
#define save_clearsv		Perl_save_clearsv
#define save_delete		Perl_save_delete
#define save_destructor		Perl_save_destructor
#define save_freeop		Perl_save_freeop
#define save_freepv		Perl_save_freepv
#define save_freesv		Perl_save_freesv
#define save_gp			Perl_save_gp
#define save_hash		Perl_save_hash
#define save_helem		Perl_save_helem
#define save_hints		Perl_save_hints
#define save_hptr		Perl_save_hptr
#define save_int		Perl_save_int
#define save_item		Perl_save_item
#define save_iv			Perl_save_iv
#define save_list		Perl_save_list
#define save_long		Perl_save_long
#define save_nogv		Perl_save_nogv
#define save_op			Perl_save_op
#define save_pptr		Perl_save_pptr
#define save_scalar		Perl_save_scalar
#define save_sptr		Perl_save_sptr
#define save_svref		Perl_save_svref
#define save_threadsv		Perl_save_threadsv
#define savepv			Perl_savepv
#define savepvn			Perl_savepvn
#define savestack_grow		Perl_savestack_grow
#define saw_return		Perl_saw_return
#define sawparens		Perl_sawparens
#define scalar			Perl_scalar
#define scalarkids		Perl_scalarkids
#define scalarseq		Perl_scalarseq
#define scalarvoid		Perl_scalarvoid
#define scan_const		Perl_scan_const
#define scan_formline		Perl_scan_formline
#define scan_heredoc		Perl_scan_heredoc
#define scan_hex		Perl_scan_hex
#define scan_ident		Perl_scan_ident
#define scan_inputsymbol	Perl_scan_inputsymbol
#define scan_num		Perl_scan_num
#define scan_oct		Perl_scan_oct
#define scan_pat		Perl_scan_pat
#define scan_prefix		Perl_scan_prefix
#define scan_str		Perl_scan_str
#define scan_subst		Perl_scan_subst
#define scan_trans		Perl_scan_trans
#define scan_word		Perl_scan_word
#define scmp_amg		Perl_scmp_amg
#define scope			Perl_scope
#define screaminstr		Perl_screaminstr
#define seq_amg			Perl_seq_amg
#define setdefout		Perl_setdefout
#define setenv_getix		Perl_setenv_getix
#define sge_amg			Perl_sge_amg
#define sgt_amg			Perl_sgt_amg
#define share_hek		Perl_share_hek
#define sharepvn		Perl_sharepvn
#define sig_name		Perl_sig_name
#define sig_num			Perl_sig_num
#define sighandler		Perl_sighandler
#define simple			Perl_simple
#define sin_amg			Perl_sin_amg
#define skipspace		Perl_skipspace
#define sle_amg			Perl_sle_amg
#define slt_amg			Perl_slt_amg
#define sne_amg			Perl_sne_amg
#define sqrt_amg		Perl_sqrt_amg
#define stack_grow		Perl_stack_grow
#define start_subparse		Perl_start_subparse
#define string_amg		Perl_string_amg
#define sub_crush_depth		Perl_sub_crush_depth
#define subtr_amg		Perl_subtr_amg
#define subtr_ass_amg		Perl_subtr_ass_amg
#define sv_2bool		Perl_sv_2bool
#define sv_2cv			Perl_sv_2cv
#define sv_2io			Perl_sv_2io
#define sv_2iv			Perl_sv_2iv
#define sv_2mortal		Perl_sv_2mortal
#define sv_2nv			Perl_sv_2nv
#define sv_2pv			Perl_sv_2pv
#define sv_2uv			Perl_sv_2uv
#define sv_add_arena		Perl_sv_add_arena
#define sv_backoff		Perl_sv_backoff
#define sv_bless		Perl_sv_bless
#define sv_catpv		Perl_sv_catpv
#define sv_catpv_mg		Perl_sv_catpv_mg
#define sv_catpvf		Perl_sv_catpvf
#define sv_catpvf_mg		Perl_sv_catpvf_mg
#define sv_catpvn		Perl_sv_catpvn
#define sv_catpvn_mg		Perl_sv_catpvn_mg
#define sv_catsv		Perl_sv_catsv
#define sv_catsv_mg		Perl_sv_catsv_mg
#define sv_chop			Perl_sv_chop
#define sv_clean_all		Perl_sv_clean_all
#define sv_clean_objs		Perl_sv_clean_objs
#define sv_clear		Perl_sv_clear
#define sv_cmp			Perl_sv_cmp
#define sv_cmp_locale		Perl_sv_cmp_locale
#define sv_collxfrm		Perl_sv_collxfrm
#define sv_compile_2op		Perl_sv_compile_2op
#define sv_dec			Perl_sv_dec
#define sv_derived_from		Perl_sv_derived_from
#define sv_dump			Perl_sv_dump
#define sv_eq			Perl_sv_eq
#define sv_free			Perl_sv_free
#define sv_free_arenas		Perl_sv_free_arenas
#define sv_gets			Perl_sv_gets
#define sv_grow			Perl_sv_grow
#define sv_inc			Perl_sv_inc
#define sv_insert		Perl_sv_insert
#define sv_isa			Perl_sv_isa
#define sv_isobject		Perl_sv_isobject
#define sv_iv			Perl_sv_iv
#define sv_len			Perl_sv_len
#define sv_magic		Perl_sv_magic
#define sv_mortalcopy		Perl_sv_mortalcopy
#define sv_newmortal		Perl_sv_newmortal
#define sv_newref		Perl_sv_newref
#define sv_nv			Perl_sv_nv
#define sv_peek			Perl_sv_peek
#define sv_pvn			Perl_sv_pvn
#define sv_pvn_force		Perl_sv_pvn_force
#define sv_ref			Perl_sv_ref
#define sv_reftype		Perl_sv_reftype
#define sv_replace		Perl_sv_replace
#define sv_report_used		Perl_sv_report_used
#define sv_reset		Perl_sv_reset
#define sv_setiv		Perl_sv_setiv
#define sv_setiv_mg		Perl_sv_setiv_mg
#define sv_setnv		Perl_sv_setnv
#define sv_setnv_mg		Perl_sv_setnv_mg
#define sv_setptrobj		Perl_sv_setptrobj
#define sv_setpv		Perl_sv_setpv
#define sv_setpv_mg		Perl_sv_setpv_mg
#define sv_setpvf		Perl_sv_setpvf
#define sv_setpvf_mg		Perl_sv_setpvf_mg
#define sv_setpviv		Perl_sv_setpviv
#define sv_setpviv_mg		Perl_sv_setpviv_mg
#define sv_setpvn		Perl_sv_setpvn
#define sv_setpvn_mg		Perl_sv_setpvn_mg
#define sv_setref_iv		Perl_sv_setref_iv
#define sv_setref_nv		Perl_sv_setref_nv
#define sv_setref_pv		Perl_sv_setref_pv
#define sv_setref_pvn		Perl_sv_setref_pvn
#define sv_setsv		Perl_sv_setsv
#define sv_setsv_mg		Perl_sv_setsv_mg
#define sv_setuv		Perl_sv_setuv
#define sv_setuv_mg		Perl_sv_setuv_mg
#define sv_taint		Perl_sv_taint
#define sv_tainted		Perl_sv_tainted
#define sv_true			Perl_sv_true
#define sv_unmagic		Perl_sv_unmagic
#define sv_unref		Perl_sv_unref
#define sv_untaint		Perl_sv_untaint
#define sv_upgrade		Perl_sv_upgrade
#define sv_usepvn		Perl_sv_usepvn
#define sv_usepvn_mg		Perl_sv_usepvn_mg
#define sv_uv			Perl_sv_uv
#define sv_vcatpvfn		Perl_sv_vcatpvfn
#define sv_vsetpvfn		Perl_sv_vsetpvfn
#define taint_env		Perl_taint_env
#define taint_proper		Perl_taint_proper
#define too_few_arguments	Perl_too_few_arguments
#define too_many_arguments	Perl_too_many_arguments
#define unlnk			Perl_unlnk
#define unlock_condpair		Perl_unlock_condpair
#define unshare_hek		Perl_unshare_hek
#define unsharepvn		Perl_unsharepvn
#define utilize			Perl_utilize
#define varies			Perl_varies
#define vivify_defelem		Perl_vivify_defelem
#define vivify_ref		Perl_vivify_ref
#define vtbl_amagic		Perl_vtbl_amagic
#define vtbl_amagicelem		Perl_vtbl_amagicelem
#define vtbl_arylen		Perl_vtbl_arylen
#define vtbl_bm			Perl_vtbl_bm
#define vtbl_collxfrm		Perl_vtbl_collxfrm
#define vtbl_dbline		Perl_vtbl_dbline
#define vtbl_defelem		Perl_vtbl_defelem
#define vtbl_env		Perl_vtbl_env
#define vtbl_envelem		Perl_vtbl_envelem
#define vtbl_fm			Perl_vtbl_fm
#define vtbl_glob		Perl_vtbl_glob
#define vtbl_isa		Perl_vtbl_isa
#define vtbl_isaelem		Perl_vtbl_isaelem
#define vtbl_mglob		Perl_vtbl_mglob
#define vtbl_mutex		Perl_vtbl_mutex
#define vtbl_nkeys		Perl_vtbl_nkeys
#define vtbl_pack		Perl_vtbl_pack
#define vtbl_packelem		Perl_vtbl_packelem
#define vtbl_pos		Perl_vtbl_pos
#define vtbl_regexp		Perl_vtbl_regexp
#define vtbl_sig		Perl_vtbl_sig
#define vtbl_sigelem		Perl_vtbl_sigelem
#define vtbl_substr		Perl_vtbl_substr
#define vtbl_sv			Perl_vtbl_sv
#define vtbl_taint		Perl_vtbl_taint
#define vtbl_uvar		Perl_vtbl_uvar
#define vtbl_vec		Perl_vtbl_vec
#define wait4pid		Perl_wait4pid
#define warn			Perl_warn
#define warn_nl			Perl_warn_nl
#define warn_nosemi		Perl_warn_nosemi
#define warn_reserved		Perl_warn_reserved
#define warn_uninit		Perl_warn_uninit
#define watch			Perl_watch
#define watchaddr		Perl_watchaddr
#define watchok			Perl_watchok
#define whichsig		Perl_whichsig
#define yychar			Perl_yychar
#define yycheck			Perl_yycheck
#define yydebug			Perl_yydebug
#define yydefred		Perl_yydefred
#define yydestruct		Perl_yydestruct
#define yydgoto			Perl_yydgoto
#define yyerrflag		Perl_yyerrflag
#define yyerror			Perl_yyerror
#define yygindex		Perl_yygindex
#define yylen			Perl_yylen
#define yylex			Perl_yylex
#define yylhs			Perl_yylhs
#define yylval			Perl_yylval
#define yyname			Perl_yyname
#define yynerrs			Perl_yynerrs
#define yyparse			Perl_yyparse
#define yyrindex		Perl_yyrindex
#define yyrule			Perl_yyrule
#define yysindex		Perl_yysindex
#define yytable			Perl_yytable
#define yyval			Perl_yyval
#define yywarn			Perl_yywarn

#endif /* EMBED */
