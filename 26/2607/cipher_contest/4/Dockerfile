FROM python:3.11-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
git \
wget \
curl \
vim \
nano \
tree \
ripgrep \
jq \
file \
binutils \
unzip \
zip \
p7zip-full \
tmux \
htop \
build-essential \
&& rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["/bin/bash"]
