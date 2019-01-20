FROM ubuntu:18.04

RUN apt update && apt install build-essential qt5-default libqt5sql5-mysql gdb -y
