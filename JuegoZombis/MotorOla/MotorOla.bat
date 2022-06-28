::EJECUTAR CON "Developer Command Prompt for VS"

:::::::::: Limpiar Solución

:: ROOT\
rmdir /s /q Temp\

:: ROOT\Exes\
cd Exes\
del *.dll
del *.lib
del *.exp
del *.pdb
del *.exe
del *.ipdb
del *.iobj
del *.log
del ogre.cfg
cd ..

:: Ogre
rmdir /s /q Dependencies\Ogre\Build\

:: Lua
rmdir /s /q Dependencies\Lua\x64\

:: PhysX
cd Dependencies\PhysX-4.1\Src\physx\
call clean-min.bat
cd ..\..\..\..\

:: Mensaje
Echo __LIMPIADO__

:::::::::: Construir Dependencias

:: BUILD OGRE
cd Dependencies\Ogre
mkdir Build
cd Build

:: CMake hace la Build de Ogre
..\..\CMake\bin\cmake.exe -DOGRE_BUILD_COMPONENT_OVERLAY=TRUE -DOGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D11=FALSE -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=FALSE -DOGRE_BUILD_RENDERSYSTEM_GL=TRUE -DOGRE_BUILD_RENDERSYSTEM_GLES2=FALSE -DOGRE_BUILD_PLUGIN_ASSIMP=FALSE -DOGRE_BUILD_PLUGIN_BSP=FALSE -DOGRE_BUILD_PLUGIN_OCTREE=FALSE -DOGRE_BUILD_PLUGIN_DOT_SCENE=FALSE -DOGRE_BUILD_PLUGIN_PCZ=FALSE -DOGRE_BUILD_COMPONENT_TERRAIN=FALSE -DOGRE_BUILD_COMPONENT_VOLUME=FALSE -DOGRE_BUILD_COMPONENT_BITES=FALSE -DOGRE_BUILD_COMPONENT_PYTHON=FALSE -DOGRE_BUILD_COMPONENT_JAVA=FALSE -DOGRE_BUILD_COMPONENT_CSHARP=FALSE -DOGRE_INSTALL_CMAKE=FALSE -DOGRE_INSTALL_SAMPLES=FALSE -DOGRE_INSTALL_DOCS=FALSE -DOGRE_INSTALL_PDB=FALSE -DOGRE_INSTALL_VSPROPS=TRUE -DOGRE_BUILD_TOOLS=FALSE ../Src
..\..\CMake\bin\cmake.exe --build . --config release 

:: Se copian las dlls de Ogre
cd bin\release
copy /Y Codec_STBI.dll "../../../../../Exes/Codec_STBI.dll"
copy /Y OgreMain.dll "../../../../../Exes/OgreMain.dll"
copy /Y OgreMeshLodGenerator.dll "../../../../../Exes/OgreMeshLodGenerator.dll"
copy /Y OgreOverlay.dll "../../../../../Exes/OgreOverlay.dll"
copy /Y OgrePaging.dll "../../../../../Exes/OgrePaging.dll"
copy /Y OgreProperty.dll "../../../../../Exes/OgreProperty.dll"
copy /Y OgreRTShaderSystem.dll "../../../../../Exes/OgreRTShaderSystem.dll"
copy /Y Plugin_ParticleFX.dll "../../../../../Exes/Plugin_ParticleFX.dll"
copy /Y RenderSystem_GL.dll "../../../../../Exes/RenderSystem_GL.dll"
copy /Y SDL2.dll "../../../../../Exes/SDL2.dll"
copy /Y zlib.dll "../../../../../Exes/zlib.dll"

:: BUILD SDL (Dentro de Ogre)
cd ..\..\SDL2-build
..\..\..\CMake\bin\cmake.exe --build . --config release

:: FMOD (Copia de fmod.dll y fmodL.dll)
cd ..\..\..\FMOD\libreria\x64
copy /Y fmod.dll "../../../../Exes/fmod.dll"
copy /Y fmodL.dll "../../../../Exes/fmodL.dll"
cd ..\..\..\..\

:: BUILD PHYSX
cd Dependencies\PhysX-4.1\Src\physx\
call buildPhysX.bat
cd ..\..\..\..\

:: BUILD LUA
cd Dependencies\Lua
msbuild -p:Configuration=Release -noLogo -m

cd x64\Release
copy /Y Lua.dll "../../../../Exes/Lua.dll"
cd ..\..\..\..\

:: Mensaje
Echo __DEPENDENCIAS_CONSTRUIDAS__

:::::::::: Compilar motor

msbuild -p:Configuration=Release -noLogo -m

:: Mensaje
Echo __COMPILADO__
