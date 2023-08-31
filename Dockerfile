FROM ubuntu:latest

RUN apt-get update \
# gitlab-runner dependencies
&& apt-get install -y --no-install-recommends git curl tar ca-certificates \
# Python + clang-format
&& apt-get install -y  g++ libtinyxml2-dev rustc rustfmt cmake \

&& cmake --version \
# cleanup
&& rm -rf /var/lib/apt/lists/*

