#ifndef _TREAD_FUNC_
#define _TREAD_FUNC_

template <class A, void(A::*F)()>
	static void* thread_func(void* p)
	{
		A* a = static_cast<A*>(p);
		(a->*F)();//a->*F() - totally mot working
		return 0;
		
	}

#endif
