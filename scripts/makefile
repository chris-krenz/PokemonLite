# Use `make PokeLite' in scripts dir to compile from src dir to build dir

CC = g++
CFLAGS = -std=c++11 -g

# w/ makedepend uses '../inc/<header.hpp>' includes in .cpp
INCS = -I../inc
LFLAGS = 	# unused
LIBS = 		# unused

src_dir := ../src/
SRCS = $(wildcard $(src_dir)*.cpp)

obj_dir := ../build/objects/
# creates objs list by replacing dir and suffix in copy of srcs list
OBJS = $(addprefix $(obj_dir), $(notdir $(SRCS:.cpp=.o)))

ALL = ../build/PokeLite

.PHONY = clean depend		# protects against conflicts from files with these names
clean:		# run `make clean' to remove .o files in buld dir
		$(RM) $(obj_dir)*.o *~
depend: $(SRCS)		# creates dependencies based on .cpp includes & places at eof
		makedepend $(INCS) $^

# // Make targets and recipes //
PokeLite: $(ALL)
	@echo The C++ console game PokeLite has been compiled

$(ALL): $(OBJS)
		$(CC) $(CFLAGS) $(INCS) -o $(ALL) $(OBJS) $(LFLAGS) $(LIBS)

# uses suffix replacement to generate .o files
$(obj_dir)%.o: $(src_dir)%.cpp
		$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# DO NOT DELETE THIS LINE -- make depend depends on it. 
