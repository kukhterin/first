#ifndef _TREAD_FUNC_
#define _TREAD_FUNC_

template <class A, void(A::*F)()>
	void* thread_func(void* p)
	{
		A* a = static_cast<A*>(p);
		(a->*F)();
		return 0;
		
	}

#endif
