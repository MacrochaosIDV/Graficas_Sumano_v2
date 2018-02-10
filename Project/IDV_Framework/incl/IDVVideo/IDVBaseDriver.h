#ifndef IDV_BASEDRIVER_H
#define IDV_BASEDRIVER_H

#include <string>
#include <vector>

enum Signature {
	// ATTRIBUTES
	HAS_NORMALS		= 0x1,
	HAS_TANGENTS	= 0x2,
	HAS_BINORMALS	= 0x4,
	HAS_TEXCOORDS0	= 0x8,
	HAS_TEXCOORDS1	= 0x10,

	// MAPS
	DIFFUSE_MAP		= 0x20,
	SPECULAR_MAP	= 0x40,
	GLOSS_MAP		= 0x80,
	NORMAL_MAP		= 0x100,
	REFLECT_MAP		= 0x200,
	HEIGHT_MAP		= 0x400,

	// CASES
	USE_NO_LIGHT	= 0x800
};

class ShaderBase {
public:
	ShaderBase() : Sig(0) {	}
	bool			CreateShader(std::string src_vs, std::string src_fs, unsigned int sig);
	virtual bool    CreateShaderAPI(std::string src_vs, std::string src_fs, unsigned int sig) = 0;

	unsigned int	Sig;
};

class BaseDriver {
public:
	enum {
		DEPTH_ATTACHMENT = -1,
		COLOR0_ATTACHMENT = 0,
		COLOR1_ATTACHMENT = 1,
		COLOR2_ATTACHMENT = 2,
		COLOR3_ATTACHMENT = 3,
		COLOR4_ATTACHMENT = 4,
		COLOR5_ATTACHMENT = 5,
		COLOR6_ATTACHMENT = 6,
		COLOR7_ATTACHMENT = 7,
	};
	BaseDriver() {  }
	virtual	void	 InitDriver() = 0;
	virtual void	 CreateSurfaces() = 0;
	virtual void	 DestroySurfaces() = 0;
	virtual void	 Update() = 0;
	virtual void	 DestroyDriver() = 0;
	virtual void	 SetWindow(void *window) = 0;
	virtual void	 SetDimensions(int,int) = 0;
	virtual void	 Clear() = 0;
	virtual void	 SwapBuffers() = 0;

	virtual int			CreateShader(std::string src_vs, std::string src_fs, unsigned int sig) = 0;
	virtual ShaderBase*	GetShaderSig(unsigned int sig) = 0;
	virtual ShaderBase*	GetShaderIdx(int id) = 0;
	virtual void		DestroyShaders() = 0;

	std::vector<ShaderBase*>	Shaders;
};


#ifndef GETDRIVERBASE
extern BaseDriver *g_pBaseDriver;
#define GETDRIVERBASE() g_pBaseDriver
#endif

#endif
