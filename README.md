# cpp-template
Template repository containing my preferred Makefile. It expects:

	a /src subdirectory contains source codes, possibly organized into other subdirectories

When a user runs "make", the Makefile searches /src for files with a given extension (.cpp by default). It determines whether a source file should be compiled into an executable by the presence of a "main" function (searches the verbatim string "int main") to organize dependency of object compilation

After it does this, it calls "rm -rf" on the following to subdirectories and rebuilds them with the appropriate files:

	a /bld subdirecotry containing object files
	a /exe subdirectory containing fully compiled executables

The substructure of the /bld and /exe subdirectories mimics the structure of /src; that is, object and executable files are named with the path relative to /src for each source file, so further subdirectories are created.
