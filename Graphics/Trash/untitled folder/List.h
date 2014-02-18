////
////  List.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 4/30/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__List__
//#define __EonilGraphics__List__
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		template<typename T>
//		class
//		List
//		{
//		public:
//			class
//			Slot
//			{
//			public:
//				Slot(List<T> const& list, T const& value);
//				
//				bool			isValid() const;
//				
//				T const&		value() const;
//				List<T> const&	list() const;
//				Slot const		firstSlot() const;
//				Slot const		previousSlot() const;							//	An exception if current slot is first.
//				Slot const		nextSlot() const;								//	An exception if current slot is last.
//				Slot const		lastSlot() const;
//				
//			public:
//				T&				mutableValue();
//				List<T>&		mutableList();
//				Slot&			push();										//	Pushes a new slot at current slot position.
//				void			pop();										//	Pops current slot from the list. Current slot becomes invalid.
//				
//			private:
//				bool			_isvalid;
//				List<T>&		_listref;
//				T& 				_valref;
//			};
//			
//		public:
//			List(std::vector<T> const source);								//	Semantically copies the object. C++ compiler may optimize out copying by case.
//			std::vector<T> const&	asStandardVector() const;
//			
//		public:
//			T const&	operator[](Size const index) const;
//			
//		public:
//			Size const	count() const;
//			bool const	containsObject(T const& object) const;
//			Size const	indexForObject(T const& object) const;
//			
//			Slot const	slotAtIndex(Size const index) const;				//	Performs value equality search.
//			Slot const	slotByObject(T const& object) const;				//	Performs pointer equality search.
//			Slot const	slotOfObject(T const& object) const;
//			Slot const	firstSlot() const;
//			Slot const	lastSlot() const;
////			T const&	objectEqualsToObject(T const& object) const;		//	Look for an equal object by value equality in this list and return reference to it. Performs linear search. O(1).
//			
////			T const&	objectWithOffsetFromFirst(Size const offset) const;
////			T const&	objectWithOffsetFromLast(Size const offset) const;
//			T const&	firstObject() const;
//			T const&	lastObject() const;
//			
//		public:
//			T&			operator[](Size const index);
////			T&			mutableObjectForObject(T const& object) const;
//			
//			void	add(T const& object);									//	Semantically copies the object. C++ compiler may optimize out copying by case.
////			void	addAll(List<T> const list);
//			void	addAt(T const& object, Size const index);				//	Semantically copies the object. C++ compiler may optimize out copying by case.
//			
//			void	remove(T const& object);
////			void	removeAll(List<T> const list);
//			void	removeAt(T const& object, Size const index);
//			
//		private:
//			std::vector<T>	_vec;
//		};
//	}
//}
//
//#endif /* defined(__EonilGraphics__List__) */
