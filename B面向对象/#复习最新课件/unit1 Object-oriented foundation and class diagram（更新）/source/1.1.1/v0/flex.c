/* flex - tool to generate fast lexical analyzers */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#define LINUX 1

#ifndef lint
char copyright[] =
"@(#) Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */


#include "flexdef.h"
#include "version.h"
#include <ctype.h> 
#include "parse.h"

static char flex_version[] = FLEX_VERSION;


/* declare functions that have forward references */

void flexinit PROTO((int, char**));
void readin PROTO((void));
void set_up_initial_allocations PROTO((void));


/* these globals are all defined and commented in flexdef.h */
int printstats, syntaxerror, eofseen, ddebug, trace, nowarn, spprdflt;
int interactive, caseins, lex_compat, useecs, fulltbl, usemecs;
int fullspd, gen_line_dirs, performance_report, backing_up_report;
int C_plus_plus, long_align, use_read, yytext_is_array, csize;
int yymore_used, reject, real_reject, continued_action;
int yymore_really_used, reject_really_used;
int datapos, dataline, linenum;
FILE *skelfile = NULL;

/* ### add for testing ### */
FILE *err = NULL;
/* ####################### */

int skel_ind = 0;
char *action_array;
int action_size, defs1_offset, prolog_offset, action_offset, action_index;
char *infilename = NULL;
int onestate[ONE_STACK_SIZE], onesym[ONE_STACK_SIZE];
int onenext[ONE_STACK_SIZE], onedef[ONE_STACK_SIZE], onesp;
int current_mns, num_rules, num_eof_rules, default_rule;
int current_max_rules, lastnfa;
int *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
int *accptnum, *assoc_rule, *state_type;
int *rule_type, *rule_linenum, *rule_useful;
int current_state_type;
int variable_trailing_context_rules;
int numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
int protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
int numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs, tecfwd[CSIZE + 1];
int tecbck[CSIZE + 1];
int lastsc, current_max_scs, *scset, *scbol, *scxclu, *sceof, *actvsc;
char **scname;
int current_max_dfa_size, current_max_xpairs;
int current_max_template_xpairs, current_max_dfas;
int lastdfa, *nxt, *chk, *tnxt;
int *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
union dfaacc_union *dfaacc;
int *accsiz, *dhash, numas;
int numsnpairs, jambase, jamstate;
int lastccl, current_maxccls, *cclmap, *ccllen, *cclng, cclreuse;
int current_max_ccl_tbl_size;
Char *ccltbl;
char nmstr[MAXLINE];
int sectnum, nummt, hshcol, dfaeql, numeps, eps2, num_reallocs;
int tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
int num_backing_up, bol_needed;
FILE *backing_up_file;
int end_of_buffer_state;
char **input_files;
int num_input_files;
char *program_name;

#ifndef SHORT_FILE_NAMES
static char *outfile_template = "lex.%s.%s";
#else
static char *outfile_template = "lex%s.%s";
#endif
static char outfile_path[64];

static int outfile_created = 0;
static int use_stdout;
static char *skelname = NULL;
static char *prefix = "yy";


int main( argc, argv )
int argc;
char **argv;
	{
	int i;

/* ### add for testing ### */
	if(--argc >0){
		err = fopen( *++argv, "w" );
		--argv; ++argc;
	}
/* ####################### */

	flexinit( argc, argv );

	readin();

	if ( syntaxerror )
		flexend( 1 );

	if ( yymore_really_used == REALLY_USED )
		yymore_used = true;
	else if ( yymore_really_used == REALLY_NOT_USED )
		yymore_used = false;

	if ( reject_really_used == REALLY_USED )
		reject = true;
	else if ( reject_really_used == REALLY_NOT_USED )
		reject = false;

	if ( performance_report > 0 )
		{
		if ( lex_compat )
			{
			fprintf( err,
"-l AT&T lex compatibility option entails a large performance penalty\n" );
			fprintf( err,
" and may be the actual source of other reported performance penalties\n" );
			}

		if ( performance_report > 1 )
			{
			if ( interactive )
				fprintf( err,
		"-I (interactive) entails a minor performance penalty\n" );

			if ( yymore_used )
				fprintf( err,
			"yymore() entails a minor performance penalty\n" );
			}

		if ( reject )
			fprintf( err,
			"REJECT entails a large performance penalty\n" );

		if ( variable_trailing_context_rules )
			fprintf( err,
"Variable trailing context rules entail a large performance penalty\n" );
		}

	if ( reject )
		real_reject = true;

	if ( variable_trailing_context_rules )
		reject = true;

	if ( (fulltbl || fullspd) && reject )
		{
		if ( real_reject )
			flexerror( "REJECT cannot be used with -f or -F" );
		else
			flexerror(
	"variable trailing context rules cannot be used with -f or -F" );
		}

	ntod();

	for ( i = 1; i <= num_rules; ++i )
		if ( ! rule_useful[i] && i != default_rule )
			line_warning( "rule cannot be matched",
					rule_linenum[i] );

	if ( spprdflt && ! reject && rule_useful[default_rule] )
		line_warning( "-s option given but default rule can be matched",
			rule_linenum[default_rule] );

	/* Generate the C state transition tables from the DFA. */
	make_tables();

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend( 0 );


	return 0;	/* keep compilers/lint happy */
	}


/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

void flexend( exit_status )
int exit_status;

	{
	int tblsiz;
	int unlink();

	if ( skelfile != NULL )
		{
		if ( ferror( skelfile ) )
			flexfatal(
				"error occurred when reading skeleton file" );

		else if ( fclose( skelfile ) )
			flexfatal(
				"error occurred when closing skeleton file" );
		}

	if ( exit_status != 0 && outfile_created )
		{
		if ( ferror( stdout ) )
			flexfatal( "error occurred when writing output file" );

		else if ( fclose( stdout ) )
			flexfatal( "error occurred when closing output file" );

		else if ( unlink( outfile_path ) )
			flexfatal( "error occurred when deleting output file" );
		}

	if ( backing_up_report && backing_up_file )
		{
		if ( num_backing_up == 0 )
			fprintf( backing_up_file, "No backing up.\n" );
		else if ( fullspd || fulltbl )
			fprintf( backing_up_file,
				"%d backing up (non-accepting) states.\n",
				num_backing_up );
		else
			fprintf( backing_up_file,
				"Compressed tables always back up.\n" );

		if ( ferror( backing_up_file ) )
			flexfatal( "error occurred when writing backup file" );

		else if ( fclose( backing_up_file ) )
			flexfatal( "error occurred when closing backup file" );
		}

	if ( printstats )
		{
		fprintf( err, "%s version %s usage statistics:\n",
			program_name, flex_version );

		fprintf( err, "  scanner options: -" );

		if ( C_plus_plus )
			putc( '+', err );
		if ( backing_up_report )
			putc( 'b', err );
		if ( ddebug )
			putc( 'd', err );
		if ( caseins )
			putc( 'i', err );
		if ( lex_compat )
			putc( 'l', err );
		if ( performance_report > 0 )
			putc( 'p', err );
		if ( performance_report > 1 )
			putc( 'p', err );
		if ( spprdflt )
			putc( 's', err );
		if ( use_stdout )
			putc( 't', err );
		if ( printstats )
			putc( 'v', err );	/* always true! */
		if ( nowarn )
			putc( 'w', err );
		if ( ! interactive )
			putc( 'B', err );
		if ( interactive )
			putc( 'I', err );
		if ( ! gen_line_dirs )
			putc( 'L', err );
		if ( trace )
			putc( 'T', err );
		if ( csize == 128 )
			putc( '7', err );
		else
			putc( '8', err );

		fprintf( err, " -C" );

		if ( long_align )
			putc( 'a', err );
		if ( fulltbl )
			putc( 'f', err );
		if ( fullspd )
			putc( 'F', err );
		if ( useecs )
			putc( 'e', err );
		if ( usemecs )
			putc( 'm', err );
		if ( use_read )
			putc( 'r', err );

		if ( skelname )
			fprintf( err, " -S%s", skelname );

		if ( yy_strcmp( prefix, "yy" ) )
			fprintf( err, " -P%s", prefix );

		putc( '\n', err );

		fprintf( err, "  %d/%d NFA states\n", lastnfa, current_mns );
		fprintf( err, "  %d/%d DFA states (%d words)\n", lastdfa,
			current_max_dfas, totnst );
		fprintf( err, "  %d rules\n",
		num_rules + num_eof_rules - 1 /* - 1 for def. rule */ );

		if ( num_backing_up == 0 )
			fprintf( err, "  No backing up\n" );
		else if ( fullspd || fulltbl )
			fprintf( err,
				"  %d backing-up (non-accepting) states\n",
				num_backing_up );
		else
			fprintf( err,
				"  Compressed tables always back-up\n" );

		if ( bol_needed )
			fprintf( err,
				"  Beginning-of-line patterns used\n" );

		fprintf( err, "  %d/%d start conditions\n", lastsc,
			current_max_scs );
		fprintf( err,
			"  %d epsilon states, %d double epsilon states\n",
			numeps, eps2 );

		if ( lastccl == 0 )
			fprintf( err, "  no character classes\n" );
		else
			fprintf( err,
	"  %d/%d character classes needed %d/%d words of storage, %d reused\n",
				lastccl, current_maxccls,
				cclmap[lastccl] + ccllen[lastccl],
				current_max_ccl_tbl_size, cclreuse );

		fprintf( err, "  %d state/nextstate pairs created\n",
			numsnpairs );
		fprintf( err, "  %d/%d unique/duplicate transitions\n",
			numuniq, numdup );

		if ( fulltbl )
			{
			tblsiz = lastdfa * numecs;
			fprintf( err, "  %d table entries\n", tblsiz );
			}

		else
			{
			tblsiz = 2 * (lastdfa + numtemps) + 2 * tblend;

			fprintf( err, "  %d/%d base-def entries created\n",
				lastdfa + numtemps, current_max_dfas );
			fprintf( err,
				"  %d/%d (peak %d) nxt-chk entries created\n",
				tblend, current_max_xpairs, peakpairs );
			fprintf( err,
			"  %d/%d (peak %d) template nxt-chk entries created\n",
				numtemps * nummecs, current_max_template_xpairs,
				numtemps * numecs );
			fprintf( err, "  %d empty table entries\n", nummt );
			fprintf( err, "  %d protos created\n", numprots );
			fprintf( err, "  %d templates created, %d uses\n",
				numtemps, tmpuses );
			}

		if ( useecs )
			{
			tblsiz = tblsiz + csize;
			fprintf( err,
				"  %d/%d equivalence classes created\n",
				numecs, csize );
			}

		if ( usemecs )
			{
			tblsiz = tblsiz + numecs;
			fprintf( err,
				"  %d/%d meta-equivalence classes created\n",
				nummecs, csize );
			}

		fprintf( err,
			"  %d (%d saved) hash collisions, %d DFAs equal\n",
			hshcol, hshsave, dfaeql );
		fprintf( err, "  %d sets of reallocations needed\n",
			num_reallocs );
		fprintf( err, "  %d total table entries needed\n", tblsiz );
		}

#ifndef VMS
	exit( exit_status );
#else
	exit( exit_status + 1 );
#endif
	}


/* flexinit - initialize flex */

void flexinit( argc, argv )
int argc;
char **argv;
	{
	int i, sawcmpflag;
	int csize_given, interactive_given;
	char *arg, *mktemp();

	printstats = syntaxerror = trace = spprdflt = caseins = false;
	lex_compat = false;
	C_plus_plus = backing_up_report = ddebug = fulltbl = fullspd = false;
	long_align = nowarn = yymore_used = continued_action = reject = false;
	yytext_is_array = yymore_really_used = reject_really_used = false;
	gen_line_dirs = usemecs = useecs = true;
	performance_report = 0;

	sawcmpflag = false;
	use_read = use_stdout = false;
	csize_given = false;
	interactive_given = false;

	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array( action_size );
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';
/* Commented by Amit Goel on 5th September 2001 to remove nomdeterminism */
/*	program_name = argv[0];  */
/* Added by Amit Goel on 5th September 2001 */
        program_name = "Executable";

	if ( program_name[0] != '\0' &&
	     program_name[yy_strlen( program_name ) - 1] == '+' )
		C_plus_plus = true;

/* ### add for testing ### */
	++argv;--argc;
/* ####################### */

	/* read flags */
	for ( --argc, ++argv; argc ; --argc, ++argv )
		{
		if ( argv[0][0] != '-' || argv[0][1] == '\0' )
			break;

		arg = argv[0];

		for ( i = 1; arg[i] != '\0'; ++i )
			switch ( arg[i] )
				{
				case '+':
					C_plus_plus = true;
					break;

				case 'B':
					interactive = false;
					interactive_given = true;
					break;

				case 'b':
					backing_up_report = true;
					break;

				case 'c':
					fprintf( err,
	"%s: Assuming use of deprecated -c flag is really intended to be -C\n",
					program_name );

					/* fall through */

				case 'C':
					if ( i != 1 )
						flexerror(
					"-C flag must be given separately" );

					if ( ! sawcmpflag )
						{
						useecs = false;
						usemecs = false;
						fulltbl = false;
						sawcmpflag = true;
						}

					for ( ++i; arg[i] != '\0'; ++i )
						switch ( arg[i] )
							{
							case 'a':
								long_align =
									true;
								break;

							case 'e':
								useecs = true;
								break;

							case 'F':
								fullspd = true;
								break;

							case 'f':
								fulltbl = true;
								break;

							case 'm':
								usemecs = true;
								break;

							case 'r':
								use_read = true;
								break;

							default:
								lerrif(
						"unknown -C option '%c'",
								(int) arg[i] );
								break;
							}

					goto get_next_arg;

				case 'd':
					ddebug = true;
					break;

				case 'f':
					useecs = usemecs = false;
					use_read = fulltbl = true;
					break;

				case 'F':
					useecs = usemecs = false;
					use_read = fullspd = true;
					break;

				case 'h':
					usage();
					exit( 0 );

				case 'I':
					interactive = true;
					interactive_given = true;
					break;

				case 'i':
					caseins = true;
					break;

				case 'l':
					lex_compat = true;
					break;

				case 'L':
					gen_line_dirs = false;
					break;

				case 'n':
					/* Stupid do-nothing deprecated
					 * option.
					 */
					break;

				case 'P':
					if ( i != 1 )
						flexerror(
					"-P flag must be given separately" );

					prefix = arg + i + 1;
					goto get_next_arg;

				case 'p':
					++performance_report;
					break;

				case 'S':
					if ( i != 1 )
						flexerror(
					"-S flag must be given separately" );

					skelname = arg + i + 1;
					goto get_next_arg;

				case 's':
					spprdflt = true;
					break;

				case 't':
					use_stdout = true;
					break;

				case 'T':
					trace = true;
					break;

				case 'v':
					printstats = true;
					break;

				case 'V':
					fprintf( err, "%s version %s\n",
						program_name, flex_version );
					exit( 0 );

				case 'w':
					nowarn = true;
					break;

				case '7':
					csize = 128;
					csize_given = true;
					break;

				case '8':
					csize = CSIZE;
					csize_given = true;
					break;

				default:
					fprintf( err,
						"%s: unknown flag '%c'\n",
						program_name, (int) arg[i] );
					usage();
					exit( 1 );
				}

		/* Used by -C, -S and -P flags in lieu of a "continue 2"
		 * control.
		 */
		get_next_arg: ;
		}

	if ( ! csize_given )
		{
		if ( (fulltbl || fullspd) && ! useecs )
			csize = DEFAULT_CSIZE;
		else
			csize = CSIZE;
		}

	if ( ! interactive_given )
		{
		if ( fulltbl || fullspd )
			interactive = false;
		else
			interactive = true;
		}

	if ( lex_compat )
		{
		if ( C_plus_plus )
			flexerror( "Can't use -+ with -l option" );

		if ( fulltbl || fullspd )
			flexerror( "Can't use -f or -F with -l option" );

		/* Don't rely on detecting use of yymore() and REJECT,
		 * just assume they'll be used.
		 */
		yymore_really_used = reject_really_used = true;

		yytext_is_array = true;
		use_read = false;
		}

	if ( (fulltbl || fullspd) && usemecs )
		flexerror( "-Cf/-CF and -Cm don't make sense together" );

	if ( (fulltbl || fullspd) && interactive )
		flexerror( "-Cf/-CF and -I are incompatible" );

	if ( fulltbl && fullspd )
		flexerror( "-Cf and -CF are mutually exclusive" );

	if ( C_plus_plus && fullspd )
		flexerror( "Can't use -+ with -CF option" );

	if ( ! use_stdout )
		{
		FILE *prev_stdout;
		char *suffix;

		if ( C_plus_plus )
			suffix = "cc";
		else
			suffix = "c";

		sprintf( outfile_path, outfile_template, prefix, suffix );

		prev_stdout = freopen( outfile_path, "w", stdout );

		if ( prev_stdout == NULL )
			lerrsf( "could not create %s", outfile_path );

		outfile_created = 1;
		}

	num_input_files = argc;
	input_files = argv;
	set_input_file( num_input_files > 0 ? input_files[0] : NULL );
	

	if ( backing_up_report )
		{
#ifndef SHORT_FILE_NAMES
		backing_up_file = fopen( "lex.backup", "w" );
#else
		backing_up_file = fopen( "lex.bck", "w" );
#endif

		if ( backing_up_file == NULL )
			flexerror( "could not create lex.backup" );
		}

	else
		backing_up_file = NULL;


	lastccl = 0;
	lastsc = 0;

	if ( skelname && (skelfile = fopen( skelname, "r" )) == NULL )
		lerrsf( "can't open skeleton file %s", skelname );

	if ( yy_strcmp( prefix, "yy" ) )
		{
#define GEN_PREFIX(name) printf( "#define yy%s %s%s\n", name, prefix, name );
		GEN_PREFIX( "FlexLexer" );
		GEN_PREFIX( "_create_buffer" );
		GEN_PREFIX( "_delete_buffer" );
		GEN_PREFIX( "_flex_debug" );
		GEN_PREFIX( "_init_buffer" );
		GEN_PREFIX( "_load_buffer_state" );
		GEN_PREFIX( "_switch_to_buffer" );
		GEN_PREFIX( "in" );
		GEN_PREFIX( "leng" );
		GEN_PREFIX( "lex" );
		GEN_PREFIX( "out" );
		GEN_PREFIX( "restart" );
		GEN_PREFIX( "text" );
		GEN_PREFIX( "wrap" );
		printf( "\n" );
		}


	lastdfa = lastnfa = 0;
	num_rules = num_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = num_reallocs = hshcol = dfaeql = totnst = 0;
	numuniq = numdup = hshsave = eofseen = datapos = dataline = 0;
	num_backing_up = onesp = numprots = 0;
	variable_trailing_context_rules = bol_needed = false;

	linenum = sectnum = 1;
	firstprot = NIL;

	/* Used in mkprot() so that the first proto goes in slot 1
	 * of the proto queue.
	 */
	lastprot = 1;

	if ( useecs )
		{
		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to csize, since ecgroup[csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		for ( i = 2; i <= csize; ++i )
			{
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
			}

		nextecm[csize] = NIL;
		}

	else
		{
		/* Put everything in its own equivalence class. */
		for ( i = 1; i <= csize; ++i )
			{
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
			}
		}

	set_up_initial_allocations();
	}


/* readin - read in the rules section of the input file(s) */

void readin()
	{
	skelout();

	line_directive_out( (FILE *) 0 );

	if ( yyparse() )
		{
		pinpoint_message( "fatal parse error" );
		flexend( 1 );
		}

	if ( csize == 256 )
		puts( "typedef unsigned char YY_CHAR;" );
	else
		puts( "typedef char YY_CHAR;" );

	if ( C_plus_plus )
		{
		puts( "#define yytext_ptr yytext" );

		if ( interactive )
			puts( "#define YY_INTERACTIVE" );
		}

	if ( fullspd )
		printf(
		"typedef const struct yy_trans_info *yy_state_type;\n" );
	else if ( ! C_plus_plus )
		printf( "typedef int yy_state_type;\n" );

	if ( reject )
		printf( "\n#define YY_USES_REJECT\n" );

	if ( ddebug )
		puts( "\n#define FLEX_DEBUG" );

	if ( lex_compat )
		{
		printf( "FILE *yyin = stdin, *yyout = stdout;\n" );
		printf( "extern int yylineno;\n" );
		printf( "int yylineno = 1;\n" );
		}
	else if ( ! C_plus_plus )
		printf( "FILE *yyin = (FILE *) 0, *yyout = (FILE *) 0;\n" );

	if ( C_plus_plus )
		printf( "\n#include \"FlexLexer.h\"\n" );

	else
		{
		if ( yytext_is_array )
			puts( "extern char yytext[];\n" );

		else
			{
			puts( "extern char *yytext;" );
			puts( "#define yytext_ptr yytext" );
			}
		}

	if ( useecs )
		numecs = cre8ecs( nextecm, ecgroup, csize );
	else
		numecs = csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[csize];
	NUL_ec = abs( ecgroup[0] );

	if ( useecs )
		ccl2ecl();
	}


/* set_up_initial_allocations - allocate memory for internal tables */

void set_up_initial_allocations()
	{
	current_mns = INITIAL_MNS;
	firstst = allocate_integer_array( current_mns );
	lastst = allocate_integer_array( current_mns );
	finalst = allocate_integer_array( current_mns );
	transchar = allocate_integer_array( current_mns );
	trans1 = allocate_integer_array( current_mns );
	trans2 = allocate_integer_array( current_mns );
	accptnum = allocate_integer_array( current_mns );
	assoc_rule = allocate_integer_array( current_mns );
	state_type = allocate_integer_array( current_mns );

	current_max_rules = INITIAL_MAX_RULES;
	rule_type = allocate_integer_array( current_max_rules );
	rule_linenum = allocate_integer_array( current_max_rules );
	rule_useful = allocate_integer_array( current_max_rules );

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array( current_max_scs );
	scbol = allocate_integer_array( current_max_scs );
	scxclu = allocate_integer_array( current_max_scs );
	sceof = allocate_integer_array( current_max_scs );
	scname = allocate_char_ptr_array( current_max_scs );
	actvsc = allocate_integer_array( current_max_scs );

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array( current_maxccls );
	ccllen = allocate_integer_array( current_maxccls );
	cclng = allocate_integer_array( current_maxccls );

	current_max_ccl_tbl_size = INITIAL_MAX_CCL_TBL_SIZE;
	ccltbl = allocate_Character_array( current_max_ccl_tbl_size );

	current_max_dfa_size = INITIAL_MAX_DFA_SIZE;

	current_max_xpairs = INITIAL_MAX_XPAIRS;
	nxt = allocate_integer_array( current_max_xpairs );
	chk = allocate_integer_array( current_max_xpairs );

	current_max_template_xpairs = INITIAL_MAX_TEMPLATE_XPAIRS;
	tnxt = allocate_integer_array( current_max_template_xpairs );

	current_max_dfas = INITIAL_MAX_DFAS;
	base = allocate_integer_array( current_max_dfas );
	def = allocate_integer_array( current_max_dfas );
	dfasiz = allocate_integer_array( current_max_dfas );
	accsiz = allocate_integer_array( current_max_dfas );
	dhash = allocate_integer_array( current_max_dfas );
	dss = allocate_int_ptr_array( current_max_dfas );
	dfaacc = allocate_dfaacc_union( current_max_dfas );

	nultrans = (int *) 0;
	}


void usage()
	{
	fprintf( err,
"%s [-bcdfhilnpstvwBFILTV78+ -C[aefFmr] -Pprefix -Sskeleton] [file ...]\n",
		program_name );

	fprintf( err,
		"\t-b  generate backing-up information to lex.backup\n" );
	fprintf( err, "\t-c  do-nothing POSIX option\n" );
	fprintf( err, "\t-d  turn on debug mode in generated scanner\n" );
	fprintf( err, "\t-f  generate fast, large scanner\n" );
	fprintf( err, "\t-h  produce this help message\n" );
	fprintf( err, "\t-i  generate case-insensitive scanner\n" );
	fprintf( err, "\t-l  maximal compatibility with original lex\n" );
	fprintf( err, "\t-n  do-nothing POSIX option\n" );
	fprintf( err, "\t-p  generate performance report to stderr\n" );
	fprintf( err,
		"\t-s  suppress default rule to ECHO unmatched text\n" );
	fprintf( err,
	"\t-t  write generated scanner on stdout instead of lex.yy.c\n" );
	fprintf( err,
		"\t-v  write summary of scanner statistics to stderr\n" );
	fprintf( err, "\t-w  do not generate warnings\n" );
	fprintf( err, "\t-B  generate batch scanner (opposite of -I)\n" );
	fprintf( err,
		"\t-F  use alternative fast scanner representation\n" );
	fprintf( err,
		"\t-I  generate interactive scanner (opposite of -B)\n" );
	fprintf( err, "\t-L  suppress #line directives in scanner\n" );
	fprintf( err, "\t-T  %s should run in trace mode\n", program_name );
	fprintf( err, "\t-V  report %s version\n", program_name );
	fprintf( err, "\t-7  generate 7-bit scanner\n" );
	fprintf( err, "\t-8  generate 8-bit scanner\n" );
	fprintf( err, "\t-+  generate C++ scanner class\n" );
	fprintf( err,
	"\t-C  specify degree of table compression (default is -Cem):\n" );
	fprintf( err,
	"\t\t-Ca  trade off larger tables for better memory alignment\n" );
	fprintf( err, "\t\t-Ce  construct equivalence classes\n" );
	fprintf( err,
	"\t\t-Cf  do not compress scanner tables; use -f representation\n" );
	fprintf( err,
	"\t\t-CF  do not compress scanner tables; use -F representation\n" );
	fprintf( err, "\t\t-Cm  construct meta-equivalence classes\n" );
	fprintf( err,
		"\t\t-Cr  use read() instead of stdio for scanner input\n" );
	fprintf( err, "\t-P  specify scanner prefix other than \"yy\"\n" );
	fprintf( err, "\t-S  specify skeleton file\n" );
	}
/* ccl - routines for character classes */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */


/* ccladd - add a single character to a ccl */

void ccladd( cclp, ch )
int cclp;
int ch;
	{
	int ind, len, newpos, i;

	check_char( ch );

	len = ccllen[cclp];
	ind = cclmap[cclp];

	/* check to see if the character is already in the ccl */

	for ( i = 0; i < len; ++i )
		if ( ccltbl[ind + i] == ch )
			return;

	newpos = ind + len;

	if ( newpos >= current_max_ccl_tbl_size )
		{
		current_max_ccl_tbl_size += MAX_CCL_TBL_SIZE_INCREMENT;

		++num_reallocs;

		ccltbl = reallocate_Character_array( ccltbl,
						current_max_ccl_tbl_size );
		}

	ccllen[cclp] = len + 1;
	ccltbl[newpos] = ch;
	}


/* cclinit - return an empty ccl */

int cclinit()
	{
	if ( ++lastccl >= current_maxccls )
		{
		current_maxccls += MAX_CCLS_INCREMENT;

		++num_reallocs;

		cclmap = reallocate_integer_array( cclmap, current_maxccls );
		ccllen = reallocate_integer_array( ccllen, current_maxccls );
		cclng = reallocate_integer_array( cclng, current_maxccls );
		}

	if ( lastccl == 1 )
		/* we're making the first ccl */
		cclmap[lastccl] = 0;

	else
		/* The new pointer is just past the end of the last ccl.
		 * Since the cclmap points to the \first/ character of a
		 * ccl, adding the length of the ccl to the cclmap pointer
		 * will produce a cursor to the first free space.
		 */
		cclmap[lastccl] = cclmap[lastccl - 1] + ccllen[lastccl - 1];

	ccllen[lastccl] = 0;
	cclng[lastccl] = 0;	/* ccl's start out life un-negated */

	return lastccl;
	}


/* cclnegate - negate the given ccl */

void cclnegate( cclp )
int cclp;
	{
	cclng[cclp] = 1;
	}


/* list_character_set - list the members of a set of characters in CCL form
 *
 * Writes to the given file a character-class representation of those
 * characters present in the given CCL.  A character is present if it
 * has a non-zero value in the cset array.
 */

void list_character_set( file, cset )
FILE *file;
int cset[];
	{
	register int i;

	putc( '[', file );

	for ( i = 0; i < csize; ++i )
		{
		if ( cset[i] )
			{
			register int start_char = i;

			putc( ' ', file );

			fputs( readable_form( i ), file );

			while ( ++i < csize && cset[i] )
				;

			if ( i - 1 > start_char )
				/* this was a run */
				fprintf( file, "-%s", readable_form( i - 1 ) );

			putc( ' ', file );
			}
		}

	putc( ']', file );
	}
/* dfa - DFA construction routines */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */



/* declare functions that have forward references */

void dump_associated_rules PROTO((FILE*, int));
void dump_transitions PROTO((FILE*, int[]));
void sympartition PROTO((int[], int, int[], int[]));
int symfollowset PROTO((int[], int, int, int[]));


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

void check_for_backing_up( ds, state )
int ds;
int state[];
	{
	if ( (reject && ! dfaacc[ds].dfaacc_set) ||
	     (! reject && ! dfaacc[ds].dfaacc_state) )
		{ /* state is non-accepting */
		++num_backing_up;

		if ( backing_up_report )
			{
			fprintf( backing_up_file,
				"State #%d is non-accepting -\n", ds );

			/* identify the state */
			dump_associated_rules( backing_up_file, ds );

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions( backing_up_file, state );

			putc( '\n', backing_up_file );
			}
		}
	}


/* check_trailing_context - check to see if NFA state set constitutes
 *                          "dangerous" trailing context
 *
 * synopsis
 *    void check_trailing_context( int nfa_states[num_states+1], int num_states,
 *				int accset[nacc+1], int nacc );
 *
 * NOTES
 *  Trailing context is "dangerous" if both the head and the trailing
 *  part are of variable size \and/ there's a DFA state which contains
 *  both an accepting state for the head part of the rule and NFA states
 *  which occur after the beginning of the trailing context.
 *
 *  When such a rule is matched, it's impossible to tell if having been
 *  in the DFA state indicates the beginning of the trailing context or
 *  further-along scanning of the pattern.  In these cases, a warning
 *  message is issued.
 *
 *    nfa_states[1 .. num_states] is the list of NFA states in the DFA.
 *    accset[1 .. nacc] is the list of accepting numbers for the DFA state.
 */

void check_trailing_context( nfa_states, num_states, accset, nacc )
int *nfa_states, num_states;
int *accset;
register int nacc;
	{
	register int i, j;

	for ( i = 1; i <= num_states; ++i )
		{
		int ns = nfa_states[i];
		register int type = state_type[ns];
		register int ar = assoc_rule[ns];

		if ( type == STATE_NORMAL || rule_type[ar] != RULE_VARIABLE )
			{ /* do nothing */
			}

		else if ( type == STATE_TRAILING_CONTEXT )
			{
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			for ( j = 1; j <= nacc; ++j )
				if ( accset[j] & YY_TRAILING_HEAD_MASK )
					{
					line_warning(
						"dangerous trailing context",
						rule_linenum[ar] );
					return;
					}
			}
		}
	}


/* dump_associated_rules - list the rules associated with a DFA state
 *
 * Goes through the set of NFA states associated with the DFA and
 * extracts the first MAX_ASSOC_RULES unique rules, sorts them,
 * and writes a report to the given file.
 */

void dump_associated_rules( file, ds )
FILE *file;
int ds;
	{
	register int i, j;
	register int num_associated_rules = 0;
	int rule_set[MAX_ASSOC_RULES + 1];
	int *dset = dss[ds];
	int size = dfasiz[ds];

	for ( i = 1; i <= size; ++i )
		{
		register int rule_num = rule_linenum[assoc_rule[dset[i]]];

		for ( j = 1; j <= num_associated_rules; ++j )
			if ( rule_num == rule_set[j] )
				break;

		if ( j > num_associated_rules )
			{ /* new rule */
			if ( num_associated_rules < MAX_ASSOC_RULES )
				rule_set[++num_associated_rules] = rule_num;
			}
		}

	bubble( rule_set, num_associated_rules );

	fprintf( file, " associated rule line numbers:" );

	for ( i = 1; i <= num_associated_rules; ++i )
		{
		if ( i % 8 == 1 )
			putc( '\n', file );

		fprintf( file, "\t%d", rule_set[i] );
		}

	putc( '\n', file );
	}


/* dump_transitions - list the transitions associated with a DFA state
 *
 * synopsis
 *     dump_transitions( FILE *file, int state[numecs] );
 *
 * Goes through the set of out-transitions and lists them in human-readable
 * form (i.e., not as equivalence classes); also lists jam transitions
 * (i.e., all those which are not out-transitions, plus EOF).  The dump
 * is done to the given file.
 */

void dump_transitions( file, state )
FILE *file;
int state[];
	{
	register int i, ec;
	int out_char_set[CSIZE];

	for ( i = 0; i < csize; ++i )
		{
		ec = abs( ecgroup[i] );
		out_char_set[i] = state[ec];
		}

	fprintf( file, " out-transitions: " );

	list_character_set( file, out_char_set );

	/* now invert the members of the set to get the jam transitions */
	for ( i = 0; i < csize; ++i )
		out_char_set[i] = ! out_char_set[i];

	fprintf( file, "\n jam-transitions: EOF " );

	list_character_set( file, out_char_set );

	putc( '\n', file );
	}


/* epsclosure - construct the epsilon closure of a set of ndfa states
 *
 * synopsis
 *    int *epsclosure( int t[num_states], int *numstates_addr,
 *			int accset[num_rules+1], int *nacc_addr,
 *			int *hashval_addr );
 *
 * NOTES
 *  The epsilon closure is the set of all states reachable by an arbitrary
 *  number of epsilon transitions, which themselves do not have epsilon
 *  transitions going out, unioned with the set of states which have non-null
 *  accepting numbers.  t is an array of size numstates of nfa state numbers.
 *  Upon return, t holds the epsilon closure and *numstates_addr is updated.
 *  accset holds a list of the accepting numbers, and the size of accset is
 *  given by *nacc_addr.  t may be subjected to reallocation if it is not
 *  large enough to hold the epsilon closure.
 *
 *  hashval is the hash value for the dfa corresponding to the state set.
 */

int *epsclosure( t, ns_addr, accset, nacc_addr, hv_addr )
int *t, *ns_addr, accset[], *nacc_addr, *hv_addr;
	{
	register int stkpos, ns, tsp;
	int numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	int stkend, nstate;
	static int did_stk_init = false, *stk; 

#define MARK_STATE(state) \
trans1[state] = trans1[state] - MARKER_DIFFERENCE;

#define IS_MARKED(state) (trans1[state] < 0)

#define UNMARK_STATE(state) \
trans1[state] = trans1[state] + MARKER_DIFFERENCE;

#define CHECK_ACCEPT(state) \
{ \
nfaccnum = accptnum[state]; \
if ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}

#define DO_REALLOCATION \
{ \
current_max_dfa_size += MAX_DFA_SIZE_INCREMENT; \
++num_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_size ); \
stk = reallocate_integer_array( stk, current_max_dfa_size ); \
} \

#define PUT_ON_STACK(state) \
{ \
if ( ++stkend >= current_max_dfa_size ) \
DO_REALLOCATION \
stk[stkend] = state; \
MARK_STATE(state) \
}

#define ADD_STATE(state) \
{ \
if ( ++numstates >= current_max_dfa_size ) \
DO_REALLOCATION \
t[numstates] = state; \
hashval += state; \
}

#define STACK_STATE(state) \
{ \
PUT_ON_STACK(state) \
CHECK_ACCEPT(state) \
if ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
ADD_STATE(state) \
}


	if ( ! did_stk_init )
		{
		stk = allocate_integer_array( current_max_dfa_size );
		did_stk_init = true;
		}

	nacc = stkend = hashval = 0;

	for ( nstate = 1; nstate <= numstates; ++nstate )
		{
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		if ( ! IS_MARKED(ns) )
			{
			PUT_ON_STACK(ns)
			CHECK_ACCEPT(ns)
			hashval += ns;
			}
		}

	for ( stkpos = 1; stkpos <= stkend; ++stkpos )
		{
		ns = stk[stkpos];
		transsym = transchar[ns];

		if ( transsym == SYM_EPSILON )
			{
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			if ( tsp != NO_TRANSITION )
				{
				if ( ! IS_MARKED(tsp) )
					STACK_STATE(tsp)

				tsp = trans2[ns];

				if ( tsp != NO_TRANSITION && ! IS_MARKED(tsp) )
					STACK_STATE(tsp)
				}
			}
		}

	/* Clear out "visit" markers. */

	for ( stkpos = 1; stkpos <= stkend; ++stkpos )
		{
		if ( IS_MARKED(stk[stkpos]) )
			UNMARK_STATE(stk[stkpos])
		else
			flexfatal( "consistency check failed in epsclosure()" );
		}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	return t;
	}


