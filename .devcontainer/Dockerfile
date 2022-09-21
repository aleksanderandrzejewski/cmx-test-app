FROM --platform=linux/amd64 centos/devtoolset-7-toolchain-centos7 as devcontainer
USER 0
RUN yum install -y --setopt=tsflags=nodocs epel-release && yum install -y --setopt=tsflags=nodocs git boost-devel cmake valgrind doxygen librdkafka-devel gtest cppcheck libtool autoconf && yum clean all -y
COPY cmw-cmx cmw-cmx
RUN cd cmw-cmx && autoreconf --force --install && ./configure && make && make install
USER 1001
