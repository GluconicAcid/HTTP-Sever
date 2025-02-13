# HTTP-Sever
# Basic HTTP Server in C++

## Overview
This project is a simple HTTP server written in C++ using **POSIX sockets**. It listens for incoming client connections, processes HTTP requests, and sends appropriate responses. The server currently supports **GET requests** and returns a basic text response.

## Features
- Implements a **TCP server** using **C++ and POSIX sockets**.
- Parses **basic HTTP requests** (method, path, and version).
- Responds to **GET requests** with a predefined message.
- Supports **multiple connections sequentially** (single-threaded).
- Uses `SO_REUSEADDR` to allow quick restarts after termination.

## Prerequisites
To compile and run the server, you need:
- A **Linux** or **Mac** environment (Windows users can use WSL or MinGW).
- A **C++ compiler** (GCC or Clang).

## Installation & Usage

### 1. Clone the Repository
```sh
git clone https://github.com/yourusername/http-server-cpp.git
cd http-server-cpp
```

### 2. Compile the Server
```sh
g++ -o server server.cpp -std=c++11
```

### 3. Run the Server
```sh
./server
```
The server will start and listen on port **8080**.

### 4. Test the Server
Open a web browser or use `curl` to send a request:
```sh
curl http://localhost:8080/
```
Expected response:
```
Basic HTTP ServerHTTP/1.1 200 OK
```

## Code Structure
- **server.cpp** - Contains the complete server implementation.
- **HttpRequest struct** - Parses the request method, path, and version.
- **parseRequestHandler()** - Extracts request details.
- **main()** - Handles socket creation, binding, listening, accepting connections, and responding to clients.

## Improvements & Future Work
To make this project more robust, consider adding:
✅ Multi-threading to handle multiple clients concurrently.
✅ Support for serving static files (HTML, CSS, JS).
✅ More HTTP methods like `POST` and `PUT`.
✅ Proper HTTP headers in responses.

## License
This project is open-source and available under the MIT License.

---

Feel free to contribute or modify the project as needed!

