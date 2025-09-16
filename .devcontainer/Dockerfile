FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

USER root

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends libgtest-dev \
    protobuf-compiler \
    libprotobuf-dev