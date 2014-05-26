javac HelloWorld.java
javah HelloWorld
g++ -I /usr/lib/jvm/jdk1.6.0_45/include -I /usr/lib/jvm/jdk1.6.0_45/include/linux -fPIC -shared -o libHelloWorld.so HelloWorld.cpp
