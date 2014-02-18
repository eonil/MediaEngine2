////
////  Presentation.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/3/13.
////
////
//
//#ifndef __EonilGraphics__Presentation__
//#define __EonilGraphics__Presentation__
//
//#include "Transform.h"
//#include "Server/Machine.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		class
//		Presentation
//		{
//		public:
//			class
//			Source
//			{
//			public:
//				struct
//				Type
//				{
//					enum
//					CODE : decltype(sizeof(void*))
//					{
//						SKELETAL_FIGURE,
//						PARTICLE_CLOUD,
//					};
//					
//					Type()	=	delete;
//					~Type()	=	delete;
//				};
//				
//				Type::CODE const	type() const;
//				void				setType(Type::CODE const code);
//				
//				
//			private:
//				Type::CODE			_tc;
//			};
//			
//			Transform const		transform() const;
//			void				setTransform(Transform const t);
//			
//			Source const&		source() const;
//			void				setSource(Source const& s);
//			
//		protected:
////			virtual void		renderOnMachine(Graphics::Server::Machine const& machine) const = 0;	//	Cannot change any state of machine and this
//			
//		private:
//			Transform			_t;
//			Source				_src;
//			
//			friend class		Renderer;
//		};
//		
//		class
//		SkeletalFigure : public Presentation::Source
//		{
//		public:
//		private:
//		};
//		
//		class
//		ParticleCloud : public Presentation::Source
//		{	
//		};
//		
//	}
//}
//
//#endif /* defined(__EonilGraphics__Presentation__) */
