FROM ubuntu:22.04

WORKDIR /ws

RUN apt update && \
	apt install -y \
	git \
	cmake \
	g++ \
	qt6-base-dev \
	build-essential \
	libgl1-mesa-dev

RUN git clone --recursive https://github.com/wojciechmadry/cpu6502emulator.git && \
	mkdir -p cpu6502emulator/build

RUN cd cpu6502emulator/build && \
	cmake .. && \
	cmake --build . -j

