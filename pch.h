#pragma once
// �̸� �����ϵ� ��� (precompiled header)
// ��� c/cpp ������ �� �ش��� #include �ؾ��Ѵ�.

#include <Windows.h>

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::wstring;

class CStage;
extern CStage g_stage;

#include "define.h"
#include "struct.h"