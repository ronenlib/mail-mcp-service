# ---------- Stage 1: Build ----------
FROM gcc:15-bookworm AS builder

WORKDIR /workarea

COPY CMakeLists.txt .
COPY src/ src/

RUN apt-get update
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y cmake make

RUN cmake -B build -S . 
RUN cmake --build build -j

# ---------- Stage 2: Runtime ----------
FROM debian:bookworm-slim

WORKDIR /app

COPY --from=builder /workarea/build/mail_mcp_service /app/mail_mcp_service

EXPOSE 8080

ENTRYPOINT ["/app/mail_mcp_service"]
