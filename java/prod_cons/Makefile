# define a makefile variable for java compiler
# 
JCC = javac
JAR = jar

# define a makefile variable for compilation flags
# the -g flag compiles with debugging information
#
JFLAGS = -g

# typing 'make' will invoke the first target entry in the makefile
#
default: Main.class Producer.class Consumer.class \
	     Product.class Storage.class

jar: Main.class Producer.class Consumer.class \
	 Product.class Storage.class manifest.mf
	$(JAR) cfm program.jar manifest.mf *.class 

Main.class: Main.java
	${JCC} $(JFLAGS) Main.java

Producer.class: Producer.java
	$(JCC) $(JFLAGS) Producer.java

Consumer.class: Consumer.java
	$(JCC) $(JFLAGS) Consumer.java

Product.class: Product.java
	$(JCC) $(JFLAGS) Product.java

Storage.class: Storage.java
	$(JCC) $(JFLAGS) Storage.java

clean:
	rm *.class *.jar
