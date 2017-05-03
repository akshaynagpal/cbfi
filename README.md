# Coverage Based Fault Injection
Coverage based fault injection.
Added python wrapper


# Compiling coreutils-8.27
1. Unzip/uncompress coreutils-8.27.tar.xz into a folder
2. Rename folder to `coreutils`
3. `cd coreutils`
4. `./configure --prefix=/absolute/path/to/some/folder/`
5. `make`
6. `make check` - ensure no errors
7. `make install`
8. Coreutils executables will be in `/absolute/path/to/some/folder/bin`