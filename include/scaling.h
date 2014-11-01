#pragma once

#include <dxgi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <vector>

#include "effect.h"
#include "rendertarget.h"

class Scaler : public Effect {
public:
	typedef enum { NEAREST, BILINEAR, BICUBIC, LANCZOS, STYPE_END } scalingType;
	
	Scaler(IDirect3DDevice9 *device, int inputwidth, int inputheight, int width, int height, bool useSRGB = false);
    virtual ~Scaler();

	void go(IDirect3DTexture9 *input, IDirect3DSurface9 *dst);

	void setScaling(scalingType t);
	void nextScaling();

	void showStatus();
	void reloadShader();

private:
	bool useSRGB;
	int inputwidth, inputheight, width, height;
	scalingType sType;

	ID3DXEffect *effect = NULL;
	
	D3DXHANDLE frameTexHandle;
	D3DXHANDLE inputSizeHandle;
	
	unsigned levels;
	std::vector<RenderTargetPtr> levelBuffers;
	FLOAT *levelInputSizes;

	string status;

	const char* getScalingName();
	void aspectQuad();
};
