#include "SpriteBatch.h"
#include <algorithm>


namespace BLONDIE
{
	SpriteBatch::SpriteBatch()
		:_Vbo(0),
		 _Vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init()
	{
		createVertexArray();

	}

	void SpriteBatch::Begin(GlyphSortType sorttype /* GlyphSortType::TEXTURE*/)
	{
		_sortType = sorttype;
		_renderBatches.clear();

		for (GLuint i = 0; i < _glyphs.size(); i++)
			delete _glyphs[i];

		_glyphs.clear();
	}

	void SpriteBatch::End()
	{
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront );
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack );
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture );
			break;
		}
		
	}

	void SpriteBatch::Draw(const glm::vec4& destrect, const glm::vec4& uvrect, GLuint texture, GLfloat depth, const Color& color)
	{
		Glyph*   newGlyph = new Glyph;
		newGlyph->_terxture = texture;
		newGlyph->_depth = depth;
				
		newGlyph->_topLeft.color = color;
		newGlyph->_topLeft.setPosition(destrect.x, destrect.y + destrect.w);
		newGlyph->_topLeft.setUV(uvrect.x, uvrect.y + uvrect.w);
				
		newGlyph->_bottomLeft.color = color;
		newGlyph->_bottomLeft.setPosition(destrect.x, destrect.y );
		newGlyph->_bottomLeft.setUV(uvrect.x, uvrect.y );
				
		newGlyph->_bottomRight.color = color;
		newGlyph->_bottomRight.setPosition(destrect.x + destrect.z, destrect.y );
		newGlyph->_bottomRight.setUV(uvrect.x + uvrect.z, uvrect.y );
				
		newGlyph->_topRight.color = color;
		newGlyph->_topRight.setPosition(destrect.x + destrect.z, destrect.y + destrect.w);
		newGlyph->_topRight.setUV(uvrect.x + uvrect.z, uvrect.y + uvrect.w);

		_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(_Vao);
		for (GLuint i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i]._texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i]._offset, _renderBatches[i]._numVertices);

		}
		glBindVertexArray(0);
		
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty())
			return;
		GLint cv = 0; // current vertex
		GLint offset = 0;
		_renderBatches.emplace_back(offset, 6, _glyphs[0]->_terxture);
		vertices[cv++] = _glyphs[0]->_topLeft;
		vertices[cv++] = _glyphs[0]->_bottomLeft;
		vertices[cv++] = _glyphs[0]->_bottomRight;
		vertices[cv++] = _glyphs[0]->_bottomRight;
		vertices[cv++] = _glyphs[0]->_topRight;
		vertices[cv++] = _glyphs[0]->_topLeft;
		offset += 6;

		for (GLuint cg = 1; cg < _glyphs.size(); cg++)
		{
			if (_glyphs[cg]->_terxture != _glyphs[cg - 1]->_terxture )
				_renderBatches.emplace_back(offset, 6, _glyphs[cg]->_terxture);
			else
				_renderBatches.back()._numVertices += 6;

			vertices[cv++] = _glyphs[cg]->_topLeft;
			vertices[cv++] = _glyphs[cg]->_bottomLeft;
			vertices[cv++] = _glyphs[cg]->_bottomRight;
			vertices[cv++] = _glyphs[cg]->_bottomRight;
			vertices[cv++] = _glyphs[cg]->_topRight;
			vertices[cv++] = _glyphs[cg]->_topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
		//clear buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//new buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data() );
		//release buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	bool SpriteBatch::compareFrontToBack(Glyph * a, Glyph * b)
	{
		return (a->_depth < b->_depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph * a, Glyph * b)
	{
		return (a->_depth > b->_depth);
	}

	bool SpriteBatch::compareTexture(Glyph * a, Glyph * b)
	{
		return (a->_terxture < b->_terxture);
	}


	void SpriteBatch::createVertexArray()
	{
		if (_Vao == 0)
			glGenVertexArrays(1, &_Vao);

		glBindVertexArray(_Vao);

		if (_Vbo == 0)
			glGenBuffers(1, &_Vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _Vbo);

		// tell opengl we want to use the first attribute array
			glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//point opengl to our vboID for position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//point opengl to our vboID for color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}


}