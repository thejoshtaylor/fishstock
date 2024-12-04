### Base environment container ###
# Get the base Ubuntu image from Docker Hub
FROM ubuntu:jammy AS base
ARG DEBIAN_FRONTEND=noninteractive

# Update the base image and install build environment
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake