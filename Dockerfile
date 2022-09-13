FROM --platform=linux/amd64 centos/devtoolset-7-toolchain-centos7 as devcontainer
USER 0
RUN yum install -y --setopt=tsflags=nodocs epel-release && yum install -y --setopt=tsflags=nodocs git boost-devel cmake valgrind doxygen librdkafka-devel gtest cppcheck libtool autoconf && yum clean all -y
COPY .devcontainer/cmw-cmx cmw-cmx
RUN cd cmw-cmx && autoreconf --force --install && ./configure && make && make install
USER 1001

FROM --platform=linux/amd64 devcontainer as build
USER 0
COPY src ./src
RUN mkdir build && cd build && cmake ../src && make
USER 1001

FROM --platform=linux/amd64 centos:centos7 as run
COPY --from=build /usr/local/ /usr/local/
COPY --from=build /opt/app-root/src/cmw-cmx/tools/cmw-cmx-reader /opt/app-root/src/cmw-cmx/tools/cmw-cmx-dumper /opt/app-root/src/cmw-cmx/tools/cmw-cmx-control ./
COPY --from=build /opt/app-root/src/build/main ./main
CMD ["./main"]
