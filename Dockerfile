# syntax=docker/dockerfile:1


# Use the official GCC image as the base image
FROM gcc:latest

# Install required packages
RUN apt-get update && \
    apt-get install -y \
        cmake \
        sudo \
        clang-format \
        vim \
        zsh \
        gdb \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash swq && \
    echo 'swq:swq' | chpasswd

# Add 'swq' to the sudo group
RUN usermod -aG sudo swq

# Switch to the 'swq' user
USER swq

# Set the working directory to the user's home directory
WORKDIR /home/swq

# Set the default command to run when the container starts
CMD ["/bin/bash"]