/* increase_max_dfas - increase the maximum number of DFAs */

void increase_max_dfas()
	{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++num_reallocs;

	base = reallocate_integer_array( base, current_max_dfas );
	def = reallocate_integer_array( def, current_max_dfas );
	dfasiz = reallocate_integer_array( dfasiz, current_max_dfas );
	accsiz = reallocate_integer_array( accsiz, current_max_dfas );
	dhash = reallocate_integer_array( dhash, current_max_dfas );
	dss = reallocate_int_ptr_array( dss, current_max_dfas );
	dfaacc = reallocate_dfaacc_union( dfaacc, current_max_dfas );

	if ( nultrans )
		nultrans =
			reallocate_integer_array( nultrans, current_max_dfas );
	}


/* ntod - convert an ndfa to a dfa
 *
 * Creates the dfa corresponding to the ndfa we've constructed.  The
 * dfa starts out in state #1.
 */

void ntod()
	{
	int *accset, ds, nacc, newds;
	int sym, hashval, numstates, dsize;
	int num_full_table_rows;	/* used only for -f */
	int *nset, *dset;
	int targptr, totaltrans, i, comstate, comfreq, targ;
	int *epsclosure(), snstods(), symlist[CSIZE + 1];
	int num_start_states;
	int todo_head, todo_next;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	int duplist[CSIZE + 1], state[CSIZE + 1];
	int targfreq[CSIZE + 1], targstate[CSIZE + 1];

	accset = allocate_integer_array( num_rules + 1 );
	nset = allocate_integer_array( current_max_dfa_size );

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_head = todo_next = 0;

	for ( i = 0; i <= csize; ++i )
		{
		duplist[i] = NIL;
		symlist[i] = false;
		}

	for ( i = 0; i <= num_rules; ++i )
		accset[i] = NIL;

	if ( trace )
		{
		dumpnfa( scset[1] );
		fputs( "\n\nDFA Dump:\n\n", err );
		}

	inittbl();

	/* Check to see whether we should build a separate table for
	 * transitions on NUL characters.  We don't do this for full-speed
	 * (-F) scanners, since for them we don't have a simple state
	 * number lying around with which to index the table.  We also
	 * don't bother doing it for scanners unless (1) NUL is in its own
	 * equivalence class (indicated by a positive value of
	 * ecgroup[NUL]), (2) NUL's equivalence class is the last
	 * equivalence class, and (3) the number of equivalence classes is
	 * the same as the number of characters.  This latter case comes
	 * about when useecs is false or when its true but every character
	 * still manages to land in its own class (unlikely, but it's
	 * cheap to check for).  If all these things are true then the
	 * character code needed to represent NUL's equivalence class for
	 * indexing the tables is going to take one more bit than the
	 * number of characters, and therefore we won't be assured of
	 * being able to fit it into a YY_CHAR variable.  This rules out
	 * storing the transitions in a compressed table, since the code
	 * for interpreting them uses a YY_CHAR variable (perhaps it
	 * should just use an integer, though; this is worth pondering ...
	 * ###).
	 *
	 * Finally, for full tables, we want the number of entries in the
	 * table to be a power of two so the array references go fast (it
	 * will just take a shift to compute the major index).  If
	 * encoding NUL's transitions in the table will spoil this, we
	 * give it its own table (note that this will be the case if we're
	 * not using equivalence classes).
	 */

	/* Note that the test for ecgroup[0] == numecs below accomplishes
	 * both (1) and (2) above
	 */
	if ( ! fullspd && ecgroup[0] == numecs )
		{
		/* NUL is alone in its equivalence class, which is the
		 * last one.
		 */
		int use_NUL_table = (numecs == csize);

		if ( fulltbl && ! use_NUL_table )
			{
			/* We still may want to use the table if numecs
			 * is a power of 2.
			 */
			int power_of_two;

			for ( power_of_two = 1; power_of_two <= csize;
			      power_of_two *= 2 )
				if ( numecs == power_of_two )
					{
					use_NUL_table = true;
					break;
					}
			}

		if ( use_NUL_table )
			nultrans = allocate_integer_array( current_max_dfas );

		/* From now on, nultrans != nil indicates that we're
		 * saving null transitions for later, separate encoding.
		 */
		}


	if ( fullspd )
		{
		for ( i = 0; i <= numecs; ++i )
			state[i] = 0;
		place_state( state, 0, 0 );
		}

	else if ( fulltbl )
		{
		if ( nultrans )
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			num_full_table_rows = numecs;

		else
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			num_full_table_rows = numecs + 1;

		/* Unless -Ca, declare it "short" because it's a real
		 * long-shot that that won't be large enough.
		 */
		printf( "static const %s yy_nxt[][%d] =\n    {\n",
			/* '}' so vi doesn't get too confused */
			long_align ? "long" : "short", num_full_table_rows );

		/* Generate 0 entries for state #0. */
		for ( i = 0; i < num_full_table_rows; ++i )
			mk2data( 0 );

		/* Force ',' and dataflush() next call to mk2data().*/
		datapos = NUMDATAITEMS;

		/* Force extra blank line next dataflush(). */
		dataline = NUMDATALINES;
		}

	/* Create the first states. */

	num_start_states = lastsc * 2;

	for ( i = 1; i <= num_start_states; ++i )
		{
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		if ( i % 2 == 1 )
			nset[numstates] = scset[(i / 2) + 1];
		else
			nset[numstates] =
				mkbranch( scbol[i / 2], scset[i / 2] );

		nset = epsclosure( nset, &numstates, accset, &nacc, &hashval );

		if ( snstods( nset, numstates, accset, nacc, hashval, &ds ) )
			{
			numas += nacc;
			totnst += numstates;
			++todo_next;

			if ( variable_trailing_context_rules && nacc > 0 )
				check_trailing_context( nset, numstates,
							accset, nacc );
			}
		}

	if ( ! fullspd )
		{
		if ( ! snstods( nset, 0, accset, 0, 0, &end_of_buffer_state ) )
			flexfatal(
				"could not create unique end-of-buffer state" );

		++numas;
		++num_start_states;
		++todo_next;
		}

	while ( todo_head < todo_next )
		{
		targptr = 0;
		totaltrans = 0;

		for ( i = 1; i <= numecs; ++i )
			state[i] = 0;

		ds = ++todo_head;

		dset = dss[ds];
		dsize = dfasiz[ds];

		if ( trace )
			fprintf( err, "state # %d:\n", ds );

		sympartition( dset, dsize, symlist, duplist );

		for ( sym = 1; sym <= numecs; ++sym )
			{
			if ( symlist[sym] )
				{
				symlist[sym] = 0;

				if ( duplist[sym] == NIL )
					{
					/* Symbol has unique out-transitions. */
					numstates = symfollowset( dset, dsize,
								sym, nset );
					nset = epsclosure( nset, &numstates,
						accset, &nacc, &hashval );

					if ( snstods( nset, numstates, accset,
						nacc, hashval, &newds ) )
						{
						totnst = totnst + numstates;
						++todo_next;
						numas += nacc;

						if (
					variable_trailing_context_rules &&
							nacc > 0 )
							check_trailing_context(
								nset, numstates,
								accset, nacc );
						}

					state[sym] = newds;

					if ( trace )
						fprintf( err, "\t%d\t%d\n",
							sym, newds );

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
					}

				else
					{
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					if ( trace )
						fprintf( err, "\t%d\t%d\n",
							sym, targ );

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					while ( targstate[++i] != targ )
						;

					++targfreq[i];
					++numdup;
					}

				++totaltrans;
				duplist[sym] = NIL;
				}
			}

		numsnpairs = numsnpairs + totaltrans;

		if ( caseins && ! useecs )
			{
			register int j;

			for ( i = 'A', j = 'a'; i <= 'Z'; ++i, ++j )
				state[i] = state[j];
			}

		if ( ds > num_start_states )
			check_for_backing_up( ds, state );

		if ( nultrans )
			{
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
			}

		if ( fulltbl )
			{
			/* Supply array's 0-element. */
			if ( ds == end_of_buffer_state )
				mk2data( -end_of_buffer_state );
			else
				mk2data( end_of_buffer_state );

			for ( i = 1; i < num_full_table_rows; ++i )
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data( state[i] ? state[i] : -ds );

			/* Force ',' and dataflush() next call to mk2data().*/
			datapos = NUMDATAITEMS;

			/* Force extra blank line next dataflush(). */
			dataline = NUMDATALINES;
			}

		else if ( fullspd )
			place_state( state, ds, totaltrans );

		else if ( ds == end_of_buffer_state )
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1( ds, 0, 0, JAMSTATE );

		else /* normal, compressed state */
			{
			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			for ( i = 1; i <= targptr; ++i )
				if ( targfreq[i] > comfreq )
					{
					comfreq = targfreq[i];
					comstate = targstate[i];
					}

			bldtbl( state, ds, totaltrans, comstate, comfreq );
			}
		}

	if ( fulltbl )
		dataend();

	else if ( ! fullspd )
		{
		cmptmps();  /* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		while ( onesp > 0 )
			{
			mk1tbl( onestate[onesp], onesym[onesp], onenext[onesp],
			onedef[onesp] );
			--onesp;
			}

		mkdeftbl();
		}
	}


/* snstods - converts a set of ndfa states into a dfa state
 *
 * synopsis
 *    is_new_state = snstods( int sns[numstates], int numstates,
 *				int accset[num_rules+1], int nacc,
 *				int hashval, int *newds_addr );
 *
 * On return, the dfa state number is in newds.
 */

int snstods( sns, numstates, accset, nacc, hashval, newds_addr )
int sns[], numstates, accset[], nacc, hashval, *newds_addr;
	{
	int didsort = 0;
	register int i, j;
	int newds, *oldsns;

	for ( i = 1; i <= lastdfa; ++i )
		if ( hashval == dhash[i] )
			{
			if ( numstates == dfasiz[i] )
				{
				oldsns = dss[i];

				if ( ! didsort )
					{
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 * We use bubble because there probably
					 * aren't very many states.
					 */
					bubble( sns, numstates );
					didsort = 1;
					}

				for ( j = 1; j <= numstates; ++j )
					if ( sns[j] != oldsns[j] )
						break;

				if ( j > numstates )
					{
					++dfaeql;
					*newds_addr = i;
					return 0;
					}

				++hshcol;
				}

			else
				++hshsave;
			}

	/* Make a new dfa. */

	if ( ++lastdfa >= current_max_dfas )
		increase_max_dfas();

	newds = lastdfa;

	dss[newds] = allocate_integer_array( numstates + 1 );

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	if ( ! didsort )
		bubble( sns, numstates );

	for ( i = 1; i <= numstates; ++i )
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	if ( nacc == 0 )
		{
		if ( reject )
			dfaacc[newds].dfaacc_set = (int *) 0;
		else
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
		}

	else if ( reject )
		{
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.  We use a bubble
		 * sort since the list is probably quite small.
		 */

		bubble( accset, nacc );

		dfaacc[newds].dfaacc_set = allocate_integer_array( nacc + 1 );

		/* Save the accepting set for later */
		for ( i = 1; i <= nacc; ++i )
			{
			dfaacc[newds].dfaacc_set[i] = accset[i];

			if ( accset[i] <= num_rules )
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				rule_useful[accset[i]] = true;
			}

		accsiz[newds] = nacc;
		}

	else
		{
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = num_rules + 1;

		for ( i = 1; i <= nacc; ++i )
			if ( accset[i] < j )
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		if ( j <= num_rules )
			rule_useful[j] = true;
		}

	*newds_addr = newds;

	return 1;
	}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

int symfollowset( ds, dsize, transsym, nset )
int ds[], dsize, transsym, nset[];
	{
	int ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	for ( i = 1; i <= dsize; ++i )
		{ /* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		if ( sym < 0 )
			{ /* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			if ( cclng[sym] )
				{
				for ( j = 0; j < lenccl; ++j )
					{
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					if ( ch == 0 )
						ch = NUL_ec;

					if ( ch > transsym )
						/* Transsym isn't in negated
						 * ccl.
						 */
						break;

					else if ( ch == transsym )
						/* next 2 */ goto bottom;
					}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
				}

			else
				for ( j = 0; j < lenccl; ++j )
					{
					ch = ccltbl[ccllist + j];

					if ( ch == 0 )
						ch = NUL_ec;

					if ( ch > transsym )
						break;
					else if ( ch == transsym )
						{
						nset[++numstates] = tsp;
						break;
						}
					}
			}

		else if ( sym >= 'A' && sym <= 'Z' && caseins )
			flexfatal( "consistency check failed in symfollowset" );

		else if ( sym == SYM_EPSILON )
			{ /* do nothing */
			}

		else if ( abs( ecgroup[sym] ) == transsym )
			nset[++numstates] = tsp;

		bottom: ;
		}

	return numstates;
	}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

