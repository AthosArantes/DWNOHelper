# Digimon World Next Order Helper
A small helper for the game **Digimon World Next Order** (steam version)\
Only the official steam version is supported.\
Use at own risk.

## Features:
- Make digimons tell their remaining life span (press F1);
- Allow unrestricted ExE;

## How to use:
There are 2 ways to use the compiled helper dll:

- Using a dll injector (any basic injector will be enough, here is a simple open source:
[DLL-Injector](https://github.com/adamhlt/DLL-Injector));
- As as plugin for [BepInEx](https://docs.bepinex.dev/index.html);

### Using a dll injector:
Once compiled, simply inject the **DWNOHelper.dll**\
If using the suggested dll injector, put the dll and the ini file in the same directory of "inject.exe" and run:

    inject.exe "DWNOHelper.dll" "Digimon World Next Order.exe"

### Using a BepInEx plugin:
Make sure the [BepInEx](https://docs.bepinex.dev/index.html) is installed properly by following the link: [Installing BepInEx on Il2Cpp Unity](https://docs.bepinex.dev/master/articles/user_guide/installation/unity_il2cpp.html)

In addition to the DWNOHelper.dll, you'll also need to compile the **BepInExLoader** project;\
The loader is a simply a .NET dll that loads the actual helper library into the process.

Put the following files in ```<Digimon World Installation Directory>\BepInEx\plugins\``` folder:
- DWNOHelper.dll
- DWNOHelper.ini
- DWNOHelper.ManagedLoader.dll

## Libraries used:
[distormx](https://github.com/gdabah/distormx)\
[inireader](https://github.com/X-rays5/inireader)