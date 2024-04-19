#
# {g,n}awk script to generate signames.c
#
# NB: On SunOS 4.1.3 - user-functions don't work properly, also \" problems
# Without 0 + hacks some nawks compare numbers as strings
#
/^[\t ]*#[\t ]*define[\t _]*SIG[A-Z][A-Z0-9]*[\t ]*[1-9][0-9]*/ { 
    sigindex = index($0, "SIG")
    sigtail = substr($0, sigindex, 80)
    split(sigtail, tmp)
    signam = substr(tmp[1], 4, 20)
    signum = tmp[2]
    if (sig[signum] == "") {
	sig[signum] = signam
	if (0 + max < 0 + signum && signum < 60)
	    max = signum
	if (signam == "ABRT")   { msg[signum] = "abort" }
	if (signam == "ALRM")   { msg[signum] = "alarm" }
	if (signam == "BUS")    { msg[signum] = "bus error" }
	if (signam == "CHLD")   { msg[signum] = "death of child" }
	if (signam == "CLD")    { msg[signum] = "death of child" }
	if (signam == "CONT")   { msg[signum] = "continued" }
	if (signam == "EMT")    { msg[signum] = "EMT instruction" }
	if (signam == "FPE")    { msg[signum] = "floating point exception" }
	if (signam == "HUP")    { msg[signum] = "hangup" }
	if (signam == "ILL")    { msg[signum] = "illegal hardware instruction" }
	if (signam == "INFO")   { msg[signum] = "status request from keyboard" }
	if (signam == "INT")    { msg[signum] = "interrupt" }
	if (signam == "IO")     { msg[signum] = "i/o ready" }
	if (signam == "IOT")    { msg[signum] = "IOT instruction" }
	if (signam == "KILL")   { msg[signum] = "killed" }
	if (signam == "LOST")	{ msg[signum] = "resource lost" }
	if (signam == "PIPE")   { msg[signum] = "broken pipe" }
	if (signam == "POLL")	{ msg[signum] = "pollable event occurred" }
	if (signam == "PROF")   { msg[signum] = "profile signal" }
	if (signam == "PWR")    { msg[signum] = "power fail" }
	if (signam == "QUIT")   { msg[signum] = "quit" }
	if (signam == "SEGV")   { msg[signum] = "segmentation fault" }
	if (signam == "SYS")    { msg[signum] = "invalid system call" }
	if (signam == "TERM")   { msg[signum] = "terminated" }
	if (signam == "TRAP")   { msg[signum] = "trace trap" }
	if (signam == "URG")	{ msg[signum] = "urgent condition" }
	if (signam == "USR1")   { msg[signum] = "user-defined signal 1" }
	if (signam == "USR2")   { msg[signum] = "user-defined signal 2" }
	if (signam == "VTALRM") { msg[signum] = "virtual time alarm" }
	if (signam == "WINCH")  { msg[signum] = "window size changed" }
	if (signam == "XCPU")   { msg[signum] = "cpu limit exceeded" }
	if (signam == "XFSZ")   { msg[signum] = "file size limit exceeded" }
    }
}

END {
    ps = "%s"
    ifdstr = sprintf("# ifdef USE_SUSPENDED\n\t%csuspended%s%c,\n%s else\n\t%cstopped%s%c,\n# endif\n", 34, ps, 34, "#", 34, ps, 34)

    printf "/** signames.c                                 **/\n"
    printf "/** architecture-customized signames.c for zsh **/\n"
    printf "\n"
    printf "#define SIGCOUNT\t%d\n", max
    printf "\n"
    printf "#include %czsh.mdh%c\n", 34, 34
    printf "\n"
    printf "/**/\n"
    printf "char *sigmsg[SIGCOUNT+2] = {\n"
    printf "\t%c%s%c,\n", 34, "done", 34

    for (i = 1; i <= 0 + max; i++)
	if (msg[i] == "") {
	    if (sig[i] == "")
		printf("\t%c%c,\n", 34, 34)
	    else if (sig[i] == "STOP")
		printf ifdstr, " (signal)", " (signal)"
	    else if (sig[i] == "TSTP")
		printf ifdstr, "", ""
	    else if (sig[i] == "TTIN")
		printf ifdstr, " (tty input)", " (tty input)"
	    else if (sig[i] == "TTOU")
		printf ifdstr, " (tty output)", " (tty output)"
	    else
		printf("\t%cSIG%s%c,\n", 34, sig[i], 34)
	} else
	    printf("\t%c%s%c,\n", 34, msg[i], 34)
    print "\tNULL"
    print "};"
    print ""
    print "/**/"
    printf "char *sigs[SIGCOUNT+4] = {\n"
    printf("\t%cEXIT%c,\n", 34, 34)
    for (i = 1; i <= 0 + max; i++)
	if (sig[i] == "")
	    printf("\t%c%d%c,\n", 34, i, 34)
	else
	    printf("\t%c%s%c,\n", 34, sig[i], 34)
    printf("\t%cZERR%c,\n", 34, 34)
    printf("\t%cDEBUG%c,\n", 34, 34)
    print "\tNULL"
    print "};"
}
