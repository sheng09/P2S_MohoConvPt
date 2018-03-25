export BIN_DIR=../bin/

#SUBS = src py_src
SUBS = src
SUBS_make    = $(foreach sub, ${SUBS}, ${sub}.make)
SUBS_clean   = $(foreach sub, ${SUBS}, ${sub}.clean)
SUBS_install = $(foreach sub, ${SUBS}, ${sub}.install)

all:  ${SUBS_make}
	-mkdir bin
###
#  Sub Project
###
${SUBS_make}:%.make:%
	make -C $<

clean: ${SUBS_clean}
	-rm bin -r

${SUBS_clean}:%.clean:%
	-make -C $< clean

install: ${SUBS_install}

${SUBS_install}:%.install:%
	-make -C $< install
