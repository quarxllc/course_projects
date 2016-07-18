# Makefile to compile programs with  ROOT libraries.
#
FILENAME	= %

#------------------------------------------------------------------------------
include /Applications/root_v6.04.16/etc/Makefile.arch

PROGRAMNAMEO       = $(FILENAME).$(ObjSuf)
PROGRAMNAMES       = $(FILENAME).$(SrcSuf)
PROGRAMNAME        = $(FILENAME)$(ExeSuf)

OBJS          = $(PROGRAMNAMEO) 

PROGRAMS      = $(PROGRAMNAME) 

#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)
.PHONY:    

all:            $(PROGRAMS)

$(PROGRAMNAME):      $(PROGRAMNAMEO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@
		@echo "$@ done"

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<
