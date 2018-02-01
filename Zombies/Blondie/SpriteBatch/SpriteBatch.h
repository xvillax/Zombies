#pragma once
#include <gl\glew.h>
#include "../Utils/VertexStruct.h"
#include <glm\glm.hpp>
#include <vector>

namespace BLONDIE
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};
	
	class Glyph
	{
	public:
		GLuint _terxture;
		GLfloat _depth;
		Vertex _topLeft;
		Vertex _bottomLeft;
		Vertex _topRight;
		Vertex _bottomRight;
	};

	class RenderBatch
	{
	public:
		GLuint _offset;
		GLuint _numVertices;
		GLuint _texture;

		RenderBatch(GLuint offest, GLuint numvertices, GLuint texture)
			:_offset(offest), _numVertices(numvertices), _texture(texture)
		{

		}

	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();
		void init();
		void Begin(GlyphSortType sorttype = GlyphSortType::TEXTURE);
		void End();
		void Draw(const glm::vec4& destrect, const glm::vec4& uvrect, GLuint texture, GLfloat depth, const Color& color);
		void renderBatch();

	private:
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();
	private:
		GLuint _Vbo;
		GLuint _Vao;
		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
		GlyphSortType _sortType;
	};
}
