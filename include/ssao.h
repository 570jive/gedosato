#pragma once

#include <dxgi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#include "effect.h"
#include "rendertarget.h"

class SSAO : public Effect {
public:
	enum Type { HBAO, VSSAO2, MSSAO, SAO };
	enum Blur { BLUR_GAUSSIAN, BLUR_SHARP };

	SSAO(IDirect3DDevice9 *device, int width, int height, unsigned strength, Type type, Blur blur, bool useSRGB, bool readHWDepth);
    virtual ~SSAO();

	void go(IDirect3DTexture9 *frame, IDirect3DTexture9 *depth, IDirect3DSurface9 *dst, bool scaleToCustomAR);
	void goHDR(IDirect3DTexture9 *frame, IDirect3DTexture9 *depth, IDirect3DSurface9 *dst, bool scaleToCustomAR);

	void dumpFrame();
	void reloadShader();

private:
	int width, height, dwidth, dheight;
	size_t blurPasses;
	bool dumping = false;
	unsigned strength;
	Type type;
	Blur blur;
	bool useSRGB, readHWDepth;

	ID3DXEffect *effect = NULL;
	
	RenderTargetPtr buffer1, buffer2, hdrBuffer, CSZBuffer;

	D3DXHANDLE depthTexHandle, frameTexHandle, prevPassTexHandle, noiseTexHandle, isBlurHorizontalHandle, projInfoHandle;
	
	void reconstructCSZPass(IDirect3DTexture9 *depth, IDirect3DSurface9* dst);
	void mainSsaoPass(IDirect3DTexture9 *depth, IDirect3DSurface9 *dst, bool scaleToCustomAR);
	void blurPass(IDirect3DTexture9 *depth, IDirect3DTexture9* src, IDirect3DSurface9* dst, bool horizontal);
	void combinePass(IDirect3DTexture9* frame, IDirect3DTexture9* ao, IDirect3DSurface9* dst);
};
