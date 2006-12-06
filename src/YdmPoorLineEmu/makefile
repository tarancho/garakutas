YDM_API_BASE=../../../other-c-apis/YdmAPI
YDM_INCLUDE=$(YDM_API_BASE)
YDM_LIB_DIR=$(YDM_API_BASE)
YDM_INST_EXE=YdmmInst.exe

LHA32=..\..\bin\lha32.exe a -gw4 $(EXE) $(DLL) \
	YdmmInst.inf $(YDM_INST_EXE) $$ !

EXE = YdmPoorLineEmu.exe
DLL = YdmPoorLineEmu.dll
OBJS = main.obj LineEmu.res

CPPFLAGS = /Zi /W3 /MT /I$(YDM_INCLUDE)
LDFLAGS = /link /debug gdi32.lib user32.lib wsock32.lib \
	/LIBPATH:$(YDM_LIB_DIR) YdmAPI.lib /dll /def:LineEmu.def

../../bin/$(EXE) : $(EXE)
	-cp $(EXE) ../../bin/.

$(EXE) : $(DLL) ! $$
	cp $(YDM_API_BASE)/$(YDM_INST_EXE) .
	-rm -f $(EXE)
	cmd /c "$(LHA32)"

$(DLL) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(DLL) $(OBJS) $(LDFLAGS)

$(OBJS) : makefile

clean:
	-rm -f *.obj *.exp *.lib *.aps *.pdb *~ *.dll *.RES *.ilk *.exe *.EXE
