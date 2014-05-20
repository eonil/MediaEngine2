////
////  Material.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/13/13.
////
////
//
//#ifndef __EonilGraphics__Material__
//#define __EonilGraphics__Material__
//
//#include "../Server/Texture.h"
//#include "../Server/Program.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		namespace
//		Resource
//		{
//			using namespace	Server;
//			
////			
////			class
////			SkinningMaterialMixin;
////			
////			class
////			OpaqueColorTextureMixin;
////			
////			class
////			TransparentColorTextureMixin;
////			
////			class
////			ToonLightingMixin;
//			
//			
//			/*!
//			 Materials will be generator by Space+Editor tool by subclassing this class.
//			 */
//			class
//			Material
//			{
//			protected:
//				Material(Program const p);
//				Program const&		program() const;
//			private:
//				Program	_p;
//			};
//
//			class
//			UnlitOpaqueColorMaterial : public Material
//			{
//			public:
//				UnlitOpaqueColorMaterial();
//				
//				PlanarTexture const&	texture() const;
//				void					setTexture(PlanarTexture const& texture);
//	
//			private:
//				PlanarTexture			_t;
//			};
//			
//			
//			
//			class
//			UnlitTransparentColorMaterial;
//			
//			/*!
//			 Toon shading + opaque color texture
//			 */
//			class
//			ToonLightingColorMaterial;
//		}
//	}
//}
//
//#endif /* defined(__EonilGraphics__Material__) */
//
//
//
//
//
//
//
//
//
//
//
