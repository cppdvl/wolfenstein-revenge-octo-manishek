
// A definition of a texte renderer, using opengl. 


namespace DGE::Type
{
	using Color = glm::vec4;
	using Color3 = glm::vec3;
	using Position2D = glm::vec2;
	using Position = glm::vec3;
	using Size = glm::vec2;
	using Size3 = glm::vec3;
	using Rotation = glm::vec3;
	using Scale = glm::vec3;
	using Matrix = glm::mat4;
	using Matrix3 = glm::mat3;
	using Matrix2 = glm::mat2;
	using Vector2 = glm::vec2;
	using Vector = glm::vec3;
	using String = std::string; 
	using Int32 = int32_t;
	using Int64 = int64_t;
	using UInt32 = uint32_t;
	using UInt64 = uint64_t;
	using Float = float;
	using Double = double;
	using Bool = bool;
	using Char = char;
	using Byte = uint8_t;
	using RendererID = uint32_t;
	

}	
	

using namespace DGE::Type;
namespace System::Renderer
{
	class Renderable
	{
		public:
			virtual void Render() = 0;
		protected:
			UInt32 mVAO;
			UInt32 mVBO;
			RendererID mRendererID;
			Matrix mProjectionMatrix;
			Position mPosition;


	}
	class Text : public Renderable
	{
		public:
			TextRenderer(const String& text, const String& font, Color& color, Int32 fontsize, RendererID id);
			~TextRenderer();

			void Render();
			void SetText(const String& text);
			void SetPosition(Position2D& position);
		private:
			String m_text;
			String m_font;
			Color m_color;
			Int32 m_fontsize;
			Position2D m_position;
			RenderID m_id;

	};
}

