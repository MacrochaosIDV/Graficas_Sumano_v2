#include <IDVVideo/IDVBaseDriver.h>

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

BaseDriver*	g_pBaseDriver = 0;


bool ShaderBase::CreateShader(std::string src_vs, std::string src_fs, unsigned int sig) {

	std::string Defines = "";

	bool LinearDepth = true;

	#if VDEBUG_NO_LIGHT
	Defines += "#define NO_LIGHT\n\n";
	#endif

	if (sig&Signature::HAS_NORMALS)
		Defines += "#define USE_NORMALS\n\n";
	if (sig&Signature::HAS_TEXCOORDS0)
		Defines += "#define USE_TEXCOORD0\n\n";
	if (sig&Signature::HAS_TEXCOORDS1)
		Defines += "#define USE_TEXCOORD1\n\n";
	if (sig&Signature::HAS_TANGENTS)
		Defines += "#define USE_TANGENTS\n\n";
	if (sig&Signature::HAS_BINORMALS)
		Defines += "#define USE_BINORMALS\n\n";
	if (sig&Signature::DIFFUSE_MAP)
		Defines += "#define DIFFUSE_MAP\n\n";
	if (sig&Signature::SPECULAR_MAP)
		Defines += "#define SPECULAR_MAP\n\n";
	if (sig&Signature::GLOSS_MAP)
		Defines += "#define GLOSS_MAP\n\n";
	if (sig&Signature::NORMAL_MAP)
		Defines += "#define NORMAL_MAP\n\n";
	if (sig&Signature::REFLECT_MAP)
		Defines += "#define REFLECT_MAP\n\n";
	
	
	Defines += "#define lowp \n\n";
	Defines += "#define mediump \n\n";
	Defines += "#define highp \n\n";


//	cout << "Compiling with the following signature[ " << Defines << endl << "]" << endl;

	src_vs = Defines + src_vs;
	src_fs = Defines + src_fs;
	this->Sig = sig;
	return CreateShaderAPI(src_vs, src_fs, sig);
}
