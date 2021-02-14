FROM ubuntu:20.04

MAINTAINER Nasanjargal Bayanmunkh <nasanjargal.b@gmail.com>

ENV TZ=Asia/Ulaanbaatar
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN sed -i 's/archive.ubuntu.com/mn.archive.ubuntu.com/g' /etc/apt/sources.list

RUN echo "deb http://security.ubuntu.com/ubuntu xenial-security main" >> /etc/apt/sources.list && \
    apt-get update && apt-get install -y qt5-default libqt5script5 qtbase5-private-dev libssl1.0.0 libsqlite3-dev git gcc g++ make

RUN cd /root && git clone --recurse-submodules https://github.com/qt-labs/qthttpserver.git && \
    mkdir qthttpserver/build && cd qthttpserver/build && qmake ../qthttpserver.pro && make && make install

RUN rm -r /root/qthttpserver && apt-get purge -y qtbase5-private-dev git gcc g++ make
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

RUN useradd -rm -d /posapi -s /bin/bash -g root -G sudo -u 1001 posapi
USER posapi
WORKDIR /posapi

ADD posapi /posapi/posapi
ADD conf.ini /posapi/conf.ini
ADD run.sh /posapi/run.sh

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/posapi/lib

EXPOSE 8080
VOLUME /posapi/.vatps
VOLUME /posapi/lib

ENTRYPOINT ["sh","run.sh"]