void sympartition( ds, numstates, symlist, duplist )
int ds[], numstates;
int symlist[], duplist[];
	{
	int tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	for ( i = 1; i <= numecs; ++i )
		{ /* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
		}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	for ( i = 1; i <= numstates; ++i )
		{
		ns = ds[i];
		tch = transchar[ns];

		if ( tch != SYM_EPSILON )
			{
			if ( tch < -lastccl || tch >= csize )
				{
				flexfatal(
			"bad transition character detected in sympartition()" );
				}

			if ( tch >= 0 )
				{ /* character transition */
				int ec = ecgroup[tch];

				mkechar( ec, dupfwd, duplist );
				symlist[ec] = 1;
				}

			else
				{ /* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl( ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec );

				if ( cclng[tch] )
					{
					j = 0;

					for ( k = 0; k < lenccl; ++k )
						{
						ich = ccltbl[cclp + k];

						if ( ich == 0 )
							ich = NUL_ec;

						for ( ++j; j < ich; ++j )
							symlist[j] = 1;
						}

					for ( ++j; j <= numecs; ++j )
						symlist[j] = 1;
					}

				else
					for ( k = 0; k < lenccl; ++k )
						{
						ich = ccltbl[cclp + k];

						if ( ich == 0 )
							ich = NUL_ec;

						symlist[ich] = 1;
						}
				}
			}
		}
	}
/* ecs - equivalence class routines */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */


/* ccl2ecl - convert character classes to set of equivalence classes */

void ccl2ecl()
	{
	int i, ich, newlen, cclp, ccls, cclmec;

	for ( i = 1; i <= lastccl; ++i )
		{
		/* We loop through each character class, and for each character
		 * in the class, add the character's equivalence class to the
		 * new "character" class we are creating.  Thus when we are all
		 * done, character classes will really consist of collections
		 * of equivalence classes
		 */

		newlen = 0;
		cclp = cclmap[i];

		for ( ccls = 0; ccls < ccllen[i]; ++ccls )
			{
			ich = ccltbl[cclp + ccls];
			cclmec = ecgroup[ich];

			if ( cclmec > 0 )
				{
				ccltbl[cclp + newlen] = cclmec;
				++newlen;
				}
			}

		ccllen[i] = newlen;
		}
	}


/* cre8ecs - associate equivalence class numbers with class members
 *
 * fwd is the forward linked-list of equivalence class members.  bck
 * is the backward linked-list, and num is the number of class members.
 *
 * Returned is the number of classes.
 */

int cre8ecs( fwd, bck, num )
int fwd[], bck[], num;
	{
	int i, j, numcl;

	numcl = 0;

	/* Create equivalence class numbers.  From now on, abs( bck(x) )
	 * is the equivalence class number for object x.  If bck(x)
	 * is positive, then x is the representative of its equivalence
	 * class.
	 */
	for ( i = 1; i <= num; ++i )
		if ( bck[i] == NIL )
			{
			bck[i] = ++numcl;
			for ( j = fwd[i]; j != NIL; j = fwd[j] )
				bck[j] = -numcl;
			}

	return numcl;
	}


/* mkeccl - update equivalence classes based on character class xtions
 *
 * synopsis
 *    Char ccls[];
 *    int lenccl, fwd[llsiz], bck[llsiz], llsiz, NUL_mapping;
 *    void mkeccl( Char ccls[], int lenccl, int fwd[llsiz], int bck[llsiz],
 *			int llsiz, int NUL_mapping );
 *
 * ccls contains the elements of the character class, lenccl is the
 * number of elements in the ccl, fwd is the forward link-list of equivalent
 * characters, bck is the backward link-list, and llsiz size of the link-list.
 *
 * NUL_mapping is the value which NUL (0) should be mapped to.
 */

void mkeccl( ccls, lenccl, fwd, bck, llsiz, NUL_mapping )
Char ccls[];
int lenccl, fwd[], bck[], llsiz, NUL_mapping;
	{
	int cclp, oldec, newec;
	int cclm, i, j;
	static unsigned char cclflags[CSIZE];	/* initialized to all '\0' */

	/* Note that it doesn't matter whether or not the character class is
	 * negated.  The same results will be obtained in either case.
	 */

	cclp = 0;

	while ( cclp < lenccl )
		{
		cclm = ccls[cclp];

		if ( NUL_mapping && cclm == 0 )
			cclm = NUL_mapping;

		oldec = bck[cclm];
		newec = cclm;

		j = cclp + 1;

		for ( i = fwd[cclm]; i != NIL && i <= llsiz; i = fwd[i] )
			{ /* look for the symbol in the character class */
			for ( ; j < lenccl; ++j )
				{
				register int ccl_char;

				if ( NUL_mapping && ccls[j] == 0 )
					ccl_char = NUL_mapping;
				else
					ccl_char = ccls[j];

				if ( ccl_char > i )
					break;

				if ( ccl_char == i && ! cclflags[j] )
					{
					/* We found an old companion of cclm
					 * in the ccl.  Link it into the new
					 * equivalence class and flag it as
					 * having been processed.
					 */

					bck[i] = newec;
					fwd[newec] = i;
					newec = i;
					/* Set flag so we don't reprocess. */
					cclflags[j] = 1;

					/* Get next equivalence class member. */
					/* continue 2 */
					goto next_pt;
					}
				}

			/* Symbol isn't in character class.  Put it in the old
			 * equivalence class.
			 */

			bck[i] = oldec;

			if ( oldec != NIL )
				fwd[oldec] = i;

			oldec = i;

			next_pt: ;
			}

		if ( bck[cclm] != NIL || oldec != bck[cclm] )
			{
			bck[cclm] = NIL;
			fwd[oldec] = NIL;
			}

		fwd[newec] = NIL;

		/* Find next ccl member to process. */

		for ( ++cclp; cclflags[cclp] && cclp < lenccl; ++cclp )
			{
			/* Reset "doesn't need processing" flag. */
			cclflags[cclp] = 0;
			}
		}
	}


/* mkechar - create equivalence class for single character */

void mkechar( tch, fwd, bck )
int tch, fwd[], bck[];
	{
	/* If until now the character has been a proper subset of
	 * an equivalence class, break it away to create a new ec
	 */

	if ( fwd[tch] != NIL )
		bck[fwd[tch]] = bck[tch];

	if ( bck[tch] != NIL )
		fwd[bck[tch]] = fwd[tch];

	fwd[tch] = NIL;
	bck[tch] = NIL;
	}
/* gen - actual generation (writing) of flex scanners */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */



/* declare functions that have forward references */

void gen_next_state PROTO((int));
void genecs PROTO((void));
void indent_put2s PROTO((char [], char []));
void indent_puts PROTO((char []));


static int indent_level = 0; /* each level is 8 spaces */

#define indent_up() (++indent_level)
#define indent_down() (--indent_level)
#define set_indent(indent_val) indent_level = indent_val

/* *Everything* is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.
 */
static char C_short_decl[] = "static const short int %s[%d] =\n    {   0,\n";
static char C_long_decl[] = "static const long int %s[%d] =\n    {   0,\n";
static char C_state_decl[] =
	"static const yy_state_type %s[%d] =\n    {   0,\n";


/* Indent to the current level. */

void do_indent()
	{
	register int i = indent_level * 8;

	while ( i >= 8 )
		{
		putchar( '\t' );
		i -= 8;
		}

	while ( i > 0 )
		{
		putchar( ' ' );
		--i;
		}
	}


/* Generate the code to keep backing-up information. */

void gen_backing_up()
	{
	if ( reject || num_backing_up == 0 )
		return;

	if ( fullspd )
		indent_puts( "if ( yy_current_state[-1].yy_nxt )" );
	else
		indent_puts( "if ( yy_accept[yy_current_state] )" );

	indent_up();
	indent_puts( "{" );
	indent_puts( "yy_last_accepting_state = yy_current_state;" );
	indent_puts( "yy_last_accepting_cpos = yy_cp;" );
	indent_puts( "}" );
	indent_down();
	}


/* Generate the code to perform the backing up. */

void gen_bu_action()
	{
	if ( reject || num_backing_up == 0 )
		return;

	set_indent( 3 );

	indent_puts( "case 0: /* must back up */" );
	indent_puts( "/* undo the effects of YY_DO_BEFORE_ACTION */" );
	indent_puts( "*yy_cp = yy_hold_char;" );

	if ( fullspd || fulltbl )
		indent_puts( "yy_cp = yy_last_accepting_cpos + 1;" );
	else
		/* Backing-up info for compressed tables is taken \after/
		 * yy_cp has been incremented for the next state.
		 */
		indent_puts( "yy_cp = yy_last_accepting_cpos;" );

	indent_puts( "yy_current_state = yy_last_accepting_state;" );
	indent_puts( "goto yy_find_action;" );
	putchar( '\n' );

	set_indent( 0 );
	}


/* genctbl - generates full speed compressed transition table */

void genctbl()
	{
	register int i;
	int end_of_buffer_action = num_rules + 1;

	/* Table of verify for transition and offset to next state. */
	printf( "static const struct yy_trans_info yy_transition[%d] =\n",
		tblend + numecs + 1 );
	printf( "    {\n" );

	/* We want the transition to be represented as the offset to the
	 * next state, not the actual state number, which is what it currently
	 * is.  The offset is base[nxt[i]] - (base of current state)].  That's
	 * just the difference between the starting points of the two involved
	 * states (to - from).
	 *
	 * First, though, we need to find some way to put in our end-of-buffer
	 * flags and states.  We do this by making a state with absolutely no
	 * transitions.  We put it at the end of the table.
	 */

	/* We need to have room in nxt/chk for two more slots: One for the
	 * action and one for the end-of-buffer transition.  We now *assume*
	 * that we're guaranteed the only character we'll try to index this
	 * nxt/chk pair with is EOB, i.e., 0, so we don't have to make sure
	 * there's room for jam entries for other characters.
	 */

	while ( tblend + 2 >= current_max_xpairs )
		expand_nxt_chk();

	while ( lastdfa + 1 >= current_max_dfas )
		increase_max_dfas();

	base[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = end_of_buffer_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1; /* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has a end-of-buffer transition and an
	 * action #.
	 */
	for ( i = 0; i <= lastdfa; ++i )
		{
		register int anum = dfaacc[i].dfaacc_state;

		chk[base[i]] = EOB_POSITION;
		chk[base[i] - 1] = ACTION_POSITION;
		nxt[base[i] - 1] = anum;	/* action number */
		}

	for ( i = 0; i <= tblend; ++i )
		{
		if ( chk[i] == EOB_POSITION )
			transition_struct_out( 0, base[lastdfa + 1] - i );

		else if ( chk[i] == ACTION_POSITION )
			transition_struct_out( 0, nxt[i] );

		else if ( chk[i] > numecs || chk[i] == 0 )
			transition_struct_out( 0, 0 );	/* unused slot */

		else	/* verify, transition */
			transition_struct_out( chk[i],
						base[nxt[i]] - (i - chk[i]) );
		}


	/* Here's the final, end-of-buffer state. */
	transition_struct_out( chk[tblend + 1], nxt[tblend + 1] );
	transition_struct_out( chk[tblend + 2], nxt[tblend + 2] );

	printf( "    };\n" );
	printf( "\n" );

	/* Table of pointers to start states. */
	printf(
	"static const struct yy_trans_info *yy_start_state_list[%d] =\n",
		lastsc * 2 + 1 );
	printf( "    {\n" );	/* } so vi doesn't get confused */

	for ( i = 0; i <= lastsc * 2; ++i )
		printf( "    &yy_transition[%d],\n", base[i] );

	dataend();

	if ( useecs )
		genecs();
	}


/* Generate equivalence-class tables. */

void genecs()
	{
	Char clower();
	static char C_char_decl[] = "static const %s %s[%d] =\n    {   0,\n";
					/* } so vi doesn't get confused */
	register int i, j;
	int numrows;

	if ( numecs < csize )
		printf( C_char_decl, "YY_CHAR", "yy_ec", csize );
	else
		printf( C_char_decl, "short", "yy_ec", csize );

	for ( i = 1; i < csize; ++i )
		{
		if ( caseins && (i >= 'A') && (i <= 'Z') )
			ecgroup[i] = ecgroup[clower( i )];

		ecgroup[i] = abs( ecgroup[i] );
		mkdata( ecgroup[i] );
		}

	dataend();

	if ( trace )
		{
		fputs( "\n\nEquivalence Classes:\n\n", err );

		numrows = csize / 8;

		for ( j = 0; j < numrows; ++j )
			{
			for ( i = j; i < csize; i = i + numrows )
				{
				fprintf( err, "%4s = %-2d",
					readable_form( i ), ecgroup[i] );

				putc( ' ', err );
				}

			putc( '\n', err );
			}
		}
	}


/* Generate the code to find the action number. */

void gen_find_action()
	{
	if ( fullspd )
		indent_puts( "yy_act = yy_current_state[-1].yy_nxt;" );

	else if ( fulltbl )
		indent_puts( "yy_act = yy_accept[yy_current_state];" );

	else if ( reject )
		{
		indent_puts( "yy_current_state = *--yy_state_ptr;" );
		indent_puts( "yy_lp = yy_accept[yy_current_state];" );

		puts(
		"find_rule: /* we branch to this label when backing up */" );

		indent_puts(
		"for ( ; ; ) /* until we find what rule we matched */" );

		indent_up();

		indent_puts( "{" );

		indent_puts(
		"if ( yy_lp && yy_lp < yy_accept[yy_current_state + 1] )" );
		indent_up();
		indent_puts( "{" );
		indent_puts( "yy_act = yy_acclist[yy_lp];" );

		if ( variable_trailing_context_rules )
			{
			indent_puts( "if ( yy_act & YY_TRAILING_HEAD_MASK ||" );
			indent_puts( "     yy_looking_for_trail_begin )" );
			indent_up();
			indent_puts( "{" );

			indent_puts(
				"if ( yy_act == yy_looking_for_trail_begin )" );
			indent_up();
			indent_puts( "{" );
			indent_puts( "yy_looking_for_trail_begin = 0;" );
			indent_puts( "yy_act &= ~YY_TRAILING_HEAD_MASK;" );
			indent_puts( "break;" );
			indent_puts( "}" );
			indent_down();

			indent_puts( "}" );
			indent_down();

			indent_puts( "else if ( yy_act & YY_TRAILING_MASK )" );
			indent_up();
			indent_puts( "{" );
			indent_puts(
		"yy_looking_for_trail_begin = yy_act & ~YY_TRAILING_MASK;" );
			indent_puts(
		"yy_looking_for_trail_begin |= YY_TRAILING_HEAD_MASK;" );

			if ( real_reject )
				{
				/* Remember matched text in case we back up
				 * due to REJECT.
				 */
				indent_puts( "yy_full_match = yy_cp;" );
				indent_puts( "yy_full_state = yy_state_ptr;" );
				indent_puts( "yy_full_lp = yy_lp;" );
				}

			indent_puts( "}" );
			indent_down();

			indent_puts( "else" );
			indent_up();
			indent_puts( "{" );
			indent_puts( "yy_full_match = yy_cp;" );
			indent_puts( "yy_full_state = yy_state_ptr;" );
			indent_puts( "yy_full_lp = yy_lp;" );
			indent_puts( "break;" );
			indent_puts( "}" );
			indent_down();

			indent_puts( "++yy_lp;" );
			indent_puts( "goto find_rule;" );
			}

		else
		{
		/* Remember matched text in case we back up due to trailing
		 * context plus REJECT.
		 */
		indent_up();
		indent_puts( "{" );
		indent_puts( "yy_full_match = yy_cp;" );
		indent_puts( "break;" );
		indent_puts( "}" );
		indent_down();
		}

		indent_puts( "}" );
		indent_down();

		indent_puts( "--yy_cp;" );

		/* We could consolidate the following two lines with those at
		 * the beginning, but at the cost of complaints that we're
		 * branching inside a loop.
		 */
		indent_puts( "yy_current_state = *--yy_state_ptr;" );
		indent_puts( "yy_lp = yy_accept[yy_current_state];" );

		indent_puts( "}" );

		indent_down();
		}

	else
		/* compressed */
		indent_puts( "yy_act = yy_accept[yy_current_state];" );
	}


/* genftbl - generates full transition table */

void genftbl()
	{
	register int i;
	int end_of_buffer_action = num_rules + 1;

	printf( long_align ? C_long_decl : C_short_decl,
		"yy_accept", lastdfa + 1 );

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	for ( i = 1; i <= lastdfa; ++i )
		{
		register int anum = dfaacc[i].dfaacc_state;

		mkdata( anum );

		if ( trace && anum )
			fprintf( err, "state # %d accepts: [%d]\n",
				i, anum );
		}

	dataend();

	if ( useecs )
		genecs();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
	}


/* Generate the code to find the next compressed-table state. */

void gen_next_compressed_state( char_map )
char *char_map;
	{
	indent_put2s( "register YY_CHAR yy_c = %s;", char_map );

	/* Save the backing-up info \before/ computing the next state
	 * because we always compute one more state than needed - we
	 * always proceed until we reach a jam state
	 */
	gen_backing_up();

	indent_puts(
"while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )" );
	indent_up();
	indent_puts( "{" );
	indent_puts( "yy_current_state = (int) yy_def[yy_current_state];" );

	if ( usemecs )
		{
		/* We've arrange it so that templates are never chained
		 * to one another.  This means we can afford to make a
		 * very simple test to see if we need to convert to
		 * yy_c's meta-equivalence class without worrying
		 * about erroneously looking up the meta-equivalence
		 * class twice
		 */
		do_indent();

		/* lastdfa + 2 is the beginning of the templates */
		printf( "if ( yy_current_state >= %d )\n", lastdfa + 2 );

		indent_up();
		indent_puts( "yy_c = yy_meta[(unsigned int) yy_c];" );
		indent_down();
		}

	indent_puts( "}" );
	indent_down();

	indent_puts(
"yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];" );
	}


/* Generate the code to find the next match. */

void gen_next_match()
	{
	/* NOTE - changes in here should be reflected in gen_next_state() and
	 * gen_NUL_trans().
	 */
	char *char_map = useecs ? "yy_ec[(unsigned int) *yy_cp]" : "*yy_cp";
	char *char_map_2 =
		useecs ? "yy_ec[(unsigned int) *++yy_cp]" : "*++yy_cp";

	if ( fulltbl )
		{
		indent_put2s(
"while ( (yy_current_state = yy_nxt[yy_current_state][(unsigned int)%s]) > 0 )",
				char_map );

		indent_up();

		if ( num_backing_up > 0 )
			{
			indent_puts( "{" );	/* } for vi */
			gen_backing_up();
			putchar( '\n' );
			}

		indent_puts( "++yy_cp;" );

		if ( num_backing_up > 0 )
			/* { for vi */
			indent_puts( "}" );

		indent_down();

		putchar( '\n' );
		indent_puts( "yy_current_state = -yy_current_state;" );
		}

	else if ( fullspd )
		{
		indent_puts( "{" );	/* } for vi */
		indent_puts(
		"register const struct yy_trans_info *yy_trans_info;\n" );
		indent_puts( "register YY_CHAR yy_c;\n" );
		indent_put2s( "for ( yy_c = %s;", char_map );
		indent_puts(
	"      (yy_trans_info = &yy_current_state[(unsigned int) yy_c])->" );
		indent_puts( "yy_verify == yy_c;" );
		indent_put2s( "      yy_c = %s )", char_map_2 );

		indent_up();

		if ( num_backing_up > 0 )
			indent_puts( "{" );	/* } for vi */

		indent_puts( "yy_current_state += yy_trans_info->yy_nxt;" );

		if ( num_backing_up > 0 )
			{
			putchar( '\n' );
			gen_backing_up();	/* { for vi */
			indent_puts( "}" );
			}

		indent_down();	/* { for vi */
		indent_puts( "}" );
		}

	else
		{ /* compressed */
		indent_puts( "do" );

		indent_up();
		indent_puts( "{" );	/* } for vi */

		gen_next_state( false );

		indent_puts( "++yy_cp;" );

		/* { for vi */
		indent_puts( "}" );
		indent_down();

		do_indent();

		if ( interactive )
			printf( "while ( yy_base[yy_current_state] != %d );\n",
				jambase );
		else
			printf( "while ( yy_current_state != %d );\n",
				jamstate );

		if ( ! reject && ! interactive )
			{
			/* Do the guaranteed-needed backing up to figure out
			 * the match.
			 */
			indent_puts( "yy_cp = yy_last_accepting_cpos;" );
			indent_puts(
				"yy_current_state = yy_last_accepting_state;" );
			}
		}
	}


/* Generate the code to find the next state. */

void gen_next_state( worry_about_NULs )
int worry_about_NULs;
	{ /* NOTE - changes in here should be reflected in get_next_match() */
	char char_map[256];

	if ( worry_about_NULs && ! nultrans )
		{
		if ( useecs )
			(void) sprintf( char_map,
				"(*yy_cp ? yy_ec[(unsigned int) *yy_cp] : %d)",
					NUL_ec );
		else
			(void) sprintf( char_map,
				"(*yy_cp ? *yy_cp : %d)", NUL_ec );
		}

	else
		yy_strcpy( char_map,
			useecs ? "yy_ec[(unsigned int) *yy_cp]" : "*yy_cp" );

	if ( worry_about_NULs && nultrans )
		{
		if ( ! fulltbl && ! fullspd )
			/* Compressed tables back up *before* they match. */
			gen_backing_up();

		indent_puts( "if ( *yy_cp )" );
		indent_up();
		indent_puts( "{" );	/* } for vi */
		}

	if ( fulltbl )
		indent_put2s(
	"yy_current_state = yy_nxt[yy_current_state][(unsigned int) %s];", 
				char_map );

	else if ( fullspd )
		indent_put2s(
	"yy_current_state += yy_current_state[(unsigned int) %s].yy_nxt;",
				char_map );

	else
		gen_next_compressed_state( char_map );

	if ( worry_about_NULs && nultrans )
		{
		/* { for vi */
		indent_puts( "}" );
		indent_down();
		indent_puts( "else" );
		indent_up();
		indent_puts(
			"yy_current_state = yy_NUL_trans[yy_current_state];" );
		indent_down();
		}

	if ( fullspd || fulltbl )
		gen_backing_up();

	if ( reject )
		indent_puts( "*yy_state_ptr++ = yy_current_state;" );
	}


/* Generate the code to make a NUL transition. */

void gen_NUL_trans()
	{ /* NOTE - changes in here should be reflected in get_next_match() */
	int need_backing_up = (num_backing_up > 0 && ! reject);

	if ( need_backing_up )
		/* We'll need yy_cp lying around for the gen_backing_up(). */
		indent_puts( "register char *yy_cp = yy_c_buf_p;" );

	putchar( '\n' );

	if ( nultrans )
		{
		indent_puts(
			"yy_current_state = yy_NUL_trans[yy_current_state];" );
		indent_puts( "yy_is_jam = (yy_current_state == 0);" );
		}

	else if ( fulltbl )
		{
		do_indent();
		printf( "yy_current_state = yy_nxt[yy_current_state][%d];\n",
			NUL_ec );
		indent_puts( "yy_is_jam = (yy_current_state <= 0);" );
		}

	else if ( fullspd )
		{
		do_indent();
		printf( "register int yy_c = %d;\n", NUL_ec );

		indent_puts(
		"register const struct yy_trans_info *yy_trans_info;\n" );
		indent_puts(
		"yy_trans_info = &yy_current_state[(unsigned int) yy_c];" );
		indent_puts( "yy_current_state += yy_trans_info->yy_nxt;" );

		indent_puts(
			"yy_is_jam = (yy_trans_info->yy_verify != yy_c);" );
		}

	else
		{
		char NUL_ec_str[20];

		(void) sprintf( NUL_ec_str, "%d", NUL_ec );
		gen_next_compressed_state( NUL_ec_str );

		if ( reject )
			indent_puts( "*yy_state_ptr++ = yy_current_state;" );

		do_indent();

		printf( "yy_is_jam = (yy_current_state == %d);\n", jamstate );
		}

	/* If we've entered an accepting state, back up; note that
	 * compressed tables have *already* done such backing up, so
	 * we needn't bother with it again.
	 */
	if ( need_backing_up && (fullspd || fulltbl) )
		{
		putchar( '\n' );
		indent_puts( "if ( ! yy_is_jam )" );
		indent_up();
		indent_puts( "{" );
		gen_backing_up();
		indent_puts( "}" );
		indent_down();
		}
	}


/* Generate the code to find the start state. */

void gen_start_state()
	{
	if ( fullspd )
		indent_put2s(
			"yy_current_state = yy_start_state_list[yy_start%s];",
			bol_needed ? " + (yy_bp[-1] == '\\n' ? 1 : 0)" : "" );

	else
		{
		indent_puts( "yy_current_state = yy_start;" );

		if ( bol_needed )
			{
			indent_puts( "if ( yy_bp[-1] == '\\n' )" );
			indent_up();
			indent_puts( "++yy_current_state;" );
			indent_down();
			}

		if ( reject )
			{
			/* Set up for storing up states. */
			indent_puts( "yy_state_ptr = yy_state_buf;" );
			indent_puts( "*yy_state_ptr++ = yy_current_state;" );
			}
		}
	}


/* gentabs - generate data statements for the transition tables */

void gentabs()
	{
	int i, j, k, *accset, nacc, *acc_array, total_states;
	int end_of_buffer_action = num_rules + 1;

	/* *Everything* is done in terms of arrays starting at 1, so provide
	 * a null entry for the zero element of all C arrays.
	 */
	static char C_char_decl[] =
		"static const YY_CHAR %s[%d] =\n    {   0,\n";	/* } for vi */

	acc_array = allocate_integer_array( current_max_dfas );
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++num_backing_up;

	if ( reject )
		{
		/* Write out accepting list and pointer list.
		 *
		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		int EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = end_of_buffer_action;
		accsiz[end_of_buffer_state] = 1;
		dfaacc[end_of_buffer_state].dfaacc_set = EOB_accepting_list;

		printf( long_align ? C_long_decl : C_short_decl,
			"yy_acclist", max( numas, 1 ) + 1 );

		j = 1;	/* index into "yy_acclist" array */

		for ( i = 1; i <= lastdfa; ++i )
			{
			acc_array[i] = j;

			if ( accsiz[i] != 0 )
				{
				accset = dfaacc[i].dfaacc_set;
				nacc = accsiz[i];

				if ( trace )
					fprintf( err,
						"state # %d accepts: ", i );

				for ( k = 1; k <= nacc; ++k )
					{
					int accnum = accset[k];

					++j;

					if ( variable_trailing_context_rules &&
					  ! (accnum & YY_TRAILING_HEAD_MASK) &&
					   accnum > 0 && accnum <= num_rules &&
					  rule_type[accnum] == RULE_VARIABLE )
						{
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_MASK;
						}

					mkdata( accnum );

					if ( trace )
						{
						fprintf( err, "[%d]",
							accset[k] );

						if ( k < nacc )
							fputs( ", ", err );
						else
							putc( '\n', err );
						}
					}
				}
			}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend();
		}

	else
		{
		dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

		for ( i = 1; i <= lastdfa; ++i )
			acc_array[i] = dfaacc[i].dfaacc_state;

		/* add accepting number for jam state */
		acc_array[i] = 0;
		}

	/* Spit out "yy_accept" array.  If we're doing "reject", it'll be
	 * pointers into the "yy_acclist" array.  Otherwise it's actual
	 * accepting numbers.  In either case, we just dump the numbers.
	 */

	/* "lastdfa + 2" is the size of "yy_accept"; includes room for C arrays
	 * beginning at 0 and for "jam" state.
	 */
	k = lastdfa + 2;

	if ( reject )
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++k;

	printf( long_align ? C_long_decl : C_short_decl, "yy_accept", k );

	for ( i = 1; i <= lastdfa; ++i )
		{
		mkdata( acc_array[i] );

		if ( ! reject && trace && acc_array[i] )
			fprintf( err, "state # %d accepts: [%d]\n",
				i, acc_array[i] );
		}

	/* Add entry for "jam" state. */
	mkdata( acc_array[i] );

	if ( reject )
		/* Add "cap" for the list. */
		mkdata( acc_array[i] );

	dataend();

	if ( useecs )
		genecs();

	if ( usemecs )
		{
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */

		if ( trace )
			fputs( "\n\nMeta-Equivalence Classes:\n", err );

		printf( C_char_decl, "yy_meta", numecs + 1 );

		for ( i = 1; i <= numecs; ++i )
			{
			if ( trace )
				fprintf( err, "%d = %d\n",
					i, abs( tecbck[i] ) );

			mkdata( abs( tecbck[i] ) );
			}

		dataend();
		}

	total_states = lastdfa + numtemps;

	printf( (tblend >= MAX_SHORT || long_align) ?
			C_long_decl : C_short_decl,
		"yy_base", total_states + 1 );

	for ( i = 1; i <= lastdfa; ++i )
		{
		register int d = def[i];

		if ( base[i] == JAMSTATE )
			base[i] = jambase;

		if ( d == JAMSTATE )
			def[i] = jamstate;

		else if ( d < 0 )
			{
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
			}

		mkdata( base[i] );
		}

	/* Generate jam state's base index. */
	mkdata( base[i] );

	for ( ++i /* skip jam state */; i <= total_states; ++i )
		{
		mkdata( base[i] );
		def[i] = jamstate;
		}

	dataend();

	printf( (total_states >= MAX_SHORT || long_align) ?
			C_long_decl : C_short_decl,
		"yy_def", total_states + 1 );

	for ( i = 1; i <= total_states; ++i )
		mkdata( def[i] );

	dataend();

	printf( (total_states >= MAX_SHORT || long_align) ?
			C_long_decl : C_short_decl,
		"yy_nxt", tblend + 1 );

	for ( i = 1; i <= tblend; ++i )
		{
		if ( nxt[i] == 0 || chk[i] == 0 )
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata( nxt[i] );
		}

	dataend();

	printf( (total_states >= MAX_SHORT || long_align) ?
			C_long_decl : C_short_decl,
		"yy_chk", tblend + 1 );

	for ( i = 1; i <= tblend; ++i )
		{
		if ( chk[i] == 0 )
			++nummt;

		mkdata( chk[i] );
		}

	dataend();
	}


/* Write out a formatted string (with a secondary string argument) at the
 * current indentation level, adding a final newline.
 */

void indent_put2s( fmt, arg )
char fmt[], arg[];
	{
	do_indent();
	printf( fmt, arg );
	putchar( '\n' );
	}


/* Write out a string at the current indentation level, adding a final
 * newline.
 */

void indent_puts( str )
char str[];
	{
	do_indent();
	puts( str );
	}


/* make_tables - generate transition tables and finishes generating output file
 */

void make_tables()
	{
	register int i;
	int did_eof_rule = false;

	skelout();

	/* First, take care of YY_DO_BEFORE_ACTION depending on yymore
	 * being used.
	 */
	set_indent( 1 );

	if ( yymore_used )
		{
		indent_puts( "yytext_ptr -= yy_more_len; \\" );
		indent_puts( "yyleng = yy_cp - yytext_ptr; \\" );
		}

	else
		indent_puts( "yyleng = yy_cp - yy_bp; \\" );

	/* Now also deal with copying yytext_ptr to yytext if needed. */
	skelout();
	if ( yytext_is_array )
		{
		indent_puts( "if ( yyleng >= YYLMAX ) \\" );
		indent_up();
		indent_puts(
		"YY_FATAL_ERROR( \"token too large, exceeds YYLMAX\" ); \\" );
		indent_down();
		indent_puts( "yy_strcpy( yytext, yytext_ptr ); \\" );
		}

	set_indent( 0 );

	skelout();


	printf( "#define YY_END_OF_BUFFER %d\n", num_rules + 1 );

	if ( fullspd )
		{
		/* Need to define the transet type as a size large
		 * enough to hold the biggest offset.
		 */
		int total_table_size = tblend + numecs + 1;
		char *trans_offset_type =
			(total_table_size >= MAX_SHORT || long_align) ?
				"long" : "short";

		set_indent( 0 );
		indent_puts( "struct yy_trans_info" );
		indent_up();
		indent_puts( "{" ); 	/* } for vi */

		if ( long_align )
			indent_puts( "long yy_verify;" );
		else
			indent_puts( "short yy_verify;" );

		/* In cases where its sister yy_verify *is* a "yes, there is
		 * a transition", yy_nxt is the offset (in records) to the
		 * next state.  In most cases where there is no transition,
		 * the value of yy_nxt is irrelevant.  If yy_nxt is the -1th
		 * record of a state, though, then yy_nxt is the action number
		 * for that state.
		 */

		indent_put2s( "%s yy_nxt;", trans_offset_type );
		indent_puts( "};" );
		indent_down();
		}

	if ( fullspd )
		genctbl();
	else if ( fulltbl )
		genftbl();
	else
		gentabs();

	/* Definitions for backing up.  We don't need them if REJECT
	 * is being used because then we use an alternative backin-up
	 * technique instead.
	 */
	if ( num_backing_up > 0 && ! reject )
		{
		if ( ! C_plus_plus )
			{
			indent_puts(
			"static yy_state_type yy_last_accepting_state;" );
			indent_puts(
				"static char *yy_last_accepting_cpos;\n" );
			}
		}

	if ( nultrans )
		{
		printf( C_state_decl, "yy_NUL_trans", lastdfa + 1 );

		for ( i = 1; i <= lastdfa; ++i )
			{
			if ( fullspd )
				printf( "    &yy_transition[%d],\n", base[i] );
			else
				mkdata( nultrans[i] );
			}

		dataend();
		}

	if ( ddebug )
		{ /* Spit out table mapping rules to line numbers. */
		indent_puts( "extern int yy_flex_debug;" );
		indent_puts( "int yy_flex_debug = 1;\n" );

		printf( long_align ? C_long_decl : C_short_decl,
			"yy_rule_linenum", num_rules );
		for ( i = 1; i < num_rules; ++i )
			mkdata( rule_linenum[i] );
		dataend();
		}

	if ( reject )
		{
		/* Declare state buffer variables. */
		if ( ! C_plus_plus )
			{
			puts(
	"static yy_state_type yy_state_buf[YY_BUF_SIZE + 2], *yy_state_ptr;" );
			puts( "static char *yy_full_match;" );
			puts( "static int yy_lp;" );
			}

		if ( variable_trailing_context_rules )
			{
			if ( ! C_plus_plus )
				{
				puts(
				"static int yy_looking_for_trail_begin = 0;" );
				puts( "static int yy_full_lp;" );
				puts( "static int *yy_full_state;" );
				}

			printf( "#define YY_TRAILING_MASK 0x%x\n",
				(unsigned int) YY_TRAILING_MASK );
			printf( "#define YY_TRAILING_HEAD_MASK 0x%x\n",
				(unsigned int) YY_TRAILING_HEAD_MASK );
			}

		puts( "#define REJECT \\" );
		puts( "{ \\" );		/* } for vi */
		puts(
	"*yy_cp = yy_hold_char; /* undo effects of setting up yytext */ \\" );
		puts(
	"yy_cp = yy_full_match; /* restore poss. backed-over text */ \\" );

		if ( variable_trailing_context_rules )
			{
			puts(
		"yy_lp = yy_full_lp; /* restore orig. accepting pos. */ \\" );
			puts(
		"yy_state_ptr = yy_full_state; /* restore orig. state */ \\" );
			puts(
	"yy_current_state = *yy_state_ptr; /* restore curr. state */ \\" );
			}

		puts( "++yy_lp; \\" );
		puts( "goto find_rule; \\" );
		/* { for vi */
		puts( "}" );
		}

	else
		{
		puts(
		"/* The intent behind this definition is that it'll catch" );
		puts( " * any uses of REJECT which flex missed." );
		puts( " */" );
		puts( "#define REJECT reject_used_but_not_detected" );
		}

	if ( yymore_used )
		{
		if ( ! C_plus_plus )
			{
			indent_puts( "static int yy_more_flag = 0;" );
			indent_puts( "static int yy_more_len = 0;" );
			}

		indent_puts( "#define yymore() (yy_more_flag = 1)" );
		indent_puts( "#define YY_MORE_ADJ yy_more_len" );
		}

	else
		{
		indent_puts( "#define yymore() yymore_used_but_not_detected" );
		indent_puts( "#define YY_MORE_ADJ 0" );
		}

	if ( ! C_plus_plus )
		{
		if ( yytext_is_array )
			{
			puts( "#ifndef YYLMAX" );
			puts( "#define YYLMAX 8192" );
			puts( "#endif\n" );
			puts( "char yytext[YYLMAX];" );
			puts( "char *yytext_ptr;" );
			}

		else
			puts( "char *yytext;" );
		}

	fputs( &action_array[defs1_offset], stdout );

	skelout();

	if ( ! C_plus_plus )
		{
		if ( use_read )
			{
			printf(
"\tif ( (result = read( fileno(yyin), (char *) buf, max_size )) < 0 ) \\\n" );
			printf(
		"\t\tYY_FATAL_ERROR( \"input in flex scanner failed\" );\n" );
			}

		else
			{
			printf(
			"\tif ( yy_current_buffer->is_interactive ) \\\n" );
			printf(
"\t\tresult = ((int) (buf[0] = getc( yyin ))) == EOF ? 0 : 1; \\\n" );
			printf(
"\telse if ( ((result = fread( (char *) buf, 1, max_size, yyin )) == 0)\\\n" );
			printf( "\t\t  && ferror( yyin ) ) \\\n" );
			printf(
		"\t\tYY_FATAL_ERROR( \"input in flex scanner failed\" );\n" );
			}
		}

	skelout();

	/* Copy prolog to output file. */
	fputs( &action_array[prolog_offset], stdout );

	skelout();

	set_indent( 2 );

	if ( yymore_used )
		{
		indent_puts( "yy_more_len = 0;" );
		indent_puts( "if ( yy_more_flag )" );
		indent_up();
		indent_puts( "{" );
		indent_puts( "yy_more_len = yyleng;" );
		indent_puts( "yy_more_flag = 0;" );
		indent_puts( "}" );
		indent_down();
		}

	skelout();

	gen_start_state();

	/* Note, don't use any indentation. */
	puts( "yy_match:" );
	gen_next_match();

	skelout();
	set_indent( 2 );
	gen_find_action();

	skelout();
	if ( lex_compat )
		{
		indent_puts( "if ( yy_act != YY_END_OF_BUFFER )" );
		indent_up();
		indent_puts( "{" );
		indent_puts( "int yyl;" );
		indent_puts( "for ( yyl = 0; yyl < yyleng; ++yyl )" );
		indent_up();
		indent_puts( "if ( yytext[yyl] == '\\n' )" );
		indent_up();
		indent_puts( "++yylineno;" );
		indent_down();
		indent_down();
		indent_puts( "}" );
		indent_down();
		}

	skelout();
	if ( ddebug )
		{
		indent_puts( "if ( yy_flex_debug )" );
		indent_up();

		indent_puts( "{" );
		indent_puts( "if ( yy_act == 0 )" );
		indent_up();
		indent_puts(
			"fprintf( stderr, \"--scanner backing up\\n\" );" );
		indent_down();

		do_indent();
		printf( "else if ( yy_act < %d )\n", num_rules );
		indent_up();
		indent_puts(
	"fprintf( stderr, \"--accepting rule at line %d (\\\"%s\\\")\\n\"," );
		indent_puts( "         yy_rule_linenum[yy_act], yytext );" );
		indent_down();

		do_indent();
		printf( "else if ( yy_act == %d )\n", num_rules );
		indent_up();
		indent_puts(
	"fprintf( stderr, \"--accepting default rule (\\\"%s\\\")\\n\"," );
		indent_puts( "         yytext );" );
		indent_down();

		do_indent();
		printf( "else if ( yy_act == %d )\n", num_rules + 1 );
		indent_up();
		indent_puts(
	"fprintf( stderr, \"--(end of buffer or a NUL)\\n\" );" );
		indent_down();

		do_indent();
		printf( "else\n" );
		indent_up();
		indent_puts(
	"fprintf( stderr, \"--EOF (start condition %d)\\n\", YY_START );" );
		indent_down();

		indent_puts( "}" );
		indent_down();
		}

	/* Copy actions to output file. */
	skelout();
	indent_up();
	gen_bu_action();
	fputs( &action_array[action_offset], stdout );

	/* generate cases for any missing EOF rules */
	for ( i = 1; i <= lastsc; ++i )
		if ( ! sceof[i] )
			{
			do_indent();
			printf( "case YY_STATE_EOF(%s):\n", scname[i] );
			did_eof_rule = true;
			}

	if ( did_eof_rule )
		{
		indent_up();
		indent_puts( "yyterminate();" );
		indent_down();
		}


	/* Generate code for handling NUL's, if needed. */

	/* First, deal with backing up and setting up yy_cp if the scanner
	 * finds that it should JAM on the NUL>
	 */
	skelout();
	set_indent( 7 );

	if ( fullspd || fulltbl )
		indent_puts( "yy_cp = yy_c_buf_p;" );

	else
		{ /* compressed table */
		if ( ! reject && ! interactive )
			{
			/* Do the guaranteed-needed backing up to figure
			 * out the match.
			 */
			indent_puts( "yy_cp = yy_last_accepting_cpos;" );
			indent_puts(
				"yy_current_state = yy_last_accepting_state;" );
			}
		}


	/* Generate code for yy_get_previous_state(). */
	set_indent( 1 );
	skelout();

	if ( bol_needed )
		indent_puts( "register char *yy_bp = yytext_ptr;\n" );

	gen_start_state();

	set_indent( 2 );
	skelout();
	gen_next_state( true );

	set_indent( 1 );
	skelout();
	gen_NUL_trans();

	skelout();
	if ( lex_compat )
		{ /* update yylineno inside of unput() */
		indent_puts( "if ( c == '\\n' )" );
		indent_up();
		indent_puts( "--yylineno;" );
		indent_down();
		}

	skelout();

	/* Copy remainder of input to output. */

	line_directive_out( stdout );

	if ( sectnum == 3 )
		(void) flexscan(); /* copy remainder of input to output */
	}
/* misc - miscellaneous flex routines */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */




/* declare functions that have forward references */

void dataflush PROTO((void));
int otoi PROTO((Char []));


void add_action( new_text )
char *new_text;
	{
	int len = yy_strlen( new_text );

	while ( len + action_index >= action_size - 10 /* slop */ )
		{
		action_size *= 2;
		action_array =
			reallocate_character_array( action_array, action_size );
		}

	yy_strcpy( &action_array[action_index], new_text );

	action_index += len;
	}


/* allocate_array - allocate memory for an integer array of the given size */

void *allocate_array( size, element_size )
int size, element_size;
	{
	register void *mem;

	/* On 16-bit int machines (e.g., 80286) we might be trying to
	 * allocate more than a signed int can hold, and that won't
	 * work.  Cheap test:
	 */
	if ( element_size * size <= 0 )
		flexfatal( "request for < 1 byte in allocate_array()" );

	mem = yy_flex_alloc( element_size * size );

	if ( mem == NULL )
		flexfatal( "memory allocation failed in allocate_array()" );

	return mem;
	}


/* all_lower - true if a string is all lower-case */

int all_lower( str )
register char *str;
	{
	while ( *str )
		{
		if ( ! isascii( (Char) *str ) || ! islower( *str ) )
			return 0;
		++str;
		}

	return 1;
	}


/* all_upper - true if a string is all upper-case */

int all_upper( str )
register char *str;
	{
	while ( *str )
		{
		if ( ! isascii( (Char) *str ) || ! isupper( *str ) )
			return 0;
		++str;
		}

	return 1;
	}


/* bubble - bubble sort an integer array in increasing order
 *
 * synopsis
 *   int v[n], n;
 *   void bubble( v, n );
 *
 * description
 *   sorts the first n elements of array v and replaces them in
 *   increasing order.
 *
 * passed
 *   v - the array to be sorted
 *   n - the number of elements of 'v' to be sorted
 */

void bubble( v, n )
int v[], n;
	{
	register int i, j, k;

	for ( i = n; i > 1; --i )
		for ( j = 1; j < i; ++j )
			if ( v[j] > v[j + 1] )	/* compare */
				{
				k = v[j];	/* exchange */
				v[j] = v[j + 1];
				v[j + 1] = k;
				}
	}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

void check_char( c )
int c;
	{
	if ( c >= CSIZE )
		lerrsf( "bad character '%s' detected in check_char()",
			readable_form( c ) );

	if ( c >= csize )
		lerrsf( "scanner requires -8 flag to use the character '%s'",
			readable_form( c ) );
	}



/* clower - replace upper-case letter to lower-case */

Char clower( c )
register int c;
	{
	return (Char) ((isascii( c ) && isupper( c )) ? tolower( c ) : c);
	}


/* copy_string - returns a dynamically allocated copy of a string */

char *copy_string( str )
register char *str;
	{
	register char *c;
	char *copy;

	/* find length */
	for ( c = str; *c; ++c )
		;

	copy = (char *) yy_flex_alloc( (c - str + 1) * sizeof( char ) );

	if ( copy == NULL )
		flexfatal( "dynamic memory failure in copy_string()" );

	for ( c = copy; (*c++ = *str++); )
		;

	return copy;
	}


/* copy_unsigned_string -
 *    returns a dynamically allocated copy of a (potentially) unsigned string
 */

Char *copy_unsigned_string( str )
register Char *str;
	{
	register Char *c;
	Char *copy;

	/* find length */
	for ( c = str; *c; ++c )
		;

	copy = allocate_Character_array( c - str + 1 );

	for ( c = copy; (*c++ = *str++); )
		;

	return copy;
	}


/* cshell - shell sort a character array in increasing order
 *
 * synopsis
 *
 *   Char v[n];
 *   int n, special_case_0;
 *   cshell( v, n, special_case_0 );
 *
 * description
 *   Does a shell sort of the first n elements of array v.
 *   If special_case_0 is true, then any element equal to 0
 *   is instead assumed to have infinite weight.
 *
 * passed
 *   v - array to be sorted
 *   n - number of elements of v to be sorted
 */

void cshell( v, n, special_case_0 )
Char v[];
int n, special_case_0;
	{
	int gap, i, j, jg;
	Char k;

	for ( gap = n / 2; gap > 0; gap = gap / 2 )
		for ( i = gap; i < n; ++i )
			for ( j = i - gap; j >= 0; j = j - gap )
				{
				jg = j + gap;

				if ( special_case_0 )
					{
					if ( v[jg] == 0 )
						break;

					else if ( v[j] != 0 && v[j] <= v[jg] )
						break;
					}

				else if ( v[j] <= v[jg] )
					break;

				k = v[j];
				v[j] = v[jg];
				v[jg] = k;
				}
	}


/* dataend - finish up a block of data declarations */

void dataend()
	{
	if ( datapos > 0 )
		dataflush();

	/* add terminator for initialization; { for vi */
	puts( "    } ;\n" );

	dataline = 0;
	datapos = 0;
	}


/* dataflush - flush generated data statements */

void dataflush()
	{
	putchar( '\n' );

	if ( ++dataline >= NUMDATALINES )
		{
		/* Put out a blank line so that the table is grouped into
		 * large blocks that enable the user to find elements easily.
		 */
		putchar( '\n' );
		dataline = 0;
		}

	/* Reset the number of characters written on the current line. */
	datapos = 0;
	}


/* flexerror - report an error message and terminate */

void flexerror( msg )
char msg[];
	{
	fprintf( err, "%s: %s\n", program_name, msg );
	flexend( 1 );
	}


/* flexfatal - report a fatal error message and terminate */

void flexfatal( msg )
char msg[];
	{
	fprintf( err, "%s: fatal internal error, %s\n", program_name, msg );
	exit( 1 );
	}


/* lerrif - report an error message formatted with one integer argument */

void lerrif( msg, arg )
char msg[];
int arg;
	{
	char errmsg[MAXLINE];
	(void) sprintf( errmsg, msg, arg );
	flexerror( errmsg );
	}


/* lerrsf - report an error message formatted with one string argument */

void lerrsf( msg, arg )
char msg[], arg[];
	{
	char errmsg[MAXLINE];

	(void) sprintf( errmsg, msg, arg );
	flexerror( errmsg );
	}


/* htoi - convert a hexadecimal digit string to an integer value */

int htoi( str )
Char str[];
	{
	unsigned int result;

	(void) sscanf( (char *) str, "%x", &result );

	return result;
	}


/* is_hex_digit - returns true if a character is a valid hex digit, false
 *		  otherwise
 */

int is_hex_digit( ch )
int ch;
	{
	if ( isdigit( ch ) )
		return 1;

	switch ( clower( ch ) )
		{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			return 1;

		default:
			return 0;
		}
	}


/* line_directive_out - spit out a "# line" statement */

void line_directive_out( output_file )
FILE *output_file;
	{
	if ( infilename && gen_line_dirs )
		{
		char directive[MAXLINE];
		sprintf( directive, "# line %d \"%s\"\n", linenum, infilename );

		/* If output_file is nil then we should put the directive in
		 * the accumulated actions.
		 */
		if ( output_file )
			fputs( directive, output_file );
		else
			add_action( directive );
		}
	}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
void mark_defs1()
	{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
	}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
void mark_prolog()
	{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
	}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
void mk2data( value )
int value;
	{
	if ( datapos >= NUMDATAITEMS )
		{
		putchar( ',' );
		dataflush();
		}

	if ( datapos == 0 )
		/* Indent. */
		fputs( "    ", stdout );

	else
		putchar( ',' );

	++datapos;

	printf( "%5d", value );
	}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
void mkdata( value )
int value;
	{
	if ( datapos >= NUMDATAITEMS )
		{
		putchar( ',' );
		dataflush();
		}

	if ( datapos == 0 )
		/* Indent. */
		fputs( "    ", stdout );
	else
		putchar( ',' );

	++datapos;

	printf( "%5d", value );
	}


/* myctoi - return the integer represented by a string of digits */

int myctoi( array )
char array[];
	{
	int val = 0;

	(void) sscanf( array, "%d", &val );

	return val;
	}


/* myesc - return character corresponding to escape sequence */

Char myesc( array )
Char array[];
	{
	Char c, esc_char;

	switch ( array[1] )
		{
		case 'b': return '\b';
		case 'f': return '\f';
		case 'n': return '\n';
		case 'r': return '\r';
		case 't': return '\t';

#ifdef __STDC__
		case 'a': return '\a';
		case 'v': return '\v';
#else
		case 'a': return '\007';
		case 'v': return '\013';
#endif

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			{ /* \<octal> */
			int sptr = 1;

			while ( isascii( array[sptr] ) &&
				isdigit( array[sptr] ) )
				/* Don't increment inside loop control
				 * because if isdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = otoi( array + 1 );

			array[sptr] = c;

			return esc_char;
			}

		case 'x':
			{ /* \x<hex> */
			int sptr = 2;

			while ( isascii( array[sptr] ) &&
				is_hex_digit( (char) array[sptr] ) )
				/* Don't increment inside loop control
				 * because if isdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = htoi( array + 2 );

			array[sptr] = c;

			return esc_char;
			}

		default:
			return array[1];
		}
	}


/* otoi - convert an octal digit string to an integer value */

int otoi( str )
Char str[];
	{
	unsigned int result;

	(void) sscanf( (char *) str, "%o", &result );
	return result;
	}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

char *readable_form( c )
register int c;
	{
	static char rform[10];

	if ( (c >= 0 && c < 32) || c >= 127 )
		{
		switch ( c )
			{
			case '\b': return "\\b";
			case '\f': return "\\f";
			case '\n': return "\\n";
			case '\r': return "\\r";
			case '\t': return "\\t";

#ifdef __STDC__
			case '\a': return "\\a";
			case '\v': return "\\v";
#endif

			default:
				(void) sprintf( rform, "\\%.3o",
						(unsigned int) c );
				return rform;
			}
		}

	else if ( c == ' ' )
		return "' '";

	else
		{
		rform[0] = c;
		rform[1] = '\0';

		return rform;
		}
	}


/* reallocate_array - increase the size of a dynamic array */

void *reallocate_array( array, size, element_size )
void *array;
int size, element_size;
	{
	register void *new_array;

	/* Same worry as in allocate_array(): */
	if ( size * element_size <= 0 )
		flexfatal(
			"attempt to increase array size by less than 1 byte" );

	new_array = yy_flex_realloc( array, size * element_size );

	if ( new_array == NULL )
		flexfatal( "attempt to increase array size failed" );

	return new_array;
	}


/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
void skelout()
	{
	char buf_storage[MAXLINE];
	char *buf = buf_storage;
	int do_copy = 1;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the skel[] array.
	 */
	while ( skelfile ?
		(fgets( buf, MAXLINE, skelfile ) != NULL) :
		((buf = skel[skel_ind++]) != 0) )
		{ /* copy from skel array */
		if ( buf[0] == '%' )
			{ /* control line */
			switch ( buf[1] )
				{
				case '%':
					return;

				case '+':
					do_copy = C_plus_plus;
					break;

				case '-':
					do_copy = ! C_plus_plus;
					break;

				case '*':
					do_copy = 1;
					break;

				default:
					flexfatal(
						"bad line in skeleton file" );
				}
			}

		else if ( do_copy )
			{
			if ( skelfile )
				/* Skeleton file reads include final
				 * newline, skel[] array does not.
				 */
				fputs( buf, stdout );
			else
				printf( "%s\n", buf );
			}
		}
	}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

void transition_struct_out( element_v, element_n )
int element_v, element_n;
	{
	printf( "%7d, %5d,", element_v, element_n );

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	if ( datapos >= 75 )
		{
		putchar( '\n' );

		if ( ++dataline % 10 == 0 )
			putchar( '\n' );

		datapos = 0;
		}
	}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 */
void *yy_flex_xmalloc( size )
int size;
	{
	void *result = yy_flex_alloc( size );

	if ( ! result  )
		flexfatal( "memory allocation failed in yy_flex_xmalloc()" );

	return result;
	}


/* zero_out - set a region of memory to 0
 *
 * Sets region_ptr[0] through region_ptr[size_in_bytes - 1] to zero.
 */

void zero_out( region_ptr, size_in_bytes )
char *region_ptr;
int size_in_bytes;
	{
	register char *rp, *rp_end;

	rp = region_ptr;
	rp_end = region_ptr + size_in_bytes;

	while ( rp < rp_end )
		*rp++ = 0;
	}
/* nfa - NFA construction routines */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */



/* declare functions that have forward references */

int dupmachine PROTO((int));
void mkxtion PROTO((int, int));


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

void add_accept( mach, accepting_number )
int mach, accepting_number;
	{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	if ( transchar[finalst[mach]] == SYM_EPSILON )
		accptnum[finalst[mach]] = accepting_number;

	else
		{
		int astate = mkstate( SYM_EPSILON );
		accptnum[astate] = accepting_number;
		(void) link_machines( mach, astate );
		}
	}


/* copysingl - make a given number of copies of a singleton machine
 *
 * synopsis
 *
 *   newsng = copysingl( singl, num );
 *
 *     newsng - a new singleton composed of num copies of singl
 *     singl  - a singleton machine
 *     num    - the number of copies of singl to be present in newsng
 */

int copysingl( singl, num )
int singl, num;
	{
	int copy, i;

	copy = mkstate( SYM_EPSILON );

	for ( i = 1; i <= num; ++i )
		copy = link_machines( copy, dupmachine( singl ) );

	return copy;
	}


/* dumpnfa - debugging routine to write out an nfa */

void dumpnfa( state1 )
int state1;

	{
	int sym, tsp1, tsp2, anum, ns;

	fprintf( err,
		"\n\n********** beginning dump of nfa with start state %d\n",
		state1 );

	/* We probably should loop starting at firstst[state1] and going to
	 * lastst[state1], but they're not maintained properly when we "or"
	 * all of the rules together.  So we use our knowledge that the machine
	 * starts at state 1 and ends at lastnfa.
	 */

	/* for ( ns = firstst[state1]; ns <= lastst[state1]; ++ns ) */
	for ( ns = 1; ns <= lastnfa; ++ns )
		{
		fprintf( err, "state # %4d\t", ns );

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		fprintf( err, "%3d:  %4d, %4d", sym, tsp1, tsp2 );

		if ( anum != NIL )
			fprintf( err, "  [%d]", anum );

		fprintf( err, "\n" );
		}

	fprintf( err, "********** end of dump\n" );
	}


/* dupmachine - make a duplicate of a given machine
 *
 * synopsis
 *
 *   copy = dupmachine( mach );
 *
 *     copy - holds duplicate of mach
 *     mach - machine to be duplicated
 *
 * note that the copy of mach is NOT an exact duplicate; rather, all the
 * transition states values are adjusted so that the copy is self-contained,
 * as the original should have been.
 *
 * also note that the original MUST be contiguous, with its low and high
 * states accessible by the arrays firstst and lastst
 */

int dupmachine( mach )
int mach;
	{
	int i, init, state_offset;
	int state = 0;
	int last = lastst[mach];

	for ( i = firstst[mach]; i <= last; ++i )
		{
		state = mkstate( transchar[i] );

		if ( trans1[i] != NO_TRANSITION )
			{
			mkxtion( finalst[state], trans1[i] + state - i );

			if ( transchar[i] == SYM_EPSILON &&
			     trans2[i] != NO_TRANSITION )
				mkxtion( finalst[state],
					trans2[i] + state - i );
			}

		accptnum[state] = accptnum[i];
		}

	if ( state == 0 )
		flexfatal( "empty machine in dupmachine()" );

	state_offset = state - i + 1;

	init = mach + state_offset;
	firstst[init] = firstst[mach] + state_offset;
	finalst[init] = finalst[mach] + state_offset;
	lastst[init] = lastst[mach] + state_offset;

	return init;
	}


/* finish_rule - finish up the processing for a rule
 *
 * An accepting number is added to the given machine.  If variable_trail_rule
 * is true then the rule has trailing context and both the head and trail
 * are variable size.  Otherwise if headcnt or trailcnt is non-zero then
 * the machine recognizes a pattern with trailing context and headcnt is
 * the number of characters in the matched part of the pattern, or zero
 * if the matched part has variable length.  trailcnt is the number of
 * trailing context characters in the pattern, or zero if the trailing
 * context has variable length.
 */

void finish_rule( mach, variable_trail_rule, headcnt, trailcnt )
int mach, variable_trail_rule, headcnt, trailcnt;
	{
	char action_text[MAXLINE];

	add_accept( mach, num_rules );

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	rule_linenum[num_rules] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	if ( continued_action )
		--rule_linenum[num_rules];

	sprintf( action_text, "case %d:\n", num_rules );
	add_action( action_text );

	if ( variable_trail_rule )
		{
		rule_type[num_rules] = RULE_VARIABLE;

		if ( performance_report > 0 )
			fprintf( err,
				"Variable trailing context rule at line %d\n",
				rule_linenum[num_rules] );

		variable_trailing_context_rules = true;
		}

	else
		{
		rule_type[num_rules] = RULE_NORMAL;

		if ( headcnt > 0 || trailcnt > 0 )
			{
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			char *scanner_cp = "yy_c_buf_p = yy_cp";
			char *scanner_bp = "yy_bp";

			add_action(
	"*yy_cp = yy_hold_char; /* undo effects of setting up yytext */\n" );

			if ( headcnt > 0 )
				{
				sprintf( action_text, "%s = %s + %d;\n",
				scanner_cp, scanner_bp, headcnt );
				add_action( action_text );
				}

			else
				{
				sprintf( action_text, "%s -= %d;\n",
					scanner_cp, trailcnt );
				add_action( action_text );
				}

			add_action(
			"YY_DO_BEFORE_ACTION; /* set up yytext again */\n" );
			}
		}

	line_directive_out( (FILE *) 0 );
	}


/* link_machines - connect two machines together
 *
 * synopsis
 *
 *   new = link_machines( first, last );
 *
 *     new    - a machine constructed by connecting first to last
 *     first  - the machine whose successor is to be last
 *     last   - the machine whose predecessor is to be first
 *
 * note: this routine concatenates the machine first with the machine
 *  last to produce a machine new which will pattern-match first first
 *  and then last, and will fail if either of the sub-patterns fails.
 *  FIRST is set to new by the operation.  last is unmolested.
 */

int link_machines( first, last )
int first, last;
	{
	if ( first == NIL )
		return last;

	else if ( last == NIL )
		return first;

	else
		{
		mkxtion( finalst[first], last );
		finalst[first] = finalst[last];
		lastst[first] = max( lastst[first], lastst[last] );
		firstst[first] = min( firstst[first], firstst[last] );

		return first;
		}
	}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

void mark_beginning_as_normal( mach )
register int mach;
	{
	switch ( state_type[mach] )
		{
		case STATE_NORMAL:
			/* Oh, we've already visited here. */
			return;

		case STATE_TRAILING_CONTEXT:
			state_type[mach] = STATE_NORMAL;

			if ( transchar[mach] == SYM_EPSILON )
				{
				if ( trans1[mach] != NO_TRANSITION )
					mark_beginning_as_normal(
						trans1[mach] );

				if ( trans2[mach] != NO_TRANSITION )
					mark_beginning_as_normal(
						trans2[mach] );
				}
			break;

		default:
			flexerror(
				"bad state type in mark_beginning_as_normal()" );
			break;
		}
	}


/* mkbranch - make a machine that branches to two machines
 *
 * synopsis
 *
 *   branch = mkbranch( first, second );
 *
 *     branch - a machine which matches either first's pattern or second's
 *     first, second - machines whose patterns are to be or'ed (the | operator)
 *
 * Note that first and second are NEITHER destroyed by the operation.  Also,
 * the resulting machine CANNOT be used with any other "mk" operation except
 * more mkbranch's.  Compare with mkor()
 */

int mkbranch( first, second )
int first, second;
	{
	int eps;

	if ( first == NO_TRANSITION )
		return second;

	else if ( second == NO_TRANSITION )
		return first;

	eps = mkstate( SYM_EPSILON );

	mkxtion( eps, first );
	mkxtion( eps, second );

	return eps;
	}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

int mkclos( state )
int state;
	{
	return mkopt( mkposcl( state ) );
	}


/* mkopt - make a machine optional
 *
 * synopsis
 *
 *   new = mkopt( mach );
 *
 *     new  - a machine which optionally matches whatever mach matched
 *     mach - the machine to make optional
 *
 * notes:
 *     1. mach must be the last machine created
 *     2. mach is destroyed by the call
 */

int mkopt( mach )
int mach;
	{
	int eps;

	if ( ! SUPER_FREE_EPSILON(finalst[mach]) )
		{
		eps = mkstate( SYM_EPSILON );
		mach = link_machines( mach, eps );
		}

	/* Can't skimp on the following if FREE_EPSILON(mach) is true because
	 * some state interior to "mach" might point back to the beginning
	 * for a closure.
	 */
	eps = mkstate( SYM_EPSILON );
	mach = link_machines( eps, mach );

	mkxtion( mach, finalst[mach] );

	return mach;
	}


/* mkor - make a machine that matches either one of two machines
 *
 * synopsis
 *
 *   new = mkor( first, second );
 *
 *     new - a machine which matches either first's pattern or second's
 *     first, second - machines whose patterns are to be or'ed (the | operator)
 *
 * note that first and second are both destroyed by the operation
 * the code is rather convoluted because an attempt is made to minimize
 * the number of epsilon states needed
 */

int mkor( first, second )
int first, second;
	{
	int eps, orend;

	if ( first == NIL )
		return second;

	else if ( second == NIL )
		return first;

	else
		{
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate( SYM_EPSILON );

		first = link_machines( eps, first );

		mkxtion( first, second );

		if ( SUPER_FREE_EPSILON(finalst[first]) &&
		     accptnum[finalst[first]] == NIL )
			{
			orend = finalst[first];
			mkxtion( finalst[second], orend );
			}

		else if ( SUPER_FREE_EPSILON(finalst[second]) &&
			  accptnum[finalst[second]] == NIL )
			{
			orend = finalst[second];
			mkxtion( finalst[first], orend );
			}

		else
			{
			eps = mkstate( SYM_EPSILON );

			first = link_machines( first, eps );
			orend = finalst[first];

			mkxtion( finalst[second], orend );
			}
		}

	finalst[first] = orend;
	return first;
	}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

int mkposcl( state )
int state;
	{
	int eps;

	if ( SUPER_FREE_EPSILON(finalst[state]) )
		{
		mkxtion( finalst[state], state );
		return state;
		}

	else
		{
		eps = mkstate( SYM_EPSILON );
		mkxtion( eps, state );
		return link_machines( state, eps );
		}
	}


/* mkrep - make a replicated machine
 *
 * synopsis
 *   new = mkrep( mach, lb, ub );
 *
 *    new - a machine that matches whatever "mach" matched from "lb"
 *          number of times to "ub" number of times
 *
 * note
 *   if "ub" is INFINITY then "new" matches "lb" or more occurrences of "mach"
 */

int mkrep( mach, lb, ub )
int mach, lb, ub;
	{
	int base_mach, tail, copy, i;

	base_mach = copysingl( mach, lb - 1 );

	if ( ub == INFINITY )
		{
		copy = dupmachine( mach );
		mach = link_machines( mach,
		link_machines( base_mach, mkclos( copy ) ) );
		}

	else
		{
		tail = mkstate( SYM_EPSILON );

		for ( i = lb; i < ub; ++i )
			{
			copy = dupmachine( mach );
			tail = mkopt( link_machines( copy, tail ) );
			}

		mach = link_machines( mach, link_machines( base_mach, tail ) );
		}

	return mach;
	}


/* mkstate - create a state with a transition on a given symbol
 *
 * synopsis
 *
 *   state = mkstate( sym );
 *
 *     state - a new state matching sym
 *     sym   - the symbol the new state is to have an out-transition on
 *
 * note that this routine makes new states in ascending order through the
 * state array (and increments LASTNFA accordingly).  The routine DUPMACHINE
 * relies on machines being made in ascending order and that they are
 * CONTIGUOUS.  Change it and you will have to rewrite DUPMACHINE (kludge
 * that it admittedly is)
 */

int mkstate( sym )
int sym;
	{
	if ( ++lastnfa >= current_mns )
		{
		if ( (current_mns += MNS_INCREMENT) >= MAXIMUM_MNS )
			lerrif(
			"input rules are too complicated (>= %d NFA states)",
				current_mns );

		++num_reallocs;

		firstst = reallocate_integer_array( firstst, current_mns );
		lastst = reallocate_integer_array( lastst, current_mns );
		finalst = reallocate_integer_array( finalst, current_mns );
		transchar = reallocate_integer_array( transchar, current_mns );
		trans1 = reallocate_integer_array( trans1, current_mns );
		trans2 = reallocate_integer_array( trans2, current_mns );
		accptnum = reallocate_integer_array( accptnum, current_mns );
		assoc_rule =
			reallocate_integer_array( assoc_rule, current_mns );
		state_type =
			reallocate_integer_array( state_type, current_mns );
		}

	firstst[lastnfa] = lastnfa;
	finalst[lastnfa] = lastnfa;
	lastst[lastnfa] = lastnfa;
	transchar[lastnfa] = sym;
	trans1[lastnfa] = NO_TRANSITION;
	trans2[lastnfa] = NO_TRANSITION;
	accptnum[lastnfa] = NIL;
	assoc_rule[lastnfa] = num_rules;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	if ( sym < 0 )
		{
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
		}

	else if ( sym == SYM_EPSILON )
		++numeps;

	else
		{
		check_char( sym );

		if ( useecs )
			/* Map NUL's to csize. */
			mkechar( sym ? sym : csize, nextecm, ecgroup );
		}

	return lastnfa;
	}


/* mkxtion - make a transition from one state to another
 *
 * synopsis
 *
 *   mkxtion( statefrom, stateto );
 *
 *     statefrom - the state from which the transition is to be made
 *     stateto   - the state to which the transition is to be made
 */

void mkxtion( statefrom, stateto )
int statefrom, stateto;
	{
	if ( trans1[statefrom] == NO_TRANSITION )
		trans1[statefrom] = stateto;

	else if ( (transchar[statefrom] != SYM_EPSILON) ||
		  (trans2[statefrom] != NO_TRANSITION) )
		flexfatal( "found too many transitions in mkxtion()" );

	else
		{ /* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
		}
	}

/* new_rule - initialize for a new rule */

void new_rule()
	{
	if ( ++num_rules >= current_max_rules )
		{
		++num_reallocs;
		current_max_rules += MAX_RULES_INCREMENT;
		rule_type = reallocate_integer_array( rule_type,
							current_max_rules );
		rule_linenum = reallocate_integer_array( rule_linenum,
							current_max_rules );
		rule_useful = reallocate_integer_array( rule_useful,
							current_max_rules );
		}

	if ( num_rules > MAX_RULE )
		lerrif( "too many rules (> %d)!", MAX_RULE );

	rule_linenum[num_rules] = linenum;
	rule_useful[num_rules] = false;
	}
/* File created from flex.skel via mkskel.sh */


char *skel[] = {
  "/* A lexical scanner generated by flex */",
  "",
  "/* Scanner skeleton version:",
  " * $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $",
  " */",
  "",
  "#define FLEX_SCANNER",
  "",
  "%-",
  "#include <stdio.h>",
  "%*",
  "",
  "",
  "/* cfront 1.2 defines \"c_plusplus\" instead of \"__cplusplus\" */",
  "#ifdef c_plusplus",
  "#ifndef __cplusplus",
  "#define __cplusplus",
  "#endif",
  "#endif",
  "",
  "",
  "#ifdef __cplusplus",
  "",
  "#include <stdlib.h>",
  "%+",
  "class istream;",
  "%*",
  "#include <unistd.h>",
  "",
  "/* Use prototypes in function declarations. */",
  "#define YY_USE_PROTOS",
  "",
  "/* The \"const\" storage-class-modifier is valid. */",
  "#define YY_USE_CONST",
  "",
  "#else	/* ! __cplusplus */",
  "",
  "#ifdef __STDC__",
  "",
  "#define YY_USE_PROTOS",
  "#define YY_USE_CONST",
  "",
  "#endif	/* __STDC__ */",
  "#endif	/* ! __cplusplus */",
  "",
  "",
  "#ifdef __TURBOC__",
  "#define YY_USE_CONST",
  "#endif",
  "",
  "",
  "#ifndef YY_USE_CONST",
  "#ifndef const",
  "#define const",
  "#endif",
  "#endif",
  "",
  "",
  "#ifdef YY_USE_PROTOS",
  "#define YY_PROTO(proto) proto",
  "#else",
  "#define YY_PROTO(proto) ()",
  "#endif",
  "",
  "/* Returned upon end-of-file. */",
  "#define YY_NULL 0",
  "",
  "/* Enter a start condition.  This macro really ought to take a parameter,",
  " * but we do it the disgusting crufty way forced on us by the ()-less",
  " * definition of BEGIN.",
  " */",
  "#define BEGIN yy_start = 1 + 2 *",
  "",
  "/* Translate the current start state into a value that can be later handed",
  " * to BEGIN to return to the state.",
  " */",
  "#define YY_START ((yy_start - 1) / 2)",
  "",
  "/* Action number for EOF rule of a given start state. */",
  "#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)",
  "",
  "/* Special action meaning \"start processing a new file\".  Now included",
  " * only for backward compatibility with previous versions of flex.",
  " */",
  "#define YY_NEW_FILE yyrestart( yyin )",
  "",
  "#define YY_END_OF_BUFFER_CHAR 0",
  "",
  "/* Size of default input buffer. */",
  "#define YY_BUF_SIZE 16384",
  "",
  "typedef struct yy_buffer_state *YY_BUFFER_STATE;",
  "",
  "extern int yyleng;",
  "%-",
  "extern FILE *yyin, *yyout;",
  "%*",
  "",
  "#ifdef __cplusplus",
  "extern \"C\" {",
  "#endif",
  "	extern void *yy_flex_alloc YY_PROTO(( int ));",
  "	extern void *yy_flex_realloc YY_PROTO(( void *ptr, int size ));",
  "	extern void yy_flex_free YY_PROTO(( void * ));",
  "	extern int yywrap YY_PROTO(( void ));",
  "	extern void yy_strcpy YY_PROTO(( char *s1, const char *s2 ));",
  "#ifdef __cplusplus",
  "	}",
  "#endif",
  "",
  "#define EOB_ACT_CONTINUE_SCAN 0",
  "#define EOB_ACT_END_OF_FILE 1",
  "#define EOB_ACT_LAST_MATCH 2",
  "",
  "/* The funky do-while in the following #define is used to turn the definition",
  " * int a single C statement (which needs a semi-colon terminator).  This",
  " * avoids problems with code like:",
  " *",
  " * 	if ( condition_holds )",
  " *		yyless( 5 );",
  " *	else",
  " *		do_something_else();",
  " *",
  " * Prior to using the do-while the compiler would get upset at the",
  " * \"else\" because it interpreted the \"if\" statement as being all",
  " * done when it reached the ';' after the yyless() call.",
  " */",
  "",
  "/* Return all but the first 'n' matched characters back to the input stream. */",
  "",
  "#define yyless(n) \\",
  "	do \\",
  "		{ \\",
  "		/* Undo effects of setting up yytext. */ \\",
  "		*yy_cp = yy_hold_char; \\",
  "		yy_c_buf_p = yy_cp = yy_bp + n - YY_MORE_ADJ; \\",
  "		YY_DO_BEFORE_ACTION; /* set up yytext again */ \\",
  "		} \\",
  "	while ( 0 )",
  "",
  "#define unput(c) yyunput( c, yytext_ptr )",
  "",
  "",
  "struct yy_buffer_state",
  "	{",
  "%-",
  "	FILE *yy_input_file;",
  "%+",
  "	istream* yy_input_file;",
  "%*",
  "",
  "	char *yy_ch_buf;		/* input buffer */",
  "	char *yy_buf_pos;		/* current position in input buffer */",
  "",
  "	/* Size of input buffer in bytes, not including room for EOB",
  "	 * characters.",
  "	 */",
  "	int yy_buf_size;",
  "",
  "	/* Number of characters read into yy_ch_buf, not including EOB",
  "	 * characters.",
  "	 */",
  "	int yy_n_chars;",
  "",
  "	/* Whether this is an \"interactive\" input source; if so, and",
  "	 * if we're using stdio for input, then we want to use getc()",
  "	 * instead of fread(), to make sure we stop fetching input after",
  "	 * each newline.",
  "	 */",
  "	int is_interactive;",
  "",
  "	/* Whether we've seen an EOF on this buffer. */",
  "	int yy_eof_status;",
  "#define EOF_NOT_SEEN 0",
  "	/* \"Pending\" happens when the EOF has been seen but there's still",
  "	 * some text to process.  Note that when we actually see the EOF,",
  "	 * we switch the status back to \"not seen\" (via yyrestart()), so",
  "	 * that the user can continue scanning by just pointing yyin at",
  "	 * a new input file.",
  "	 */",
  "#define EOF_PENDING 1",
  "	};",
  "",
  "%- Standard (non-C++) definition",
  "static YY_BUFFER_STATE yy_current_buffer = 0;",
  "%*",
  "",
  "/* We provide macros for accessing buffer states in case in the",
  " * future we want to put the buffer states in a more general",
  " * \"scanner state\".",
  " */",
  "#define YY_CURRENT_BUFFER yy_current_buffer",
  "",
  "",
  "%- Standard (non-C++) definition",
  "/* yy_hold_char holds the character lost when yytext is formed. */",
  "static char yy_hold_char;",
  "",
  "static int yy_n_chars;		/* number of characters read into yy_ch_buf */",
  "",
  "",
  "int yyleng;",
  "",
  "/* Points to current character in buffer. */",
  "static char *yy_c_buf_p = (char *) 0;",
  "static int yy_init = 1;		/* whether we need to initialize */",
  "static int yy_start = 0;	/* start state number */",
  "",
  "/* Flag which is used to allow yywrap()'s to do buffer switches",
  " * instead of setting up a fresh yyin.  A bit of a hack ...",
  " */",
  "static int yy_did_buffer_switch_on_eof;",
  "",
  "static void yyunput YY_PROTO(( int c, char *buf_ptr ));",
  "void yyrestart YY_PROTO(( FILE *input_file ));",
  "void yy_switch_to_buffer YY_PROTO(( YY_BUFFER_STATE new_buffer ));",
  "void yy_load_buffer_state YY_PROTO(( void ));",
  "YY_BUFFER_STATE yy_create_buffer YY_PROTO(( FILE *file, int size ));",
  "void yy_delete_buffer YY_PROTO(( YY_BUFFER_STATE b ));",
  "void yy_init_buffer YY_PROTO(( YY_BUFFER_STATE b, FILE *file ));",
  "%*",
  "",
  "#define yy_new_buffer yy_create_buffer",
  "",
  "%% yytext/yyin/yyout/yy_state_type/yylineno etc. def's & init go here",
  "",
  "%- Standard (non-C++) definition",
  "#ifdef __cplusplus",
  "static int yyinput YY_PROTO(( void ));",
  "#else",
  "static int input YY_PROTO(( void ));",
  "#endif",
  "%*",
  "",
  "%- Standard (non-C++) definition",
  "static yy_state_type yy_get_previous_state YY_PROTO(( void ));",
  "static yy_state_type yy_try_NUL_trans YY_PROTO(( yy_state_type current_state ));",
  "static int yy_get_next_buffer YY_PROTO(( void ));",
  "%*",
  "static void yy_fatal_error YY_PROTO(( const char msg[] ));",
  "",
  "/* Done after the current pattern has been matched and before the",
  " * corresponding action - sets up yytext.",
  " */",
  "#define YY_DO_BEFORE_ACTION \\",
  "	yytext_ptr = yy_bp; \\",
  "%% code to fiddle yytext and yyleng for yymore() goes here",
  "	yy_hold_char = *yy_cp; \\",
  "	*yy_cp = '\\0'; \\",
  "%% code to copy yytext_ptr to yytext[] goes here, if %array",
  "	yy_c_buf_p = yy_cp;",
  "",
  "%% data tables for the DFA and the user's section 1 definitions go here",
  "",
  "/* Macros after this point can all be overridden by user definitions in",
  " * section 1.",
  " */",
  "",
  "/* Amount of stuff to slurp up with each read. */",
  "#ifndef YY_READ_BUF_SIZE",
  "#define YY_READ_BUF_SIZE 8192",
  "#endif",
  "",
  "/* Copy whatever the last rule matched to the standard output. */",
  "",
  "#ifndef ECHO",
  "%- Standard (non-C++) definition",
  "/* This used to be an fputs(), but since the string might contain NUL's,",
  " * we now use fwrite().",
  " */",
  "#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )",
  "%+ C++ definition",
  "#define ECHO LexerOutput( yytext, yyleng )",
  "%*",
  "#endif",
  "",
  "/* Gets input and stuffs it into \"buf\".  number of characters read, or YY_NULL,",
  " * is returned in \"result\".",
  " */",
  "#ifndef YY_INPUT",
  "#define YY_INPUT(buf,result,max_size) \\",
  "%% fread()/read() definition of YY_INPUT goes here unless we're doing C++",
  "%+ C++ definition",
  "	if ( (result = LexerInput( (char *) buf, max_size )) < 0 ) \\",
  "		YY_FATAL_ERROR( \"input in flex scanner failed\" );",
  "%*",
  "#endif",
  "",
  "/* No semi-colon after return; correct usage is to write \"yyterminate();\" -",
  " * we don't want an extra ';' after the \"return\" because that will cause",
  " * some compilers to complain about unreachable statements.",
  " */",
  "#ifndef yyterminate",
  "#define yyterminate() return YY_NULL",
  "#endif",
  "",
  "/* Report a fatal error. */",
  "#ifndef YY_FATAL_ERROR",
  "#define YY_FATAL_ERROR(msg) yy_fatal_error( msg )",
  "#endif",
  "",
  "/* Default declaration of generated scanner - a define so the user can",
  " * easily add parameters.",
  " */",
  "#ifndef YY_DECL",
  "%- Standard (non-C++) definition",
  "#define YY_DECL int yylex YY_PROTO(( void ))",
  "%+ C++ definition",
  "#define YY_DECL int yyFlexLexer::yylex()",
  "%*",
  "#endif",
  "",
  "/* Code executed at the end of each rule. */",
  "#ifndef YY_BREAK",
  "#define YY_BREAK break;",
  "#endif",
  "",
  "YY_DECL",
  "	{",
  "	register yy_state_type yy_current_state;",
  "	register char *yy_cp, *yy_bp;",
  "	register int yy_act;",
  "",
  "%% user's declarations go here",
  "",
  "	if ( yy_init )",
  "		{",
  "#ifdef YY_USER_INIT",
  "		YY_USER_INIT;",
  "#endif",
  "",
  "		if ( ! yy_start )",
  "			yy_start = 1;	/* first start state */",
  "",
  "		if ( ! yyin )",
  "%-",
  "			yyin = stdin;",
  "%+",
  "			yyin = &cin;",
  "%*",
  "",
  "		if ( ! yyout )",
  "%-",
  "			yyout = stdout;",
  "%+",
  "			yyout = &cout;",
  "%*",
  "",
  "		if ( yy_current_buffer )",
  "			yy_init_buffer( yy_current_buffer, yyin );",
  "		else",
  "			yy_current_buffer =",
  "				yy_create_buffer( yyin, YY_BUF_SIZE );",
  "",
  "		yy_load_buffer_state();",
  "",
  "		yy_init = 0;",
  "		}",
  "",
  "	while ( 1 )		/* loops until end-of-file is reached */",
  "		{",
  "%% yymore()-related code goes here",
  "		yy_cp = yy_c_buf_p;",
  "",
  "		/* Support of yytext. */",
  "		*yy_cp = yy_hold_char;",
  "",
  "		/* yy_bp points to the position in yy_ch_buf of the start of",
  "		 * the current run.",
  "		 */",
  "		yy_bp = yy_cp;",
  "",
  "%% code to set up and find next match goes here",
  "",
  "yy_find_action:",
  "%% code to find the action number goes here",
  "",
  "		YY_DO_BEFORE_ACTION;",
  "",
  "#ifdef YY_USER_ACTION",
  "		if ( yy_act != YY_END_OF_BUFFER )",
  "			{",
  "			YY_USER_ACTION;",
  "			}",
  "#endif",
  "",
  "%% code for yylineno update goes here, if -l option",
  "",
  "do_action:	/* This label is used only to access EOF actions. */",
  "",
  "%% debug code goes here",
  "",
  "		switch ( yy_act )",
  "	{ /* beginning of action switch */",
  "%% actions go here",
  "",
  "	case YY_END_OF_BUFFER:",
  "		{",
  "		/* Amount of text matched not including the EOB char. */",
  "		int yy_amount_of_matched_text = yy_cp - yytext_ptr - 1;",
  "",
  "		/* Undo the effects of YY_DO_BEFORE_ACTION. */",
  "		*yy_cp = yy_hold_char;",
  "",
  "		/* Note that here we test for yy_c_buf_p \"<=\" to the position",
  "		 * of the first EOB in the buffer, since yy_c_buf_p will",
  "		 * already have been incremented past the NUL character",
  "		 * (since all states make transitions on EOB to the",
  "		 * end-of-buffer state).  Contrast this with the test",
  "		 * in input().",
  "		 */",
  "		if ( yy_c_buf_p <= &yy_current_buffer->yy_ch_buf[yy_n_chars] )",
  "			{ /* This was really a NUL. */",
  "			yy_state_type yy_next_state;",
  "",
  "			yy_c_buf_p = yytext_ptr + yy_amount_of_matched_text;",
  "",
  "			yy_current_state = yy_get_previous_state();",
  "",
  "			/* Okay, we're now positioned to make the NUL",
  "			 * transition.  We couldn't have",
  "			 * yy_get_previous_state() go ahead and do it",
  "			 * for us because it doesn't know how to deal",
  "			 * with the possibility of jamming (and we don't",
  "			 * want to build jamming into it because then it",
  "			 * will run more slowly).",
  "			 */",
  "",
  "			yy_next_state = yy_try_NUL_trans( yy_current_state );",
  "",
  "			yy_bp = yytext_ptr + YY_MORE_ADJ;",
  "",
  "			if ( yy_next_state )",
  "				{",
  "				/* Consume the NUL. */",
  "				yy_cp = ++yy_c_buf_p;",
  "				yy_current_state = yy_next_state;",
  "				goto yy_match;",
  "				}",
  "",
  "			else",
  "				{",
  "%% code to do back-up for compressed tables and set up yy_cp goes here",
  "				goto yy_find_action;",
  "				}",
  "			}",
  "",
  "		else switch ( yy_get_next_buffer() )",
  "			{",
  "			case EOB_ACT_END_OF_FILE:",
  "				{",
  "				yy_did_buffer_switch_on_eof = 0;",
  "",
  "				if ( yywrap() )",
  "					{",
  "					/* Note: because we've taken care in",
  "					 * yy_get_next_buffer() to have set up",
  "					 * yytext, we can now set up",
  "					 * yy_c_buf_p so that if some total",
  "					 * hoser (like flex itself) wants to",
  "					 * call the scanner after we return the",
  "					 * YY_NULL, it'll still work - another",
  "					 * YY_NULL will get returned.",
  "					 */",
  "					yy_c_buf_p = yytext_ptr + YY_MORE_ADJ;",
  "",
  "					yy_act = YY_STATE_EOF(YY_START);",
  "					goto do_action;",
  "					}",
  "",
  "				else",
  "					{",
  "					if ( ! yy_did_buffer_switch_on_eof )",
  "						YY_NEW_FILE;",
  "					}",
  "				break;",
  "				}",
  "",
  "			case EOB_ACT_CONTINUE_SCAN:",
  "				yy_c_buf_p =",
  "					yytext_ptr + yy_amount_of_matched_text;",
  "",
  "				yy_current_state = yy_get_previous_state();",
  "",
  "				yy_cp = yy_c_buf_p;",
  "				yy_bp = yytext_ptr + YY_MORE_ADJ;",
  "				goto yy_match;",
  "",
  "			case EOB_ACT_LAST_MATCH:",
  "				yy_c_buf_p =",
  "				&yy_current_buffer->yy_ch_buf[yy_n_chars];",
  "",
  "				yy_current_state = yy_get_previous_state();",
  "",
  "				yy_cp = yy_c_buf_p;",
  "				yy_bp = yytext_ptr + YY_MORE_ADJ;",
  "				goto yy_find_action;",
  "			}",
  "		break;",
  "		}",
  "",
  "	default:",
  "#ifdef FLEX_DEBUG",
  "%-",
  "		printf( \"action # %d\\n\", yy_act );",
  "%+",
  "		cout << \"action # \" << yy_act << '\\n';",
  "%*",
  "#endif",
  "		YY_FATAL_ERROR(",
  "			\"fatal flex scanner internal error--no action found\" );",
  "	} /* end of action switch */",
  "		} /* end of scanning one token */",
  "	} /* end of yylex */",
  "",
  "%+",
  "#ifdef YY_INTERACTIVE",
  "int yyFlexLexer::LexerInput( char* buf, int /* max_size */ )",
  "#else",
  "int yyFlexLexer::LexerInput( char* buf, int max_size )",
  "#endif",
  "	{",
  "	if ( yyin->eof() || yyin->fail() )",
  "		return 0;",
  "",
  "#ifdef YY_INTERACTIVE",
  "	yyin->get( buf[0] );",
  "",
  "	if ( yyin->eof() )",
  "		return 0;",
  "",
  "	if ( yyin->bad() )",
  "		return -1;",
  "",
  "	return 1;",
  "",
  "#else",
  "	(void) yyin->read( buf, max_size );",
  "",
  "	if ( yyin->bad() )",
  "		return -1;",
  "	else",
  "		return yyin->gcount();",
  "#endif",
  "	}",
  "",
  "void yyFlexLexer::LexerOutput( const char* buf, int size )",
  "	{",
  "	(void) yyout->write( buf, size );",
  "	}",
  "%*",
  "",
  "/* yy_get_next_buffer - try to read in a new buffer",
  " *",
  " * Returns a code representing an action:",
  " *	EOB_ACT_LAST_MATCH -",
  " *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position",
  " *	EOB_ACT_END_OF_FILE - end of file",
  " */",
  "",
  "%-",
  "static int yy_get_next_buffer()",
  "%+",
  "int yyFlexLexer::yy_get_next_buffer()",
  "%*",
  "	{",
  "	register char *dest = yy_current_buffer->yy_ch_buf;",
  "	register char *source = yytext_ptr - 1; /* copy prev. char, too */",
  "	register int number_to_move, i;",
  "	int ret_val;",
  "",
  "	if ( yy_c_buf_p > &yy_current_buffer->yy_ch_buf[yy_n_chars + 1] )",
  "		YY_FATAL_ERROR(",
  "		\"fatal flex scanner internal error--end of buffer missed\" );",
  "",
  "	/* Try to read more data. */",
  "",
  "	/* First move last chars to start of buffer. */",
  "	number_to_move = yy_c_buf_p - yytext_ptr;",
  "",
  "	for ( i = 0; i < number_to_move; ++i )",
  "		*(dest++) = *(source++);",
  "",
  "	if ( yy_current_buffer->yy_eof_status != EOF_NOT_SEEN )",
  "		/* don't do the read, it's not guaranteed to return an EOF,",
  "		 * just force an EOF",
  "		 */",
  "		yy_n_chars = 0;",
  "",
  "	else",
  "		{",
  "		int num_to_read =",
  "			yy_current_buffer->yy_buf_size - number_to_move - 1;",
  "",
  "		while ( num_to_read <= 0 )",
  "			{ /* Not enough room in the buffer - grow it. */",
  "#ifdef YY_USES_REJECT",
  "			YY_FATAL_ERROR(",
  "\"input buffer overflow, can't enlarge buffer because scanner uses REJECT\" );",
  "#else",
  "",
  "			/* just a shorter name for the current buffer */",
  "			YY_BUFFER_STATE b = yy_current_buffer;",
  "",
  "			int yy_c_buf_p_offset = yy_c_buf_p - b->yy_ch_buf;",
  "",
  "			b->yy_buf_size *= 2;",
  "			b->yy_ch_buf = (char *)",
  "				yy_flex_realloc( (void *) b->yy_ch_buf,",
  "						 b->yy_buf_size );",
  "",
  "			if ( ! b->yy_ch_buf )",
  "				YY_FATAL_ERROR(",
  "				\"fatal error - scanner input buffer overflow\" );",
  "",
  "			yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];",
  "",
  "			num_to_read = yy_current_buffer->yy_buf_size -",
  "						number_to_move - 1;",
  "#endif",
  "			}",
  "",
  "		if ( num_to_read > YY_READ_BUF_SIZE )",
  "			num_to_read = YY_READ_BUF_SIZE;",
  "",
  "		/* Read in more data. */",
  "		YY_INPUT( (&yy_current_buffer->yy_ch_buf[number_to_move]),",
  "			yy_n_chars, num_to_read );",
  "		}",
  "",
  "	if ( yy_n_chars == 0 )",
  "		{",
  "		if ( number_to_move - YY_MORE_ADJ == 1 )",
  "			{",
  "			ret_val = EOB_ACT_END_OF_FILE;",
  "			yyrestart( yyin );",
  "			}",
  "",
  "		else",
  "			{",
  "			ret_val = EOB_ACT_LAST_MATCH;",
  "			yy_current_buffer->yy_eof_status = EOF_PENDING;",
  "			}",
  "		}",
  "",
  "	else",
  "		ret_val = EOB_ACT_CONTINUE_SCAN;",
  "",
  "	yy_n_chars += number_to_move;",
  "	yy_current_buffer->yy_ch_buf[yy_n_chars] = YY_END_OF_BUFFER_CHAR;",
  "	yy_current_buffer->yy_ch_buf[yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;",
  "",
  "	/* yytext begins at the second character in yy_ch_buf; the first",
  "	 * character is the one which preceded it before reading in the latest",
  "	 * buffer; it needs to be kept around in case it's a newline, so",
  "	 * yy_get_previous_state() will have with '^' rules active.",
  "	 */",
  "",
  "	yytext_ptr = &yy_current_buffer->yy_ch_buf[1];",
  "",
  "	return ret_val;",
  "	}",
  "",
  "",
  "/* yy_get_previous_state - get the state just before the EOB char was reached */",
  "",
  "%-",
  "static yy_state_type yy_get_previous_state()",
  "%+",
  "yy_state_type yyFlexLexer::yy_get_previous_state()",
  "%*",
  "	{",
  "	register yy_state_type yy_current_state;",
  "	register char *yy_cp;",
  "",
  "%% code to get the start state into yy_current_state goes here",
  "",
  "	for ( yy_cp = yytext_ptr + YY_MORE_ADJ; yy_cp < yy_c_buf_p; ++yy_cp )",
  "		{",
  "%% code to find the next state goes here",
  "		}",
  "",
  "	return yy_current_state;",
  "	}",
  "",
  "",
  "/* yy_try_NUL_trans - try to make a transition on the NUL character",
  " *",
  " * synopsis",
  " *	next_state = yy_try_NUL_trans( current_state );",
  " */",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "static yy_state_type yy_try_NUL_trans( yy_state_type yy_current_state )",
  "#else",
  "static yy_state_type yy_try_NUL_trans( yy_current_state )",
  "yy_state_type yy_current_state;",
  "#endif",
  "%+",
  "yy_state_type yyFlexLexer::yy_try_NUL_trans( yy_state_type yy_current_state )",
  "%*",
  "	{",
  "	register int yy_is_jam;",
  "%% code to find the next state, and perhaps do backing up, goes here",
  "",
  "	return yy_is_jam ? 0 : yy_current_state;",
  "	}",
  "",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "static void yyunput( int c, register char *yy_bp )",
  "#else",
  "static void yyunput( c, yy_bp )",
  "int c;",
  "register char *yy_bp;",
  "#endif",
  "%+",
  "void yyFlexLexer::yyunput( int c, register char* yy_bp )",
  "%*",
  "	{",
  "	register char *yy_cp = yy_c_buf_p;",
  "",
  "	/* undo effects of setting up yytext */",
  "	*yy_cp = yy_hold_char;",
  "",
  "	if ( yy_cp < yy_current_buffer->yy_ch_buf + 2 )",
  "		{ /* need to shift things up to make room */",
  "		/* +2 for EOB chars. */",
  "		register int number_to_move = yy_n_chars + 2;",
  "		register char *dest = &yy_current_buffer->yy_ch_buf[",
  "					yy_current_buffer->yy_buf_size + 2];",
  "		register char *source =",
  "				&yy_current_buffer->yy_ch_buf[number_to_move];",
  "",
  "		while ( source > yy_current_buffer->yy_ch_buf )",
  "			*--dest = *--source;",
  "",
  "		yy_cp += dest - source;",
  "		yy_bp += dest - source;",
  "		yy_n_chars = yy_current_buffer->yy_buf_size;",
  "",
  "		if ( yy_cp < yy_current_buffer->yy_ch_buf + 2 )",
  "			YY_FATAL_ERROR( \"flex scanner push-back overflow\" );",
  "		}",
  "",
  "	if ( yy_cp > yy_bp && yy_cp[-1] == '\\n' )",
  "		yy_cp[-2] = '\\n';",
  "",
  "	*--yy_cp = (char) c;",
  "",
  "%% update yylineno here, if doing -l",
  "",
  "	/* Note: the formal parameter *must* be called \"yy_bp\" for this",
  "	 * macro to now work correctly.",
  "	 */",
  "	YY_DO_BEFORE_ACTION; /* set up yytext again */",
  "	}",
  "",
  "",
  "%-",
  "#ifdef __cplusplus",
  "static int yyinput()",
  "#else",
  "static int input()",
  "#endif",
  "%+",
  "int yyFlexLexer::yyinput()",
  "%*",
  "	{",
  "	int c;",
  "",
  "	*yy_c_buf_p = yy_hold_char;",
  "",
  "	if ( *yy_c_buf_p == YY_END_OF_BUFFER_CHAR )",
  "		{",
  "		/* yy_c_buf_p now points to the character we want to return.",
  "		 * If this occurs *before* the EOB characters, then it's a",
  "		 * valid NUL; if not, then we've hit the end of the buffer.",
  "		 */",
  "		if ( yy_c_buf_p < &yy_current_buffer->yy_ch_buf[yy_n_chars] )",
  "			/* This was really a NUL. */",
  "			*yy_c_buf_p = '\\0';",
  "",
  "		else",
  "			{ /* need more input */",
  "			yytext_ptr = yy_c_buf_p;",
  "			++yy_c_buf_p;",
  "",
  "			switch ( yy_get_next_buffer() )",
  "				{",
  "				case EOB_ACT_END_OF_FILE:",
  "					{",
  "					if ( yywrap() )",
  "						{",
  "						yy_c_buf_p =",
  "						yytext_ptr + YY_MORE_ADJ;",
  "						return EOF;",
  "						}",
  "",
  "					YY_NEW_FILE;",
  "#ifdef __cplusplus",
  "					return yyinput();",
  "#else",
  "					return input();",
  "#endif",
  "					}",
  "",
  "				case EOB_ACT_CONTINUE_SCAN:",
  "					yy_c_buf_p = yytext_ptr + YY_MORE_ADJ;",
  "					break;",
  "",
  "				case EOB_ACT_LAST_MATCH:",
  "#ifdef __cplusplus",
  "					YY_FATAL_ERROR(",
  "					\"unexpected last match in yyinput()\" );",
  "#else",
  "					YY_FATAL_ERROR(",
  "					\"unexpected last match in input()\" );",
  "#endif",
  "				}",
  "			}",
  "		}",
  "",
  "	c = *yy_c_buf_p;",
  "	*yy_c_buf_p = '\\0';	/* preserve yytext */",
  "	yy_hold_char = *++yy_c_buf_p;",
  "",
  "	return c;",
  "	}",
  "",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "void yyrestart( FILE *input_file )",
  "#else",
  "void yyrestart( input_file )",
  "FILE *input_file;",
  "#endif",
  "%+",
  "void yyFlexLexer::yyrestart( istream* input_file )",
  "%*",
  "	{",
  "	if ( ! yy_current_buffer )",
  "		yy_current_buffer = yy_create_buffer( yyin, YY_BUF_SIZE );",
  "",
  "	yy_init_buffer( yy_current_buffer, input_file );",
  "	yy_load_buffer_state();",
  "	}",
  "",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "void yy_switch_to_buffer( YY_BUFFER_STATE new_buffer )",
  "#else",
  "void yy_switch_to_buffer( new_buffer )",
  "YY_BUFFER_STATE new_buffer;",
  "#endif",
  "%+",
  "void yyFlexLexer::yy_switch_to_buffer( YY_BUFFER_STATE new_buffer )",
  "%*",
  "	{",
  "	if ( yy_current_buffer == new_buffer )",
  "		return;",
  "",
  "	if ( yy_current_buffer )",
  "		{",
  "		/* Flush out information for old buffer. */",
  "		*yy_c_buf_p = yy_hold_char;",
  "		yy_current_buffer->yy_buf_pos = yy_c_buf_p;",
  "		yy_current_buffer->yy_n_chars = yy_n_chars;",
  "		}",
  "",
  "	yy_current_buffer = new_buffer;",
  "	yy_load_buffer_state();",
  "",
  "	/* We don't actually know whether we did this switch during",
  "	 * EOF (yywrap()) processing, but the only time this flag",
  "	 * is looked at is after yywrap() is called, so it's safe",
  "	 * to go ahead and always set it.",
  "	 */",
  "	yy_did_buffer_switch_on_eof = 1;",
  "	}",
  "",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "void yy_load_buffer_state( void )",
  "#else",
  "void yy_load_buffer_state()",
  "#endif",
  "%+",
  "void yyFlexLexer::yy_load_buffer_state()",
  "%*",
  "	{",
  "	yy_n_chars = yy_current_buffer->yy_n_chars;",
  "	yytext_ptr = yy_c_buf_p = yy_current_buffer->yy_buf_pos;",
  "	yyin = yy_current_buffer->yy_input_file;",
  "	yy_hold_char = *yy_c_buf_p;",
  "	}",
  "",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "YY_BUFFER_STATE yy_create_buffer( FILE *file, int size )",
  "#else",
  "YY_BUFFER_STATE yy_create_buffer( file, size )",
  "FILE *file;",
  "int size;",
  "#endif",
  "%+",
  "YY_BUFFER_STATE yyFlexLexer::yy_create_buffer( istream* file, int size )",
  "%*",
  "	{",
  "	YY_BUFFER_STATE b;",
  "",
  "	b = (YY_BUFFER_STATE) yy_flex_alloc( sizeof( struct yy_buffer_state ) );",
  "",
  "	if ( ! b )",
  "		YY_FATAL_ERROR( \"out of dynamic memory in yy_create_buffer()\" );",
  "",
  "	b->yy_buf_size = size;",
  "",
  "	/* yy_ch_buf has to be 2 characters longer than the size given because",
  "	 * we need to put in 2 end-of-buffer characters.",
  "	 */",
  "	b->yy_ch_buf = (char *) yy_flex_alloc( b->yy_buf_size + 2 );",
  "",
  "	if ( ! b->yy_ch_buf )",
  "		YY_FATAL_ERROR( \"out of dynamic memory in yy_create_buffer()\" );",
  "",
  "	yy_init_buffer( b, file );",
  "",
  "	return b;",
  "	}",
  "",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "void yy_delete_buffer( YY_BUFFER_STATE b )",
  "#else",
  "void yy_delete_buffer( b )",
  "YY_BUFFER_STATE b;",
  "#endif",
  "%+",
  "void yyFlexLexer::yy_delete_buffer( YY_BUFFER_STATE b )",
  "%*",
  "	{",
  "	if ( b == yy_current_buffer )",
  "		yy_current_buffer = (YY_BUFFER_STATE) 0;",
  "",
  "	yy_flex_free( (void *) b->yy_ch_buf );",
  "	yy_flex_free( (void *) b );",
  "	}",
  "",
  "",
  "%-",
  "#ifdef YY_USE_PROTOS",
  "void yy_init_buffer( YY_BUFFER_STATE b, FILE *file )",
  "#else",
  "void yy_init_buffer( b, file )",
  "YY_BUFFER_STATE b;",
  "FILE *file;",
  "#endif",
  "%+",
  "void yyFlexLexer::yy_init_buffer( YY_BUFFER_STATE b, istream* file )",
  "%*",
  "	{",
  "	b->yy_input_file = file;",
  "",
  "	/* We put in the '\\n' and start reading from [1] so that an",
  "	 * initial match-at-newline will be true.",
  "	 */",
  "",
  "	b->yy_ch_buf[0] = '\\n';",
  "	b->yy_n_chars = 1;",
  "",
  "	/* We always need two end-of-buffer characters.  The first causes",
  "	 * a transition to the end-of-buffer state.  The second causes",
  "	 * a jam in that state.",
  "	 */",
  "	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;",
  "	b->yy_ch_buf[2] = YY_END_OF_BUFFER_CHAR;",
  "",
  "	b->yy_buf_pos = &b->yy_ch_buf[1];",
  "",
  "%-",
  "	b->is_interactive = file ? isatty( fileno(file) ) : 0;",
  "%+",
  "	b->is_interactive = 0;",
  "%*",
  "",
  "	b->yy_eof_status = EOF_NOT_SEEN;",
  "	}",
  "",
  "",
  "#ifdef YY_USE_PROTOS",
  "static void yy_fatal_error( const char msg[] )",
  "#else",
  "static void yy_fatal_error( msg )",
  "char msg[];",
  "#endif",
  "	{",
  "%-",
  "FILE *err;",  /* ### modified(Jan.24.2001) ### */
  "	(void) fprintf( err, \"%s\\n\", msg );",
  "%+",
  "	cerr << msg << '\\n';",
  "%*",
  "	exit( 1 );",
  "	}",
  "",
  "",
  "/* Redefine yyless() so it works in section 3 code. */",
  "",
  "#undef yyless",
  "#define yyless(n) \\",
  "	do \\",
  "		{ \\",
  "		/* Undo effects of setting up yytext. */ \\",
  "		yytext[yyleng] = yy_hold_char; \\",
  "		yy_c_buf_p = yytext + n - YY_MORE_ADJ; \\",
  "		yy_hold_char = *yy_c_buf_p; \\",
  "		*yy_c_buf_p = '\\0'; \\",
  "		yyleng = n; \\",
  "		} \\",
  "	while ( 0 )",
  0
};
/* sym - symbol table routines */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */



/* declare functions that have forward references */

int hashfunct PROTO((register char[], int));


struct hash_entry *ndtbl[NAME_TABLE_HASH_SIZE];
struct hash_entry *sctbl[START_COND_HASH_SIZE];
struct hash_entry *ccltab[CCL_HASH_SIZE];

struct hash_entry *findsym();


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

int addsym( sym, str_def, int_def, table, table_size )
register char sym[];
char *str_def;
int int_def;
hash_table table;
int table_size;
	{
	int hash_val = hashfunct( sym, table_size );
	register struct hash_entry *sym_entry = table[hash_val];
	register struct hash_entry *new_entry;
	register struct hash_entry *successor;

	while ( sym_entry )
		{
		if ( ! yy_strcmp( sym, sym_entry->name ) )
			{ /* entry already exists */
			return -1;
			}

		sym_entry = sym_entry->next;
		}

	/* create new entry */
	new_entry = (struct hash_entry *)
		yy_flex_alloc( sizeof( struct hash_entry ) );

	if ( new_entry == NULL )
		flexfatal( "symbol table memory allocation failed" );

	if ( (successor = table[hash_val]) )
		{
		new_entry->next = successor;
		successor->prev = new_entry;
		}
	else
		new_entry->next = NULL;

	new_entry->prev = NULL;
	new_entry->name = sym;
	new_entry->str_val = str_def;
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	return 0;
	}


/* cclinstal - save the text of a character class */

void cclinstal( ccltxt, cclnum )
Char ccltxt[];
int cclnum;
	{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */
	Char *copy_unsigned_string();

	(void) addsym( (char *) copy_unsigned_string( ccltxt ),
			(char *) 0, cclnum,
			ccltab, CCL_HASH_SIZE );
	}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

int ccllookup( ccltxt )
Char ccltxt[];
	{
	return findsym( (char *) ccltxt, ccltab, CCL_HASH_SIZE )->int_val;
	}


/* findsym - find symbol in symbol table */

struct hash_entry *findsym( sym, table, table_size )
register char sym[];
hash_table table;
int table_size;
	{
	static struct hash_entry empty_entry =
		{
		(struct hash_entry *) 0, (struct hash_entry *) 0,
		(char *) 0, (char *) 0, 0,
		} ;
	register struct hash_entry *sym_entry =
		table[hashfunct( sym, table_size )];

	while ( sym_entry )
		{
		if ( ! yy_strcmp( sym, sym_entry->name ) )
			return sym_entry;
		sym_entry = sym_entry->next;
		}

	return &empty_entry;
	}

    
/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

int hashfunct( str, hash_size )
register char str[];
int hash_size;
	{
	register int hashval;
	register int locstr;

	hashval = 0;
	locstr = 0;

	while ( str[locstr] )
		{
		hashval = (hashval << 1) + (unsigned char) str[locstr++];
		hashval %= hash_size;
		}

	return hashval;
	}


/* ndinstal - install a name definition */

void ndinstal( name, definition )
char name[];
Char definition[];
	{
	char *copy_string();
	Char *copy_unsigned_string();

	if ( addsym( copy_string( name ),
			(char *) copy_unsigned_string( definition ), 0,
			ndtbl, NAME_TABLE_HASH_SIZE ) )
		synerr( "name defined twice" );
	}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

Char *ndlookup( nd )
char nd[];
	{
	return (Char *) findsym( nd, ndtbl, NAME_TABLE_HASH_SIZE )->str_val;
	}


/* scextend - increase the maximum number of start conditions */

void scextend()
	{
	current_max_scs += MAX_SCS_INCREMENT;

	++num_reallocs;

	scset = reallocate_integer_array( scset, current_max_scs );
	scbol = reallocate_integer_array( scbol, current_max_scs );
	scxclu = reallocate_integer_array( scxclu, current_max_scs );
	sceof = reallocate_integer_array( sceof, current_max_scs );
	scname = reallocate_char_ptr_array( scname, current_max_scs );
	actvsc = reallocate_integer_array( actvsc, current_max_scs );
	}


/* scinstal - make a start condition
 *
 * NOTE
 *    The start condition is "exclusive" if xcluflg is true.
 */

void scinstal( str, xcluflg )
char str[];
int xcluflg;
	{
	char *copy_string();

	/* Generate start condition definition, for use in BEGIN et al. */
	printf( "#define %s %d\n", str, lastsc );

	if ( ++lastsc >= current_max_scs )
		scextend();

	scname[lastsc] = copy_string( str );

	if ( addsym( scname[lastsc], (char *) 0, lastsc,
			sctbl, START_COND_HASH_SIZE ) )
		format_pinpoint_message( "start condition %s declared twice",
					str );

	scset[lastsc] = mkstate( SYM_EPSILON );
	scbol[lastsc] = mkstate( SYM_EPSILON );
	scxclu[lastsc] = xcluflg;
	sceof[lastsc] = false;
	}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

int sclookup( str )
char str[];
	{
	return findsym( str, sctbl, START_COND_HASH_SIZE )->int_val;
	}
/* tblcmp - table compression routines */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */



/* declarations for functions that have forward references */

void mkentry PROTO((register int*, int, int, int, int));
void mkprot PROTO((int[], int, int));
void mktemplate PROTO((int[], int, int));
void mv2front PROTO((int));
int tbldiff PROTO((int[], int, int[]));


/* bldtbl - build table entries for dfa state
 *
 * synopsis
 *   int state[numecs], statenum, totaltrans, comstate, comfreq;
 *   bldtbl( state, statenum, totaltrans, comstate, comfreq );
 *
 * State is the statenum'th dfa state.  It is indexed by equivalence class and
 * gives the number of the state to enter for a given equivalence class.
 * totaltrans is the total number of transitions out of the state.  Comstate
 * is that state which is the destination of the most transitions out of State.
 * Comfreq is how many transitions there are out of State to Comstate.
 *
 * A note on terminology:
 *    "protos" are transition tables which have a high probability of
 * either being redundant (a state processed later will have an identical
 * transition table) or nearly redundant (a state processed later will have
 * many of the same out-transitions).  A "most recently used" queue of
 * protos is kept around with the hope that most states will find a proto
 * which is similar enough to be usable, and therefore compacting the
 * output tables.
 *    "templates" are a special type of proto.  If a transition table is
 * homogeneous or nearly homogeneous (all transitions go to the same
 * destination) then the odds are good that future states will also go
 * to the same destination state on basically the same character set.
 * These homogeneous states are so common when dealing with large rule
 * sets that they merit special attention.  If the transition table were
 * simply made into a proto, then (typically) each subsequent, similar
 * state will differ from the proto for two out-transitions.  One of these
 * out-transitions will be that character on which the proto does not go
 * to the common destination, and one will be that character on which the
 * state does not go to the common destination.  Templates, on the other
 * hand, go to the common state on EVERY transition character, and therefore
 * cost only one difference.
 */

void bldtbl( state, statenum, totaltrans, comstate, comfreq )
int state[], statenum, totaltrans, comstate, comfreq;
	{
	int extptr, extrct[2][CSIZE + 1];
	int mindiff, minprot, i, d;

	/* If extptr is 0 then the first array of extrct holds the result
	 * of the "best difference" to date, which is those transitions
	 * which occur in "state" but not in the proto which, to date,
	 * has the fewest differences between itself and "state".  If
	 * extptr is 1 then the second array of extrct hold the best
	 * difference.  The two arrays are toggled between so that the
	 * best difference to date can be kept around and also a difference
	 * just created by checking against a candidate "best" proto.
	 */

	extptr = 0;

	/* If the state has too few out-transitions, don't bother trying to
	 * compact its tables.
	 */

	if ( (totaltrans * 100) < (numecs * PROTO_SIZE_PERCENTAGE) )
		mkentry( state, numecs, statenum, JAMSTATE, totaltrans );

	else
		{
		/* "checkcom" is true if we should only check "state" against
		 * protos which have the same "comstate" value.
		 */
		int checkcom =
			comfreq * 100 > totaltrans * CHECK_COM_PERCENTAGE;

		minprot = firstprot;
		mindiff = totaltrans;

		if ( checkcom )
			{
			/* Find first proto which has the same "comstate". */
			for ( i = firstprot; i != NIL; i = protnext[i] )
				if ( protcomst[i] == comstate )
					{
					minprot = i;
					mindiff = tbldiff( state, minprot,
							extrct[extptr] );
					break;
					}
			}

		else
			{
			/* Since we've decided that the most common destination
			 * out of "state" does not occur with a high enough
			 * frequency, we set the "comstate" to zero, assuring
			 * that if this state is entered into the proto list,
			 * it will not be considered a template.
			 */
			comstate = 0;

			if ( firstprot != NIL )
				{
				minprot = firstprot;
				mindiff = tbldiff( state, minprot,
						extrct[extptr] );
				}
			}

		/* We now have the first interesting proto in "minprot".  If
		 * it matches within the tolerances set for the first proto,
		 * we don't want to bother scanning the rest of the proto list
		 * to see if we have any other reasonable matches.
		 */

		if ( mindiff * 100 > totaltrans * FIRST_MATCH_DIFF_PERCENTAGE )
			{
			/* Not a good enough match.  Scan the rest of the
			 * protos.
			 */
			for ( i = minprot; i != NIL; i = protnext[i] )
				{
				d = tbldiff( state, i, extrct[1 - extptr] );
				if ( d < mindiff )
					{
					extptr = 1 - extptr;
					mindiff = d;
					minprot = i;
					}
				}
			}

		/* Check if the proto we've decided on as our best bet is close
		 * enough to the state we want to match to be usable.
		 */

		if ( mindiff * 100 > totaltrans * ACCEPTABLE_DIFF_PERCENTAGE )
			{
			/* No good.  If the state is homogeneous enough,
			 * we make a template out of it.  Otherwise, we
			 * make a proto.
			 */

			if ( comfreq * 100 >=
			     totaltrans * TEMPLATE_SAME_PERCENTAGE )
				mktemplate( state, statenum, comstate );

			else
				{
				mkprot( state, statenum, comstate );
				mkentry( state, numecs, statenum,
					JAMSTATE, totaltrans );
				}
			}

		else
			{ /* use the proto */
			mkentry( extrct[extptr], numecs, statenum,
				prottbl[minprot], mindiff );

			/* If this state was sufficiently different from the
			 * proto we built it from, make it, too, a proto.
			 */

			if ( mindiff * 100 >=
			     totaltrans * NEW_PROTO_DIFF_PERCENTAGE )
				mkprot( state, statenum, comstate );

			/* Since mkprot added a new proto to the proto queue,
			 * it's possible that "minprot" is no longer on the
			 * proto queue (if it happened to have been the last
			 * entry, it would have been bumped off).  If it's
			 * not there, then the new proto took its physical
			 * place (though logically the new proto is at the
			 * beginning of the queue), so in that case the
			 * following call will do nothing.
			 */

			mv2front( minprot );
			}
		}
	}


/* cmptmps - compress template table entries
 *
 * Template tables are compressed by using the 'template equivalence
 * classes', which are collections of transition character equivalence
 * classes which always appear together in templates - really meta-equivalence
 * classes.
 */

void cmptmps()
	{
	int tmpstorage[CSIZE + 1];
	register int *tmp = tmpstorage, i, j;
	int totaltrans, trans;

	peakpairs = numtemps * numecs + tblend;

	if ( usemecs )
		{
		/* Create equivalence classes based on data gathered on
		 * template transitions.
		 */
		nummecs = cre8ecs( tecfwd, tecbck, numecs );
		}

	else
		nummecs = numecs;

	while ( lastdfa + numtemps + 1 >= current_max_dfas )
		increase_max_dfas();

	/* Loop through each template. */

	for ( i = 1; i <= numtemps; ++i )
		{
		/* Number of non-jam transitions out of this template. */
		totaltrans = 0;

		for ( j = 1; j <= numecs; ++j )
			{
			trans = tnxt[numecs * i + j];

			if ( usemecs )
				{
				/* The absolute value of tecbck is the
				 * meta-equivalence class of a given
				 * equivalence class, as set up by cre8ecs().
				 */
				if ( tecbck[j] > 0 )
					{
					tmp[tecbck[j]] = trans;

					if ( trans > 0 )
						++totaltrans;
					}
				}

			else
				{
				tmp[j] = trans;

				if ( trans > 0 )
					++totaltrans;
				}
			}

		/* It is assumed (in a rather subtle way) in the skeleton
		 * that if we're using meta-equivalence classes, the def[]
		 * entry for all templates is the jam template, i.e.,
		 * templates never default to other non-jam table entries
		 * (e.g., another template)
		 */

		/* Leave room for the jam-state after the last real state. */
		mkentry( tmp, nummecs, lastdfa + i + 1, JAMSTATE, totaltrans );
		}
	}



/* expand_nxt_chk - expand the next check arrays */

void expand_nxt_chk()
	{
	register int old_max = current_max_xpairs;

	current_max_xpairs += MAX_XPAIRS_INCREMENT;

	++num_reallocs;

	nxt = reallocate_integer_array( nxt, current_max_xpairs );
	chk = reallocate_integer_array( chk, current_max_xpairs );

	zero_out( (char *) (chk + old_max),
		MAX_XPAIRS_INCREMENT * sizeof( int ) / sizeof( char ) );
	}


/* find_table_space - finds a space in the table for a state to be placed
 *
 * synopsis
 *     int *state, numtrans, block_start;
 *     int find_table_space();
 *
 *     block_start = find_table_space( state, numtrans );
 *
 * State is the state to be added to the full speed transition table.
 * Numtrans is the number of out-transitions for the state.
 *
 * find_table_space() returns the position of the start of the first block (in
 * chk) able to accommodate the state
 *
 * In determining if a state will or will not fit, find_table_space() must take
 * into account the fact that an end-of-buffer state will be added at [0],
 * and an action number will be added in [-1].
 */

int find_table_space( state, numtrans )
int *state, numtrans;
	{
	/* Firstfree is the position of the first possible occurrence of two
	 * consecutive unused records in the chk and nxt arrays.
	 */
	register int i;
	register int *state_ptr, *chk_ptr;
	register int *ptr_to_last_entry_in_state;

	/* If there are too many out-transitions, put the state at the end of
	 * nxt and chk.
	 */
	if ( numtrans > MAX_XTIONS_FULL_INTERIOR_FIT )
		{
		/* If table is empty, return the first available spot in
		 * chk/nxt, which should be 1.
		 */
		if ( tblend < 2 )
			return 1;

		/* Start searching for table space near the end of
		 * chk/nxt arrays.
		 */
		i = tblend - numecs;
		}

	else
		/* Start searching for table space from the beginning
		 * (skipping only the elements which will definitely not
		 * hold the new state).
		 */
		i = firstfree;

	while ( 1 )	/* loops until a space is found */
		{
		while ( i + numecs >= current_max_xpairs )
			expand_nxt_chk();

		/* Loops until space for end-of-buffer and action number
		 * are found.
		 */
		while ( 1 )
			{
			/* Check for action number space. */
			if ( chk[i - 1] == 0 )
				{
				/* Check for end-of-buffer space. */
				if ( chk[i] == 0 )
					break;

				else
					/* Since i != 0, there is no use
					 * checking to see if (++i) - 1 == 0,
					 * because that's the same as i == 0,
					 * so we skip a space.
					 */
					i += 2;
				}

			else
				++i;

			while ( i + numecs >= current_max_xpairs )
				expand_nxt_chk();
			}

		/* If we started search from the beginning, store the new
		 * firstfree for the next call of find_table_space().
		 */
		if ( numtrans <= MAX_XTIONS_FULL_INTERIOR_FIT )
			firstfree = i + 1;

		/* Check to see if all elements in chk (and therefore nxt)
		 * that are needed for the new state have not yet been taken.
		 */

		state_ptr = &state[1];
		ptr_to_last_entry_in_state = &chk[i + numecs + 1];

		for ( chk_ptr = &chk[i + 1];
		      chk_ptr != ptr_to_last_entry_in_state; ++chk_ptr )
			if ( *(state_ptr++) != 0 && *chk_ptr != 0 )
				break;

		if ( chk_ptr == ptr_to_last_entry_in_state )
			return i;

		else
		++i;
		}
	}


/* inittbl - initialize transition tables
 *
 * Initializes "firstfree" to be one beyond the end of the table.  Initializes
 * all "chk" entries to be zero.
 */
void inittbl()
	{
	register int i;

	zero_out( (char *) chk,
		current_max_xpairs * sizeof( int ) / sizeof( char ) );

	tblend = 0;
	firstfree = tblend + 1;
	numtemps = 0;

	if ( usemecs )
		{
		/* Set up doubly-linked meta-equivalence classes; these
		 * are sets of equivalence classes which all have identical
		 * transitions out of TEMPLATES.
		 */

		tecbck[1] = NIL;

		for ( i = 2; i <= numecs; ++i )
			{
			tecbck[i] = i - 1;
			tecfwd[i - 1] = i;
			}

		tecfwd[numecs] = NIL;
		}
	}


/* mkdeftbl - make the default, "jam" table entries */

void mkdeftbl()
	{
	int i;

	jamstate = lastdfa + 1;

	++tblend; /* room for transition on end-of-buffer character */

	while ( tblend + numecs >= current_max_xpairs )
		expand_nxt_chk();

	/* Add in default end-of-buffer transition. */
	nxt[tblend] = end_of_buffer_state;
	chk[tblend] = jamstate;

	for ( i = 1; i <= numecs; ++i )
		{
		nxt[tblend + i] = 0;
		chk[tblend + i] = jamstate;
		}

	jambase = tblend;

	base[jamstate] = jambase;
	def[jamstate] = 0;

	tblend += numecs;
	++numtemps;
	}


/* mkentry - create base/def and nxt/chk entries for transition array
 *
 * synopsis
 *   int state[numchars + 1], numchars, statenum, deflink, totaltrans;
 *   mkentry( state, numchars, statenum, deflink, totaltrans );
 *
 * "state" is a transition array "numchars" characters in size, "statenum"
 * is the offset to be used into the base/def tables, and "deflink" is the
 * entry to put in the "def" table entry.  If "deflink" is equal to
 * "JAMSTATE", then no attempt will be made to fit zero entries of "state"
 * (i.e., jam entries) into the table.  It is assumed that by linking to
 * "JAMSTATE" they will be taken care of.  In any case, entries in "state"
 * marking transitions to "SAME_TRANS" are treated as though they will be
 * taken care of by whereever "deflink" points.  "totaltrans" is the total
 * number of transitions out of the state.  If it is below a certain threshold,
 * the tables are searched for an interior spot that will accommodate the
 * state array.
 */

void mkentry( state, numchars, statenum, deflink, totaltrans )
register int *state;
int numchars, statenum, deflink, totaltrans;
	{
	register int minec, maxec, i, baseaddr;
	int tblbase, tbllast;

	if ( totaltrans == 0 )
		{ /* there are no out-transitions */
		if ( deflink == JAMSTATE )
			base[statenum] = JAMSTATE;
		else
			base[statenum] = 0;

		def[statenum] = deflink;
		return;
		}

	for ( minec = 1; minec <= numchars; ++minec )
		{
		if ( state[minec] != SAME_TRANS )
			if ( state[minec] != 0 || deflink != JAMSTATE )
				break;
		}

	if ( totaltrans == 1 )
		{
		/* There's only one out-transition.  Save it for later to fill
		 * in holes in the tables.
		 */
		stack1( statenum, minec, state[minec], deflink );
		return;
		}

	for ( maxec = numchars; maxec > 0; --maxec )
		{
		if ( state[maxec] != SAME_TRANS )
			if ( state[maxec] != 0 || deflink != JAMSTATE )
				break;
		}

	/* Whether we try to fit the state table in the middle of the table
	 * entries we have already generated, or if we just take the state
	 * table at the end of the nxt/chk tables, we must make sure that we
	 * have a valid base address (i.e., non-negative).  Note that
	 * negative base addresses dangerous at run-time (because indexing
	 * the nxt array with one and a low-valued character will access
	 * memory before the start of the array.
	 */

	/* Find the first transition of state that we need to worry about. */
	if ( totaltrans * 100 <= numchars * INTERIOR_FIT_PERCENTAGE )
		{
		/* Attempt to squeeze it into the middle of the tables. */
		baseaddr = firstfree;

		while ( baseaddr < minec )
			{
			/* Using baseaddr would result in a negative base
			 * address below; find the next free slot.
			 */
			for ( ++baseaddr; chk[baseaddr] != 0; ++baseaddr )
				;
			}

		while ( baseaddr + maxec - minec + 1 >= current_max_xpairs )
			expand_nxt_chk();

		for ( i = minec; i <= maxec; ++i )
			if ( state[i] != SAME_TRANS &&
			     (state[i] != 0 || deflink != JAMSTATE) &&
			     chk[baseaddr + i - minec] != 0 )
				{ /* baseaddr unsuitable - find another */
				for ( ++baseaddr;
				      baseaddr < current_max_xpairs &&
				      chk[baseaddr] != 0; ++baseaddr )
					;

				while ( baseaddr + maxec - minec + 1 >=
					current_max_xpairs )
					expand_nxt_chk();

				/* Reset the loop counter so we'll start all
				 * over again next time it's incremented.
				 */

				i = minec - 1;
				}
		}

	else
		{
		/* Ensure that the base address we eventually generate is
		 * non-negative.
		 */
		baseaddr = max( tblend + 1, minec );
		}

	tblbase = baseaddr - minec;
	tbllast = tblbase + maxec;

	while ( tbllast + 1 >= current_max_xpairs )
		expand_nxt_chk();

	base[statenum] = tblbase;
	def[statenum] = deflink;

	for ( i = minec; i <= maxec; ++i )
		if ( state[i] != SAME_TRANS )
			if ( state[i] != 0 || deflink != JAMSTATE )
				{
				nxt[tblbase + i] = state[i];
				chk[tblbase + i] = statenum;
				}

	if ( baseaddr == firstfree )
		/* Find next free slot in tables. */
		for ( ++firstfree; chk[firstfree] != 0; ++firstfree )
			;

	tblend = max( tblend, tbllast );
	}


/* mk1tbl - create table entries for a state (or state fragment) which
 *            has only one out-transition
 */

void mk1tbl( state, sym, onenxt, onedef )
int state, sym, onenxt, onedef;
	{
	if ( firstfree < sym )
		firstfree = sym;

	while ( chk[firstfree] != 0 )
		if ( ++firstfree >= current_max_xpairs )
			expand_nxt_chk();

	base[state] = firstfree - sym;
	def[state] = onedef;
	chk[firstfree] = state;
	nxt[firstfree] = onenxt;

	if ( firstfree > tblend )
		{
		tblend = firstfree++;

		if ( firstfree >= current_max_xpairs )
			expand_nxt_chk();
		}
	}


/* mkprot - create new proto entry */

void mkprot( state, statenum, comstate )
int state[], statenum, comstate;
	{
	int i, slot, tblbase;

	if ( ++numprots >= MSP || numecs * numprots >= PROT_SAVE_SIZE )
		{
		/* Gotta make room for the new proto by dropping last entry in
		 * the queue.
		 */
		slot = lastprot;
		lastprot = protprev[lastprot];
		protnext[lastprot] = NIL;
		}

	else
		slot = numprots;

	protnext[slot] = firstprot;

	if ( firstprot != NIL )
		protprev[firstprot] = slot;

	firstprot = slot;
	prottbl[slot] = statenum;
	protcomst[slot] = comstate;

	/* Copy state into save area so it can be compared with rapidly. */
	tblbase = numecs * (slot - 1);

	for ( i = 1; i <= numecs; ++i )
		protsave[tblbase + i] = state[i];
	}


/* mktemplate - create a template entry based on a state, and connect the state
 *              to it
 */

void mktemplate( state, statenum, comstate )
int state[], statenum, comstate;
	{
	int i, numdiff, tmpbase, tmp[CSIZE + 1];
	Char transset[CSIZE + 1];
	int tsptr;

	++numtemps;

	tsptr = 0;

	/* Calculate where we will temporarily store the transition table
	 * of the template in the tnxt[] array.  The final transition table
	 * gets created by cmptmps().
	 */

	tmpbase = numtemps * numecs;

	if ( tmpbase + numecs >= current_max_template_xpairs )
		{
		current_max_template_xpairs += MAX_TEMPLATE_XPAIRS_INCREMENT;

		++num_reallocs;

		tnxt = reallocate_integer_array( tnxt,
			current_max_template_xpairs );
		}

	for ( i = 1; i <= numecs; ++i )
		if ( state[i] == 0 )
			tnxt[tmpbase + i] = 0;
		else
			{
			transset[tsptr++] = i;
			tnxt[tmpbase + i] = comstate;
			}

	if ( usemecs )
		mkeccl( transset, tsptr, tecfwd, tecbck, numecs, 0 );

	mkprot( tnxt + tmpbase, -numtemps, comstate );

	/* We rely on the fact that mkprot adds things to the beginning
	 * of the proto queue.
	 */

	numdiff = tbldiff( state, firstprot, tmp );
	mkentry( tmp, numecs, statenum, -numtemps, numdiff );
	}


/* mv2front - move proto queue element to front of queue */

void mv2front( qelm )
int qelm;
	{
	if ( firstprot != qelm )
		{
		if ( qelm == lastprot )
			lastprot = protprev[lastprot];

		protnext[protprev[qelm]] = protnext[qelm];

		if ( protnext[qelm] != NIL )
			protprev[protnext[qelm]] = protprev[qelm];

		protprev[qelm] = NIL;
		protnext[qelm] = firstprot;
		protprev[firstprot] = qelm;
		firstprot = qelm;
		}
	}


/* place_state - place a state into full speed transition table
 *
 * State is the statenum'th state.  It is indexed by equivalence class and
 * gives the number of the state to enter for a given equivalence class.
 * Transnum is the number of out-transitions for the state.
 */

void place_state( state, statenum, transnum )
int *state, statenum, transnum;
	{
	register int i;
	register int *state_ptr;
	int position = find_table_space( state, transnum );

	/* "base" is the table of start positions. */
	base[statenum] = position;

	/* Put in action number marker; this non-zero number makes sure that
	 * find_table_space() knows that this position in chk/nxt is taken
	 * and should not be used for another accepting number in another
	 * state.
	 */
	chk[position - 1] = 1;

	/* Put in end-of-buffer marker; this is for the same purposes as
	 * above.
	 */
	chk[position] = 1;

	/* Place the state into chk and nxt. */
	state_ptr = &state[1];

	for ( i = 1; i <= numecs; ++i, ++state_ptr )
		if ( *state_ptr != 0 )
			{
			chk[position + i] = i;
			nxt[position + i] = *state_ptr;
			}

	if ( position + numecs > tblend )
		tblend = position + numecs;
	}


/* stack1 - save states with only one out-transition to be processed later
 *
 * If there's room for another state on the "one-transition" stack, the
 * state is pushed onto it, to be processed later by mk1tbl.  If there's
 * no room, we process the sucker right now.
 */

void stack1( statenum, sym, nextstate, deflink )
int statenum, sym, nextstate, deflink;
	{
	if ( onesp >= ONE_STACK_SIZE - 1 )
		mk1tbl( statenum, sym, nextstate, deflink );

	else
		{
		++onesp;
		onestate[onesp] = statenum;
		onesym[onesp] = sym;
		onenext[onesp] = nextstate;
		onedef[onesp] = deflink;
		}
	}


/* tbldiff - compute differences between two state tables
 *
 * "state" is the state array which is to be extracted from the pr'th
 * proto.  "pr" is both the number of the proto we are extracting from
 * and an index into the save area where we can find the proto's complete
 * state table.  Each entry in "state" which differs from the corresponding
 * entry of "pr" will appear in "ext".
 *
 * Entries which are the same in both "state" and "pr" will be marked
 * as transitions to "SAME_TRANS" in "ext".  The total number of differences
 * between "state" and "pr" is returned as function value.  Note that this
 * number is "numecs" minus the number of "SAME_TRANS" entries in "ext".
 */

int tbldiff( state, pr, ext )
int state[], pr, ext[];
	{
	register int i, *sp = state, *ep = ext, *protp;
	register int numdiff = 0;

	protp = &protsave[numecs * (pr - 1)];

	for ( i = numecs; i > 0; --i )
		{
		if ( *++protp == *++sp )
			*++ep = SAME_TRANS;
		else
			{
			*++ep = *sp;
			++numdiff;
			}
		}

	return numdiff;
	}
/* yylex - scanner front-end for flex */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */



/* yylex - scan for a regular expression token */

int yylex()
	{
	int toktype;
	static int beglin = false;

	if ( eofseen )
		toktype = EOF;
	else
		toktype = flexscan();

	if ( toktype == EOF || toktype == 0 )
		{
		eofseen = 1;

		if ( sectnum == 1 )
			{
			synerr( "premature EOF" );
			sectnum = 2;
			toktype = SECTEND;
			}

		else
			toktype = 0;
		}

	if ( trace )
		{
		if ( beglin )
			{
			fprintf( err, "%d\t", num_rules + 1 );
			beglin = 0;
			}

		switch ( toktype )
			{
			case '<':
			case '>':
			case '^':
			case '$':
			case '"':
			case '[':
			case ']':
			case '{':
			case '}':
			case '|':
			case '(':
			case ')':
			case '-':
			case '/':
			case '\\':
			case '?':
			case '.':
			case '*':
			case '+':
			case ',':
				(void) putc( toktype, err );
				break;

			case '\n':
				(void) putc( '\n', err );

				if ( sectnum == 2 )
				beglin = 1;

				break;

			case SCDECL:
				fputs( "%s", err );
				break;

			case XSCDECL:
				fputs( "%x", err );
				break;

			case WHITESPACE:
				(void) putc( ' ', err );
				break;

			case SECTEND:
				fputs( "%%\n", err );

				/* We set beglin to be true so we'll start
				 * writing out numbers as we echo rules.
				 * flexscan() has already assigned sectnum.
				 */

				if ( sectnum == 2 )
				beglin = 1;

				break;

			case NAME:
				fprintf( err, "'%s'", nmstr );
				break;

			case CHAR:
				switch ( yylval )
					{
					case '<':
					case '>':
					case '^':
					case '$':
					case '"':
					case '[':
					case ']':
					case '{':
					case '}':
					case '|':
					case '(':
					case ')':
					case '-':
					case '/':
					case '\\':
					case '?':
					case '.':
					case '*':
					case '+':
					case ',':
						fprintf( err, "\\%c",
							yylval );
						break;

					default:
						if ( ! isascii( yylval ) ||
						     ! isprint( yylval ) )
							fprintf( err,
								"\\%.3o",
							(unsigned int) yylval );
						else
							(void) putc( yylval,
								err );
					break;
					}

				break;

			case NUMBER:
				fprintf( err, "%d", yylval );
				break;

			case PREVCCL:
				fprintf( err, "[%d]", yylval );
				break;

			case EOF_OP:
				fprintf( err, "<<EOF>>" );
				break;

			case 0:
				fprintf( err, "End Marker" );
				break;

			default:
				fprintf( err,
					"*Something Weird* - tok: %d val: %d\n",
					toktype, yylval );
				break;
			}
		}

	return toktype;
	}

/*  A Bison parser, made from ./parse.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	CHAR	257
#define	NUMBER	258
#define	SECTEND	259
#define	SCDECL	260
#define	XSCDECL	261
#define	WHITESPACE	262
#define	NAME	263
#define	PREVCCL	264
#define	EOF_OP	265


/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */


/* Some versions of bison are broken in that they use alloca() but don't
 * declare it properly.  The following is the patented (just kidding!)
 * #ifdef chud to fix the problem, courtesy of Francois Pinard.
 */
#ifdef YYBISON
/* AIX requires this to be the first thing in the file.  */
#if (defined(__GNUC__) && (!defined(LINUX)))
#define alloca __builtin_alloca
#else /* not __GNUC__ */
#if HAVE_ALLOCA_H
#include <alloca.h>
#else /* not HAVE_ALLOCA_H */
#ifdef _AIX
 #pragma alloca
#else /* not _AIX */
char *alloca ();
#endif /* not _AIX */
#endif /* not HAVE_ALLOCA_H */
#endif /* not __GNUC__ */
#endif /* YYBISON */

/* Bletch, ^^^^ that was ugly! */



int pat, scnum, eps, headcnt, trailcnt, anyccl, lastchar, i, actvp, rulelen;
int trlcontxt, xcluflg, cclsorted, varlength, variable_trail_rule;
int *active_ss;
Char clower();
void build_eof_action();
void yyerror();

static int madeany = false;  /* whether we've made the '.' character class */
int previous_continued_action;	/* whether the previous rule's action was '|' */

/* On some over-ambitious machines, such as DEC Alpha's, the default
 * token type is "long" instead of "int"; this leads to problems with
 * declaring yylval in flexdef.h.  But so far, all the yacc's I've seen
 * wrap their definitions of YYSTYPE with "#ifndef YYSTYPE"'s, so the
 * following should ensure that the default token type is "int".
 */
#define YYSTYPE int

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		85
#define	YYFLAG		-32768
#define	YYNTBASE	32

#define YYTRANSLATE(x) ((unsigned)(x) <= 265 ? yytranslate[x] : 53)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    12,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    26,     2,    18,     2,     2,     2,    27,
    28,    16,    21,    17,    31,    25,    20,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    14,
     2,    15,    22,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    29,     2,    30,    13,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    23,    19,    24,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     6,     7,    13,    14,    17,    19,    21,    23,    27,
    29,    31,    36,    37,    38,    42,    45,    48,    50,    53,
    55,    57,    61,    65,    69,    70,    73,    75,    77,    80,
    84,    87,    89,    93,    95,    98,   101,   103,   106,   109,
   112,   119,   125,   130,   132,   134,   136,   140,   144,   146,
   150,   155,   160,   163,   164,   167
};

static const short yyrhs[] = {    33,
    34,    35,    38,    39,     0,     0,    34,    36,     8,    37,
    12,     0,     0,     1,    12,     0,     5,     0,     6,     0,
     7,     0,    37,     8,     9,     0,     9,     0,     1,     0,
    38,    39,    40,    12,     0,     0,     0,    41,    13,    45,
     0,    41,    45,     0,    13,    45,     0,    45,     0,    41,
    11,     0,    11,     0,     1,     0,    14,    42,    15,     0,
    14,    16,    15,     0,    42,    17,    44,     0,     0,    43,
    44,     0,     1,     0,     9,     0,    47,    46,     0,    47,
    46,    18,     0,    46,    18,     0,    46,     0,    46,    19,
    48,     0,    48,     0,    46,    20,     0,    48,    49,     0,
    49,     0,    49,    16,     0,    49,    21,     0,    49,    22,
     0,    49,    23,     4,    17,     4,    24,     0,    49,    23,
     4,    17,    24,     0,    49,    23,     4,    24,     0,    25,
     0,    50,     0,    10,     0,    26,    52,    26,     0,    27,
    46,    28,     0,     3,     0,    29,    51,    30,     0,    29,
    13,    51,    30,     0,    51,     3,    31,     3,     0,    51,
     3,     0,     0,    52,     3,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    82,   111,   124,   125,   126,   130,   143,   146,   150,   153,
   156,   160,   161,   164,   175,   195,   206,   230,   241,   244,
   263,   267,   269,   278,   280,   282,   282,   286,   307,   362,
   365,   413,   431,   437,   442,   469,   477,   481,   488,   494,
   500,   528,   542,   561,   583,   601,   608,   611,   614,   625,
   628,   635,   663,   674,   682,   692
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","CHAR","NUMBER",
"SECTEND","SCDECL","XSCDECL","WHITESPACE","NAME","PREVCCL","EOF_OP","'\\n'",
"'^'","'<'","'>'","'*'","','","'$'","'|'","'/'","'+'","'?'","'{'","'}'","'.'",
"'\\\"'","'('","')'","'['","']'","'-'","goal","initlex","sect1","sect1end","startconddecl",
"namelist1","sect2","initforrule","flexrule","scon","namelist2","@1","sconname",
"rule","re","re2","series","singleton","fullccl","ccl","string", NULL
};
#endif

static const short yyr1[] = {     0,
    32,    33,    34,    34,    34,    35,    36,    36,    37,    37,
    37,    38,    38,    39,    40,    40,    40,    40,    40,    40,
    40,    41,    41,    42,    43,    42,    42,    44,    45,    45,
    45,    45,    46,    46,    47,    48,    48,    49,    49,    49,
    49,    49,    49,    49,    49,    49,    49,    49,    49,    50,
    50,    51,    51,    51,    52,    52
};

static const short yyr2[] = {     0,
     5,     0,     5,     0,     2,     1,     1,     1,     3,     1,
     1,     4,     0,     0,     3,     2,     2,     1,     2,     1,
     1,     3,     3,     3,     0,     2,     1,     1,     2,     3,
     2,     1,     3,     1,     2,     2,     1,     2,     2,     2,
     6,     5,     4,     1,     1,     1,     3,     3,     1,     3,
     4,     4,     2,     0,     2,     0
};

static const short yydefact[] = {     2,
     0,     0,     0,     5,     6,     7,     8,    13,     0,    14,
     0,     0,    11,    10,     0,    21,    49,    46,    20,     0,
     0,    44,    56,     0,    54,     0,     0,    18,    32,     0,
    34,    37,    45,     0,     3,    17,    27,     0,     0,     0,
     0,     0,    54,     0,    12,    19,     0,    16,    31,     0,
    35,    29,    36,    38,    39,    40,     0,     9,    23,    22,
     0,    28,    26,    55,    47,    48,     0,    53,    50,    15,
    33,    30,     0,    24,    51,     0,     0,    43,    52,     0,
    42,    41,     0,     0,     0
};

static const short yydefgoto[] = {    83,
     1,     3,     8,     9,    15,    10,    12,    26,    27,    39,
    40,    63,    28,    29,    30,    31,    32,    33,    44,    41
};

static const short yypact[] = {-32768,
    61,    -2,    64,-32768,-32768,-32768,-32768,-32768,    13,-32768,
    34,     1,-32768,-32768,    30,-32768,-32768,-32768,-32768,    21,
    48,-32768,-32768,    21,    31,    33,    26,-32768,    54,    21,
    21,    38,-32768,    47,-32768,-32768,-32768,    43,     5,    56,
    15,   -11,-32768,     2,-32768,-32768,    21,-32768,-32768,    21,
-32768,    57,    38,-32768,-32768,-32768,    59,-32768,-32768,-32768,
    56,-32768,-32768,-32768,-32768,-32768,     4,    46,-32768,-32768,
    21,-32768,    -8,-32768,-32768,    75,    -1,-32768,-32768,    55,
-32768,-32768,    80,    81,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    22,   -14,    -5,-32768,    32,   -31,-32768,    41,-32768
};


#define	YYLAST		84


static const short yytable[] = {    53,
    -1,    16,    80,    17,    68,    36,    68,    50,    77,     4,
    18,    19,    48,    20,    21,    78,    66,    64,    42,    60,
    11,    61,    81,    17,    52,    22,    23,    24,    17,    25,
    18,    69,    70,    75,    13,    18,    46,    34,    47,    53,
    65,    35,    14,    43,    45,    22,    23,    24,    37,    25,
    22,    23,    24,    54,    25,    58,   -25,    59,    55,    56,
    57,     2,    73,    38,    62,    -4,    -4,    -4,     5,     6,
     7,    49,    50,    51,    72,    50,    76,    79,    82,    84,
    85,    71,    74,    67
};

static const short yycheck[] = {    31,
     0,     1,     4,     3,     3,    20,     3,    19,    17,    12,
    10,    11,    27,    13,    14,    24,    28,     3,    24,    15,
     8,    17,    24,     3,    30,    25,    26,    27,     3,    29,
    10,    30,    47,    30,     1,    10,    11,     8,    13,    71,
    26,    12,     9,    13,    12,    25,    26,    27,     1,    29,
    25,    26,    27,    16,    29,     9,     9,    15,    21,    22,
    23,     1,     4,    16,     9,     5,     6,     7,     5,     6,
     7,    18,    19,    20,    18,    19,    31,     3,    24,     0,
     0,    50,    61,    43
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif
/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(err, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(err, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(err, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(err, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(err, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (err, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (err, yychar, yylval);
#endif
	  fprintf (err, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(err, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (err, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (err, "%s ", yytname[yyrhs[i]]);
      fprintf (err, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
{ /* add default rule */
			int def_rule;

			pat = cclinit();
			cclnegate( pat );

			def_rule = mkstate( -pat );

			/* Remember the number of the default rule so we
			 * don't generate "can't match" warnings for it.
			 */
			default_rule = num_rules;

			finish_rule( def_rule, false, 0, 0 );

			for ( i = 1; i <= lastsc; ++i )
				scset[i] = mkbranch( scset[i], def_rule );

			if ( spprdflt )
				add_action(
				"YY_FATAL_ERROR( \"flex scanner jammed\" )" );
			else
				add_action( "ECHO" );

			add_action( ";\n\tYY_BREAK\n" );
			;
    break;}
case 2:
{ /* initialize for processing rules */

			/* Create default DFA start condition. */
			scinstal( "INITIAL", false );

			/* Initially, the start condition scoping is
			 * "no start conditions active".
			 */
			actvp = 0;
			;
    break;}
case 5:
{ synerr( "unknown error processing section 1" ); ;
    break;}
case 6:
{
			/* We now know how many start conditions there
			 * are, so create the "activity" map indicating
			 * which conditions are active.
			 */
			active_ss = allocate_integer_array( lastsc + 1 );

			for ( i = 1; i <= lastsc; ++i )
				active_ss[i] = 0;
			;
    break;}
case 7:
{ xcluflg = false; ;
    break;}
case 8:
{ xcluflg = true; ;
    break;}
case 9:
{ scinstal( nmstr, xcluflg ); ;
    break;}
case 10:
{ scinstal( nmstr, xcluflg ); ;
    break;}
case 11:
{ synerr( "bad start condition list" ); ;
    break;}
case 14:
{
			/* Initialize for a parse of one rule. */
			trlcontxt = variable_trail_rule = varlength = false;
			trailcnt = headcnt = rulelen = 0;
			current_state_type = STATE_NORMAL;
			previous_continued_action = continued_action;
			new_rule();
			;
    break;}
case 15:
{
			pat = yyvsp[0];
			finish_rule( pat, variable_trail_rule,
				headcnt, trailcnt );

			for ( i = 1; i <= actvp; ++i )
				scbol[actvsc[i]] =
					mkbranch( scbol[actvsc[i]], pat );

			if ( ! bol_needed )
				{
				bol_needed = true;

				if ( performance_report > 1 )
					pinpoint_message( 
			"'^' operator results in sub-optimal performance" );
				}
			;
    break;}
case 16:
{
			pat = yyvsp[0];
			finish_rule( pat, variable_trail_rule,
				headcnt, trailcnt );

			for ( i = 1; i <= actvp; ++i )
				scset[actvsc[i]] =
					mkbranch( scset[actvsc[i]], pat );
			;
    break;}
case 17:
{
			pat = yyvsp[0];
			finish_rule( pat, variable_trail_rule,
				headcnt, trailcnt );

			/* Add to all non-exclusive start conditions,
			 * including the default (0) start condition.
			 */

			for ( i = 1; i <= lastsc; ++i )
				if ( ! scxclu[i] )
					scbol[i] = mkbranch( scbol[i], pat );

			if ( ! bol_needed )
				{
				bol_needed = true;

				if ( performance_report > 1 )
					pinpoint_message(
			"'^' operator results in sub-optimal performance" );
				}
			;
    break;}
case 18:
{
			pat = yyvsp[0];
			finish_rule( pat, variable_trail_rule,
				headcnt, trailcnt );

			for ( i = 1; i <= lastsc; ++i )
				if ( ! scxclu[i] )
					scset[i] = mkbranch( scset[i], pat );
			;
    break;}
case 19:
{ build_eof_action(); ;
    break;}
case 20:
{
			/* This EOF applies to all start conditions
			 * which don't already have EOF actions.
			 */
			actvp = 0;

			for ( i = 1; i <= lastsc; ++i )
				if ( ! sceof[i] )
					actvsc[++actvp] = i;

			if ( actvp == 0 )
				warn(
			"all start conditions already have <<EOF>> rules" );

			else
				build_eof_action();
			;
    break;}
case 21:
{ synerr( "unrecognized rule" ); ;
    break;}
case 23:
{
			actvp = 0;

			for ( i = 1; i <= lastsc; ++i )
				actvsc[++actvp] = i;
			;
    break;}
case 25:
{ actvp = 0; ;
    break;}
case 27:
{ synerr( "bad start condition list" ); ;
    break;}
case 28:
{
			if ( (scnum = sclookup( nmstr )) == 0 )
				format_pinpoint_message(
					"undeclared start condition %s",
					nmstr );
			else
				{
				if ( ++actvp >= current_max_scs )
					/* Some bozo has included multiple
					 * instances of start condition names.
					 */
					pinpoint_message(
				"too many start conditions in <> construct!" );

				else
					actvsc[actvp] = scnum;
				}
			;
    break;}
case 29:
{
			if ( transchar[lastst[yyvsp[0]]] != SYM_EPSILON )
				/* Provide final transition \now/ so it
				 * will be marked as a trailing context
				 * state.
				 */
				yyvsp[0] = link_machines( yyvsp[0],
						mkstate( SYM_EPSILON ) );

			mark_beginning_as_normal( yyvsp[0] );
			current_state_type = STATE_NORMAL;

			if ( previous_continued_action )
				{
				/* We need to treat this as variable trailing
				 * context so that the backup does not happen
				 * in the action but before the action switch
				 * statement.  If the backup happens in the
				 * action, then the rules "falling into" this
				 * one's action will *also* do the backup,
				 * erroneously.
				 */
				if ( ! varlength || headcnt != 0 )
					warn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;
				}

			if ( lex_compat || (varlength && headcnt == 0) )
				{ /* variable trailing context rule */
				/* Mark the first part of the rule as the
				 * accepting "head" part of a trailing
				 * context rule.
				 *
				 * By the way, we didn't do this at the
				 * beginning of this production because back
				 * then current_state_type was set up for a
				 * trail rule, and add_accept() can create
				 * a new state ...
				 */
				add_accept( yyvsp[-1],
					num_rules | YY_TRAILING_HEAD_MASK );
				variable_trail_rule = true;
				}
			
			else
				trailcnt = rulelen;

			yyval = link_machines( yyvsp[-1], yyvsp[0] );
			;
    break;}
case 30:
{ synerr( "trailing context used twice" ); ;
    break;}
case 31:
{
			if ( trlcontxt )
				{
				synerr( "trailing context used twice" );
				yyval = mkstate( SYM_EPSILON );
				}

			else if ( previous_continued_action )
				{
				/* See the comment in the rule for "re2 re"
				 * above.
				 */
				if ( ! varlength || headcnt != 0 )
					warn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;
				}

			if ( lex_compat || (varlength && headcnt == 0) )
				{
				/* Again, see the comment in the rule for
				 * "re2 re" above.
				 */
				add_accept( yyvsp[-1],
					num_rules | YY_TRAILING_HEAD_MASK );
				variable_trail_rule = true;
				}

			else
				{
				if ( ! varlength )
					headcnt = rulelen;

				++rulelen;
				trailcnt = 1;
				}

			trlcontxt = true;

			eps = mkstate( SYM_EPSILON );
			yyval = link_machines( yyvsp[-1],
				link_machines( eps, mkstate( '\n' ) ) );
			;
    break;}
case 32:
{
			yyval = yyvsp[0];

			if ( trlcontxt )
				{
				if ( lex_compat || (varlength && headcnt == 0) )
					/* Both head and trail are
					 * variable-length.
					 */
					variable_trail_rule = true;
				else
					trailcnt = rulelen;
				}
			;
    break;}
case 33:
{
			varlength = true;
			yyval = mkor( yyvsp[-2], yyvsp[0] );
			;
    break;}
case 34:
{ yyval = yyvsp[0]; ;
    break;}
case 35:
{
			/* This rule is written separately so the
			 * reduction will occur before the trailing
			 * series is parsed.
			 */

			if ( trlcontxt )
				synerr( "trailing context used twice" );
			else
				trlcontxt = true;

			if ( varlength )
				/* We hope the trailing context is
				 * fixed-length.
				 */
				varlength = false;
			else
				headcnt = rulelen;

			rulelen = 0;

			current_state_type = STATE_TRAILING_CONTEXT;
			yyval = yyvsp[-1];
			;
    break;}
case 36:
{
			/* This is where concatenation of adjacent patterns
			 * gets done.
			 */
			yyval = link_machines( yyvsp[-1], yyvsp[0] );
			;
    break;}
case 37:
{ yyval = yyvsp[0]; ;
    break;}
case 38:
{
			varlength = true;

			yyval = mkclos( yyvsp[-1] );
			;
    break;}
case 39:
{
			varlength = true;
			yyval = mkposcl( yyvsp[-1] );
			;
    break;}
case 40:
{
			varlength = true;
			yyval = mkopt( yyvsp[-1] );
			;
    break;}
case 41:
{
			varlength = true;

			if ( yyvsp[-3] > yyvsp[-1] || yyvsp[-3] < 0 )
				{
				synerr( "bad iteration values" );
				yyval = yyvsp[-5];
				}
			else
				{
				if ( yyvsp[-3] == 0 )
					{
					if ( yyvsp[-1] <= 0 )
						{
						synerr(
						"bad iteration values" );
						yyval = yyvsp[-5];
						}
					else
						yyval = mkopt(
							mkrep( yyvsp[-5], 1, yyvsp[-1] ) );
					}
				else
					yyval = mkrep( yyvsp[-5], yyvsp[-3], yyvsp[-1] );
				}
			;
    break;}
case 42:
{
			varlength = true;

			if ( yyvsp[-2] <= 0 )
				{
				synerr( "iteration value must be positive" );
				yyval = yyvsp[-4];
				}

			else
				yyval = mkrep( yyvsp[-4], yyvsp[-2], INFINITY );
			;
    break;}
case 43:
{
			/* The singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			if ( yyvsp[-1] <= 0 )
				{
				synerr( "iteration value must be positive" );
				yyval = yyvsp[-3];
				}

			else
				yyval = link_machines( yyvsp[-3],
						copysingl( yyvsp[-3], yyvsp[-1] - 1 ) );
			;
    break;}
case 44:
{
			if ( ! madeany )
				{
				/* Create the '.' character class. */
				anyccl = cclinit();
				ccladd( anyccl, '\n' );
				cclnegate( anyccl );

				if ( useecs )
					mkeccl( ccltbl + cclmap[anyccl],
						ccllen[anyccl], nextecm,
						ecgroup, csize, csize );

				madeany = true;
				}

			++rulelen;

			yyval = mkstate( -anyccl );
			;
    break;}
case 45:
{
			if ( ! cclsorted )
				/* Sort characters for fast searching.  We
				 * use a shell sort since this list could
				 * be large.
				 */
				cshell( ccltbl + cclmap[yyvsp[0]], ccllen[yyvsp[0]], true );

			if ( useecs )
				mkeccl( ccltbl + cclmap[yyvsp[0]], ccllen[yyvsp[0]],
					nextecm, ecgroup, csize, csize );

			++rulelen;

			yyval = mkstate( -yyvsp[0] );
			;
    break;}
case 46:
{
			++rulelen;

			yyval = mkstate( -yyvsp[0] );
			;
    break;}
case 47:
{ yyval = yyvsp[-1]; ;
    break;}
case 48:
{ yyval = yyvsp[-1]; ;
    break;}
case 49:
{
			++rulelen;

			if ( caseins && yyvsp[0] >= 'A' && yyvsp[0] <= 'Z' )
				yyvsp[0] = clower( yyvsp[0] );

			yyval = mkstate( yyvsp[0] );
			;
    break;}
case 50:
{ yyval = yyvsp[-1]; ;
    break;}
case 51:
{
			cclnegate( yyvsp[-1] );
			yyval = yyvsp[-1];
			;
    break;}
case 52:
{
			if ( caseins )
				{
				if ( yyvsp[-2] >= 'A' && yyvsp[-2] <= 'Z' )
					yyvsp[-2] = clower( yyvsp[-2] );
				if ( yyvsp[0] >= 'A' && yyvsp[0] <= 'Z' )
					yyvsp[0] = clower( yyvsp[0] );
				}

			if ( yyvsp[-2] > yyvsp[0] )
				synerr( "negative range in character class" );

			else
				{
				for ( i = yyvsp[-2]; i <= yyvsp[0]; ++i )
					ccladd( yyvsp[-3], i );

				/* Keep track if this ccl is staying in
				 * alphabetical order.
				 */
				cclsorted = cclsorted && (yyvsp[-2] > lastchar);
				lastchar = yyvsp[0];
				}

			yyval = yyvsp[-3];
			;
    break;}
case 53:
{
			if ( caseins && yyvsp[0] >= 'A' && yyvsp[0] <= 'Z' )
				yyvsp[0] = clower( yyvsp[0] );

			ccladd( yyvsp[-1], yyvsp[0] );
			cclsorted = cclsorted && (yyvsp[0] > lastchar);
			lastchar = yyvsp[0];
			yyval = yyvsp[-1];
			;
    break;}
case 54:
{
			cclsorted = true;
			lastchar = 0;
			yyval = cclinit();
			;
    break;}
case 55:
{
			if ( caseins && yyvsp[0] >= 'A' && yyvsp[0] <= 'Z' )
				yyvsp[0] = clower( yyvsp[0] );

			++rulelen;

			yyval = link_machines( yyvsp[-1], mkstate( yyvsp[0] ) );
			;
    break;}
case 56:
{ yyval = mkstate( SYM_EPSILON ); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (err, "state stack now");
      while (ssp1 != yyssp)
	fprintf (err, " %d", *++ssp1);
      fprintf (err, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(err, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (err, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (err, " %d", *++ssp1);
      fprintf (err, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(err, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}



/* build_eof_action - build the "<<EOF>>" action for the active start
 *                    conditions
 */

void build_eof_action()
	{
	register int i;
	char action_text[MAXLINE];

	for ( i = 1; i <= actvp; ++i )
		{
		if ( sceof[actvsc[i]] )
			format_pinpoint_message(
				"multiple <<EOF>> rules for start condition %s",
				scname[actvsc[i]] );

		else
			{
			sceof[actvsc[i]] = true;
			sprintf( action_text, "case YY_STATE_EOF(%s):\n",
			scname[actvsc[i]] );
			add_action( action_text );
			}
		}

	line_directive_out( (FILE *) 0 );

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++num_eof_rules;
	}


/* format_synerr - write out formatted syntax error */

void format_synerr( msg, arg )
char msg[], arg[];
	{
	char errmsg[MAXLINE];

	(void) sprintf( errmsg, msg, arg );
	synerr( errmsg );
	}


/* synerr - report a syntax error */

void synerr( str )
char str[];
	{
	syntaxerror = true;
	pinpoint_message( str );
	}


/* warn - report a warning, unless -w was given */

void warn( str )
char str[];
	{
	line_warning( str, linenum );
	}

/* format_pinpoint_message - write out a message formatted with one string,
 *			     pinpointing its location
 */

void format_pinpoint_message( msg, arg )
char msg[], arg[];
	{
	char errmsg[MAXLINE];

	(void) sprintf( errmsg, msg, arg );
	pinpoint_message( errmsg );
	}


/* pinpoint_message - write out a message, pinpointing its location */

void pinpoint_message( str )
char str[];
	{
	line_pinpoint( str, linenum );
	}


/* line_warning - report a warning at a given line, unless -w was given */

void line_warning( str, line )
char str[];
int line;
	{
	char warning[MAXLINE];

	if ( ! nowarn )
		{
		sprintf( warning, "warning, %s", str );
		line_pinpoint( warning, line );
		}
	}


/* line_pinpoint - write out a message, pinpointing it at the given line */

void line_pinpoint( str, line )
char str[];
int line;
	{
	fprintf( err, "\"%s\", line %d: %s\n", infilename, line, str );
	}


/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignore
 */

void yyerror( msg )
char msg[];
	{
	}
/* A lexical scanner generated by flex */

/* Scanner skeleton version:
 * $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $
 */

#define FLEX_SCANNER

#include <stdio.h>


/* cfront 1.2 defines "c_plusplus" instead of "__cplusplus" */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif


#ifdef __cplusplus

#include <stdlib.h>
#include <unistd.h>

/* Use prototypes in function declarations. */
#define YY_USE_PROTOS

/* The "const" storage-class-modifier is valid. */
#define YY_USE_CONST

#else	/* ! __cplusplus */

#ifdef __STDC__

#define YY_USE_PROTOS
#define YY_USE_CONST

#endif	/* __STDC__ */
#endif	/* ! __cplusplus */


#ifdef __TURBOC__
#define YY_USE_CONST
#endif


#ifndef YY_USE_CONST
#ifndef const
#define const
#endif
#endif


#ifdef YY_USE_PROTOS
#define YY_PROTO(proto) proto
#else
#define YY_PROTO(proto) ()
#endif

/* Returned upon end-of-file. */
#define YY_NULL 0

/* Enter a start condition.  This macro really ought to take a parameter,
 * but we do it the disgusting crufty way forced on us by the ()-less
 * definition of BEGIN.
 */
#define BEGIN yy_start = 1 + 2 *

/* Translate the current start state into a value that can be later handed
 * to BEGIN to return to the state.
 */
#define YY_START ((yy_start - 1) / 2)

/* Action number for EOF rule of a given start state. */
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)

/* Special action meaning "start processing a new file".  Now included
 * only for backward compatibility with previous versions of flex.
 */
#define YY_NEW_FILE yyrestart( yyin )

#define YY_END_OF_BUFFER_CHAR 0

/* Size of default input buffer. */
#define YY_BUF_SIZE 16384

typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern int yyleng;
extern FILE *yyin, *yyout;

#ifdef __cplusplus
extern "C" {
#endif
	extern void *yy_flex_alloc YY_PROTO(( int ));
	extern void *yy_flex_realloc YY_PROTO(( void *ptr, int size ));
	extern void yy_flex_free YY_PROTO(( void * ));
	extern int yywrap YY_PROTO(( void ));
	extern void yy_strcpy YY_PROTO(( char *s1, const char *s2 ));
#ifdef __cplusplus
	}
#endif

#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

/* The funky do-while in the following #define is used to turn the definition
 * int a single C statement (which needs a semi-colon terminator).  This
 * avoids problems with code like:
 *
 * 	if ( condition_holds )
 *		yyless( 5 );
 *	else
 *		do_something_else();
 *
 * Prior to using the do-while the compiler would get upset at the
 * "else" because it interpreted the "if" statement as being all
 * done when it reached the ';' after the yyless() call.
 */

/* Return all but the first 'n' matched characters back to the input stream. */

#define yyless(n) \
	do \
		{ \
		/* Undo effects of setting up yytext. */ \
		*yy_cp = yy_hold_char; \
		yy_c_buf_p = yy_cp = yy_bp + n - YY_MORE_ADJ; \
		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
		} \
	while ( 0 )

#define unput(c) yyunput( c, yytext_ptr )


struct yy_buffer_state
	{
	FILE *yy_input_file;

	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	 * characters.
	 */
	int yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	 * characters.
	 */
	int yy_n_chars;

	/* Whether this is an "interactive" input source; if so, and
	 * if we're using stdio for input, then we want to use getc()
	 * instead of fread(), to make sure we stop fetching input after
	 * each newline.
	 */
	int is_interactive;

	/* Whether we've seen an EOF on this buffer. */
	int yy_eof_status;
#define EOF_NOT_SEEN 0
	/* "Pending" happens when the EOF has been seen but there's still
	 * some text to process.  Note that when we actually see the EOF,
	 * we switch the status back to "not seen" (via yyrestart()), so
	 * that the user can continue scanning by just pointing yyin at
	 * a new input file.
	 */
#define EOF_PENDING 1
	};

static YY_BUFFER_STATE yy_current_buffer = 0;

/* We provide macros for accessing buffer states in case in the
 * future we want to put the buffer states in a more general
 * "scanner state".
 */
#define YY_CURRENT_BUFFER yy_current_buffer


/* yy_hold_char holds the character lost when yytext is formed. */
static char yy_hold_char;

static int yy_n_chars;		/* number of characters read into yy_ch_buf */


int yyleng;

/* Points to current character in buffer. */
static char *yy_c_buf_p = (char *) 0;
static int yy_init = 1;		/* whether we need to initialize */
static int yy_start = 0;	/* start state number */

/* Flag which is used to allow yywrap()'s to do buffer switches
 * instead of setting up a fresh yyin.  A bit of a hack ...
 */
static int yy_did_buffer_switch_on_eof;

static void yyunput YY_PROTO(( int c, char *buf_ptr ));
void yyrestart YY_PROTO(( FILE *input_file ));
void yy_switch_to_buffer YY_PROTO(( YY_BUFFER_STATE new_buffer ));
void yy_load_buffer_state YY_PROTO(( void ));
YY_BUFFER_STATE yy_create_buffer YY_PROTO(( FILE *file, int size ));
void yy_delete_buffer YY_PROTO(( YY_BUFFER_STATE b ));
void yy_init_buffer YY_PROTO(( YY_BUFFER_STATE b, FILE *file ));

#define yy_new_buffer yy_create_buffer

#define INITIAL 0
#define SECT2 1
#define SECT2PROLOG 2
#define SECT3 3
#define CODEBLOCK 4
#define PICKUPDEF 5
#define SC 6
#define CARETISBOL 7
#define NUM 8
#define QUOTE 9
#define FIRSTCCL 10
#define CCL 11
#define ACTION 12
#define RECOVER 13
#define BRACEERROR 14
#define C_COMMENT 15
#define ACTION_COMMENT 16
#define ACTION_STRING 17
#define PERCENT_BRACE_ACTION 18
#define USED_LIST 19
#define CODEBLOCK_2 20
typedef unsigned char YY_CHAR;
typedef int yy_state_type;
FILE *yyin = (FILE *) 0, *yyout = (FILE *) 0;
extern char *yytext;
#define yytext_ptr yytext

#ifdef __cplusplus
static int yyinput YY_PROTO(( void ));
#else
static int input YY_PROTO(( void ));
#endif

static yy_state_type yy_get_previous_state YY_PROTO(( void ));
static yy_state_type yy_try_NUL_trans YY_PROTO(( yy_state_type current_state ));
static int yy_get_next_buffer YY_PROTO(( void ));
static void yy_fatal_error YY_PROTO(( const char msg[] ));

/* Done after the current pattern has been matched and before the
 * corresponding action - sets up yytext.
 */
#define YY_DO_BEFORE_ACTION \
	yytext_ptr = yy_bp; \
	yyleng = yy_cp - yy_bp; \
	yy_hold_char = *yy_cp; \
	*yy_cp = '\0'; \
	yy_c_buf_p = yy_cp;

#define YY_END_OF_BUFFER 113
static const short int yy_accept[408] =
    {   0,
        0,    0,    0,    0,   41,   41,  110,  110,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,  113,  111,    6,   17,  111,   15,    1,   16,
      111,  111,  111,   14,   60,   53,   54,   60,   47,   60,
       59,   60,   60,   60,   60,   44,   43,   60,   60,   45,
       46,   41,   42,   41,   40,   39,   40,   40,  110,  110,
       26,   27,   26,   26,   26,   26,   26,   26,   29,   28,
       30,   29,   65,   61,   62,   64,   66,   80,   81,   80,

       78,   77,   79,   67,   69,   67,   68,   67,   72,   72,
       72,   74,   76,   74,   74,   74,   75,   92,   97,   92,
       96,   98,   98,   93,   93,   93,   90,   91,  111,   31,
      111,   83,  111,   82,   20,   22,   20,   21,  101,  102,
      101,  100,  103,  105,  103,  106,  107,   88,   88,   89,
       88,   88,   88,   88,   88,   88,   36,   33,   32,   36,
       36,   36,   88,    6,   17,    0,   17,   15,    1,   16,
        0,   16,   13,    7,    0,    0,    0,    3,    0,    4,
        0,    2,   14,   53,   54,    0,    0,    0,   54,   50,
       50,    0,    0,   57,    0,  108,  108,  108,   49,   48,

       49,   44,   43,    0,   43,   56,   44,   41,   42,   40,
       39,   39,   37,   38,  110,  110,   26,   27,   26,   26,
       26,   26,   29,   28,   30,   63,   64,   81,   77,   69,
      109,  109,  109,   70,   71,   76,   73,   92,   97,    0,
       95,    0,   94,   93,   93,   93,    0,   31,    0,   31,
       31,   83,   20,   22,   18,  101,  102,  101,  102,  102,
       99,  103,  105,  104,   88,   88,   88,   89,   85,   88,
       88,   88,   36,   33,   32,   36,   36,   84,   13,    7,
        0,   12,    0,    0,    0,    0,    3,    0,    0,    4,
        0,    5,    0,   51,    0,   52,    0,    0,   57,    0,

       57,   57,  108,  108,   49,   49,   58,   56,   37,   38,
       26,   26,   26,   23,   26,    0,  109,  109,   93,   93,
        0,   19,    0,   85,   85,   88,   88,   36,   36,   12,
        0,    0,    0,    3,    0,    0,    4,    5,    5,   52,
       52,    0,   57,   57,   57,   57,  108,   26,   26,   23,
       23,    0,  109,   93,   93,   19,   19,   88,   88,   36,
       36,    0,    0,    0,   10,    0,   57,   57,   57,   57,
       26,   26,   93,   93,   88,   88,   36,   36,    0,    0,
        0,    0,   57,   57,   24,   25,   86,   87,   86,   87,
       34,   35,    0,    9,    0,    0,   11,   55,    9,    9,

        0,    0,    8,    0,    8,    8,    0
    } ;

static const YY_CHAR yy_ec[256] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
        1,    1,    4,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    2,    1,    5,    1,    6,    7,    1,    8,    9,
        9,   10,    9,   11,   12,    9,   13,   14,   14,   14,
       14,   14,   14,   14,   14,   14,   14,    1,    1,   15,
        1,   16,    9,    1,   22,   23,   24,   25,   26,   27,
       21,   21,   28,   29,   30,   21,   31,   32,   33,   34,
       21,   35,   36,   37,   38,   21,   21,   39,   40,   21,
       17,   18,   19,   20,   21,    1,   22,   23,   24,   25,

       26,   27,   21,   21,   28,   29,   30,   21,   31,   32,
       33,   34,   21,   35,   36,   37,   38,   21,   21,   39,
       40,   21,   41,   42,   43,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,

        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1
    } ;

static const YY_CHAR yy_meta[44] =
    {   0,
        1,    2,    3,    1,    4,    1,    1,    5,    1,    6,
        1,    7,    5,    8,    1,    1,    1,    9,   10,    1,
       11,   12,   12,   12,   12,   12,   12,   11,   11,   11,
       11,   11,   11,   11,   11,   11,   13,   11,   11,   11,
        5,    1,   14
    } ;

static const short int yy_base[470] =
    {   0,
        0,   43,   85,  126,   89,  102, 1611, 1610,  168, 1605,
      108,  111,  211,    0, 1591, 1590,  252,  254,  116,  119,
       98,  122,  144,  146,  297,    0,   93,  104,  338,  340,
      149,  151,  257,  266,  268,  274,  383,    0,  425,  428,
     1596, 1595, 1607, 1615,  278, 1602, 1602,    0,  281, 1600,
     1600,  462, 1592,    0, 1615,  431, 1597, 1597, 1615,  285,
     1615, 1584, 1580,  331,  503,  437, 1593, 1593,  110, 1580,
     1615,    0, 1590, 1590,    0, 1590, 1588,  221, 1587, 1615,
        0, 1585, 1585, 1615,    0, 1561, 1546, 1511,    0, 1551,
     1543, 1543, 1615, 1615, 1498,    0, 1615, 1615, 1500, 1487,

     1615, 1463, 1615, 1615, 1466, 1460, 1615,  332, 1615,  333,
      126, 1615, 1411, 1398,    0,  334, 1615,    0, 1383, 1383,
     1615,  341, 1371,    0, 1354, 1336, 1615, 1615,  271, 1371,
      287, 1370, 1366, 1615,    0, 1362, 1349, 1331,  290, 1335,
      347, 1325,    0, 1323, 1310, 1615,    0,    0,  350, 1306,
     1287, 1246, 1615,    0, 1249, 1227,    0, 1264, 1261, 1255,
     1225, 1197, 1213,  351, 1213, 1213, 1615,    0,  358, 1198,
     1193, 1615,    0,    0,  443,  361,  447,    0,  342,    0,
      363, 1615,    0,  451, 1191, 1188, 1149,  365, 1615, 1615,
     1185, 1181, 1155, 1135,  423, 1615, 1125,    0,    0, 1615,

      546,  588, 1121, 1108, 1615,    0, 1615,    0, 1615,    0,
        0, 1095,    0,    0, 1088, 1615,    0, 1615,    0, 1061,
     1041,  630,    0, 1069, 1615, 1615,    0, 1615,  838, 1615,
     1615,  837,    0, 1615, 1615, 1615, 1615,    0, 1615,  434,
     1615,    0, 1615,    0,  821,  817,  373,  843,  376, 1615,
      842, 1615,    0, 1615,  463,  467,  834,  471, 1615,  833,
     1615,    0, 1615, 1615,    0,  441,  793, 1615,  673,    0,
      805,  802,    0,  830, 1615,  795,  792, 1615,    0,    0,
      594,  818,  817,  597,  784,  790,    0,  775,  786,    0,
      473,  807,  478, 1615,  486,  806,  590,  776,  790,  588,

      469,  703,  793,    0,    0,    0, 1615,    0,    0,    0,
      780,  772,    0,  800,  800,  730,  788,    0,  775,  767,
      600,  795,  602,    0,  773,  772,  764,  770,  762, 1615,
      610,  772,  751,    0,  740,  745,    0, 1615,  765, 1615,
      764,  740,  488,  803,  601,  817, 1615,  742,  730, 1615,
      760,  760, 1615,  738,  726, 1615,  756,  735,  723,  733,
      721,  714,  716,  726, 1615,  724,  602,  831,  715,  658,
      512,  473,  454,  459,  435,  438,  422,  430,  606,  410,
      357,  342,  338,  278,    0,    0,    0,    0,    0,    0,
        0,    0,  614,  255,  618,  131, 1615, 1615, 1615,  156,

      620,  622,  153,  625, 1615,   95, 1615,  858,  872,  886,
      900,  914,  928,  942,  956,  970,  984,  998, 1012, 1026,
     1040, 1054, 1062, 1075, 1081, 1094, 1108, 1122, 1136, 1150,
     1164, 1178, 1186, 1199, 1207, 1220, 1234, 1248, 1262, 1272,
     1280, 1293, 1307, 1321, 1335, 1349, 1363, 1371, 1384, 1398,
     1412, 1416, 1419, 1432, 1446, 1460,  710, 1474, 1487, 1501,
     1515,  711, 1529, 1537, 1544,  712,  743, 1557, 1571
    } ;

static const short int yy_def[470] =
    {   0,
      407,  407,  408,  408,  409,  410,  411,  411,  407,    9,
      412,  412,  407,   13,  413,  413,  414,  414,  415,  415,
      416,  416,  417,  417,  407,   25,  418,  418,  413,  413,
      419,  419,  420,  420,  421,  421,  407,   37,  422,  422,
       37,   37,  407,  407,  407,  407,  407,  423,  407,  407,
      407,  424,  407,  425,  407,  407,  407,  407,  407,  407,
      407,  407,  426,  427,  407,  407,  407,  407,  407,  407,
      407,  428,  407,  428,  429,  430,  429,  429,  431,  407,
      432,  407,  432,  407,  433,  433,  433,  432,  434,  407,
      407,  434,  407,  407,  407,  435,  407,  407,  407,  407,

      407,  407,  407,  407,  407,  407,  407,  427,  407,  436,
      437,  407,  407,  407,  438,  427,  407,  439,  407,  439,
      407,  440,  407,  441,  441,  441,  407,  407,  442,  407,
      442,  407,  407,  407,  443,  407,  443,  407,  444,  407,
      444,  407,  445,  407,  445,  407,  446,  447,  447,  407,
      447,  447,  407,  448,  448,  448,  449,  407,  407,  449,
      449,  449,  447,  407,  407,  407,  407,  423,  407,  407,
      407,  407,  450,  451,  407,  407,  407,  452,  407,  453,
      454,  407,  425,  407,  407,  407,  407,  455,  407,  407,
      407,  407,  407,  456,  426,  407,  407,  457,  458,  407,

      407,  407,  407,  407,  407,  459,  407,  428,  407,  429,
      430,  430,  460,  461,  431,  407,  432,  407,  433,  433,
      433,  407,  434,  407,  407,  407,  435,  407,  407,  407,
      407,  407,  462,  407,  407,  407,  407,  439,  407,  440,
      407,  440,  407,  441,  441,  441,  442,  407,  442,  407,
      407,  407,  443,  407,  463,  444,  407,  444,  407,  407,
      407,  445,  407,  407,  447,  447,  447,  407,  407,  448,
      448,  448,  449,  407,  407,  449,  449,  407,  450,  451,
      407,  407,  407,  407,  407,  407,  464,  407,  407,  465,
      454,  407,  454,  407,  455,  407,  455,  407,  456,  456,

      456,  456,  407,  466,  458,  201,  407,  459,  460,  461,
      433,  433,  222,  407,  222,  222,  407,  467,  441,  441,
      463,  407,  463,  269,  269,  448,  448,  449,  449,  407,
      407,  407,  407,  464,  407,  407,  465,  407,  407,  407,
      407,  407,  456,  456,  456,  456,  407,  433,  433,  407,
      407,  316,  407,  441,  441,  407,  407,  448,  448,  449,
      449,  407,  407,  407,  407,  407,  456,  456,  456,  456,
      433,  433,  441,  441,  448,  448,  449,  449,  468,  407,
      407,  407,  456,  456,  433,  433,  441,  441,  448,  448,
      449,  449,  468,  407,  468,  407,  407,  407,  407,  407,

      469,  469,  407,  469,  407,  407,    0,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407
    } ;

static const short int yy_nxt[1659] =
    {   0,
       44,   45,   46,   47,   44,   44,   44,   44,   44,   44,
       44,   44,   44,   44,   44,   44,   44,   44,   44,   44,
       48,   48,   48,   48,   48,   48,   48,   48,   48,   48,
       48,   48,   48,   48,   48,   48,   48,   48,   48,   48,
       44,   44,   44,   44,   49,   50,   51,   44,   44,   52,
       44,   44,   44,   44,   44,   53,   44,   44,   44,   44,
       44,   44,   44,   54,   54,   54,   54,   54,   54,   54,
       54,   54,   54,   54,   54,   54,   54,   54,   54,   54,
       54,   54,   54,   44,   44,   44,   56,   57,   58,   59,
       60,   73,   74,   61,   61,  130,  131,   61,  405,   62,

       44,   63,   64,   76,   73,   77,  130,  131,   78,   90,
       91,   92,   90,   91,   92,  110,  206,  111,  105,  106,
      107,  105,  106,  107,   44,   65,   61,   66,   67,   68,
       59,   60,   69,  108,   61,   61,  108,  235,   61,  110,
       70,  111,   63,   64,  235,   71,  113,  114,  113,  114,
      207,  136,  137,  136,  137,  115,  405,  115,  138,  399,
      138,  116,  117,  116,  117,  401,   65,   61,   81,   81,
       82,   83,   81,   81,   81,   81,   81,   84,   81,   81,
       81,   81,   81,   81,   81,   81,   81,   81,   85,   85,
       85,   85,   85,   85,   85,   85,   85,   85,   85,   85,

       85,   85,   86,   85,   85,   85,   85,   87,   81,   81,
       81,   93,   93,   44,   93,   93,   93,   93,   93,   93,
       94,   94,   93,   93,   93,   93,   95,   93,   93,   93,
       93,   96,   96,   96,   96,   96,   96,   96,   96,   96,
       96,   96,   96,   96,   96,   96,   96,   96,   96,   96,
       96,   93,   93,   93,   99,  100,   99,  100,  399,  140,
      141,  213,  101,  214,  101,  102,  142,  102,  140,  141,
      144,  145,  146,  248,  249,  142,  144,  145,  146,  164,
      165,  166,  169,  170,  171,  147,  190,  191,  192,  251,
      249,  147,  257,  258,  103,  300,  103,  118,  118,  119,

      120,  121,  118,  118,  122,  118,  118,  118,  118,  123,
      118,  118,  118,  118,  118,  118,  118,  124,  124,  124,
      124,  124,  124,  124,  124,  124,  124,  124,  124,  124,
      124,  125,  124,  124,  124,  124,  126,  127,  118,  128,
      132,  133,  132,  133,  197,  197,  232,  197,  241,  260,
      258,  266,  164,  165,  166,  300,  267,  398,  242,  169,
      170,  171,  281,  282,  283,  292,  293,  296,  297,  198,
      198,  233,  198,  288,  284,  248,  249,  289,  251,  249,
      134,  397,  134,  148,  149,  150,  151,  148,  148,  152,
      148,  148,  153,  148,  148,  148,  148,  148,  148,  148,

      148,  148,  148,  154,  154,  154,  154,  154,  154,  154,
      154,  154,  154,  154,  154,  154,  154,  155,  154,  154,
      154,  154,  156,  148,  148,  148,  158,  159,  160,  158,
      159,  160,  184,  185,  186,  396,  301,  187,  202,  203,
      204,  241,  266,  187,  281,  282,  283,  267,  281,  282,
      283,  242,  184,  185,  186,  392,  284,  187,  391,  161,
      284,  302,  161,  390,  162,  322,  323,  162,  174,  257,
      258,  389,  188,  260,  258,  292,  293,  285,  188,  286,
      339,  293,  345,  175,  388,  176,  300,  176,  296,  297,
      387,  176,  188,  176,  176,  177,  176,  178,  386,  179,

      180,  367,  181,  199,  199,  300,  199,  199,  199,  199,
      199,  199,  199,  199,  199,  199,  200,  199,  199,  199,
      199,  199,  199,  201,  201,  201,  201,  201,  201,  201,
      201,  201,  201,  201,  201,  201,  201,  201,  201,  201,
      201,  201,  201,  199,  199,  199,  305,  305,  385,  305,
      305,  305,  305,  305,  305,  305,  305,  306,  305,  306,
      305,  305,  305,  305,  305,  305,  306,  306,  306,  306,
      306,  306,  306,  306,  306,  306,  306,  306,  306,  306,
      306,  306,  306,  306,  306,  306,  305,  305,  307,  202,
      203,  204,  341,  297,  187,  281,  282,  283,  331,  282,

      283,  343,  322,  323,  357,  323,  299,  284,  394,  395,
      284,  331,  282,  283,  369,  383,  394,  395,  300,  300,
      400,  395,  403,  404,  403,  404,  344,  406,  404,  188,
      313,  313,  314,  315,  313,  313,  313,  313,  313,  316,
      313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
      316,  316,  316,  316,  316,  316,  316,  316,  316,  316,
      316,  316,  316,  316,  316,  316,  316,  316,  316,  316,
      313,  313,  313,  324,  324,  300,  324,  324,  324,  324,
      324,  324,  325,  324,  324,  324,  324,  324,  324,  324,
      324,  324,  324,  325,  325,  325,  325,  325,  325,  325,

      325,  325,  325,  325,  325,  325,  325,  325,  325,  325,
      325,  325,  325,  324,  324,  324,  346,  304,  318,  347,
      300,  304,  318,  347,  346,  346,  346,  346,  346,  346,
      316,  316,  300,  352,  316,  316,  316,  316,  316,  382,
      316,  316,  316,  316,  316,  316,  316,  316,  316,  316,
      353,  381,  380,  379,  353,  378,  377,  376,  375,  356,
      374,  373,  351,  350,  372,  371,  366,  340,  338,  365,
      316,  316,  316,  325,  325,  364,  325,  325,  325,  325,
      325,  325,  363,  325,  325,  325,  325,  325,  325,  325,
      325,  325,  325,  362,  361,  360,  359,  358,  356,  355,

      354,  231,  351,  350,  349,  348,  196,  300,  342,  340,
      338,  336,  335,  325,  325,  325,  368,  333,  332,  330,
      300,  330,  329,  328,  368,  368,  368,  368,  368,  368,
      370,  274,  327,  326,  300,  269,  259,  259,  370,  370,
      370,  370,  370,  370,  384,  250,  250,  320,  300,  319,
      317,  229,  384,  384,  384,  384,  384,  384,   55,   55,
       55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
       55,   55,   72,   72,   72,   72,   72,   72,   72,   72,
       72,   72,   72,   72,   72,   72,   75,   75,   75,   75,
       75,   75,   75,   75,   75,   75,   75,   75,   75,   75,

       79,   79,   79,   79,   79,   79,   79,   79,   79,   79,
       79,   79,   79,   79,   89,   89,   89,   89,   89,   89,
       89,   89,   89,   89,   89,   89,   89,   89,   44,   44,
       44,   44,   44,   44,   44,   44,   44,   44,   44,   44,
       44,   44,   98,   98,   98,   98,   98,   98,   98,   98,
       98,   98,   98,   98,   98,   98,  104,  104,  104,  104,
      104,  104,  104,  104,  104,  104,  104,  104,  104,  104,
      109,  109,  109,  109,  109,  109,  109,  109,  109,  109,
      109,  109,  109,  109,  112,  112,  112,  112,  112,  112,
      112,  112,  112,  112,  112,  112,  112,  112,  129,  129,

      129,  129,  129,  129,  129,  129,  129,  129,  129,  129,
      129,  129,  135,  135,  135,  135,  135,  135,  135,  135,
      135,  135,  135,  135,  135,  135,  139,  139,  139,  139,
      139,  139,  139,  139,  139,  139,  139,  139,  139,  139,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  157,  157,  157,  157,  157,  157,
      157,  157,  157,  157,  157,  157,  157,  157,  168,  168,
      224,  312,  168,  168,  168,  173,  173,  173,  173,  173,
      173,  173,  173,  173,  173,  173,  173,  183,  183,  311,
      216,  183,  183,  183,  194,  194,  212,  194,  194,  194,

      194,  194,  194,  194,  194,  194,  194,  194,  196,  196,
      205,  196,  196,  196,  196,  196,  196,  196,  196,  196,
      196,  196,  208,  208,  205,  208,  208,  208,  208,  208,
      208,  208,  208,  208,  208,  208,  210,  210,  303,  210,
      210,  210,  210,  210,  210,  210,  210,  210,  210,  210,
      211,  211,  300,  211,  211,  211,  211,  211,  211,  211,
      211,  211,  211,  211,  215,  215,  215,  215,  215,  215,
      215,  215,  215,  215,  215,  215,  215,  215,  217,  217,
      298,  217,  217,  190,  217,  217,  217,  217,  190,  294,
      189,  217,  219,  219,  189,  172,  219,  219,  219,  223,

      223,  172,  223,  223,  223,  223,  223,  223,  223,  223,
      223,  223,  223,  227,  227,  167,  167,  227,  227,  227,
      231,  231,  278,  231,  231,  231,  231,  231,  231,  231,
      231,  231,  231,  231,  234,  234,  277,  234,  234,  234,
      234,  234,  234,  234,  234,  234,  234,  234,  237,  237,
      276,  237,  237,  237,  237,  237,  237,  275,  237,  237,
      237,  237,  238,  238,  275,  274,  272,  238,  238,  238,
      238,  238,  240,  240,  271,  240,  240,  240,  240,  240,
      240,  240,  240,  240,  240,  240,  244,  244,  269,  268,
      244,  244,  244,  247,  247,  247,  247,  247,  247,  247,

      247,  247,  247,  247,  247,  247,  247,  253,  253,  268,
      253,  253,  263,  253,  253,  253,  253,  253,  253,  253,
      253,  256,  256,  256,  256,  256,  263,  256,  256,  256,
      256,  256,  256,  256,  256,  262,  262,  261,  259,  262,
      262,  262,  262,  255,  262,  262,  262,  262,  262,  264,
      264,  254,  264,  264,  264,  264,  264,  264,  264,  264,
      264,  264,  264,  265,  265,  254,  265,  265,  252,  265,
      265,  265,  265,  252,  250,  246,  265,  270,  270,  245,
      243,  270,  270,  270,  273,  239,  239,  273,  273,  273,
      273,  273,  273,  273,  273,  273,  273,  273,  279,  279,

      236,  279,  279,  279,  279,  279,  279,  279,  279,  279,
      279,  279,  280,  280,  236,  280,  280,  280,  280,  280,
      280,  280,  280,  280,  280,  280,  287,  287,  287,  290,
      290,  290,  291,  291,  291,  291,  291,  291,  291,  291,
      291,  291,  291,  291,  291,  291,  295,  295,  295,  295,
      295,  295,  295,  295,  295,  295,  295,  295,  295,  295,
      299,  299,  230,  299,  299,  299,  299,  299,  299,  230,
      299,  299,  299,  299,  305,  305,  229,  305,  305,  305,
      305,  305,  305,  305,  305,  305,  305,  308,  308,  228,
      308,  308,  308,  308,  308,  308,  308,  308,  308,  308,

      308,  309,  309,  228,  309,  309,  309,  309,  309,  309,
      309,  309,  309,  309,  309,  310,  310,  226,  310,  310,
      310,  310,  310,  310,  310,  310,  310,  310,  310,  321,
      321,  321,  321,  321,  321,  321,  321,  321,  321,  321,
      321,  321,  321,  334,  334,  225,  225,  334,  334,  334,
      337,  337,  224,  222,  337,  337,  337,  393,  393,  393,
      393,  393,  393,  393,  393,  393,  393,  393,  393,  393,
      393,  402,  402,  402,  402,  402,  402,  402,  402,  402,
      402,  402,  402,  402,  402,  221,  220,  218,  218,  216,
      209,  212,  209,  209,  193,  205,  205,  195,  193,  189,

      189,  182,  172,  172,  167,  167,  407,  163,  163,   97,
       97,   88,   80,   80,   43,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407
    } ;

static const short int yy_chk[1659] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    2,    2,    2,    2,    2,    2,    2,
        2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
        2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
        2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
        2,    2,    2,    2,    2,    2,    3,    3,    3,    3,
        3,    5,    5,    3,    3,   27,   27,    3,  406,    3,

       21,    3,    3,    6,    6,    6,   28,   28,    6,   11,
       11,   11,   12,   12,   12,   21,   69,   21,   19,   19,
       19,   20,   20,   20,   22,    3,    3,    4,    4,    4,
        4,    4,    4,   19,    4,    4,   20,  111,    4,   22,
        4,   22,    4,    4,  111,    4,   23,   23,   24,   24,
       69,   31,   31,   32,   32,   23,  403,   24,   31,  400,
       32,   23,   23,   24,   24,  396,    4,    4,    9,    9,
        9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
        9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
        9,    9,    9,    9,    9,    9,    9,    9,    9,    9,

        9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
        9,   13,   13,   13,   13,   13,   13,   13,   13,   13,
       13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
       13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
       13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
       13,   13,   13,   13,   17,   17,   18,   18,  394,   33,
       33,   78,   17,   78,   18,   17,   33,   18,   34,   34,
       35,   35,   35,  129,  129,   34,   36,   36,   36,   45,
       45,   45,   49,   49,   49,   35,   60,   60,   60,  131,
      131,   36,  139,  139,   17,  384,   18,   25,   25,   25,

       25,   25,   25,   25,   25,   25,   25,   25,   25,   25,
       25,   25,   25,   25,   25,   25,   25,   25,   25,   25,
       25,   25,   25,   25,   25,   25,   25,   25,   25,   25,
       25,   25,   25,   25,   25,   25,   25,   25,   25,   25,
       29,   29,   30,   30,   64,  108,  110,  116,  122,  141,
      141,  149,  164,  164,  164,  383,  149,  382,  122,  169,
      169,  169,  176,  176,  176,  181,  181,  188,  188,   64,
      108,  110,  116,  179,  176,  247,  247,  179,  249,  249,
       29,  381,   30,   37,   37,   37,   37,   37,   37,   37,
       37,   37,   37,   37,   37,   37,   37,   37,   37,   37,

       37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
       37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
       37,   37,   37,   37,   37,   37,   39,   39,   39,   40,
       40,   40,   56,   56,   56,  380,  195,   56,   66,   66,
       66,  240,  266,   66,  175,  175,  175,  266,  177,  177,
      177,  240,  184,  184,  184,  378,  175,  184,  377,   39,
      177,  195,   40,  376,   39,  255,  255,   40,   52,  256,
      256,  375,   56,  258,  258,  291,  291,  175,   66,  177,
      293,  293,  301,   52,  374,   52,  301,   52,  295,  295,
      373,   52,  184,   52,   52,   52,   52,   52,  372,   52,

       52,  343,   52,   65,   65,  343,   65,   65,   65,   65,
       65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
       65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
       65,   65,   65,   65,   65,   65,   65,   65,   65,   65,
       65,   65,   65,   65,   65,   65,  201,  201,  371,  201,
      201,  201,  201,  201,  201,  201,  201,  201,  201,  201,
      201,  201,  201,  201,  201,  201,  201,  201,  201,  201,
      201,  201,  201,  201,  201,  201,  201,  201,  201,  201,
      201,  201,  201,  201,  201,  201,  201,  201,  201,  202,
      202,  202,  297,  297,  202,  281,  281,  281,  284,  284,

      284,  300,  321,  321,  323,  323,  300,  281,  379,  379,
      284,  331,  331,  331,  345,  367,  393,  393,  345,  367,
      395,  395,  401,  401,  402,  402,  300,  404,  404,  202,
      222,  222,  222,  222,  222,  222,  222,  222,  222,  222,
      222,  222,  222,  222,  222,  222,  222,  222,  222,  222,
      222,  222,  222,  222,  222,  222,  222,  222,  222,  222,
      222,  222,  222,  222,  222,  222,  222,  222,  222,  222,
      222,  222,  222,  269,  269,  370,  269,  269,  269,  269,
      269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
      269,  269,  269,  269,  269,  269,  269,  269,  269,  269,

      269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
      269,  269,  269,  269,  269,  269,  302,  457,  462,  466,
      302,  457,  462,  466,  302,  302,  302,  302,  302,  302,
      316,  316,  369,  316,  316,  316,  316,  316,  316,  366,
      316,  316,  316,  316,  316,  316,  316,  316,  316,  316,
      467,  364,  363,  362,  467,  361,  360,  359,  358,  357,
      355,  354,  352,  351,  349,  348,  342,  341,  339,  336,
      316,  316,  316,  325,  325,  335,  325,  325,  325,  325,
      325,  325,  333,  325,  325,  325,  325,  325,  325,  325,
      325,  325,  325,  332,  329,  328,  327,  326,  322,  320,

      319,  317,  315,  314,  312,  311,  303,  299,  298,  296,
      292,  289,  288,  325,  325,  325,  344,  286,  285,  283,
      344,  282,  277,  276,  344,  344,  344,  344,  344,  344,
      346,  274,  272,  271,  346,  267,  260,  257,  346,  346,
      346,  346,  346,  346,  368,  251,  248,  246,  368,  245,
      232,  229,  368,  368,  368,  368,  368,  368,  408,  408,
      408,  408,  408,  408,  408,  408,  408,  408,  408,  408,
      408,  408,  409,  409,  409,  409,  409,  409,  409,  409,
      409,  409,  409,  409,  409,  409,  410,  410,  410,  410,
      410,  410,  410,  410,  410,  410,  410,  410,  410,  410,

      411,  411,  411,  411,  411,  411,  411,  411,  411,  411,
      411,  411,  411,  411,  412,  412,  412,  412,  412,  412,
      412,  412,  412,  412,  412,  412,  412,  412,  413,  413,
      413,  413,  413,  413,  413,  413,  413,  413,  413,  413,
      413,  413,  414,  414,  414,  414,  414,  414,  414,  414,
      414,  414,  414,  414,  414,  414,  415,  415,  415,  415,
      415,  415,  415,  415,  415,  415,  415,  415,  415,  415,
      416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
      416,  416,  416,  416,  417,  417,  417,  417,  417,  417,
      417,  417,  417,  417,  417,  417,  417,  417,  418,  418,

      418,  418,  418,  418,  418,  418,  418,  418,  418,  418,
      418,  418,  419,  419,  419,  419,  419,  419,  419,  419,
      419,  419,  419,  419,  419,  419,  420,  420,  420,  420,
      420,  420,  420,  420,  420,  420,  420,  420,  420,  420,
      421,  421,  421,  421,  421,  421,  421,  421,  421,  421,
      421,  421,  421,  421,  422,  422,  422,  422,  422,  422,
      422,  422,  422,  422,  422,  422,  422,  422,  423,  423,
      224,  221,  423,  423,  423,  424,  424,  424,  424,  424,
      424,  424,  424,  424,  424,  424,  424,  425,  425,  220,
      215,  425,  425,  425,  426,  426,  212,  426,  426,  426,

      426,  426,  426,  426,  426,  426,  426,  426,  427,  427,
      204,  427,  427,  427,  427,  427,  427,  427,  427,  427,
      427,  427,  428,  428,  203,  428,  428,  428,  428,  428,
      428,  428,  428,  428,  428,  428,  429,  429,  197,  429,
      429,  429,  429,  429,  429,  429,  429,  429,  429,  429,
      430,  430,  194,  430,  430,  430,  430,  430,  430,  430,
      430,  430,  430,  430,  431,  431,  431,  431,  431,  431,
      431,  431,  431,  431,  431,  431,  431,  431,  432,  432,
      193,  432,  432,  192,  432,  432,  432,  432,  191,  187,
      186,  432,  433,  433,  185,  171,  433,  433,  433,  434,

      434,  170,  434,  434,  434,  434,  434,  434,  434,  434,
      434,  434,  434,  435,  435,  166,  165,  435,  435,  435,
      436,  436,  163,  436,  436,  436,  436,  436,  436,  436,
      436,  436,  436,  436,  437,  437,  162,  437,  437,  437,
      437,  437,  437,  437,  437,  437,  437,  437,  438,  438,
      161,  438,  438,  438,  438,  438,  438,  160,  438,  438,
      438,  438,  439,  439,  159,  158,  156,  439,  439,  439,
      439,  439,  440,  440,  155,  440,  440,  440,  440,  440,
      440,  440,  440,  440,  440,  440,  441,  441,  152,  151,
      441,  441,  441,  442,  442,  442,  442,  442,  442,  442,

      442,  442,  442,  442,  442,  442,  442,  443,  443,  150,
      443,  443,  145,  443,  443,  443,  443,  443,  443,  443,
      443,  444,  444,  444,  444,  444,  144,  444,  444,  444,
      444,  444,  444,  444,  444,  445,  445,  142,  140,  445,
      445,  445,  445,  138,  445,  445,  445,  445,  445,  446,
      446,  137,  446,  446,  446,  446,  446,  446,  446,  446,
      446,  446,  446,  447,  447,  136,  447,  447,  133,  447,
      447,  447,  447,  132,  130,  126,  447,  448,  448,  125,
      123,  448,  448,  448,  449,  120,  119,  449,  449,  449,
      449,  449,  449,  449,  449,  449,  449,  449,  450,  450,

      114,  450,  450,  450,  450,  450,  450,  450,  450,  450,
      450,  450,  451,  451,  113,  451,  451,  451,  451,  451,
      451,  451,  451,  451,  451,  451,  452,  452,  452,  453,
      453,  453,  454,  454,  454,  454,  454,  454,  454,  454,
      454,  454,  454,  454,  454,  454,  455,  455,  455,  455,
      455,  455,  455,  455,  455,  455,  455,  455,  455,  455,
      456,  456,  106,  456,  456,  456,  456,  456,  456,  105,
      456,  456,  456,  456,  458,  458,  102,  458,  458,  458,
      458,  458,  458,  458,  458,  458,  458,  459,  459,  100,
      459,  459,  459,  459,  459,  459,  459,  459,  459,  459,

      459,  460,  460,   99,  460,  460,  460,  460,  460,  460,
      460,  460,  460,  460,  460,  461,  461,   95,  461,  461,
      461,  461,  461,  461,  461,  461,  461,  461,  461,  463,
      463,  463,  463,  463,  463,  463,  463,  463,  463,  463,
      463,  463,  463,  464,  464,   92,   91,  464,  464,  464,
      465,  465,   90,   88,  465,  465,  465,  468,  468,  468,
      468,  468,  468,  468,  468,  468,  468,  468,  468,  468,
      468,  469,  469,  469,  469,  469,  469,  469,  469,  469,
      469,  469,  469,  469,  469,   87,   86,   83,   82,   79,
       77,   76,   74,   73,   70,   68,   67,   63,   62,   58,

       57,   53,   51,   50,   47,   46,   43,   42,   41,   16,
       15,   10,    8,    7,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407,  407,  407,
      407,  407,  407,  407,  407,  407,  407,  407
    } ;

static yy_state_type yy_last_accepting_state;
static char *yy_last_accepting_cpos;

/* The intent behind this definition is that it'll catch
 * any uses of REJECT which flex missed.
 */
#define REJECT reject_used_but_not_detected
#define yymore() yymore_used_but_not_detected
#define YY_MORE_ADJ 0
char *yytext;
/* scan.l - scanner for flex input */
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Vern Paxson.
 * 
 * The United States Government has rights in this work pursuant
 * to contract no. DE-AC03-76SF00098 between the United States
 * Department of Energy and the University of California.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* $Header: /a1/cvsadm/cvsroot/expsir/csubjects/flex/versions.alt/versions.orig/v0/flex.c,v 1.1.1.1 2003/06/02 17:12:00 expsir Exp $ */


#define ACTION_ECHO add_action( yytext )
#define MARK_END_OF_PROLOG mark_prolog();

#define YY_DECL \
	int flexscan()

#define RETURNCHAR \
	yylval = yytext[0]; \
	return CHAR;

#define RETURNNAME \
	yy_strcpy( nmstr, yytext ); \
	return NAME;

#define PUT_BACK_STRING(str, start) \
	for ( i = yy_strlen( str ) - 1; i >= start; --i ) \
		unput((str)[i])

#define CHECK_REJECT(str) \
	if ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYMORE(str) \
	if ( all_lower( str ) ) \
		yymore_used = true;

/* Macros after this point can all be overridden by user definitions in
 * section 1.
 */

/* Amount of stuff to slurp up with each read. */
#ifndef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE 8192
#endif

/* Copy whatever the last rule matched to the standard output. */

#ifndef ECHO
/* This used to be an fputs(), but since the string might contain NUL's,
 * we now use fwrite().
 */
#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
#endif

/* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
 * is returned in "result".
 */
#ifndef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( yy_current_buffer->is_interactive ) \
		result = ((int) (buf[0] = getc( yyin ))) == EOF ? 0 : 1; \
	else if ( ((result = fread( (char *) buf, 1, max_size, yyin )) == 0)\
		  && ferror( yyin ) ) \
		YY_FATAL_ERROR( "input in flex scanner failed" );
#endif

/* No semi-colon after return; correct usage is to write "yyterminate();" -
 * we don't want an extra ';' after the "return" because that will cause
 * some compilers to complain about unreachable statements.
 */
#ifndef yyterminate
#define yyterminate() return YY_NULL
#endif

/* Report a fatal error. */
#ifndef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) yy_fatal_error( msg )
#endif

/* Default declaration of generated scanner - a define so the user can
 * easily add parameters.
 */
#ifndef YY_DECL
#define YY_DECL int yylex YY_PROTO(( void ))
#endif

/* Code executed at the end of each rule. */
#ifndef YY_BREAK
#define YY_BREAK break;
#endif

YY_DECL
	{
	register yy_state_type yy_current_state;
	register char *yy_cp, *yy_bp;
	register int yy_act;


	static int bracelevel, didadef, indented_code, checking_used;

	int doing_codeblock = false;
	int i;
	Char nmdef[MAXLINE], myesc();



	if ( yy_init )
		{
#ifdef YY_USER_INIT
		YY_USER_INIT;
#endif

		if ( ! yy_start )
			yy_start = 1;	/* first start state */

		if ( ! yyin )
			yyin = stdin;

		if ( ! yyout )
			yyout = stdout;

		if ( yy_current_buffer )
			yy_init_buffer( yy_current_buffer, yyin );
		else
			yy_current_buffer =
				yy_create_buffer( yyin, YY_BUF_SIZE );

		yy_load_buffer_state();

		yy_init = 0;
		}

	while ( 1 )		/* loops until end-of-file is reached */
		{
		yy_cp = yy_c_buf_p;

		/* Support of yytext. */
		*yy_cp = yy_hold_char;

		/* yy_bp points to the position in yy_ch_buf of the start of
		 * the current run.
		 */
		yy_bp = yy_cp;

		yy_current_state = yy_start;
		if ( yy_bp[-1] == '\n' )
			++yy_current_state;
yy_match:
		do
			{
			register YY_CHAR yy_c = yy_ec[(unsigned int) *yy_cp];
			if ( yy_accept[yy_current_state] )
				{
				yy_last_accepting_state = yy_current_state;
				yy_last_accepting_cpos = yy_cp;
				}
			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
				{
				yy_current_state = (int) yy_def[yy_current_state];
				if ( yy_current_state >= 408 )
					yy_c = yy_meta[(unsigned int) yy_c];
				}
			yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
			++yy_cp;
			}
		while ( yy_base[yy_current_state] != 1615 );

yy_find_action:
		yy_act = yy_accept[yy_current_state];

		YY_DO_BEFORE_ACTION;

#ifdef YY_USER_ACTION
		if ( yy_act != YY_END_OF_BUFFER )
			{
			YY_USER_ACTION;
			}
#endif


do_action:	/* This label is used only to access EOF actions. */


		switch ( yy_act )
	{ /* beginning of action switch */
			case 0: /* must back up */
			/* undo the effects of YY_DO_BEFORE_ACTION */
			*yy_cp = yy_hold_char;
			yy_cp = yy_last_accepting_cpos;
			yy_current_state = yy_last_accepting_state;
			goto yy_find_action;

case 1:
indented_code = true; BEGIN(CODEBLOCK);
	YY_BREAK
case 2:
ACTION_ECHO; BEGIN(C_COMMENT);
	YY_BREAK
case 3:
return SCDECL;
	YY_BREAK
case 4:
return XSCDECL;
	YY_BREAK
case 5:
{
			++linenum;
			line_directive_out( (FILE *) 0 );
			indented_code = false;
			BEGIN(CODEBLOCK);
			}
	YY_BREAK
case 6:
return WHITESPACE;
	YY_BREAK
case 7:
{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			line_directive_out( (FILE *) 0 );
			BEGIN(SECT2PROLOG);
			return SECTEND;
			}
	YY_BREAK
case 8:
{
			if ( lex_compat )
				warn( "%pointer incompatible with -l option" );
			else
				yytext_is_array = false;
			++linenum;
			}
	YY_BREAK
case 9:
{
			if ( C_plus_plus )
				warn( "%array incompatible with -+ option" );
			else
				yytext_is_array = true;
			++linenum;
			}
	YY_BREAK
case 10:
{
			warn( "%used/%unused have been deprecated" );
			checking_used = REALLY_USED; BEGIN(USED_LIST);
			}
	YY_BREAK
case 11:
{
			warn( "%used/%unused have been deprecated" );
			checking_used = REALLY_NOT_USED; BEGIN(USED_LIST);
			}
	YY_BREAK
case 12:
++linenum;	/* ignore */
	YY_BREAK
case 13:
synerr( "unrecognized '%' directive" );
	YY_BREAK
case 14:
{
			yy_strcpy( nmstr, yytext );
			didadef = false;
			BEGIN(PICKUPDEF);
			}
	YY_BREAK
case 15:
RETURNNAME;
	YY_BREAK
case 16:
++linenum; /* allows blank lines in section 1 */
	YY_BREAK
case 17:
++linenum; return '\n';
	YY_BREAK
case 18:
ACTION_ECHO; BEGIN(INITIAL);
	YY_BREAK
case 19:
++linenum; ACTION_ECHO; BEGIN(INITIAL);
	YY_BREAK
case 20:
ACTION_ECHO;
	YY_BREAK
case 21:
ACTION_ECHO;
	YY_BREAK
case 22:
++linenum; ACTION_ECHO;
	YY_BREAK
case 23:
++linenum; BEGIN(INITIAL);
	YY_BREAK
case 24:
ACTION_ECHO; CHECK_REJECT(yytext);
	YY_BREAK
case 25:
ACTION_ECHO; CHECK_YYMORE(yytext);
	YY_BREAK
case 26:
ACTION_ECHO;
	YY_BREAK
case 27:
{
			++linenum;
			ACTION_ECHO;
			if ( indented_code )
				BEGIN(INITIAL);
			}
	YY_BREAK
case 28:
/* separates name and definition */
	YY_BREAK
case 29:
{
			yy_strcpy( (char *) nmdef, yytext );

			/* Skip trailing whitespace. */
			for ( i = yy_strlen( (char *) nmdef ) - 1;
			      i >= 0 && (nmdef[i] == ' ' || nmdef[i] == '\t');
			      --i )
				;

			nmdef[i + 1] = '\0';

			ndinstal( nmstr, nmdef );
			didadef = true;
			}
	YY_BREAK
case 30:
{
			if ( ! didadef )
				synerr( "incomplete name definition" );
			BEGIN(INITIAL);
			++linenum;
			}
	YY_BREAK
case 31:
++linenum; BEGIN(INITIAL); RETURNNAME;
	YY_BREAK
case 32:
++linenum; BEGIN(INITIAL);
	YY_BREAK
case 33:

	YY_BREAK
case 34:
{
			if ( all_upper( yytext ) )
				reject_really_used = checking_used;
			else
				synerr(
				"unrecognized %used/%unused construct" );
			}
	YY_BREAK
case 35:
{
			if ( all_lower( yytext ) )
				yymore_really_used = checking_used;
			else
				synerr(
				"unrecognized %used/%unused construct" );
			}
	YY_BREAK
case 36:
synerr( "unrecognized %used/%unused construct" );
	YY_BREAK
case 37:
++bracelevel; yyless( 2 );	/* eat only %{ */
	YY_BREAK
case 38:
--bracelevel; yyless( 2 );	/* eat only %} */
	YY_BREAK
case 39:
ACTION_ECHO;	/* indented code in prolog */
	YY_BREAK
case 40:
{	/* non-indented code */
			if ( bracelevel <= 0 )
				{ /* not in %{ ... %} */
				yyless( 0 );	/* put it all back */
				mark_prolog();
				BEGIN(SECT2);
				}
			else
				ACTION_ECHO;
			}
	YY_BREAK
case 41:
ACTION_ECHO;
	YY_BREAK
case 42:
++linenum; ACTION_ECHO;
	YY_BREAK
case YY_STATE_EOF(SECT2PROLOG):
{
			mark_prolog();
			sectnum = 0;
			yyterminate(); /* to stop the parser */
			}
	YY_BREAK
case 43:
++linenum; /* allow blank lines in section 2 */
	YY_BREAK
case 44:
{
			indented_code = (yytext[0] != '%');
			doing_codeblock = true;
			bracelevel = 1;

			if ( indented_code )
				ACTION_ECHO;

			BEGIN(CODEBLOCK_2);
			}
	YY_BREAK
case 45:
BEGIN(SC); return '<';
	YY_BREAK
case 46:
return '^';
	YY_BREAK
case 47:
BEGIN(QUOTE); return '"';
	YY_BREAK
case 48:
*yy_cp = yy_hold_char; /* undo effects of setting up yytext */
yy_c_buf_p = yy_cp = yy_bp + 1;
YY_DO_BEFORE_ACTION; /* set up yytext again */
BEGIN(NUM); return '{';
	YY_BREAK
case 49:
BEGIN(BRACEERROR);
	YY_BREAK
case 50:
*yy_cp = yy_hold_char; /* undo effects of setting up yytext */
yy_c_buf_p = yy_cp = yy_bp + 1;
YY_DO_BEFORE_ACTION; /* set up yytext again */
return '$';
	YY_BREAK
case 51:
{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);
			return '\n';
			}
	YY_BREAK
case 52:
continued_action = true; ++linenum; return '\n';
	YY_BREAK
case 53:
{
			/* This rule is separate from the one below because
			 * otherwise we get variable trailing context, so
			 * we can't build the scanner using -{f,F}.
			 */
			bracelevel = 0;
			continued_action = false;
			BEGIN(ACTION);
			return '\n';
			}
	YY_BREAK
case 54:
{
			bracelevel = 0;
			continued_action = false;
			BEGIN(ACTION);
			unput( '\n' );	/* so <ACTION> sees it */
			return '\n';
			}
	YY_BREAK
case 55:
return EOF_OP;
	YY_BREAK
case 56:
{
			sectnum = 3;
			BEGIN(SECT3);
			yyterminate(); /* to stop the parser */
			}
	YY_BREAK
case 57:
{
			int cclval;

			yy_strcpy( nmstr, yytext );

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			if ( (cclval = ccllookup( (Char *) nmstr )) )
				{
				if ( input() != ']' )
					synerr( "bad character class" );

				yylval = cclval;
				++cclreuse;
				return PREVCCL;
				}
			else
				{
				/* We fudge a bit.  We know that this ccl will
				 * soon be numbered as lastccl + 1 by cclinit.
				 */
				cclinstal( (Char *) nmstr, lastccl + 1 );

				/* Push back everything but the leading bracket
				 * so the ccl can be rescanned.
				 */
				yyless( 1 );

				BEGIN(FIRSTCCL);
				return '[';
				}
			}
	YY_BREAK
case 58:
{
			register Char *nmdefptr;
			Char *ndlookup();

			yy_strcpy( nmstr, yytext + 1 );
			nmstr[yyleng - 2] = '\0';  /* chop trailing brace */

			if ( ! (nmdefptr = ndlookup( nmstr )) )
				format_synerr( "undefined definition {%s}",
						nmstr );

			else
				{ /* push back name surrounded by ()'s */
				int len = yy_strlen( (char *) nmdefptr );

				if ( lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$') )
					{ /* don't use ()'s after all */
					PUT_BACK_STRING((char *) nmdefptr, 0);

					if ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				else
					{
					unput(')');
					PUT_BACK_STRING((char *) nmdefptr, 0);
					unput('(');
					}
				}
			}
	YY_BREAK
case 59:
return (int) yytext[0];
	YY_BREAK
case 60:
RETURNCHAR;
	YY_BREAK
case 61:
return (int) yytext[0];
	YY_BREAK
case 62:
BEGIN(SECT2); return '>';
	YY_BREAK
case 63:
*yy_cp = yy_hold_char; /* undo effects of setting up yytext */
yy_c_buf_p = yy_cp = yy_bp + 1;
YY_DO_BEFORE_ACTION; /* set up yytext again */
BEGIN(CARETISBOL); return '>';
	YY_BREAK
case 64:
RETURNNAME;
	YY_BREAK
case 65:
{
			format_synerr( "bad <start condition>: %s", yytext );
			}
	YY_BREAK
case 66:
BEGIN(SECT2); return '^';
	YY_BREAK
case 67:
RETURNCHAR;
	YY_BREAK
case 68:
BEGIN(SECT2); return '"';
	YY_BREAK
case 69:
{
			synerr( "missing quote" );
			BEGIN(SECT2);
			++linenum;
			return '"';
			}
	YY_BREAK
case 70:
*yy_cp = yy_hold_char; /* undo effects of setting up yytext */
yy_c_buf_p = yy_cp = yy_bp + 1;
YY_DO_BEFORE_ACTION; /* set up yytext again */
BEGIN(CCL); return '^';
	YY_BREAK
case 71:
*yy_cp = yy_hold_char; /* undo effects of setting up yytext */
yy_c_buf_p = yy_cp = yy_bp + 1;
YY_DO_BEFORE_ACTION; /* set up yytext again */
return '^';
	YY_BREAK
case 72:
BEGIN(CCL); RETURNCHAR;
	YY_BREAK
case 73:
*yy_cp = yy_hold_char; /* undo effects of setting up yytext */
yy_c_buf_p = yy_cp = yy_bp + 1;
YY_DO_BEFORE_ACTION; /* set up yytext again */
return '-';
	YY_BREAK
case 74:
RETURNCHAR;
	YY_BREAK
case 75:
BEGIN(SECT2); return ']';
	YY_BREAK
case 76:
{
			synerr( "bad character class" );
			BEGIN(SECT2);
			return ']';
			}
	YY_BREAK
case 77:
{
			yylval = myctoi( yytext );
			return NUMBER;
			}
	YY_BREAK
case 78:
return ',';
	YY_BREAK
case 79:
BEGIN(SECT2); return '}';
	YY_BREAK
case 80:
{
			synerr( "bad character inside {}'s" );
			BEGIN(SECT2);
			return '}';
			}
	YY_BREAK
case 81:
{
			synerr( "missing }" );
			BEGIN(SECT2);
			++linenum;
			return '}';
			}
	YY_BREAK
case 82:
synerr( "bad name in {}'s" ); BEGIN(SECT2);
	YY_BREAK
case 83:
synerr( "missing }" ); ++linenum; BEGIN(SECT2);
	YY_BREAK
case 84:
ACTION_ECHO; BEGIN(ACTION_COMMENT);
	YY_BREAK
case 85:
bracelevel = 0;
	YY_BREAK
case 86:
{
			ACTION_ECHO;
			CHECK_REJECT(yytext);
			}
	YY_BREAK
case 87:
{
			ACTION_ECHO;
			CHECK_YYMORE(yytext);
			}
	YY_BREAK
case 88:
ACTION_ECHO;
	YY_BREAK
case 89:
{
			++linenum;
			ACTION_ECHO;
			if ( bracelevel == 0 ||
			     (doing_codeblock && indented_code) )
				{
				if ( ! doing_codeblock )
					add_action( "\tYY_BREAK\n" );
				
				doing_codeblock = false;
				BEGIN(SECT2);
				}
			}
	YY_BREAK
	/* Reject and YYmore() are checked for above, in PERCENT_BRACE_ACTION */
case 90:
ACTION_ECHO; ++bracelevel;
	YY_BREAK
case 91:
ACTION_ECHO; --bracelevel;
	YY_BREAK
case 92:
ACTION_ECHO;
	YY_BREAK
case 93:
ACTION_ECHO;
	YY_BREAK
case 94:
ACTION_ECHO; BEGIN(ACTION_COMMENT);
	YY_BREAK
case 95:
ACTION_ECHO; /* character constant */
	YY_BREAK
case 96:
ACTION_ECHO; BEGIN(ACTION_STRING);
	YY_BREAK
case 97:
{
			++linenum;
			ACTION_ECHO;
			if ( bracelevel == 0 )
				{
				add_action( "\tYY_BREAK\n" );
				BEGIN(SECT2);
				}
			}
	YY_BREAK
case 98:
ACTION_ECHO;
	YY_BREAK
case 99:
{
			ACTION_ECHO;
			if ( doing_codeblock )
				BEGIN(CODEBLOCK_2);
			else
				BEGIN(ACTION);
			}
	YY_BREAK
case 100:
ACTION_ECHO;
	YY_BREAK
case 101:
ACTION_ECHO;
	YY_BREAK
case 102:
++linenum; ACTION_ECHO;
	YY_BREAK
case 103:
ACTION_ECHO;
	YY_BREAK
case 104:
ACTION_ECHO;
	YY_BREAK
case 105:
++linenum; ACTION_ECHO;
	YY_BREAK
case 106:
ACTION_ECHO; BEGIN(ACTION);
	YY_BREAK
case 107:
ACTION_ECHO;
	YY_BREAK
case YY_STATE_EOF(ACTION):
case YY_STATE_EOF(ACTION_COMMENT):
case YY_STATE_EOF(ACTION_STRING):
{
			synerr( "EOF encountered inside an action" );
			yyterminate();
			}
	YY_BREAK
case 108:
{
			yylval = myesc( (Char *) yytext );
			return CHAR;
			}
	YY_BREAK
case 109:
{
			yylval = myesc( (Char *) yytext );
			BEGIN(CCL);
			return CHAR;
			}
	YY_BREAK
case 110:
ECHO;
	YY_BREAK
case YY_STATE_EOF(SECT3):
sectnum = 0; yyterminate();
	YY_BREAK
case 111:
format_synerr( "bad character: %s", yytext );
	YY_BREAK
case 112:
YY_FATAL_ERROR( "flex scanner jammed" );
	YY_BREAK
case YY_STATE_EOF(INITIAL):
case YY_STATE_EOF(SECT2):
case YY_STATE_EOF(CODEBLOCK):
case YY_STATE_EOF(PICKUPDEF):
case YY_STATE_EOF(SC):
case YY_STATE_EOF(CARETISBOL):
case YY_STATE_EOF(NUM):
case YY_STATE_EOF(QUOTE):
case YY_STATE_EOF(FIRSTCCL):
case YY_STATE_EOF(CCL):
case YY_STATE_EOF(RECOVER):
case YY_STATE_EOF(BRACEERROR):
case YY_STATE_EOF(C_COMMENT):
case YY_STATE_EOF(PERCENT_BRACE_ACTION):
case YY_STATE_EOF(USED_LIST):
case YY_STATE_EOF(CODEBLOCK_2):
	yyterminate();

	case YY_END_OF_BUFFER:
		{
		/* Amount of text matched not including the EOB char. */
		int yy_amount_of_matched_text = yy_cp - yytext_ptr - 1;

		/* Undo the effects of YY_DO_BEFORE_ACTION. */
		*yy_cp = yy_hold_char;

		/* Note that here we test for yy_c_buf_p "<=" to the position
		 * of the first EOB in the buffer, since yy_c_buf_p will
		 * already have been incremented past the NUL character
		 * (since all states make transitions on EOB to the
		 * end-of-buffer state).  Contrast this with the test
		 * in input().
		 */
		if ( yy_c_buf_p <= &yy_current_buffer->yy_ch_buf[yy_n_chars] )
			{ /* This was really a NUL. */
			yy_state_type yy_next_state;

			yy_c_buf_p = yytext_ptr + yy_amount_of_matched_text;

			yy_current_state = yy_get_previous_state();

			/* Okay, we're now positioned to make the NUL
			 * transition.  We couldn't have
			 * yy_get_previous_state() go ahead and do it
			 * for us because it doesn't know how to deal
			 * with the possibility of jamming (and we don't
			 * want to build jamming into it because then it
			 * will run more slowly).
			 */

			yy_next_state = yy_try_NUL_trans( yy_current_state );

			yy_bp = yytext_ptr + YY_MORE_ADJ;

			if ( yy_next_state )
				{
				/* Consume the NUL. */
				yy_cp = ++yy_c_buf_p;
				yy_current_state = yy_next_state;
				goto yy_match;
				}

			else
				{
				goto yy_find_action;
				}
			}

		else switch ( yy_get_next_buffer() )
			{
			case EOB_ACT_END_OF_FILE:
				{
				yy_did_buffer_switch_on_eof = 0;

				if ( yywrap() )
					{
					/* Note: because we've taken care in
					 * yy_get_next_buffer() to have set up
					 * yytext, we can now set up
					 * yy_c_buf_p so that if some total
					 * hoser (like flex itself) wants to
					 * call the scanner after we return the
					 * YY_NULL, it'll still work - another
					 * YY_NULL will get returned.
					 */
					yy_c_buf_p = yytext_ptr + YY_MORE_ADJ;

					yy_act = YY_STATE_EOF(YY_START);
					goto do_action;
					}

				else
					{
					if ( ! yy_did_buffer_switch_on_eof )
						YY_NEW_FILE;
					}
				break;
				}

			case EOB_ACT_CONTINUE_SCAN:
				yy_c_buf_p =
					yytext_ptr + yy_amount_of_matched_text;

				yy_current_state = yy_get_previous_state();

				yy_cp = yy_c_buf_p;
				yy_bp = yytext_ptr + YY_MORE_ADJ;
				goto yy_match;

			case EOB_ACT_LAST_MATCH:
				yy_c_buf_p =
				&yy_current_buffer->yy_ch_buf[yy_n_chars];

				yy_current_state = yy_get_previous_state();

				yy_cp = yy_c_buf_p;
				yy_bp = yytext_ptr + YY_MORE_ADJ;
				goto yy_find_action;
			}
		break;
		}

	default:
#ifdef FLEX_DEBUG
		printf( "action # %d\n", yy_act );
#endif
		YY_FATAL_ERROR(
			"fatal flex scanner internal error--no action found" );
	} /* end of action switch */
		} /* end of scanning one token */
	} /* end of yylex */


/* yy_get_next_buffer - try to read in a new buffer
 *
 * Returns a code representing an action:
 *	EOB_ACT_LAST_MATCH -
 *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
 *	EOB_ACT_END_OF_FILE - end of file
 */

static int yy_get_next_buffer()
	{
	register char *dest = yy_current_buffer->yy_ch_buf;
	register char *source = yytext_ptr - 1; /* copy prev. char, too */
	register int number_to_move, i;
	int ret_val;

	if ( yy_c_buf_p > &yy_current_buffer->yy_ch_buf[yy_n_chars + 1] )
		YY_FATAL_ERROR(
		"fatal flex scanner internal error--end of buffer missed" );

	/* Try to read more data. */

	/* First move last chars to start of buffer. */
	number_to_move = yy_c_buf_p - yytext_ptr;

	for ( i = 0; i < number_to_move; ++i )
		*(dest++) = *(source++);

	if ( yy_current_buffer->yy_eof_status != EOF_NOT_SEEN )
		/* don't do the read, it's not guaranteed to return an EOF,
		 * just force an EOF
		 */
		yy_n_chars = 0;

	else
		{
		int num_to_read =
			yy_current_buffer->yy_buf_size - number_to_move - 1;

		while ( num_to_read <= 0 )
			{ /* Not enough room in the buffer - grow it. */
#ifdef YY_USES_REJECT
			YY_FATAL_ERROR(
"input buffer overflow, can't enlarge buffer because scanner uses REJECT" );
#else

			/* just a shorter name for the current buffer */
			YY_BUFFER_STATE b = yy_current_buffer;

			int yy_c_buf_p_offset = yy_c_buf_p - b->yy_ch_buf;

			b->yy_buf_size *= 2;
			b->yy_ch_buf = (char *)
				yy_flex_realloc( (void *) b->yy_ch_buf,
						 b->yy_buf_size );

			if ( ! b->yy_ch_buf )
				YY_FATAL_ERROR(
				"fatal error - scanner input buffer overflow" );

			yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];

			num_to_read = yy_current_buffer->yy_buf_size -
						number_to_move - 1;
#endif
			}

		if ( num_to_read > YY_READ_BUF_SIZE )
			num_to_read = YY_READ_BUF_SIZE;

		/* Read in more data. */
		YY_INPUT( (&yy_current_buffer->yy_ch_buf[number_to_move]),
			yy_n_chars, num_to_read );
		}

	if ( yy_n_chars == 0 )
		{
		if ( number_to_move - YY_MORE_ADJ == 1 )
			{
			ret_val = EOB_ACT_END_OF_FILE;
			yyrestart( yyin );
			}

		else
			{
			ret_val = EOB_ACT_LAST_MATCH;
			yy_current_buffer->yy_eof_status = EOF_PENDING;
			}
		}

	else
		ret_val = EOB_ACT_CONTINUE_SCAN;

	yy_n_chars += number_to_move;
	yy_current_buffer->yy_ch_buf[yy_n_chars] = YY_END_OF_BUFFER_CHAR;
	yy_current_buffer->yy_ch_buf[yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;

	/* yytext begins at the second character in yy_ch_buf; the first
	 * character is the one which preceded it before reading in the latest
	 * buffer; it needs to be kept around in case it's a newline, so
	 * yy_get_previous_state() will have with '^' rules active.
	 */

	yytext_ptr = &yy_current_buffer->yy_ch_buf[1];

	return ret_val;
	}


/* yy_get_previous_state - get the state just before the EOB char was reached */

static yy_state_type yy_get_previous_state()
	{
	register yy_state_type yy_current_state;
	register char *yy_cp;

	register char *yy_bp = yytext_ptr;

	yy_current_state = yy_start;
	if ( yy_bp[-1] == '\n' )
		++yy_current_state;

	for ( yy_cp = yytext_ptr + YY_MORE_ADJ; yy_cp < yy_c_buf_p; ++yy_cp )
		{
		register YY_CHAR yy_c = (*yy_cp ? yy_ec[(unsigned int) *yy_cp] : 1);
		if ( yy_accept[yy_current_state] )
			{
			yy_last_accepting_state = yy_current_state;
			yy_last_accepting_cpos = yy_cp;
			}
		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
			{
			yy_current_state = (int) yy_def[yy_current_state];
			if ( yy_current_state >= 408 )
				yy_c = yy_meta[(unsigned int) yy_c];
			}
		yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
		}

	return yy_current_state;
	}


/* yy_try_NUL_trans - try to make a transition on the NUL character
 *
 * synopsis
 *	next_state = yy_try_NUL_trans( current_state );
 */

#ifdef YY_USE_PROTOS
static yy_state_type yy_try_NUL_trans( yy_state_type yy_current_state )
#else
static yy_state_type yy_try_NUL_trans( yy_current_state )
yy_state_type yy_current_state;
#endif
	{
	register int yy_is_jam;
	register char *yy_cp = yy_c_buf_p;

	register YY_CHAR yy_c = 1;
	if ( yy_accept[yy_current_state] )
		{
		yy_last_accepting_state = yy_current_state;
		yy_last_accepting_cpos = yy_cp;
		}
	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
		{
		yy_current_state = (int) yy_def[yy_current_state];
		if ( yy_current_state >= 408 )
			yy_c = yy_meta[(unsigned int) yy_c];
		}
	yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
	yy_is_jam = (yy_current_state == 407);

	return yy_is_jam ? 0 : yy_current_state;
	}


#ifdef YY_USE_PROTOS
static void yyunput( int c, register char *yy_bp )
#else
static void yyunput( c, yy_bp )
int c;
register char *yy_bp;
#endif
	{
	register char *yy_cp = yy_c_buf_p;

	/* undo effects of setting up yytext */
	*yy_cp = yy_hold_char;

	if ( yy_cp < yy_current_buffer->yy_ch_buf + 2 )
		{ /* need to shift things up to make room */
		/* +2 for EOB chars. */
		register int number_to_move = yy_n_chars + 2;
		register char *dest = &yy_current_buffer->yy_ch_buf[
					yy_current_buffer->yy_buf_size + 2];
		register char *source =
				&yy_current_buffer->yy_ch_buf[number_to_move];

		while ( source > yy_current_buffer->yy_ch_buf )
			*--dest = *--source;

		yy_cp += dest - source;
		yy_bp += dest - source;
		yy_n_chars = yy_current_buffer->yy_buf_size;

		if ( yy_cp < yy_current_buffer->yy_ch_buf + 2 )
			YY_FATAL_ERROR( "flex scanner push-back overflow" );
		}

	if ( yy_cp > yy_bp && yy_cp[-1] == '\n' )
		yy_cp[-2] = '\n';

	*--yy_cp = (char) c;


	/* Note: the formal parameter *must* be called "yy_bp" for this
	 * macro to now work correctly.
	 */
	YY_DO_BEFORE_ACTION; /* set up yytext again */
	}


#ifdef __cplusplus
static int yyinput()
#else
static int input()
#endif
	{
	int c;

	*yy_c_buf_p = yy_hold_char;

	if ( *yy_c_buf_p == YY_END_OF_BUFFER_CHAR )
		{
		/* yy_c_buf_p now points to the character we want to return.
		 * If this occurs *before* the EOB characters, then it's a
		 * valid NUL; if not, then we've hit the end of the buffer.
		 */
		if ( yy_c_buf_p < &yy_current_buffer->yy_ch_buf[yy_n_chars] )
			/* This was really a NUL. */
			*yy_c_buf_p = '\0';

		else
			{ /* need more input */
			yytext_ptr = yy_c_buf_p;
			++yy_c_buf_p;

			switch ( yy_get_next_buffer() )
				{
				case EOB_ACT_END_OF_FILE:
					{
					if ( yywrap() )
						{
						yy_c_buf_p =
						yytext_ptr + YY_MORE_ADJ;
						return EOF;
						}

					YY_NEW_FILE;
#ifdef __cplusplus
					return yyinput();
#else
					return input();
#endif
					}

				case EOB_ACT_CONTINUE_SCAN:
					yy_c_buf_p = yytext_ptr + YY_MORE_ADJ;
					break;

				case EOB_ACT_LAST_MATCH:
#ifdef __cplusplus
					YY_FATAL_ERROR(
					"unexpected last match in yyinput()" );
#else
					YY_FATAL_ERROR(
					"unexpected last match in input()" );
#endif
				}
			}
		}

	c = *yy_c_buf_p;
	*yy_c_buf_p = '\0';	/* preserve yytext */
	yy_hold_char = *++yy_c_buf_p;

	return c;
	}


#ifdef YY_USE_PROTOS
void yyrestart( FILE *input_file )
#else
void yyrestart( input_file )
FILE *input_file;
#endif
	{
	if ( ! yy_current_buffer )
		yy_current_buffer = yy_create_buffer( yyin, YY_BUF_SIZE );

	yy_init_buffer( yy_current_buffer, input_file );
	yy_load_buffer_state();
	}


#ifdef YY_USE_PROTOS
void yy_switch_to_buffer( YY_BUFFER_STATE new_buffer )
#else
void yy_switch_to_buffer( new_buffer )
YY_BUFFER_STATE new_buffer;
#endif
	{
	if ( yy_current_buffer == new_buffer )
		return;

	if ( yy_current_buffer )
		{
		/* Flush out information for old buffer. */
		*yy_c_buf_p = yy_hold_char;
		yy_current_buffer->yy_buf_pos = yy_c_buf_p;
		yy_current_buffer->yy_n_chars = yy_n_chars;
		}

	yy_current_buffer = new_buffer;
	yy_load_buffer_state();

	/* We don't actually know whether we did this switch during
	 * EOF (yywrap()) processing, but the only time this flag
	 * is looked at is after yywrap() is called, so it's safe
	 * to go ahead and always set it.
	 */
	yy_did_buffer_switch_on_eof = 1;
	}


#ifdef YY_USE_PROTOS
void yy_load_buffer_state( void )
#else
void yy_load_buffer_state()
#endif
	{
	yy_n_chars = yy_current_buffer->yy_n_chars;
	yytext_ptr = yy_c_buf_p = yy_current_buffer->yy_buf_pos;
	yyin = yy_current_buffer->yy_input_file;
	yy_hold_char = *yy_c_buf_p;
	}


#ifdef YY_USE_PROTOS
YY_BUFFER_STATE yy_create_buffer( FILE *file, int size )
#else
YY_BUFFER_STATE yy_create_buffer( file, size )
FILE *file;
int size;
#endif
	{
	YY_BUFFER_STATE b;

	b = (YY_BUFFER_STATE) yy_flex_alloc( sizeof( struct yy_buffer_state ) );

	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	b->yy_buf_size = size;

	/* yy_ch_buf has to be 2 characters longer than the size given because
	 * we need to put in 2 end-of-buffer characters.
	 */
	b->yy_ch_buf = (char *) yy_flex_alloc( b->yy_buf_size + 2 );

	if ( ! b->yy_ch_buf )
		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

	yy_init_buffer( b, file );

	return b;
	}


#ifdef YY_USE_PROTOS
void yy_delete_buffer( YY_BUFFER_STATE b )
#else
void yy_delete_buffer( b )
YY_BUFFER_STATE b;
#endif
	{
	if ( b == yy_current_buffer )
		yy_current_buffer = (YY_BUFFER_STATE) 0;

	yy_flex_free( (void *) b->yy_ch_buf );
	yy_flex_free( (void *) b );
	}


#ifdef YY_USE_PROTOS
void yy_init_buffer( YY_BUFFER_STATE b, FILE *file )
#else
void yy_init_buffer( b, file )
YY_BUFFER_STATE b;
FILE *file;
#endif
	{
	b->yy_input_file = file;

	/* We put in the '\n' and start reading from [1] so that an
	 * initial match-at-newline will be true.
	 */

	b->yy_ch_buf[0] = '\n';
	b->yy_n_chars = 1;

	/* We always need two end-of-buffer characters.  The first causes
	 * a transition to the end-of-buffer state.  The second causes
	 * a jam in that state.
	 */
	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;
	b->yy_ch_buf[2] = YY_END_OF_BUFFER_CHAR;

	b->yy_buf_pos = &b->yy_ch_buf[1];

	b->is_interactive = file ? isatty( fileno(file) ) : 0;

	b->yy_eof_status = EOF_NOT_SEEN;
	}


#ifdef YY_USE_PROTOS
static void yy_fatal_error( const char msg[] )
#else
static void yy_fatal_error( msg )
char msg[];
#endif
	{
	(void) fprintf( err, "%s\n", msg );
	exit( 1 );
	}


/* Redefine yyless() so it works in section 3 code. */

#undef yyless
#define yyless(n) \
	do \
		{ \
		/* Undo effects of setting up yytext. */ \
		yytext[yyleng] = yy_hold_char; \
		yy_c_buf_p = yytext + n - YY_MORE_ADJ; \
		yy_hold_char = *yy_c_buf_p; \
		*yy_c_buf_p = '\0'; \
		yyleng = n; \
		} \
	while ( 0 )



int yywrap()
	{
	if ( --num_input_files > 0 )
		{
		set_input_file( *++input_files );
		return 0;
		}

	else
		return 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

void set_input_file( file )
char *file;
	{
	if ( file )
		{
		infilename = file;
		yyin = fopen( infilename, "r" );

		if ( yyin == NULL )
			lerrsf( "can't open %s", file );
		}

	else
		{
		yyin = stdin;
		infilename = "<stdin>";
		}
	}
