#!./perl

# $RCSfile: pat.t,v $$Revision: 1.1.1.1 $$Date: 1999/04/23 01:28:38 $

print "1..2\n";

# first test to see if we can run the tests.

$_ = 'test';
if (/^test/) { print "ok 1\n"; } else { print "not ok 1\n";}
if (/^foo/) { print "not ok 2\n"; } else { print "ok 2\n";}
