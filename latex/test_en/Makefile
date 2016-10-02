TEXFILE=test_en.tex
TEXOUT=test_en.pdf

all: pdf

pdf: ${TEXFILE}
	xelatex ${TEXFILE}

open: ${TEXOUT}
	gnome-open ${TEXOUT}

clean:
	rm -rf ${TEXOUT} *.aux *.log
