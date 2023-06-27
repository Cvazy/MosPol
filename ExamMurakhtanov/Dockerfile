FROM ubuntu

LABEL author="Murakhtanov221-332"

RUN apt-get update && apt-get install -y g++

RUN mkdir /MyProj_Murakhtanov221-332

COPY . /MyProj_Murakhtanov221-332

WORKDIR /MyProj_Murakhtanov221-332

RUN g++ -o my_Program main.cpp

CMD ["./my_Program"]
