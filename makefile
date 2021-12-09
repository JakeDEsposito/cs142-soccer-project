#complie logic variables
CC=g++
CFLAGS11 = -Wall -g -std=c++11
#main directories variables
O=./.
E=./executables
S=./code
#project directories of sourceCode
PR= $(S)/private
PU=$(S)/public
V=$(Pu)/vendor
LE=$(V)/listeditor

#explains which clean operations can be used
clean:
        @echo -e "\nclean must be used as one of the following:"
        @echo -e "1: cleanA to run all clean comands"
        @echo -e "2: cleanO to remove all .o files"
        @echo -e "3: clean~ to remove all files that end with tilde"
        @echo -e "4: cleanP to remove all files that end with a numbersign"
        @echo -e ""
#removes all .o files only
cleanO:
        rm -f $(O)/*.o
#removes all files ending in ~ only
clean~:
        rm -f *~
        rm -f $(S)/*~
        rm -f $(PR)/*~
        rm -f $(PU)/*~
        rm -f $(V)/*~
        rm -f $(LE)/*~
#removes all files ending in #
cleanP:
        rm -f *#
        rm -f $(S)/*#
        rm -f $(PR)/*#
        rm -f $(PU)/*#
        rm -f $(V)/*#
        rm -f $(LE)/*#
#removes all files ending in .o, #, and ~
cleanA:
        make cleanO
        make clean~
        make cleanP

#SoccerProject
SoccerReg: $(O)/ui.o $(O)/ledge.o $(O)/player.o
        $(CC) $(CFLAGS11) -c $(O)/ui.o $(O)/ledge.o $(O)/player.o -o $(E)/SoccerReg
ledge.o: $(PR)/ledge.cpp $(PU)/ledge.h $(PU)/player.h
        $(CC) $(CFLAGS11) -c $(PR)/ledge.cpp -o $(O)/ledge.o
player.o: $(PR)/player.cpp $(PU)/player.h
        $(CC) $(CFLAGS11) -c $(PR)/player.cpp -o $(O)/player.o
ui.o: $(PR)/ui.cpp $(PU)/ledge.h $(PU)/player.h
        $(CC) $(CFLAGS11) -c $(PR)/ui.cpp -o $(O)/ui.o

