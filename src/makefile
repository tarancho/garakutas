# $Id: makefile,v 1.2 2006/12/06 14:05:40 tfuruka1 Exp $
# $Name:  $
#
# make‚Ìe‹Ê
#
# $Log: makefile,v $
# Revision 1.2  2006/12/06 14:05:40  tfuruka1
# lha32‚ğV‹K’Ç‰Á
#
# Revision 1.1  2006/11/15 12:08:03  tfuruka1
# V‹K’Ç‰Á
#

all :
	sh -c "(cd batkey; nmake)"
	sh -c "(cd crlf; nmake)"
	sh -c "(cd ExSleep; nmake)"
	sh -c "(cd img2java; nmake)"
	sh -c "(cd lha32; nmake)"
	sh -c "(cd wlsfonts; nmake)"

clean :
	sh -c "(cd batkey; nmake clean)"
	sh -c "(cd crlf; nmake clean)"
	sh -c "(cd ExSleep; nmake clean)"
	sh -c "(cd img2java; nmake clean)"
	sh -c "(cd lha32; nmake clean)"
	sh -c "(cd wlsfonts; nmake clean)"
	-rm -fr ../bin/*
