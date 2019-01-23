## List of subsystems
##### Note: This file can be automatically maintained #####
subsystem=builtin mysh

## List of Source files
sources+=Cd.c \
Exit.c \
Ls.c \
Pwd.c \
Executor.c \
Mysh.c \
Parser.c \
Reader.c \
Scanner.c

## The part below does not change across projects!
## Const Path Variable
src_path=$(proj_path)/source
sub_path=$(addprefix $(src_path)/, $(subsystem))

## Implicit Variable
VPATH+=$(src_path) $(sub_path)
CXXFLAGS+=-I $(src_path) 
