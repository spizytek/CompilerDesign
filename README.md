To run the code, enter the following commands below (This has only been tested on Linux):

```
cmake --build /build
```
Navigate into the build directory:

```
cd build
```
Run run the Compiller to Compile `hydro.hy` file.
```
./hydro ../hydro.hy
```
After Compilation, execute the output file `out` by entering the command below:
```
./out
```
Basically, our program in `hydro.hy` returns 33, so after the command above, you should be to see 33 as the returned exist code when you run `echo $?`.
