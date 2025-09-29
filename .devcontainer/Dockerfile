FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

USER root

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends libgtest-dev cmake \
    protobuf-compiler \
    libprotobuf-dev \
    && cmake -S /usr/src/googletest -B /tmp/build-gtest -DBUILD_GMOCK=OFF -DBUILD_GTEST=ON \
    && cmake --build /tmp/build-gtest --config Release \
    && find /tmp/build-gtest -name "libgtest*.a" -exec cp {} /usr/local/lib/ \; \
    && ldconfig