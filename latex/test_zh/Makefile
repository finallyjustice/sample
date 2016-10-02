TEXFILE=test_zh.tex
TEXOUT=test_zh.pdf

all: pdf

pdf: ${TEXFILE}
	xelatex ${TEXFILE}

open: ${TEXOUT}
	gnome-open ${TEXOUT}

clean:
	rm -rf ${TEXOUT} *.aux *.log
