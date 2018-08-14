# SendFile CoPy
This program is a simple Linux-based copy utility which hopes to leverage the
Linux kernel's ability (since version 2.6.33) to use the `sendfile` system call
to copy files.

## Usage
This program supports only the simple
```
sfcp <path_to_source> <path_to_destination>
```
It should work with any paths for which the user has appropriate permissions
(including remote file systems, external drives, etc.)

## Getting the code and compiling
To get most recent source code, clone the repository with
```
git clone https://github.com/cout-hello-world/sfcp.git
```
and
```
cd sfcp/
make
```

You can copy the resulting executable wherever you like.
Note that Linux 2.6.33 or greater, a compatible libc (such as glibc), and C11
support are required.
