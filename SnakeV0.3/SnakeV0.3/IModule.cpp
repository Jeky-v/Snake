//#include "stdafx.h"
#include "IModule.h"


IModule::IModule() :
  m_isinit(false),
  m_isexit(false),
  m_mgr(nullptr)
{
}

void IModule::Init()
{
  if (m_isinit)
    Close();

  m_isinit = true;
  m_isexit = false;

  doInit();
}

bool IModule::Frame()
{
  if (!m_isinit || m_isexit)
    return false;
  else
    return doRun();
}

void IModule::Close()
{
  if (m_isinit)
  {
    doClose();
    m_isinit = false;
  }  
}