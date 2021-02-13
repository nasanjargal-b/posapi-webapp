FROM ubuntu:20.04

MAINTAINER Nasanjargal Bayanmunkh <nasanjargal@monsource.mn>

WORKDIR app

RUN mkdir -p /app

ADD posapi /app/posapi
ADD webapp.ini /app/webapp.ini
ADD run.sh /app/run.sh

ENV TZ=Asia/Ulaanbaatar
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN echo "deb http://security.ubuntu.com/ubuntu xenial-security main" >> /etc/apt/sources.list && \
    apt-get update && apt-get install -y qt5-default libqt5script5 qtbase5-private-dev libssl1.0.0 libsqlite3-dev git gcc g++ make

RUN cd /app && git clone --recurse-submodules https://github.com/qt-labs/qthttpserver.git && \
    mkdir qthttpserver/build && cd qthttpserver/build && qmake ../qthttpserver.pro && make && make install

RUN rm -r /app/qthttpserver && apt-get purge -y qtbase5-private-dev git gcc g++ make
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*

ENTRYPOINT ["sh","run.sh"]
