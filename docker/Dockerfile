### Build/test container ###
# Define builder stage
FROM fishstock:base AS builder

# Share work directory
COPY CMakeLists.txt /usr/src/project/CMakeLists.txt
COPY src /usr/src/project/src
COPY test /usr/src/project/test
WORKDIR /usr/src/project

# Build and test
RUN cmake .
RUN make -j$((`nproc`+1))
RUN make install
RUN ctest --output-on-failure

### Deploy container ###
# Define deploy stage
FROM ubuntu:jammy AS deploy

# Copy server output binary and configs "."
COPY --from=builder /usr/src/project/bin/fishstock .

# Expose some port(s)
EXPOSE 80

# Use ENTRYPOINT to specify the binary name
ENTRYPOINT ["./fishstock"]

# Default command
# CMD ["configs/therac_26.conf"]