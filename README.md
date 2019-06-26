Game Engine
------------------
### Build Status

Windows:
[![Build status](https://ci.appveyor.com/api/projects/status/8390s6ladpv4mjsa/branch/master?svg=true)](https://ci.appveyor.com/project/furkandinc52995/engine/branch/master)

### Requirements
- Visual Studio 2017 with the packages below
	1. Desktop development with C++ (Default pack)
	2. Windows10 Sdk 10.0.17134.0
	3. The builds tools for v140
	These packages can be downloaded via Visual Studio Installer

### Compiling
Select "Release | x86 (32bit)" mode from the upper panel.
Set startup project to the project you want to compile.
Execute compile event.
Not: If external libraries are missing, open NuGet Package Manager then restore the libraries.

### Executing
Test games are available to execute (Engine project produces non-executable library files). There are two ways to execute.
Using debugger: After setting the startup project, push the local windows debugger button from the upper panel.
Executing from exe: Start the {GameName}.exe file at the {BaseDirectory}/Release.

## Contributing
Commiting to master branch is not allowed. You should create branch named "issue #[issue-number] [issue-header]" and pull request.