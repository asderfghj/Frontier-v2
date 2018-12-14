#include <memory>
#include <GL/glew.h>

namespace frontier
{
	class Shader;
	class RenderTexture;
	class Core;

	class RenderQuad
	{
	private:
		std::shared_ptr<Shader> m_attachedShader;
		std::shared_ptr<RenderTexture> m_attachedRenderTexture;
		GLuint m_VAO, m_vertVBO, m_texVBO;
		std::weak_ptr<Core> m_corePtr;
		float m_exposure = 0.2f, m_exposureIncrement = 0.0005f;
		bool m_useGamma = false, m_useHDR = false;

	public:
		void OnInit(std::weak_ptr<Core> _corePtr);
		void Draw();
		void AttachRendertexture(std::shared_ptr<RenderTexture> _renderTexture);
		void AttachShader(std::shared_ptr<Shader> _shader);
		void InfoDump();
	};
}