#pragma once

#ifndef NOT_UNIVOX_EXPORT_API
#ifdef UNIVOX_EXPORT_API
#define UNIVOX_API __declspec(dllexport)
#else
#define UNIVOX_API __declspec(dllimport)
#endif
#else
#define UNIVOX_API
#endif