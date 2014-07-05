//
//  TestSuite3.cpp
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 5/3/14.
//
//

#include "TestSuite3.h"

using namespace	Eonil::CommonRealtimeGameAlgorithms;
using namespace	Eonil::CommonRealtimeGameAlgorithms::DataStructures;
using namespace	Eonil::CommonRealtimeGameAlgorithms::GenericUtilities;
using namespace	Eonil::CommonRealtimeGameAlgorithms::FlatContainers;













inline auto
test_tree1() -> void
{
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		
		n1.setNext(&n2);
		test_assert(n1.next() == &n2);
		test_assert(n2.prior() == &n1);
		
		n1.unsetNext();
		test_assert(n1.next() == nullptr);
		test_assert(n2.prior() == nullptr);
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		
		n1.setPrior(&n2);
		test_assert(n2.next() == &n1);
		test_assert(n1.prior() == &n2);
		
		n1.unsetPrior();
		test_assert(n1.next() == nullptr);
		test_assert(n2.prior() == nullptr);
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		
		n1.setParent(&n2);
		test_assert(n1.parent() == &n2);
		
		TreeNode*	ptr1	=	&*n2.children().begin();
		test_assert(ptr1 == &n1);
		
		n1.unsetParent();
		test_assert(n1.parent() == nullptr);
		test_assert(&*n2.children().begin() == nullptr);
		test_assert(&*n2.children().end() == nullptr);
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		n1.setNext(&n2);
		n2.setNext(&n3);
		TreeNodeRange<false>	rr{&n1, &n3};
		std::vector<TreeNode*>	nodes{};
		for (TreeNode& node: rr)
		{
			nodes.push_back(&node);
		}
		test_assert(nodes.size() == 3);
		test_assert(nodes.at(0) == &n1);
		test_assert(nodes.at(1) == &n2);
		test_assert(nodes.at(2) == &n3);
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		n1.setNext(&n2);
		TreeNodeRange<false>	rr{&n1, &n2};
		n3.setChildren(rr);
		test_assert(n1.parent() == &n3);
		test_assert(n2.parent() == &n3);
		test_assert(&*n3.children().begin() == &n1);

		std::vector<TreeNode*>	nodes{};
		for (TreeNode& node: n3.children())
		{
			nodes.push_back(&node);
		}
		test_assert(nodes.size() == 2);
		test_assert(nodes.at(0) == &n1);
		test_assert(nodes.at(1) == &n2);
	}
	
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		test_assert_always_exception([&](){ n1.setNext(&n1); });
		test_assert(n1.next() == nullptr);
		
		n1.setNext(&n2);
		test_assert(n1.next() == &n2);
		
		n2.setNext(&n3);
		test_assert(n2.next() == &n3);
		test_assert_always_exception([&](){ n3.setNext(&n1); });
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		test_assert_always_exception([&](){ n1.setPrior(&n1); });
		test_assert(n1.prior() == nullptr);
		
		n1.setPrior(&n2);
		test_assert(n1.prior() == &n2);
		
		n2.setPrior(&n3);
		test_assert(n2.prior() == &n3);
		test_assert_always_exception([&](){ n3.setPrior(&n1); });
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		test_assert_always_exception([&](){ n1.setParent(&n1); });
		test_assert(n1.parent() == nullptr);
		
		n1.setParent(&n2);
		test_assert(n1.parent() == &n2);
		
		n2.setParent(&n3);
		test_assert(n2.parent() == &n3);
		test_assert_always_exception([&](){ n3.setParent(&n1); });
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		test_assert_always_exception([&](){ n1.setChildren({&n2, &n3}); });
		n2.setNext(&n3);
		n1.setChildren({&n2, &n3});
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		n1.setNext(&n2);
		test_assert_always_exception([&](){ n1.setParent(&n3); });
		test_assert(n1.parent() == nullptr);
		test_assert(&*n3.children().begin() == nullptr);
		test_assert(&*n3.children().end() == nullptr);
		test_assert(n2.parent() == nullptr);
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		n1.setParent(&n3);
		n1.setNext(&n2);
		test_assert(n2.parent() == &n3);
	}
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		n2.setParent(&n1);
		n2.setNext(&n3);
		
		std::vector<TreeNode const*>	ptrs	{};
		for (TreeNode const& a2: n1.children())
		{
			ptrs.push_back(&a2);
		}
		test_assert(ptrs.size() == 2);
		test_assert(ptrs.at(0) == &n2);
		test_assert(ptrs.at(1) == &n3);
	}
	
	{
		TreeNode	n1	{};
		TreeNode	n2	{};
		TreeNode	n3	{};
		
		n2.setParent(&n1);
		n2.setPrior(&n3);
		
		std::vector<TreeNode const*>	ptrs	{};
		for (TreeNode const& a2: n1.children())
		{
			ptrs.push_back(&a2);
		}
		test_assert(ptrs.size() == 2);
		test_assert(ptrs.at(0) == &n3);
		test_assert(ptrs.at(1) == &n2);
	}
	
}






