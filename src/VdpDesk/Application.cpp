#include "stdafx.h"
#include "Application.h"

Application::Application()
	: OweAppBase(_AtlBaseModule)
{
	m_flags |= OWE_AF_HIDE_SOLUTION_NODE | OWE_AF_STORAGE_DOC;
}
