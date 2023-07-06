![reNamerLogo](https://github.com/AleMatGra/reNamer/assets/116359958/a0f9bba3-5482-452f-b6d4-8a5bbc1b4eb8)

# Introduction

One of my old projects, this is meant to be a "mobile" '.exe'.

You can move the reNamer.exe in any directory and execute it.

It will generate a "reNamerConfig.txt".

In there, you can set up what it is supposed to rename.

After executing again, it will rename all the files in the same directory, depending on the config / settings.

Then you can delete it or move it to the next directory.

# What can it do? How does it operate?

## Config setup:
- one extension will be defined in the config file (e.g., '.jpg')
- it can remove a specific amount of characters from the end of the name
- you can define pairs of strings, the left one will be replaced by the right one if they occur
- remove a list of keywords
- replace specific characters with a defined replacement-character (default is ' ')
- remove specific characters

When you execute reNamer, all files with the defined extension will be renamed according to the config (order as described above).

## Settings:
- auto delete the config file (makes cleanup easier)
- enable logging (recommended for the first time using it), generates log with all the renaming that has been done
- enable print to console
- enable to place a safety stop, so you can't accidentally run it twice

# using/changing it

If you trust me you can run the .exe from this repo, if not you can re-compile the code.

If you want to change the settings permanently, they are set in the constructor of reNamer.
