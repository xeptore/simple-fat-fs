# Simple FAT FS

University project simple FAT File System Implementation.

## Usage

1. [Download](https://cmake.org/download/) and install CMake for your operating system from [its website](https://cmake.org/).
2. Clone/download project:

If you have installed [git](https://git-scm.com/) on your computer, execute following command:

```sh
git clone git@github.com:xeptore/simple-fat-fs.git
```

This will download the repository. Then you can navigate to project's root directory by executing following command:

```sh
cd simple-fat-fs
```

If you do not have _git_, you can download repository from [here](https://github.com/xeptore/simple-fat-fs/archive/main.zip). Then extract the archive file and navigate to project's root directory.

3. Install a compiler:

You can use any compiler you'd like, I personally prefer Clang, but you can use GCC if you'd like to.
To download Clang go to [its official website](https://releases.llvm.org/download.html) and download the correct compiler for your operating system.
If you are on Linux machine, you can install it, if it's not already installed, using your distribution package manager.

4. Run CMake in project's directory to generate `Makefile`

* Using command line:

```sh
cmake -S . -B build
```

If it throws error on failure to find compiler, change compiler path in CMakeLists.txt file via `CMAKE_C_COMPILER` variable value.

* Using Graphical User Interface (GUI):
<!-- TODO: Add screenshots -->

This will create a `build` subdirectory in project's root directory which contains files and directories alongside `Makefile`.
Execute following command to compile project:

```sh
make --directory=build
```

This command will generate `simple-fat` executable file in `build/` directory which is the main application executable, if succeeded.

## Testing

Alongside `simple-fat` executable file, there are other executables named in format `_test_<lib_name>`, e.g., `_test_fat` and `_test_directory`, which are testing executables and can be run separately from each other. Each one executes tests on its own library.

Also there are files in `src/` directory which are named in format `<lib_name>_test.c` that contain tests for `<lib_name>` library.
