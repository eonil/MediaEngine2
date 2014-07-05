//
//  Markdown.cpp
//  Aliens
//
//  Created by Hoon H. on 14/4/27.
//
//

#include "Markdown.h"

#include <string>

EONIL_ALIENS_NAMESPACE_BEGIN


extern "C"
{
#include "../../../Discount/Sources/mkdio.h"
}


namespace
{
	/*!
	 @exception
	 Strong exception guarantee. No state corruption on any exception.
	 */
	class
	MKD final
	{
		MMIOT*		_doc			{NULL};
		
		struct
		{
			bool	toc_enabled		{false};
			bool	compiled		{false};
		}
		_state_flags		{};
		
		static auto
		_fail() -> void
		{
			throw	Markdown::Exception("Cannot perform the operation.");
		}
		static auto
		_always_assert(bool const cond) -> void
		{
			if (not cond)
			{
				_fail();
			}
		}
		
	public:
		enum class
		FLAG : mkd_flag_t
		{
			DEFAULT		=	0,
			NOLINK		=	MKD_NOLINKS,
			TOC			=	MKD_TOC,
		};
	public:
		MKD(std::string const& text)
		{
			EONIL_ALIENS_DEBUG_ASSERT(text.size() <= std::numeric_limits<int>::max());
			
			unsigned int	flags1		=	0;
			
			_doc	=	mkd_string(text.data(), int(text.size()), flags1);
			
			_always_assert(_doc != NULL);
		}
		~MKD()
		{
			mkd_cleanup(_doc);
			_doc	=	NULL;
		}
		
		auto
		compile(std::vector<FLAG> const& options) -> void
		{
			_always_assert(_doc != NULL);
			
			////
			
			mkd_flag_t	f1	=	0;
			for (auto const& opt1: options)
			{
				f1	|=	mkd_flag_t(opt1);
			}
			
			_state_flags.toc_enabled	=	(f1 & MKD_TOC) == MKD_TOC;
			
			////
			
			auto	r1		=	mkd_compile(_doc, f1);		//	Returns 1 for success. See the source code.
			_always_assert(r1 == 1);
			
			_state_flags.compiled		=	true;
		}
		auto
		toc() -> std::string
		{
			_always_assert(_state_flags.toc_enabled);
			_always_assert(_state_flags.compiled);
			
			////
			
			char*	toc1	=	NULL;
			auto	r1		=	mkd_toc(_doc, &toc1);
			_always_assert(r1 > 0);
			size_t	len1	=	r1;
			
			////
			
			std::string	html2	{toc1, len1};
			return		html2;
		}
		auto
		document() -> std::string
		{
			_always_assert(_state_flags.compiled);
			
			////
			
			char*	html1	=	NULL;
			auto	r1		=	mkd_document(_doc, &html1);
			size_t	len1	=	r1;

			////
			
			std::string	html2	{html1, len1};
			return		html2;
		}
	};
}


auto
Markdown::process(const std::string &text) -> std::string
{
	MKD						mkd1	{text};
	std::vector<MKD::FLAG>	opts1
	{
		MKD::FLAG::DEFAULT,
//		MKD::FLAG::TOC,
	};
	
	mkd1.compile(opts1);
	
	return	mkd1.document();
}









EONIL_ALIENS_NAMESPACE_END