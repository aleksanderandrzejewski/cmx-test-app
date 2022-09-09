FROM centos/devtoolset-7-toolchain-centos7

USER 0
RUN yum install -y --setopt=tsflags=nodocs epel-release && yum install -y --setopt=tsflags=nodocs git boost-devel cmake valgrind doxygen librdkafka-devel gtest cppcheck libtool autoconf && yum clean all -y
RUN git clone https://gitlab.cern.ch/cmx/cmw-cmx.git && cd cmw-cmx && autoreconf --force --install && ./configure && make && make install
USER 1001
