#ifndef __GBCALLBACK__
#define __GBCALLBACK__
#include <functional>

#define GBCALLBACK_0(FUNC, INS) std::bind(&FUNC, INS)
#define GBCALLBACK_1(FUNC, INS) std::bind(&FUNC, INS, std::placeholders::_1)
#define GBCALLBACK_2(FUNC, INS) std::bind(&FUNC, INS, std::placeholders::_1, std::placeholders::_2)
#define GBCALLBACK_3(FUNC, INS) std::bind(&FUNC, INS, std::placeholders::_3)
#define GBCALLBACK_4(FUNC, INS) std::bind(&FUNC, INS, std::placeholders::_4)
#define GBCALLBACK_5(FUNC, INS) std::bind(&FUNC, INS, std::placeholders::_5)

#endif