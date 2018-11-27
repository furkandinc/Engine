#pragma once

#ifdef DLLDIR_EX
#define DLLDIR __declspec(dllexport)
#else
#define DLLDIR __declspec(dllimport)
#endif