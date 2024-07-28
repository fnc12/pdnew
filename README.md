# pdnew - CLI tool for creating new project for Playdate

Tired of creating new projects for Playdate by copying other template projects and modifying them? `pdnew` is what you need. Just type

`pdnew MyGame -l lua -a "Author Name" -b com.example.myGame` to create a new Lua project or

`pdnew MyGame -l c -a "Author Name" -b com.example.myGame` to create a new pure C project.

This tool creates a defeault folder structure, pdxinfo file, `CMakeLists.txt` (for pure C projects not Lua), sample title images.

## Available options:
- `-l|--language` - programming language of the project. Available values: `c` and `lua`. This option is required. `c` option creates CMake based project. `lua` option creates simple Lua project.
- `-d|--directory` - parent folder where project folder has to be located. Optional. If you omit this option `$PWD` is used instead. Please note that `pdnew` creates a new folder named `project-name` where `project-name` is the second argument located right after `pdnew`. If CLI call ran with no errors parent folder will contain a folder named just like the second command line argument. It means that parent folder is expected to exist if you decide to specify it explicitly. But project folder doesn't have to exist - it will be created by `pdnew`.
- `-b|--bundleId` - bundle ID of the project. Every Playdate project has its own unique bundle ID (just like any iOS and Android project as well) formatted as reverse DNS name (e.g. `com.example.myFancyGame`). You may specify bundle ID explicitly using this option or you can omit it. If you omit it you will be asked to input it. You may press enter to input empty field. In that case default value will be used. Default value is `com.example.project-name` where `project-name` is the second argument of CLI arguments.
- `-a|--author` - game author. This field is only required to be put in `pdxinfo` file. Just put your personal name or your team name. If you skip this option you will be promted to type it before generating.

## Tips
Once the project is generated you can work with it using your favourite IDE. Pure C project requires project generating using `cmake` utility first. To generate `cd` to your project directory after `pdnew` call, then run
- `mkdir build` - to create `build` folder where `cmake` is going to generate your project. This folder is added to `.gitignore` automatically by `pdnew` so don't need to worry this folder is going to corrupt your git index.
- `cd build` - to go to fresh folder.
- `cmake ..` - to generate a `make` project. This step can be modified is you want to use let's say Xcode or Visual Studio: `cmake -G Xcode ..` will generate Xcode project instead of raw `make` project. If you are intrested in this topic and want to know more - google/gpt 'cmake generators'.
- `cmake --build .` - to compile the project. Or just `make`. This command prouces `pdx` file in the project root directory. `*.pdx` is also added to `.gitignore` automatically by `pdnew`.

## Compiling `pdnew` from source
If you like `pdnew` and want to have it compiled just clone this repo

- `git clone git@github.com:fnc12/pdnew.git`.
- `cd pdnew` - to go to cloned folder.
- `mkdir build` - to create a folder for cmake generated project.
- `cd build` - to go to freshly created folder.
- `cmake ..` - to generate `pdnew` project.
- `make` - to compile `pdnew` project right on you operating system.
- `make install` - to install freshly compiled `pdnew` project system-wide.
Now you can use `pdnew` in your command line anywhere