inline auto
test_tree2() -> void
{
	{
		struct
		TestTreeNode1 : public GenericTreeNode<TestTreeNode1>
		{
			std::string		string1		=	"AAA";
		};
		
		using	TTN	=	TestTreeNode1;
		
		TTN	n1	{};
		
		test_assert(n1.string1 == "AAA");
		
		TTN	n2	{};
		TTN	n3	{};
		
		n2.setParent(&n1);
		n2.setNext(&n3);
		
		std::string	s3	=	"";
		for (TTN const& a2: n1.children())
		{
			s3	+=	a2.string1;
		}
		test_assert(s3 == "AAAAAA");
	}
	{
		struct
		TestTreeNode1 : GenericTreeNode<TestTreeNode1>
		{
			std::string		string1		=	"AAA";
			int	unused	=	0;	//	To suppress warning.
		};
		
		using	TTN	=	TestTreeNode1;
		
		TTN	n1	=	{};
		TTN	n2	=	{};
		TTN	n3	=	{};
		
		n2.setParent(&n1);
		n3.setParent(&n2);
		
		int	f1	=	0;
		for (TTN& sub: n1.children())
		{
			for (TTN& sub2: sub.children())
			{
				sub2.unused++;	//	To suppress warning.
				f1	++;
			}
		}
		test_assert(f1 == 1);
	}
	{
		struct
		TestTreeNode1 : GenericTreeNode<TestTreeNode1>
		{
			std::string		string1		=	"AAA";
		};
		
		using	TTN	=	TestTreeNode1;
		
		TTN	a1	=	{};
		TTN	b1	=	{};
		TTN	b2	=	{};
		TTN	b3	=	{};
		TTN	c1	=	{};
		TTN	c2	=	{};
		TTN	c3	=	{};
		
		a1.setChildren({&b1,&b1});
		
		b1.setNext(&b2);
		b2.setNext(&b3);
		
		b1.setChildren({&c1, &c1});
		
		c1.setNext(&c2);
		c2.setNext(&c3);
		
		int	f1	=	0;
		auto a1_children	=	a1.children();
		for (TTN const& sub1: a1_children)
		{
			f1++;
			for (TTN const& sub2: sub1.children())
			{
				if (&sub2 != nullptr)
				{
					f1++;
				}
			}
		}
		test_assert(f1 == 6);
	}
	{
		
		struct
		TestTreeNode1 : GenericTreeNode<TestTreeNode1>
		{
			std::string		string1		=	"AAA";
		};
		
		using	TTN	=	TestTreeNode1;
		
		TTN	n1	{};
		TTN	n2	{};
		TTN	n3	{};

		n2.setParent(&n1);
		n2.setNext(&n3);

		test_assert(&n1.children().back() == &n3);
	}
}

















auto
test_all3() -> void
{
	test_tree1();
	test_tree2();
}










