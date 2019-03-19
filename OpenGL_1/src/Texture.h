#pragma once

#include "Renderer.h"

class Texture
{

private:
	unsigned int m_RendereID;
	std::string m_FilePath;
	//Local storage for our texture
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; //bits per pixel

public:
	Texture(const std::string& path);
	~Texture();

	//if we don't specify it it will be zero
	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};
