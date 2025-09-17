# Use Ubuntu as base image
FROM ubuntu:22.04

# Install build essentials and CMake
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Set working directory inside container
WORKDIR /app

# Copy project files into container
COPY . .

# Create build folder
RUN rm -rf build && mkdir build
RUN mkdir -p build

WORKDIR /app/build

# Run cmake and build
RUN cmake .. && make

# Default command to run the executable
CMD ["./snn"]
# Create a vscode user so devcontainers can attach
RUN useradd -ms /bin/bash vscode 
    

USER vscode
