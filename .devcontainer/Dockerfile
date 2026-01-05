FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

# Install additional OS packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends libtbb-dev curl unzip build-essential gdb
