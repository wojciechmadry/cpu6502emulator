FROM ubuntu:22.04

WORKDIR /ws

RUN apt update

RUN apt install -y git cmake g++ qt6-base-dev build-essential libgl1-mesa-dev

RUN git clone https://github.com/wojciechmadry/cpu6502emulator.git

RUN cd cpu6502emulator && git submodule init && git submodule update
