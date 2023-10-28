FROM gcc:latest
WORKDIR /backrooms
COPY . /backrooms
RUN apt update
RUN apt-get -y install libsfml-dev
RUN make
ENTRYPOINT ["./bin/main"]