# sudo docker build -t my_test_repo:version_1 .
# REPOSITORY is my_test_repo
# TAG is version_1

FROM ubuntu

MAINTAINER Dongli Zhang

RUN echo "Hello World!"

ADD info.txt /info.txt

RUN cat /info.txt

ENV TEST_ENV_VAR "variable"

RUN echo "hello $TEST_ENV_VAR"

# The command to run by default
CMD "echo" "Hello docker!"
