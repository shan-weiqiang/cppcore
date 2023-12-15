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

### setup git branch view in cli ############
run echo "parse_git_branch() {" >> /home/swq/.bashrc \
    && echo "    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\\\1)/'" >> /home/swq/.bashrc \
    && echo "}" >> /home/swq/.bashrc \
    && echo "export PS1='\u@\h \[\e[32m\]\w \[\e[91m\]\$(parse_git_branch)\[\e[00m\]$ '" >> /home/swq/.bashrc

# Set the working directory to the user's home directory
WORKDIR /home/swq

# Set the default command to run when the container starts
CMD ["/bin/bash"]

